// ===========================================================================
// CTmplWindowUtils.cp					
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2005-01-15 09:55:49
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Implements the functions defining the various fields and controls in the 
// CTmplEditorWindow class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CTmplListItemView.h"
#include "CTmplListButton.h"
#include "CTmplBevelButton.h"
#include "CTemplatesController.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CDualDataView.h"
#include "CHexDataSubView.h"
#include "CSingleScrollBar.h"
#include "CTxtDataSubView.h"
#include "CWasteEditView.h"
#include "CColorWell.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LIconPane.h>
#include <LEditText.h>
#include <LTextGroupBox.h>
#include <LCheckBox.h>
#include <LPushButton.h>
#include <LScrollerView.h>
#include <LSeparatorLine.h>
#include <UDrawingState.h>
#include <LArray.h>

#include <ControlDefinitions.h>

#include <stdio.h>
#include <string.h>



// ---------------------------------------------------------------------------
//		� InitPaneInfos												[static]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InitPaneInfos()
{
	// Label fields basic values
	sStaticPaneInfo.paneID			= 0;
	sStaticPaneInfo.height			= kTmplLabelHeight;
	sStaticPaneInfo.visible			= true;
	sStaticPaneInfo.enabled			= true;
	sStaticPaneInfo.bindings.left	= true;
	sStaticPaneInfo.bindings.top	= false;
	sStaticPaneInfo.bindings.right	= false;
	sStaticPaneInfo.bindings.bottom = false;
	sStaticPaneInfo.userCon			= 0;
	
	// Edit fields basic values
	sEditPaneInfo.paneID			= 0;
	sEditPaneInfo.height			= kTmplEditHeight;
	sEditPaneInfo.visible			= true;
	sEditPaneInfo.enabled			= true;
	sEditPaneInfo.bindings.left		= true;
	sEditPaneInfo.bindings.top		= false;
	sEditPaneInfo.bindings.bottom	= false;
	sEditPaneInfo.userCon			= 0;

	// Radio group view basic values
	sRgvPaneInfo.paneID				= 0;
	sRgvPaneInfo.width				= kTmplRgvWidth;
	sRgvPaneInfo.height				= kTmplRgvHeight;
	sRgvPaneInfo.visible			= true;
	sRgvPaneInfo.enabled			= true;
	sRgvPaneInfo.bindings.left		= true;
	sRgvPaneInfo.bindings.top		= false;
	sRgvPaneInfo.bindings.right		= false;
	sRgvPaneInfo.bindings.bottom	= false;
	sRgvPaneInfo.userCon			= 0;
	
	// Radio buttons basic values
	sRadioPaneInfo.paneID			= 0;
	sRadioPaneInfo.width			= kTmplRadioWidth;
	sRadioPaneInfo.height			= kTmplRadioHeight;
	sRadioPaneInfo.visible			= true;
	sRadioPaneInfo.enabled			= true;
	sRadioPaneInfo.bindings.left	= true;
	sRadioPaneInfo.bindings.top		= false;
	sRadioPaneInfo.bindings.right	= false;
	sRadioPaneInfo.bindings.bottom	= false;
	sRadioPaneInfo.userCon			= 0;

	// Check boxes basic values
	sCheckPaneInfo.paneID			= 0;
	sCheckPaneInfo.width			= kTmplCheckWidth;
	sCheckPaneInfo.height			= kTmplCheckHeight;
	sCheckPaneInfo.visible			= true;
	sCheckPaneInfo.enabled			= true;
	sCheckPaneInfo.bindings.left	= true;
	sCheckPaneInfo.bindings.top		= false;
	sCheckPaneInfo.bindings.right	= false;
	sCheckPaneInfo.bindings.bottom	= false;
	sCheckPaneInfo.userCon			= 0;

	// Rectangle labels basic values
	sRectLabelInfo.paneID			= 0;
	sRectLabelInfo.width			= kTmplRectWidth;
	sRectLabelInfo.height			= kTmplRectHeight;
	sRectLabelInfo.visible			= true;
	sRectLabelInfo.enabled			= true;
	sRectLabelInfo.bindings.left	= true;
	sRectLabelInfo.bindings.top		= false;
	sRectLabelInfo.bindings.right	= false;
	sRectLabelInfo.bindings.bottom	= false;
	sRectLabelInfo.userCon			= 0;

	// Rectangle edit basic values
	sRectPaneInfo.width				= kTmplRectWidth;
	sRectPaneInfo.height			= kTmplEditHeight;
	sRectPaneInfo.visible			= true;
	sRectPaneInfo.enabled			= true;
	sRectPaneInfo.bindings.left		= true;
	sRectPaneInfo.bindings.top		= false;
	sRectPaneInfo.bindings.right	= false;
	sRectPaneInfo.bindings.bottom	= false;
	sRectPaneInfo.userCon			= 0;
	
	// Active scrollers basic values
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.visible			= true;
	sScrollPaneInfo.enabled			= true;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.bindings.top	= true;
	sScrollPaneInfo.bindings.right	= true;
	sScrollPaneInfo.bindings.bottom	= true;
	sScrollPaneInfo.userCon			= 0;

	// Text group box for text views basic values
	sTgbPaneInfo.height				= kTmplTextMaxHeight;
	sTgbPaneInfo.visible			= true;
	sTgbPaneInfo.enabled			= true;
	sTgbPaneInfo.bindings.top		= false;
	sTgbPaneInfo.bindings.left		= true;
	sTgbPaneInfo.bindings.bottom	= false;
	sTgbPaneInfo.bindings.right		= true;
	sTgbPaneInfo.userCon			= 0;

	// Text views basic values
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.visible			= true;
	sWastePaneInfo.enabled			= true;
	sWastePaneInfo.bindings.top		= true;
	sWastePaneInfo.bindings.bottom	= true;
	sWastePaneInfo.userCon			= 0;
	
	// Push buttons basic values
	sPushPaneInfo.width				= kTmplPushWidth;
	sPushPaneInfo.height			= kTmplPushHeight;
	sPushPaneInfo.visible			= true;
	sPushPaneInfo.enabled			= true;
	sPushPaneInfo.bindings.left		= false;
	sPushPaneInfo.bindings.top		= false;
	sPushPaneInfo.bindings.right	= false;
	sPushPaneInfo.bindings.bottom	= false;
	sPushPaneInfo.userCon			= 0;
	
	// List item views basic values
	sListItemInfo.height			= 0;
	sListItemInfo.visible			= true;
	sListItemInfo.enabled			= true;
	sListItemInfo.bindings.left		= true;
	sListItemInfo.bindings.top		= false;
	sListItemInfo.bindings.right	= true;
	sListItemInfo.bindings.bottom	= false;
	sListItemInfo.userCon			= 0;
	
	// Separator horizontal line basic values
	sSeparatorPaneInfo.paneID			= 0;
	sSeparatorPaneInfo.height			= kTmplSeparatorHeight;
	sSeparatorPaneInfo.visible			= true;
	sSeparatorPaneInfo.enabled			= true;
	sSeparatorPaneInfo.bindings.left	= true;
	sSeparatorPaneInfo.bindings.top		= false;
	sSeparatorPaneInfo.bindings.right	= true;
	sSeparatorPaneInfo.bindings.bottom = false;
	sSeparatorPaneInfo.userCon			= 0;
	
	// Popup button fields basic values
	sBevelPaneInfo.width			= kTmplBevelWidth;
	sBevelPaneInfo.height			= kTmplBevelHeight;
	sBevelPaneInfo.visible			= true;
	sBevelPaneInfo.enabled			= true;
	sBevelPaneInfo.bindings.left	= false;
	sBevelPaneInfo.bindings.top		= false;
	sBevelPaneInfo.bindings.right	= false;
	sBevelPaneInfo.bindings.bottom 	= false;
	sBevelPaneInfo.userCon			= 0;

	// Color panes basic values
	sColorPaneInfo.width			= kTmplColorWidth;
	sColorPaneInfo.height			= kTmplColorHeight;
	sColorPaneInfo.visible			= true;
	sColorPaneInfo.enabled			= true;
	sColorPaneInfo.bindings.left	= true;
	sColorPaneInfo.bindings.top		= false;
	sColorPaneInfo.bindings.right	= false;
	sColorPaneInfo.bindings.bottom 	= false;
	sColorPaneInfo.userCon			= 0;
	
}


#pragma mark -

// ---------------------------------------------------------------------------
//	� AddStaticField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddStaticField(OSType inType, Str255 inLabel, LView * inContainer, 
								  ResIDT inTextTraitsID, SInt32 inReqLength, Boolean fullWidth)
{
	Str255		theString;
	LStr255		theLabel(inLabel);
	
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.superView	= inContainer;
	
	// For a comment label (DVDR) extend the width to the entire window.
	// Ditto for a sized hex/txt field to ensure the extended label fits in.
	if (inType == 'DVDR' || inReqLength > 0 || fullWidth) {
		SDimension16	theFrame;
		inContainer->GetFrameSize(theFrame);
		sStaticPaneInfo.width = theFrame.width - kTmplLeftMargin * 2;
	} else {
		sStaticPaneInfo.width = kTmplLabelWidth;
	}

	if (inReqLength > 0) {
		::NumToString( inReqLength, theString);
		theLabel += "\p (";
		theLabel.Append(theString);
		theLabel += "\p bytes)";
	} 
	LStaticText * theStaticText = new LStaticText(sStaticPaneInfo, theLabel, inTextTraitsID);
	ThrowIfNil_(theStaticText);
}


// ---------------------------------------------------------------------------
//	� AddEditField													[public]
// ---------------------------------------------------------------------------
// If the inWidth argument is not 0, it is used to impose the width of the
// EditField. If it is 0, the width is calculated using the inMaxChars
// argument:
// - if (kTmplEditMinFixedChars <= inMaxChars <= kTmplEditMaxFixedChars),
//   the width is calculated to fit exactly with this number of chars. The
//   field is not bound to the right edge of the window.
// - if (inMaxChars > kTmplEditMaxFixedChars), the width is calculated to
//   extend to the right edge of the container and the field is bound to
//   the right edge of the window.
// - if (inMaxChars < kTmplEditMinFixedChars), the width is adjusted to
//   kTmplEditMaxFixedChars and the field is not redimesionable.

void
CTmplEditorWindow::AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer)
{
	SDimension16	theFrame;
	Boolean			incrY = true;
	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left				= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.top				= mYCoord - 3;
	sEditPaneInfo.paneID			= mCurrentID;
	sEditPaneInfo.superView			= inContainer;
	sEditPaneInfo.bindings.right	= true;

	if (inWidth > 0) {
		sEditPaneInfo.width = inWidth;
	} else {
		if (inMaxChars > kTmplEditMaxFixedChars) {
			sEditPaneInfo.width = theFrame.width - kTmplLeftMargin * 2 - kTmplLabelWidth - kTmplHorizSep - kTmplHorizSkip;
		} else {
			// Add space for three more chars
			sEditPaneInfo.width = kTmplEditUnitWidth * (((inMaxChars < kTmplEditMinFixedChars)? kTmplEditMinFixedChars : inMaxChars) + 3);
			sEditPaneInfo.bindings.right = false;
		}
	}
	
	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_EditorItemModified, inMaxChars, 0, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Filler types can be invisible or disabled
	if (inType == 'FBYT' || inType == 'FWRD' || inType == 'FLNG') {
		if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			theEditText->Hide();
			incrY = false;	
		} else if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_enableFillers) ) {
			theEditText->Disable();
		} 
	} 
	
	// Advance the counters
	if (incrY) {
		mYCoord += sEditPaneInfo.height + kTmplVertSep;
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddBooleanField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBooleanField(Boolean inValue,
								   OSType inType,
								   SInt16 inTitleType, 
								   LView * inContainer)
{
	LStdRadioButton * theRadio;
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	sRgvPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRgvPaneInfo.top		= mYCoord - 2;
	sRgvPaneInfo.paneID		= mCurrentID;
	sRgvPaneInfo.superView	= inContainer;

	LRadioGroupView * theRGV = new LRadioGroupView(sRgvPaneInfo, theViewInfo);
	ThrowIfNil_(theRGV);

	// Store the template's type in the userCon field
	theRGV->SetUserCon(inType);
	
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Create two radiobuttons in this group
	//     "Yes/On" radiobutton
	sRadioPaneInfo.left			= 0;
	sRadioPaneInfo.top			= 0;
	sRadioPaneInfo.paneID		= mCurrentID;
	sRadioPaneInfo.superView	= theRGV;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_EditorItemModified, 
								   inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOn":"\pYes"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);
	
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	//     "No/Off" radiobutton
	sRadioPaneInfo.left += kTmplRadioWidth + kTmplHorizSep;
	sRadioPaneInfo.paneID = mCurrentID;

	theRadio = new LStdRadioButton(sRadioPaneInfo, msg_EditorItemModified, 
								   1 - inValue, sLeftLabelTraitsID, (UInt8 *)(inTitleType ? "\pOff":"\pNo"));
	ThrowIfNil_(theRadio);
	
	// Add to the radio-group
	theRGV->AddRadio(theRadio);
	
	// Let the window listen to this button
	theRadio->AddListener(this);

	theRGV->SetCurrentRadioID( inValue ?  mCurrentID - 1 : mCurrentID );
	
	// Advance the counters
	mYCoord += sRgvPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddBitField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddBitField(OSType inType,
							   Str255 inLabel,
							   UInt16 inBitCount, 
							   UInt16 inBytesLen,
							   LView * inContainer)
{
	SInt8	i;
	UInt8	theUInt8;
	UInt16	theUInt16;
	UInt32	val;
	Str255	numStr;
	
	if (!mBitSeqInProgress) {
		mBitSeqInProgress = true;
		mBitSeqBytesLen = inBytesLen;
		// The first bit enumerated in a template is the highest bit.
		mBitSeqIndex = mBitSeqBytesLen * 8 - 1;
		if (mRezStream->GetMarker() < mRezStream->GetLength() - mBitSeqBytesLen + 1) {
			switch (mBitSeqBytesLen) {
				case 1:
				*mRezStream >> theUInt8;
				mBitSeqValue = theUInt8;
				break;
				
				case 2:
				*mRezStream >> theUInt16;
				mBitSeqValue = theUInt16;
				break;
				
				case 4:
				*mRezStream >> mBitSeqValue;
				break;
				
			}
		} else {
			mBitSeqValue = 0;
		}
	} 
	
	
	if (inBitCount == 1) {
		AddStaticField(inType, inLabel, inContainer);
		AddCheckField( ((mBitSeqValue & 1 << mBitSeqIndex) > 0), inType, inContainer);	
		mBitSeqIndex--;
	} else {
		// Add the bits count to the label
		LStr255 theLabel(inLabel);
		theLabel += "\p (";
		::NumToString( (long) inBitCount, numStr);
		theLabel += numStr;
		theLabel += "\p bits)";
		AddStaticField(inType, theLabel, inContainer);
		
		// Build the value
		val = 0;
		for (i = 0; i < inBitCount; i++) {
			val |= mBitSeqValue & (1 << mBitSeqIndex);
			mBitSeqIndex--;
		}
		val = val >> (mBitSeqIndex + 1);
		
		::NumToString( (long) val, numStr);
		AddEditField(numStr, inType, 2 * mBitSeqBytesLen + 1 + (mBitSeqBytesLen == 4), 
					 0, UKeyFilters::SelectTEKeyFilter(keyFilter_Integer), inContainer);
	}
	
	if (mBitSeqIndex < 0) {
		mBitSeqInProgress = false;
	} 
}


// ---------------------------------------------------------------------------
//	� AddCheckField											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer)
{
	sCheckPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sCheckPaneInfo.top			= mYCoord - 2;
	sCheckPaneInfo.paneID		= mCurrentID;
	sCheckPaneInfo.superView	= inContainer;

	LCheckBox * theCheck = new LCheckBox(sCheckPaneInfo, msg_EditorItemModified, inValue);
	ThrowIfNil_(theCheck);
		
	// Store the template's type in the userCon field
	theCheck->SetUserCon(inType);
	
	// Let the window listen to this button
	theCheck->AddListener(this);

	// Advance the counters
	mYCoord += sCheckPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddWasteField													[public]
// ---------------------------------------------------------------------------
// C string. This should be either characters followed by a null or all
// the chars until the end of the stream if there is no null byte.
// The height of the WE depends on the estimated number of lines. Moreover,
// if the size is fixed and the text fits in the frame, we don't need a
// scrollbar. 
// The strategy is to first create the WE inside the container in order to
// get an estimate of the number of lines. Then we decide if a scrollbar is
// necessary: if yes, the WE must be made a subpane of the scrollbar and
// its associated scrolling view.

void
CTmplEditorWindow::AddWasteField(OSType inType, LView * inContainer, SInt32 inReqLength)
{
	SInt32		oldPos, newPos, nextPos, reqLength = inReqLength;
	Handle		theHandle;
	Boolean		isFixed = false, hasText, canReduce;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	SInt16		boxHeight = sTgbPaneInfo.height, delta = 0;
	
	// Calculate the limits of the text	to insert
	hasText = CalcTextPositions(inType, oldPos, newPos, nextPos, reqLength, isFixed);
	
	// Install the overall container
	inContainer->GetFrameSize(theFrame);

	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= 0;
	sTgbPaneInfo.superView			= inContainer;

	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= CRezillaApp::sBasics.charHeight;
	theViewInfo.reconcileOverhang	= false;
	
	LTextGroupBox * theTGB = new LTextGroupBox(sTgbPaneInfo, theViewInfo, false);
	ThrowIfNil_(theTGB);

	// Install the WasteEdit view
	sWastePaneInfo.left				= kTmplTextInset;
	sWastePaneInfo.top				= kTmplTextHeadHeight;
	sWastePaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2 - kTmplScrollWidth;
	sWastePaneInfo.height			= boxHeight - kTmplTextHeadHeight - kTmplTextFootHeight;
	sWastePaneInfo.bindings.left	= true;
	sWastePaneInfo.bindings.right	= true;
	sWastePaneInfo.paneID			= mCurrentID;
	sWastePaneInfo.superView		= theTGB;
	
	// Make the Waste edit writable, not wrapping, selectable
	CWasteEditView * theWE = new CWasteEditView(this, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true, mOwnerDoc->IsReadOnly());
	ThrowIfNil_(theWE);
	// Store the template's type in the userCon field
	theWE->SetUserCon(inType);
	
	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);

	// Install the ChangesMessage and let the window listen
	theWE->SetChangesMessage(msg_EditorItemModified);
	theWE->AddListener(this);

	// Insert the text
	if (hasText) {
		theHandle = mRezStream->GetDataHandle();
		HLock(theHandle);
		theWE->Insert( (*theHandle) + oldPos , newPos - oldPos, NULL, true);
		HUnlock(theHandle);
		mRezStream->SetMarker(nextPos, streamFrom_Start);
	} 
		
	// Adjust the height of the TextGroupBox
	canReduce = RecalcTextBoxHeight(newPos - oldPos, theWE, isFixed, reqLength, delta);
	
	// If we have a fixed size and it does not exceed the frame, we don't
	// need a scrollbar. 
	if (!canReduce || !isFixed) {
		sScrollPaneInfo.left			= kTmplTextInset;
		sScrollPaneInfo.top				= kTmplTextHeadHeight;
		sScrollPaneInfo.width			= sTgbPaneInfo.width - kTmplTextInset * 2;
		sScrollPaneInfo.height			= boxHeight - kTmplTextHeadHeight - kTmplTextFootHeight;
		sScrollPaneInfo.bindings.left	= true;
		sScrollPaneInfo.paneID			= 0;
		sScrollPaneInfo.superView		= theTGB;

		LScrollerView * theScroller = new LScrollerView(sScrollPaneInfo, theViewInfo, -1, 15, 0, 0, 16, theWE, true);
		ThrowIfNil_(theScroller);

		theWE->PutInside(theScroller);
	} 
	
	if (delta < 0) {
		theTGB->ResizeFrameBy(0, delta, false);
		boxHeight += delta;
	} 
	
	// Advance the counters
	mYCoord += boxHeight + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddHexDumpField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddHexDumpField(OSType inType, LView * inContainer, SInt32 inReqLength)
{
	SInt32		oldPos, newPos, nextPos, reqLength = inReqLength;
	SInt16		hexWidth, hexHeight, txtWidth, txtHeight;
	SInt32		hexLeft, txtLeft;
	Boolean		incrY = true, isFixed = false, hasText, canReduce;
	Handle		theHandle;
	UInt8		theUInt8 = 0;
	UInt16		theUInt16 = 0;
	UInt32		theUInt32 = 0;
	SViewInfo	theViewInfo;
	SDimension16	theFrame;
	SInt16		boxHeight = sTgbPaneInfo.height, delta = 0;
	DualGeometry geo;
	
	// Calculate the limits of the text	to insert
	hasText = CalcTextPositions(inType, oldPos, newPos, nextPos, reqLength, isFixed);
	
	// Install the UI elements
	inContainer->GetFrameSize(theFrame);

	geo.hinst = kTmplTextInset;
	geo.vinst = kTmplTextInset;
	geo.hsep = kTmplHorizSep;
	geo.scrlw = kTmplScrollWidth;
	
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= CRezillaApp::sBasics.charHeight;
	theViewInfo.reconcileOverhang	= false;
	
	sTgbPaneInfo.top				= mYCoord;
	sTgbPaneInfo.left				= kTmplTextMargin;
	sTgbPaneInfo.width				= theFrame.width - kTmplTextMargin * 2;
	sTgbPaneInfo.paneID				= mCurrentID;
	sTgbPaneInfo.superView			= inContainer;

	CDualDataView * theTGB = new CDualDataView(this, sTgbPaneInfo, theViewInfo, geo, false);
	ThrowIfNil_(theTGB);
	
	// Make the single vertical scroll bar
	sScrollPaneInfo.left			= sTgbPaneInfo.width - kTmplTextInset - kTmplScrollWidth;
	sScrollPaneInfo.top				= kTmplTextInset;
	sScrollPaneInfo.width			= kTmplScrollWidth;
	sScrollPaneInfo.height			= boxHeight - kTmplTextInset * 2;
	sScrollPaneInfo.bindings.left	= false;
	sScrollPaneInfo.paneID			= 0;
	sScrollPaneInfo.superView		= theTGB;

	CSingleScrollBar * theScroller = new CSingleScrollBar(sScrollPaneInfo, msg_HexScroller, 0, 0, 0, true);
	ThrowIfNil_(theScroller);

	// Make the Waste edit panes: they are, by default, selectable with 
	// wrapping on (so that the image size is recalculated automatically 
	// when the frame size changes). The read only property is set 
	// by InstallSubViews() below.
	theTGB->CalcPanesPositions(hexLeft, hexWidth, hexHeight, txtLeft, txtWidth, txtHeight);
	
	sWastePaneInfo.left				= hexLeft;
	sWastePaneInfo.top				= kTmplTextInset;
	sWastePaneInfo.width			= hexWidth;
	sWastePaneInfo.height			= hexHeight;
	sWastePaneInfo.bindings.left	= false;
	sWastePaneInfo.bindings.right	= false;
	sWastePaneInfo.paneID			= 0;
	sWastePaneInfo.superView		= theTGB;

	CHexDataSubView * theHexWE = new CHexDataSubView(theTGB, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true);
	ThrowIfNil_(theHexWE);

	sWastePaneInfo.left				= txtLeft;
	sWastePaneInfo.width			= txtWidth;
	
	CTxtDataSubView * theTxtWE = new CTxtDataSubView(theTGB, sWastePaneInfo, theViewInfo, 0, sEditTraitsID, true);
	ThrowIfNil_(theTxtWE);
		
	// Install the subpanes and the scroller in the dual view
	theTGB->InstallSubViews(theHexWE, theTxtWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Adjust to the style specified in the preferences
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	theTGB->ResizeDataPanes();
	theTGB->UpdatePaneCounts();
	theHexWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);

	theScroller->SetMinValue(1);	
	theScroller->SetLinesPerPage( theTGB->GetPaneCount(count_LinesPerPane) - 1);
	
	// Install the ChangesMessage and let the window listen
	theHexWE->SetChangesMessage(msg_EditorItemModified);
	theTxtWE->SetChangesMessage(msg_EditorItemModified);
	theHexWE->AddListener(this);
	theTxtWE->AddListener(this);

	// Store the template's type in the userCon field
	theTGB->SetUserCon(inType);
			
	if (hasText) {
		theHandle = mRezStream->GetDataHandle();
		HLock(theHandle);
		theTGB->InstallBackStoreData((*theHandle) + oldPos, newPos - oldPos);
		theScroller->SetValue(0);
		theTGB->SetMaxScrollerValue();
		theTGB->InstallContentsFromLine(1);
		HUnlock(theHandle);

		WESetSelection(0, 0, theTGB->GetInMemoryWasteRef());
		mRezStream->SetMarker(newPos, streamFrom_Start);
	}
		
	// Fnnn filler hex strings can be invisible or disabled
	if (inType >> 24 == 'F') {
		if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_displayFillers) ) {
			theTGB->Hide();
			incrY = false;	
		} else if ( ! CRezillaPrefs::GetPrefValue(kPref_templates_enableFillers) ) {
			theHexWE->Disable();
			theTxtWE->Disable();
		} 
	} 
	
	// Advance the counters
	if (incrY) {
		// Adjust the height of the TextGroupBox. 
		// In case of fixed size, we multiply by three (3 chars per byte).
		// Otherwise the text is already installed and the number of lines
		// will be calculated directly.
		reqLength *= 3;
		canReduce = RecalcTextBoxHeight(newPos - oldPos, theHexWE, isFixed, reqLength, delta);
		if (delta < 0) {
			theTGB->ResizeFrameBy(0, delta, false);
			boxHeight += delta;
			if (isFixed) {
				// We have a fixed size and the box has been reduced, so we
				// can hide the scrollbar
				theScroller->Hide();
			} else {
				theScroller->SetLinesPerPage( theTGB->GetPaneCount(count_LinesPerPane) - 1);
			}
		} 
		mYCoord += boxHeight + kTmplVertSep;
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddPointField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddPointField(SInt16 inX, 
								SInt16 inY, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// X coord
	theStaticText = new LStaticText(sRectLabelInfo, "\pHoriz", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inX, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Y coord
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pVert", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inY, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	� AddRectField													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddRectField(SInt16 inTop, 
								SInt16 inLeft, 
								SInt16 inBottom, 
								SInt16 inRight, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer)
{
	Str255	numStr;
	LEditText * theEditText;
	LStaticText * theStaticText;

	sRectLabelInfo.top			= mYCoord;
	sRectLabelInfo.left 		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sRectLabelInfo.superView	= inContainer;

	sRectPaneInfo.top		= mYCoord + kTmplRectHeight;
	sRectPaneInfo.left		= sRectLabelInfo.left;
	sRectPaneInfo.superView	= inContainer;

	// Top
	theStaticText = new LStaticText(sRectLabelInfo, "\pTop", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inTop, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Left
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pLeft", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inLeft, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Bottom
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pBottom", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inBottom, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Right
	sRectLabelInfo.left += kTmplRectWidth + kTmplHorizSep;
	theStaticText = new LStaticText(sRectLabelInfo, "\pRight", sEditTraitsID);
	ThrowIfNil_(theStaticText);
	sRectPaneInfo.left += kTmplRectWidth + kTmplHorizSep;
	sRectPaneInfo.paneID = mCurrentID;
	::NumToString( (long) inRight, numStr);
	theEditText = new LEditText(sRectPaneInfo, this, numStr, sEditTraitsID, 
								msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);
	theEditText->SetUserCon(inType);
	// Let the window listen to this field
	theEditText->AddListener(this);
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters
	mYCoord += (kTmplRectHeight * 2) + kTmplVertSep + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	� AddListHeaderField											[public]
// ---------------------------------------------------------------------------

PaneIDT
CTmplEditorWindow::AddListHeaderField(Str255 inLabel, 
									  short inCount, 
									  Str255 inCountLabel, 
									  LView * inContainer, 
									  Boolean isFixedCount)
{
	Str255			numStr;
	PaneIDT			theCountPaneID;
	LStaticText *	theStaticText;
	CTmplListButton *	thePushButton;
	
	// This is the label of the list
	sStaticPaneInfo.left		= kTmplLeftMargin;
	sStaticPaneInfo.top			= mYCoord;
	sStaticPaneInfo.width		= kTmplLabelWidth * 2;
	sStaticPaneInfo.superView	= inContainer;

	theStaticText = new LStaticText(sStaticPaneInfo, inLabel, sHeaderTraitsID);
	ThrowIfNil_(theStaticText);

	mYCoord += kTmplEditHeight;

	// This is the label of the count field (BCNT, FCNT, LCNT, LZCT, OCNT, WCNT, ZCNT)
	sStaticPaneInfo.top		= mYCoord;
	sStaticPaneInfo.width	= kTmplLabelWidth;
	theStaticText = new LStaticText(sStaticPaneInfo, inCountLabel, sRightLabelTraitsID);
	ThrowIfNil_(theStaticText);
	
	// This is the value of the counts
	sStaticPaneInfo.left 	+= sStaticPaneInfo.width + kTmplHorizSep;
	sStaticPaneInfo.width	= kTmplCountWidth;
	sStaticPaneInfo.paneID 	= mCurrentID;
	::NumToString( (long) inCount, numStr);
	theStaticText = new LStaticText(sStaticPaneInfo, numStr, sLeftLabelTraitsID);
	ThrowIfNil_(theStaticText);
	if (isFixedCount) {
		// If it is a fixed count list, don't show the count field because the
		// info is already in the label.
		theStaticText->Hide();
	} 	
	sStaticPaneInfo.paneID = 0;
	theCountPaneID = mCurrentID;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Create the buttons
	sPushPaneInfo.top		= sStaticPaneInfo.top - 3;
	sPushPaneInfo.left		= sStaticPaneInfo.left + sStaticPaneInfo.width + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	sPushPaneInfo.superView	= inContainer;
	
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_MinusButton, "\p-");
	ThrowIfNil_(thePushButton);
	// Store the current position in the template stream
	thePushButton->SetUserCon( mTemplateStream->GetMarker());
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Hide();
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	
	sPushPaneInfo.left		+= kTmplCountWidth + kTmplHorizSep;
	sPushPaneInfo.paneID	= mCurrentID;
	thePushButton = new CTmplListButton(sPushPaneInfo, msg_PlusButton, "\p+");
	ThrowIfNil_(thePushButton);
	// The UserCon field will contain a pointer to the first ListItemView. Initialize with nil.
	thePushButton->SetUserCon(nil);
	// Let the window listen to this button
	thePushButton->AddListener(this);
	if (isFixedCount) {
		thePushButton->Hide();
	} 
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Advance the counters    kTmplVertSep
	mYCoord += sStaticPaneInfo.height + kTmplVertSkip;
	
	return theCountPaneID;
}
 

// ---------------------------------------------------------------------------
//	� AddListItemView											[public]
// ---------------------------------------------------------------------------

CTmplListItemView *
CTmplEditorWindow::AddListItemView(CTmplListItemView * inPrevListItemView, 
								   CTmplListItemView * inNextListItemView, 
								   CTmplListButton * inMinusButton,
								   LView * inContainer)
{
	SDimension16	theFrame;
	
	SViewInfo	theViewInfo;
	theViewInfo.imageSize.width		= theViewInfo.imageSize.height	= 0 ;
	theViewInfo.scrollPos.h			= theViewInfo.scrollPos.v		= 0;
	theViewInfo.scrollUnit.h		= theViewInfo.scrollUnit.v		= 1;
	theViewInfo.reconcileOverhang	= false;
	
	inContainer->GetFrameSize(theFrame);

	sListItemInfo.paneID			= 0;
	sListItemInfo.top				= mYCoord;
	sListItemInfo.left				= kTmplTextMargin + mIndent;
	sListItemInfo.width				= theFrame.width - sListItemInfo.left - kTmplHorizSep;
	sListItemInfo.superView			= inContainer;
	
	CTmplListItemView * theLIV = new CTmplListItemView(sListItemInfo, theViewInfo, this, false);
	ThrowIfNil_(theLIV);

	theLIV->mPrevItem = inPrevListItemView;
	theLIV->mNextItem = inNextListItemView;
	if (inNextListItemView != nil) {
		inNextListItemView->mPrevItem = theLIV;
	} 
	if (inPrevListItemView != nil) {
		inPrevListItemView->mNextItem = theLIV;
	} 

	theLIV->mMinusButton = inMinusButton;
	theLIV->mFirstItemID = mCurrentID;

	return theLIV;
}


// ---------------------------------------------------------------------------
//	� AddSeparatorLine											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddSeparatorLine(LView * inContainer)
{
	SDimension16	theFrame;

	inContainer->GetFrameSize(theFrame);
	sSeparatorPaneInfo.left			= kTmplLeftMargin;
	sSeparatorPaneInfo.top			= mYCoord;
	sSeparatorPaneInfo.width		= theFrame.width - kTmplLeftMargin * 2;
	sSeparatorPaneInfo.superView	= inContainer;

	LSeparatorLine * theSeparator = new LSeparatorLine(sSeparatorPaneInfo);
	ThrowIfNil_(theSeparator);
	
	// Advance the counters
	mYCoord += sSeparatorPaneInfo.height + kTmplVertSep;
}


// ---------------------------------------------------------------------------
//	� AddCasePopup													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::AddCasePopup(ResType inType, Str255 inLabel, SInt32 inStartMark, LView * inContainer)
{
	OSErr			error = noErr;
	Rect			theFrame;
	SInt16			index = 1, foundIdx = -1;
	ResType			theType;
	SInt32			currMark, totalLength = mTemplateStream->GetLength();
	Str255			theString, theValue;
	Str255 * 		rightPtr;

	// Get a pointer to the associated edit field
	LEditText * theEditText = dynamic_cast<LEditText *>(this->FindPaneByID(mCurrentID - 1));
	if (theEditText == NULL) {
		return err_TmplPopupNotConnectedToEditField;
	} 
	
	theEditText->CalcPortFrameRect(theFrame);
	inContainer->PortToLocalPoint(botRight(theFrame));
	
	sBevelPaneInfo.left				= theFrame.right + kTmplBevelSep;
	sBevelPaneInfo.top				= mYCoord - sEditPaneInfo.height -kTmplVertSep -1;
	sBevelPaneInfo.paneID			= mCurrentID;
	sBevelPaneInfo.superView		= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplCasePopup, kControlBevelButtonSmallBevelProc,
													 MENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
	// Store the pointer to the associated edit field
	theBevelButton->SetUserCon( (long) theEditText);
	// Store the position mark of the first CASE in the userCon of the edit field
	theEditText->SetUserCon(inStartMark);
	// Retrieve the value of the associated edit field
	theEditText->GetDescriptor(theValue);
	
	// Let the popup listen to the edit field
	theEditText->AddListener(theBevelButton);

	// Populate the popup with all the successive cases
	if ( SplitCaseValue(inLabel, &rightPtr) ) {
		theBevelButton->InsertMenuItem(inLabel, index, true);
		if (rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) theValue, rightPtr) == 0) {
			foundIdx = index;
		} 
	} 
	currMark = mTemplateStream->GetMarker();
	while (currMark < totalLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != inType) {
			// We went too far. Reposition the stream marker.
			mTemplateStream->SetMarker(currMark, streamFrom_Start);
			break;
		} 
		currMark = mTemplateStream->GetMarker();
		index++;
		if ( SplitCaseValue(theString, &rightPtr) ) {
			theBevelButton->InsertMenuItem(theString, index, true);
			if (foundIdx == -1 && rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) theValue, rightPtr) == 0) {
				foundIdx = index;
			} 
		} 
	}
	
	// Mark the item corresponding to the value
	if (foundIdx != -1) {
		theBevelButton->SetCurrentMenuItem(foundIdx);						
	} else {
		::MacCheckMenuItem(theBevelButton->GetMacMenuH(), theBevelButton->GetCurrentMenuItem(), 0);
	}
	
	// Advance the counters. mYCoord has already been increased by the edit field
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
	
	return error;
}


// ---------------------------------------------------------------------------
//	� AddEditPopup													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddEditPopup(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								ResIDT inResourceID,
								LView * inContainer)
{
	SDimension16	theFrame;
	SInt16			index = 1, foundIdx = -1;
	SInt32			totalLength = mTemplateStream->GetLength();
	Str255			theString;
	Str255 * 		rightPtr;

	inContainer->GetFrameSize(theFrame);

	sEditPaneInfo.left		= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sEditPaneInfo.width		= inWidth;
	sEditPaneInfo.top		= mYCoord - 3;
	sEditPaneInfo.paneID	= mCurrentID;
	sEditPaneInfo.superView	= inContainer;

	LEditText * theEditText = new LEditText(sEditPaneInfo, this, inValue, sEditTraitsID, 
											msg_EditorItemModified, inMaxChars, inAttributes, inKeyFilter);
	ThrowIfNil_(theEditText);

	// Store the template's type in the userCon field
	theEditText->SetUserCon(inType);
	
	// Let the window listen to this field
	theEditText->AddListener(this);

	// Incr the pane ID
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;

	// Now build the popup
	sBevelPaneInfo.left			= sEditPaneInfo.left + inWidth + kTmplHorizSep;
	sBevelPaneInfo.top			= sEditPaneInfo.top + 2;
	sBevelPaneInfo.paneID		= mCurrentID;
	sBevelPaneInfo.superView	= inContainer;

	CTmplBevelButton * theBevelButton = new CTmplBevelButton(sBevelPaneInfo, msg_TmplPopupField, kControlBevelButtonSmallBevelProc,
													 MENU_TemplateCases, kControlBevelButtonMenuOnBottom, 
													 kControlContentTextOnly, 0, 0, Str_Empty, 1, 
													 kControlBevelButtonPlaceNormally, teFlushDefault, 0, 
													 kControlBevelButtonAlignCenter, Point_00, true);													 
	ThrowIfNil_(theBevelButton);

	// Let the window listen to this menu
	theBevelButton->AddListener(this);
	
	// Populate the popup with the items from the STR# resource with ID inResourceID
	while (true) {
		GetIndString(theString, inResourceID, index);
		if ( SplitCaseValue(theString, &rightPtr) ) {
			theBevelButton->InsertMenuItem(theString, index, true);
			if (foundIdx == -1 && rightPtr != NULL && UCompareUtils::CompareStr255( (Str255 *) inValue, rightPtr) == 0) {
				foundIdx = index;
			} 
			index++;
		} else {
			break;
		}
	} 
	
	// Store a pointer to the associated edit field
	theBevelButton->SetUserCon( (long) theEditText);
	// Store the STR# resource ID in the userCon of the edit field
	theEditText->SetUserCon(inResourceID);
	
	// Let the popup listen to the edit field
	theEditText->AddListener(theBevelButton);

	// Mark the item corresponding to the value
	if (foundIdx != -1) {
		theBevelButton->SetCurrentMenuItem(foundIdx);						
	} else {
		::MacCheckMenuItem(theBevelButton->GetMacMenuH(), theBevelButton->GetCurrentMenuItem(), 0);
	}

	// Advance the counters
	mYCoord += sEditPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


// ---------------------------------------------------------------------------
//	� AddColorPane													[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AddColorPane(LView * inContainer, 
								RGBColor * inRGB)
{
	sColorPaneInfo.left			= kTmplLeftMargin + kTmplLabelWidth + kTmplHorizSep;
	sColorPaneInfo.top			= mYCoord;
	sColorPaneInfo.superView	= inContainer;
	sColorPaneInfo.paneID		= mCurrentID;
	
	CColorWell * theWell = new CColorWell(sColorPaneInfo, inRGB, msg_EditorItemModified);
	ThrowIfNil_(theWell);

	// Let the window listen to this control
	theWell->AddListener(this);

	// Advance the counters
	mYCoord += sColorPaneInfo.height + kTmplVertSep;
	mPaneIDs.AddItem(mCurrentID);
	mCurrentID++;
}


