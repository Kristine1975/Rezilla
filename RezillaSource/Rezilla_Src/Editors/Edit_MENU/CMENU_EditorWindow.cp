// ===========================================================================
// CMENU_EditorWindow.cp					
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-11 22:17:36
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CMENU_EditorDoc.h"
#include "CMENU_EditorWindow.h"
#include "CMENU_EditorTable.h"
#include "CMenuObject.h"
#include "CRezillaApp.h"
#include "CMenuItem.h"
#include "RezillaConstants.h"
#include "UMessageDialogs.h"

#include <LCheckBox.h>
#include <LEditText.h>
#include <LPopupButton.h>
// #include <LScrollerView.h>
// #include <UMemoryMgr.h>

#include <stdio.h>



// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow()
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//  CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::CMENU_EditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
//  ~CMENU_EditorWindow				[public]
// ---------------------------------------------------------------------------

CMENU_EditorWindow::~CMENU_EditorWindow()
{	
// 	// Remove the window from the list of listeners to the prefs object
// 	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
// FinishCreateSelf											[protected]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::FinishCreateSelf()
{	
	mHasXmnu = false;

	// The main view containing the labels and editing panes
	mItemsTable = dynamic_cast<CMENU_EditorTable *>(this->FindPaneByID(item_EditorContents));
	ThrowIfNil_( mItemsTable );
	
	mItemsTable->SetOwnerWindow(this);
	
// 	SwitchTarget(mItemsTable);
		
	// Link the broadcasters
	UReanimator::LinkListenerToControls( this, this, PPob_TextEditorWindow );
	
// 	// Make the window a listener to the prefs object
// 	CRezillaApp::sPrefs->AddListener(this);

}


// ---------------------------------------------------------------------------
//  ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{	
	switch (inMessage) {
		
		default:
		dynamic_cast<CMENU_EditorDoc *>(mOwnerDoc)->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	 FindCommandStatus
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {
		
		default:
		CEditorWindow::FindCommandStatus(inCommand, outEnabled,
									  outUsesMark, outMark, outName);
		break;
	}
}


// ---------------------------------------------------------------------------
//	 ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CMENU_EditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	 InstallMenuData													[public]
// ---------------------------------------------------------------------------

OSErr
CMENU_EditorWindow::InstallMenuData(Handle inMenuHandle, Handle inXmnuHandle)
{
	OSErr		error = noErr, ignoreErr = noErr;
	StHandleLocker	menulock(inMenuHandle);

	LHandleStream * theStream = new LHandleStream(inMenuHandle);
	
	if ( theStream->GetLength() == 0 ) {
		// We are creating a new resource
		mMenuObj = new CMenuObject();
	} else {
		mMenuObj = new CMenuObject(theStream);
	}
	
	// Check that all the data have been parsed
	if (theStream->GetMarker() < theStream->GetLength() ) {
		error = err_MoreDataThanExpected;
	} 
	delete theStream;
	theStream = nil;
	
	try {
		if (inXmnuHandle != nil) {
			mHasXmnu = true;
			
			StHandleLocker	xmnulock(inXmnuHandle);
			theStream = new LHandleStream(inXmnuHandle);
			
			TArrayIterator<CMenuItem*> iterator( *(mMenuObj->GetItems()) );
			CMenuItem *	theItem;
			
			while (iterator.Next(theItem)) {
				ignoreErr = theItem->InstallExtendedData(theStream);
			}
			
			delete theStream;
		} 	
	}
	catch (...) {
		if (theStream != nil) {delete theStream;} 
		if (ignoreErr) {
			// todo
		} 
		UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ParseXmnuRezFailed"), PPob_SimpleMessage);
	}
	
	
	if (error == noErr) {
		InstallMenuValues();
		InstallCurrentItemValues();
		InstallTableValues();
		SetDirty(false);
	} 

	return error;
}


// ---------------------------------------------------------------------------
//  � CollectMenuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::CollectMenuData() 
{
	Handle	menuHandle = RetrieveMenuData();
	Handle	xmnuHandle = RetrieveXmnuData();
		
	dynamic_cast<CMENU_EditorDoc *>(mOwnerDoc)->SaveXmnuResource(xmnuHandle);

	return menuHandle;
}


// ---------------------------------------------------------------------------
//  � RetrieveMenuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::RetrieveMenuData() 
{
	Handle	menuHandle = NULL;

	return menuHandle;
}


// ---------------------------------------------------------------------------
//  � RetrieveXmnuData										[public]
// ---------------------------------------------------------------------------

Handle
CMENU_EditorWindow::RetrieveXmnuData() 
{
	Handle	xmnuHandle = NULL;

	return xmnuHandle;
}


// ---------------------------------------------------------------------------
//	 InstallMenuValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallMenuValues()
{
	Str255		theString;
	ResIDT		theID, theMDEF;
	UInt32		theEnableFlag;
	LEditText * theEditText;
	LCheckBox *	theCheckBox;
	
	mMenuObj->GetValues( theID, theMDEF, theEnableFlag, theString);
	
	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMenuTitle ));
	ThrowIfNil_( theEditText );
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMenuID ));
	ThrowIfNil_( theEditText );
	::NumToString( theID, theString);
	theEditText->SetDescriptor(theString);

	theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMDEF ));
	ThrowIfNil_( theEditText );
	::NumToString( theMDEF, theString);
	theEditText->SetDescriptor(theString);

	theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditMenuEnabled ));
	ThrowIfNil_( theCheckBox );
	theEditText->SetValue( (theEnableFlag & 1) );

}


// ---------------------------------------------------------------------------
//	 InstallCurrentItemValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallCurrentItemValues()
{
	ArrayIndexT theIndex = mMenuObj->GetItemIndex();
	
	if (theIndex == 0) {
		ClearItemValues();
	} else {
		InstallItemValuesAtIndex(theIndex);
	}
}


// ---------------------------------------------------------------------------
//	 InstallItemValuesAtIndex
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallItemValuesAtIndex( ArrayIndexT inAtIndex )
{
	CMenuItem * theItem;
	if (mMenuObj->GetItems()->FetchItemAt(inAtIndex, theItem)) {
		Str255		theString;
		UInt8		theIconID, theShortcut, theMark, theStyle;
		MenuRef		theMenuH;
		LEditText * theEditText;
		LCheckBox *	theCheckBox;
		LPopupButton *	thePopup;

		theItem->GetValues(theString, theIconID, theShortcut, theMark, theStyle);
		
		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditItemTitle ));
		ThrowIfNil_( theEditText );
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditIconID ));
		ThrowIfNil_( theEditText );
		::NumToString( theIconID, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditShortcut ));
		ThrowIfNil_( theEditText );
		::NumToString( theShortcut, theString);
		theEditText->SetDescriptor(theString);

		theEditText = dynamic_cast<LEditText *>(this->FindPaneByID( item_MenuEditMarkChar ));
		ThrowIfNil_( theEditText );
		::NumToString( theMark, theString);
		theEditText->SetDescriptor(theString);

		theCheckBox = dynamic_cast<LCheckBox *>(this->FindPaneByID( item_MenuEditItemEnabled ));
		ThrowIfNil_( theCheckBox );
// 		theEditText->SetValue( (theEnableFlag & 1) );
		
		// popup
		thePopup = dynamic_cast<LPopupButton *>(this->FindPaneByID( item_MenuEditStylePopup ));
		ThrowIfNil_(thePopup);
		theMenuH = thePopup->GetMacMenuH();
// 		for ( i = 0; i < theCount; i++) {
// 			::MacCheckMenuItem(theMenuH, i+2, ( (inFlags & (1 << flagsArray[i])) > 0 ) );
// 		}

		if (hasXmnu) {
			UInt8 theModifiers;
			SInt32 theEncoding, theRefcon1, theRefcon2, theFontID, theSubstituteGlyph;
			
			GetExtendedValues(theModifiers, theEncoding,
							   theRefcon1, theRefcon2, 
							   theFontID, theSubstituteGlyph );
			
			
			
		} 
	} 
}


// ---------------------------------------------------------------------------
//	 ClearItemValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::ClearItemValues()
{
}


// ---------------------------------------------------------------------------
//	 InstallTableValues
// ---------------------------------------------------------------------------

void
CMENU_EditorWindow::InstallTableValues()
{
}



