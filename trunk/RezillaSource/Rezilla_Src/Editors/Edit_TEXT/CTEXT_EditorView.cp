// ===========================================================================
// CTEXT_EditorView.cp
// 
//                       Created: 2004-06-19 13:23:32
//             Last modification: 2005-01-08 17:31:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CTEXT_EditorDoc.h"
#include "CTEXT_EditorView.h"
#include "CTEXT_EditorWindow.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	� CTEXT_EditorView							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::CTEXT_EditorView()
		: LTextEditView()
{
}


// ---------------------------------------------------------------------------
//	� CTEXT_EditorView							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::CTEXT_EditorView(
	const SPaneInfo&	inPaneInfo,
	const SViewInfo&	inViewInfo,
	UInt16				inTextAttributes,
	ResIDT				inTextTraitsID)

	: LTextEditView(inPaneInfo, inViewInfo, inTextAttributes, inTextTraitsID)
{
}


// ---------------------------------------------------------------------------
//	� CTEXT_EditorView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------
// Use the Preference interface settings when creating a new TEXT resource.

CTEXT_EditorView::CTEXT_EditorView(
	LStream*	inStream)

	: LTextEditView(inStream)
{
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	TextStyle	theStyle;
	SInt16		justification = teFlushDefault;

	theStyle.tsFont			= theTraits.fontNumber;
	theStyle.tsFace			= static_cast<UInt8>(theTraits.style);
	theStyle.tsSize			= theTraits.size;
	theStyle.tsColor		= theTraits.color;
	justification			= theTraits.justification;

	::TextFont(theStyle.tsFont);		// Set Port Font and Size so TE
	::TextSize(theStyle.tsSize);		// uses the correct settings for
										// its internal tables.

	::TESetStyle( doAll, &theStyle, false, mTextEditH );
	::TESetAlignment( justification, mTextEditH );
}


// ---------------------------------------------------------------------------
//	� ~CTEXT_EditorView						Destructor				  [public]
// ---------------------------------------------------------------------------

CTEXT_EditorView::~CTEXT_EditorView()
{
}



#pragma mark -

// ---------------------------------------------------------------------------
//	� ClickSelf								[protected, virtual]
// ---------------------------------------------------------------------------

void
CTEXT_EditorView::ClickSelf(
	const SMouseDownEvent	&inMouseDown)
{
	LTextEditView::ClickSelf(inMouseDown);
	
	mOwnerWindow->AdjustMenusToSelection();
}


// ---------------------------------------------------------------------------
//	� HandleKeyPress							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorView::HandleKeyPress(
	const EventRecord	&inKeyEvent)
{
	Boolean		keyHandled	 = LTextEditView::HandleKeyPress(inKeyEvent);
	
	if (UKeyFilters::PrintingCharField(inKeyEvent) == keyStatus_TECursor) {
		mOwnerWindow->AdjustMenusToSelection();
	} 
	mOwnerWindow->SetLengthField();
	return keyHandled;
}


// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------

void
CTEXT_EditorView::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	Boolean		enableIt = false;
	Boolean		handled = false;
	ResIDT		theMenuID;
	SInt16		theMenuItem;
	Boolean		foundFontItem = false;
	
	try
	{
		// First check for font menu. We get only one call for the entire font
		// menu because it's synthetic.
		if ( LCommander::IsSyntheticCommand( inCommand, theMenuID, theMenuItem ) )
		{
			LMenu *	theFontMenu = CTEXT_EditorWindow::sTextFontMenu;
			Str255	menuItemName, fontName;
			SInt16	theFontNum;
			Boolean	result;

			if ( !theFontMenu || (theMenuID != MENU_TextFonts) ) return;
			
			// The font menu is shared between different windows, so we need to
			// uncheck the previous item and check the current one. The easiest
			// way to do this is to just run through the entire menu.
			MenuHandle	fontMenuH = theFontMenu->GetMacMenuH();
			if ( !fontMenuH ) return;	// shouldn't happen
			
			result = GetFont(theFontNum);
			if (result) {
				::GetFontName( theFontNum, fontName );
				SInt32 numItems = ::CountMenuItems( fontMenuH );
				for ( SInt32 count = 1; count <= numItems; count++ )
				{
					if ( foundFontItem )		// if we found the item already, just uncheck the rest
						::MacCheckMenuItem( fontMenuH, count, false );
					else
					{
						::GetMenuItemText( fontMenuH, count, menuItemName );
						foundFontItem = ::EqualString( menuItemName, fontName, false, true );
						::MacCheckMenuItem( fontMenuH, count, foundFontItem );
					}
				}
			}

			outEnabled = true;		// font menu always enabled
			outUsesMark = true;
			outMark = 0;
			outName[0] = 0;
			return;
		}
		
		// Now deal with the Size menu 
		if ( (inCommand >= cmd_MenuTextSizeBase) && (inCommand <= cmd_MenuTextSizeLast) )
		{
			SInt16	theSize;

			GetSize(theSize);
			
			// This won't put a checkMark next to "Other size" if a
			// non-standard size is selected.
			if ( inCommand - cmd_MenuTextSizeBase == theSize ) {
				outMark = checkMark;
			} else {
				outMark = 0;
			}
			outEnabled = true;
			outUsesMark = true;
			outName[0] = 0;
			return;
		}
		
		// Now deal with the Style menu 
		if ( (inCommand >= cmd_Plain) && (inCommand <= cmd_Extend) )
		{
			Style theStyle;
			GetStyle(theStyle);
			
			// This won't put a checkMark next to "Other size" if a
			// non-standard size is selected.
			if ( inCommand == cmd_Plain ) {
				outMark = theStyle ? 0 : checkMark;
			} else {
				UInt8 i = inCommand - cmd_Plain - 1;
				outMark = (theStyle & (1 << i)) ? checkMark : 0;
			}
			outEnabled = true;
			outUsesMark = true;
			outName[0] = 0;
			return;
		}
		
		// Other commands
		switch( inCommand )
		{
				
// 			case cmd_JustifyLeft:
// 				outUsesMark = true;
// 				outMark = (inTraits.justification == teFlushLeft) ? checkMark : 0;
// 				outEnabled = true;
// 				handled = true;
// 				break;
// 			case cmd_JustifyCenter:
// 				outUsesMark = true;
// 				outMark = (inTraits.justification == teCenter) ? checkMark : 0;
// 				outEnabled = true;
// 				handled = true;
// 				break;
// 			case cmd_JustifyRight:
// 				outUsesMark = true;
// 				outMark = (inTraits.justification == teFlushRight) ? checkMark : 0;
// 				outEnabled = true;
// 				handled = true;
// 				break;
				
			case cmd_FontLarger:
			case cmd_FontSmaller:
			enableIt = true;
				break;				

			case cmd_FontOther:
			enableIt = true;
// 			// This is the "Other size" item
// 			// If they match, no need to use 'Other' item
// 			if (UMiscUtils::FontSizeExists(mSizePopup, theSize, theIndex)) {
// 				mSizePopup->SetValue(theIndex);
// 				::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, LStr255("\pOther�"));					
// 			} else {
// 				// Modify the text of the 'Other' item.
// 				Str255	theSizeString;
// 				theLine = "\pOther (" ;
// 				::NumToString( theSize, theSizeString );
// 				// Append the current size
// 				theLine += theSizeString;
// 				theLine += "\p)�";
// 				// Set the menu item text.
// 				::SetMenuItemText( mSizePopup->GetMacMenuH(), kLastSizeMenuItem + 2, theLine );					
// 			}
			break;

		}
			
		if ( enableIt )
		{
			outEnabled = true;
			outUsesMark = false;
			outMark = 0;
			outName[0] = 0;
		} else {
			mOwnerWindow->FindCommandStatus( inCommand, outEnabled, outUsesMark, outMark, outName );
		}
	}
	catch( ... )
	{
		outEnabled = false;
		outUsesMark = false;
		outMark = 0;
		outName[0] = 0;
	}
}


// ---------------------------------------------------------------------------
//	� ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CTEXT_EditorView::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	if ( mTextEditH == nil ) {
		return cmdHandled;
	}
	
	// First check for font menu
	ResIDT	theMenuID;
	SInt16	theMenuItem;
	
	if ( LCommander::IsSyntheticCommand( inCommand, theMenuID, theMenuItem ) )
	{
		if ( theMenuID == MENU_TextFonts )
		{
			Str255		fontName;
			SInt16		theFontNum;
			MenuHandle	fontMenuH = ::GetMenuHandle( theMenuID );
			
			if ( fontMenuH )
			{
				::GetMenuItemText( fontMenuH, theMenuItem, fontName );
				::GetFNum(fontName, &theFontNum);
				SetFont(theFontNum);
			}
		}
		return true;
	}
	
	// Now check for size menu
	if ( (inCommand >= cmd_MenuTextSizeBase) && (inCommand <= cmd_MenuTextSizeLast) )
	{
		SetSize(inCommand - cmd_MenuTextSizeBase);
		return true;
	}
	
	// Other commands
	switch (inCommand) {
		
		case cmd_Cut: 
		case cmd_Paste: 
		case cmd_Clear: 
		LTextEditView::ObeyCommand(inCommand, ioParam);
		mOwnerWindow->SetLengthField();
		break;
		
		case cmd_Plain:
		SetStyle(normal);
		break;
		
		case cmd_Bold:
		case cmd_Italic:
		case cmd_Underline:
		case cmd_Outline:
		case cmd_Shadow:
		case cmd_Condense:
		case cmd_Extend: {
			Style theStyle;
			UInt8 i = inCommand - cmd_Plain - 1;
			GetStyle(theStyle);
			theStyle ^= (1 << i);
			SetStyle(theStyle);
			break;
		}
		
		case cmd_FontOther: {
			// This is the "Other size" item
			SInt32 	theSize = 10;
			if (UModalDialogs::AskForOneNumber(this, PPob_FontSizeDialog, item_SizeField, theSize)) {
				if (theSize == 0) {theSize = 10;}
				SetSize(theSize);
			}
		}
		break;
		
		default:
		cmdHandled = LTextEditView::ObeyCommand(inCommand, ioParam);
		break;
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	� UserChangedText						[public, virtual]
// ---------------------------------------------------------------------------
//	Text of WasteEdit has changed as a result of user action

void
CTEXT_EditorView::UserChangedText()
{
	if ( ! mOwnerWindow->IsDirty() ) {

		// Set the update menus flag.
		SetUpdateCommandStatus( true );
		
		// Set the dirty flag.
		mOwnerWindow->SetDirty( true );
	}
}


// ---------------------------------------------------------------------------
//  � GetModifiedText										[public]
// ---------------------------------------------------------------------------

Handle
CTEXT_EditorView::GetModifiedText() 
{
	Handle	outTextHandle = GetTextHandle();
	
	long numStyle = ::TENumStyles(0, ::GetHandleSize(outTextHandle), mTextEditH);

	if (numStyle > 1) {
		StScrpHandle	theScrapHandle;
		
		SelectAll();
		theScrapHandle = ::TEGetStyleScrapHandle(mTextEditH);
		
		dynamic_cast<CTEXT_EditorDoc *>(mOwnerWindow->GetOwnerDoc())->SaveStylResource(theScrapHandle);
	} 
	return outTextHandle;
}




PP_End_Namespace_PowerPlant
