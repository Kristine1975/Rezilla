// ===========================================================================
// CTmplWindowUtils.cp					
// 
//                       Created: 2004-08-20 16:45:08
//             Last modification: 2004-09-28 07:20:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Implements the utility functions defined in the CTmplEditorWindow 
// class.


#include "CTmplEditorWindow.h"
#include "CTmplEditorDoc.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezObj.h"
#include "CWasteEditView.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LPopupButton.h>
#include <LStaticText.h>
#include <LIconPane.h>

#include <stdio.h>
#include <string.h>


// ---------------------------------------------------------------------------
//  � InstallReadOnlyIcon											[public]
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::InstallReadOnlyIcon() 
{
	LIconPane * theIcon = dynamic_cast<LIconPane *>(this->FindPaneByID( item_ReadOnlyIcon ));
	ThrowIfNil_( theIcon );
	if (mOwnerDoc->IsReadOnly()) {
		theIcon->SetIconID(ics8_Locked);
	} else {
		theIcon->SetIconID(ics8_Unlocked);
	}
}


// ---------------------------------------------------------------------------
//	� IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CTmplEditorWindow::IsDirty()
{	
	if (!mIsDirty) {
		// The mWasteFieldsList contains all the Waste views. Check if they
		// are modified.
		TArrayIterator<CWasteEditView *> iterator(mWasteFieldsList);
		CWasteEditView *	theWasteView = nil;
		
		while (iterator.Next(theWasteView)) {
			mIsDirty = theWasteView->IsDirty();
			if (mIsDirty) {
				break;
			} 
		}
	} 

	return mIsDirty;
}


// ---------------------------------------------------------------------------
//	� IsValidBitField													[public]
// ---------------------------------------------------------------------------
// BB0n  	BB01 to BB07	Bit field within a byte
// WBnn  	WB01 to WB16	Bit field within a word
// LBnn  	LB01 to LB31	Bit field within a long

Boolean
CTmplEditorWindow::IsValidBitField(OSType inType, Str255 inStr, 
								   UInt16 & ioBitsCount, UInt16 & ioBytesLen)
{
	Boolean isValid = false;
	long	theLong;
	
	if (inType >> 8 == 'BB0') {
		if (inStr[4] > '0' && inStr[4] < '8') {
			ioBitsCount = inStr[4] - '0';
			ioBytesLen = 1;
			isValid = true;
		} 
	} else {
		if ( (inStr[3] >= '0') && (inStr[3] <= '3') && (inStr[4] >= '0') && (inStr[4] <= '9') ) {
			inStr[2] = 2;
			::StringToNum( inStr + 2, &theLong);
			if (inType >> 16 == 'LB' && theLong <= 32) {
				ioBitsCount = theLong;
				ioBytesLen = 4;
				isValid = true;				
			} else if (inType >> 16 == 'WB' && theLong <= 16) {
				ioBitsCount = theLong;
				ioBytesLen = 2;
				isValid = true;
			} 
		} 
	}
	
	return isValid;
}


// ---------------------------------------------------------------------------
//	� BuildFormatString													[public]
// ---------------------------------------------------------------------------


void
CTmplEditorWindow::BuildFormatString(char * ioString, UInt8 inLength)
{
	if (CRezillaPrefs::GetPrefValue(kPref_editors_hexSymbol) == hex_Symb0x) {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "0x%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "0x%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	} else {
		if (CRezillaPrefs::GetPrefValue(kPref_editors_hexCase) == hex_uppercase) {
			sprintf(ioString, "$%s.%dX%sc%c", "%", inLength, "%", 0);
		} else {
			sprintf(ioString, "$%s.%dx%sc%c", "%", inLength, "%", 0);
		}
	}
}


// ---------------------------------------------------------------------------
//	� BuildScanString													[public]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::BuildScanString(char * inString, char * ioFormat, UInt8 inLength)
{
	OSErr error = noErr;
	
	if (inString[0] == '$') {
		sprintf(ioFormat, "$%s%dx%c", "%", inLength, 0);
	} else if (inString[0] == '0' && inString[1] == 'x') {
		sprintf(ioFormat, "0x%s%dx%c", "%", inLength, 0);		
	} else {
		// alert
		error = err_TmplMalformedHexValue;
	}
	return error;
}


// ---------------------------------------------------------------------------
//	� AdjustCounterField
// ---------------------------------------------------------------------------

void
CTmplEditorWindow::AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta) {
	LStaticText *	theCounterText;
	Str255	numStr;
	long	theLong;
	
	theCounterText = dynamic_cast<LStaticText *>(this->FindPaneByID(inPaneID));
	theCounterText->GetDescriptor(numStr);	
	::StringToNum( numStr, &theLong);
	theLong += inDelta;
	if (theLong < 0) {
		theLong = 0;
	} 
	::NumToString(theLong, numStr);
	theCounterText->SetDescriptor(numStr);	
}


// ---------------------------------------------------------------------------
//	� RenumberSubPanes
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its subpanes are numbered from
// (inOldLastID) to (mCurrentID - 1). The argument (inNewFirstID) is the ID
// which should normally be affected to the first numbered subpane of the new 
// list item. So there are three possibilities when a subpane is visited:
// - if its ID is < (inNewFirstID), leave it unchanged
// - if its value is >= (inNewFirstID) and < (inOldLastID), increase it by 
//   (mCurrentID - inOldLastID)
// - if its value is >= (inOldLastID), decrease it by (inOldLastID - inNewFirstID)
// 
// If a list item has been deleted, all the IDs of its subpanes will be
// removed. They are numbered between inNewFirstID and inOldLastID
// inclusive. There are two possibilities:
// - if an ID is < (inNewFirstID), leave it unchanged
// - otherwise, decrease it by (inOldLastID - inNewFirstID + 1)
//   Note that the IDs between inNewFirstID and inOldLastID won't be found since 
//   the object has already been removed from the list of subpanes. Last
//   mCurrentID has to be adjusted likewise.

void
CTmplEditorWindow::RenumberSubPanes(LView * inView, PaneIDT inOldLastID, PaneIDT inNewFirstID, Boolean adding) 
{
	PaneIDT	theID;
	LView *	theView;
	
	if (adding) {
		// We've been inserting a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID) {
				if (theID < inNewFirstID) {
					// Do nothing
				} else if (theID < inOldLastID) {
					theID += mCurrentID - inOldLastID;
					theSub->SetPaneID(theID);
				} else {
					theID -= inOldLastID - inNewFirstID;
					theSub->SetPaneID(theID);
				}
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}

	} else {
		
		// We've been removing a list item
		TArrayIterator<LPane *> iterator( inView->GetSubPanes() );
		LPane	* theSub;
		while (iterator.Next(theSub)) {
			theID = theSub->GetPaneID();
			if (theID > inOldLastID) {
				theID -= inOldLastID - inNewFirstID + 1;
				theSub->SetPaneID(theID);
			} 
			theView = dynamic_cast<LView *>(theSub);
			if (theView) {
				RenumberSubPanes(theView, inOldLastID, inNewFirstID, adding);
			} 
		}
		
	}
}


// ---------------------------------------------------------------------------
//	� RecalcPositions
// ---------------------------------------------------------------------------
// If a new list item has been inserted, its first level subpanes must be
// repositioned. Their top pos must be increased by the height of the
// inserted list item. Then one must propagate to the containing view
// repeatedly until we reach the root contents view.

void
CTmplEditorWindow::RecalcPositions(LView * inView, SInt32 inVertPos, SInt32 inPosDelta) 
{
	Rect	theFrame;
	LPane *	theSub;
	SInt32	thePos = inVertPos;
	LView *	theContainer = inView->GetSuperView();
	
	while (theContainer != nil) {
		TArrayIterator<LPane *> iterator( theContainer->GetSubPanes() );
		while (iterator.Next(theSub)) {
			theSub->CalcPortFrameRect(theFrame);
			theContainer->PortToLocalPoint(topLeft(theFrame));

			if (theSub != inView && theFrame.top >= thePos) {
				theSub->MoveBy(0, inPosDelta, false);
			} 
		}
		if (theContainer == mContentsView) {
			break;
		} 
		theContainer->ResizeFrameBy(0, inPosDelta, false);
		theContainer->CalcPortFrameRect(theFrame);
		theContainer = theContainer->GetSuperView();
		if (theContainer != nil) {
			theContainer->PortToLocalPoint(topLeft(theFrame));
			// Increase by one pixel to ensure that the container won't
			// move itself
			thePos = theFrame.top + 1;
		} 
	}
}


// ---------------------------------------------------------------------------
//	� AlignBytesRead											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesRead(UInt8 inStep)
{
	ExceptionCode	error = noErr;
	
	SInt32 theSInt32 = mRezStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {
		if (theSInt32 + theRest > mRezStream->GetLength()) {
			error = writErr;
		} else {
			mRezStream->SetMarker(inStep - theRest, streamFrom_Marker);
		}
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	� AlignBytesWrite											[public]
// ---------------------------------------------------------------------------

ExceptionCode
CTmplEditorWindow::AlignBytesWrite(UInt8 inStep)
{
	ExceptionCode	error = noErr;
	
	SInt32 theSInt32 = mOutStream->GetMarker();
	SInt32 theRest = theSInt32 % inStep;

	if (theRest != 0) {	
		for (UInt8 i = theRest; i < inStep; i++) {
				*mOutStream << (UInt8) 0x00;
			}
		}
	
	return error;
}


#pragma mark -

// ---------------------------------------------------------------------------
//	� KeyValueToString											[private]
// ---------------------------------------------------------------------------
// The value of the key tag is stored as an SInt32 in the mKeyedValuesList 
// for faster validation.

void
CTmplEditorWindow::KeyValueToString(ResType inType, Str255 keyString)
{
	char	theChar = 0;
	UInt8	theUInt8 = 0;
	UInt16	theUInt16 = 0;
	UInt32	theUInt32 = 0;
	SInt8	theSInt8 = 0;
	SInt16	theSInt16 = 0;
	SInt32	theSInt32 = 0;
	char 	charString[256];
	char 	formatString[16];
	OSType	theOSType;
	
	switch (inType) {
		case 'KBYT':
		*mRezStream >> theSInt8;
		mKeyedValuesList.AddItem( (SInt32) theSInt8);
		::NumToString( (long) theSInt8, keyString);
		break;

		case 'KCHR':
		*mRezStream >> theChar;
		mKeyedValuesList.AddItem( (SInt32) theChar);
		keyString[0] = 1;
		keyString[1] = theChar;
		break;

		case 'KHBT':
		*mRezStream >> theUInt8;
		mKeyedValuesList.AddItem( (SInt32) theUInt8);
		BuildFormatString(formatString, 2);
		sprintf(charString, formatString, theUInt8, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHLG':
		*mRezStream >> theUInt32;
		mKeyedValuesList.AddItem( (SInt32) theUInt32);
		BuildFormatString(formatString, 8);
		sprintf(charString, formatString, theUInt32, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KHWD':
		*mRezStream >> theUInt16;
		mKeyedValuesList.AddItem( (SInt32) theUInt16);
		BuildFormatString(formatString, 4);
		sprintf(charString, formatString, theUInt16, NULL);
		CopyCStringToPascal(charString, keyString);
		break;

		case 'KLNG':
		*mRezStream >> theSInt32;
		mKeyedValuesList.AddItem( (SInt32) theSInt32);
		::NumToString( (long) theSInt32, keyString);
		break;

		case 'KRID':
		theSInt16 = GetOwnerDoc()->GetRezObj()->GetID();
		mKeyedValuesList.AddItem( (SInt32) theSInt16);
		::NumToString( (long) theSInt16, keyString);	
		break;

		case 'KTYP': {
			Str255 tempString;
			*mRezStream >> theOSType;
			mKeyedValuesList.AddItem( (SInt32) theOSType);
			UMiscUtils::OSTypeToPString(theOSType, tempString);
			LString::CopyPStr(tempString, keyString);
			break;
		}
		
		case 'KUBT':
		*mRezStream >> theUInt8;
		mKeyedValuesList.AddItem( (SInt32) theUInt8);
		::NumToString( (long) theUInt8, keyString);
		break;

		case 'KULG':
		*mRezStream >> theUInt32;
		mKeyedValuesList.AddItem( (SInt32) theUInt32);
		::NumToString( (long) theUInt32, keyString);
		break;

		case 'KUWD':
		*mRezStream >> theUInt16;
		mKeyedValuesList.AddItem( (SInt32) theUInt16);
		::NumToString( (long) theUInt16, keyString);
		break;

		case 'KWRD':
		*mRezStream >> theSInt16;
		mKeyedValuesList.AddItem( (SInt32) theSInt16);
		::NumToString( (long) theSInt16, keyString);
		break;
	}
}


// ---------------------------------------------------------------------------
//	� FindKeyStartForValue											[private]
// ---------------------------------------------------------------------------
// The marker is positionned after the last CASE statement. Scan the 
// keyed sections until the corresponding key is found.

OSErr
CTmplEditorWindow::FindKeyStartForValue(Str255 keyString, SInt32 * outStart)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	SInt32	currMark, maxPos;
	Str255	theString;
	ResType	theType;
		
	currMark = mTemplateStream->GetMarker();
	maxPos = mTemplateStream->GetLength();
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		currMark = mTemplateStream->GetMarker();		
	
		// The type at this point should normally be 'KEYB'
		if (theType != 'KEYB') {
			error = err_TmplMalformedKeySection;
			return error;
		} 
		
		// Is it the case corresponding to our keyString?
		if ( ::EqualString(theString, keyString, true, true) ) {
			found = true;
			break;
		} 
		
		// If not, go to the corresponding KEYE
		error = FindMatchingKeyEnd(&currMark);
		if (error != noErr) {
			break;
		} 
	}
	
	if (!found) {
		error = err_TmplCantFindKeyStartForValue;
	} else {
		*outStart = currMark;
		// Store the value for future validation
		mKeyedMarksList.AddItem(currMark);
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	� WriteOutKeyValue											[private]
// ---------------------------------------------------------------------------
// The value of the key tag has been stored as an SInt32 in the mKeyedValuesList.

void
CTmplEditorWindow::WriteOutKeyValue(ResType inType)
{
	SInt32	keyValue;
	
	mKeyedValuesList.RemoveLastItem(keyValue);
	
	switch (inType) {
		case 'KBYT':
		*mOutStream << (SInt8) keyValue;
		break;

		case 'KCHR':
		*mOutStream << (UInt8) keyValue;
		break;

		case 'KHBT':
		*mOutStream << (UInt8) keyValue;
		break;

		case 'KHLG':
		*mOutStream << (UInt32) keyValue;
		break;

		case 'KHWD':
		*mOutStream << (UInt16) keyValue;
		break;

		case 'KLNG':
		*mOutStream << (SInt32) keyValue;
		break;

		case 'KRID':
		*mOutStream << (SInt16) keyValue;
		break;

		case 'KTYP': 
		*mOutStream << (OSType) keyValue;
		break;
		
		case 'KUBT':
		*mOutStream << (UInt8) keyValue;
		break;

		case 'KULG':
		*mOutStream << (UInt32) keyValue;
		break;

		case 'KUWD':
		*mOutStream << (UInt16) keyValue;
		break;

		case 'KWRD':
		*mOutStream << (SInt16) keyValue;
		break;
	}
}


// ---------------------------------------------------------------------------
//	� FindMatchingKeyEnd											[private]
// ---------------------------------------------------------------------------
// Starting from a given KEYB find the corresponding KEYE. It returns 
// the position after the KEYE.

OSErr
CTmplEditorWindow::FindMatchingKeyEnd(SInt32 * outEnd)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	SInt32	currMark, maxPos;
	UInt16	keybCount, keyeCount;
	Str255	theString;
	ResType	theType;

	currMark = mTemplateStream->GetMarker();
	maxPos = mTemplateStream->GetLength();
	keybCount = 1;
	keyeCount = 0;
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		currMark = mTemplateStream->GetMarker();		
		
		if (theType == 'KEYB') {
			keybCount++;
		} else if (theType == 'KEYE') {
			keyeCount++;
		} else continue;
		
		if (keybCount == keyeCount) {
			found = true;
			break;
		} 
	}
	
	if (!found) {
		error = err_TmplCantFindMatchingKeyEnd;
	} else {
		*outEnd = currMark;
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//	� SkipNextKeyCases											[private]
// ---------------------------------------------------------------------------
// Skip all the CASE statements starting from current position

OSErr
CTmplEditorWindow::SkipNextKeyCases(UInt16 inPreCount)
{	
	OSErr	error = noErr;
	Boolean	found = false;
	Str255	theString;
	ResType	theType;
	UInt16	caseCount = inPreCount + 1;
	SInt32	currMark = mTemplateStream->GetMarker();
	SInt32	maxPos = mTemplateStream->GetLength();
	
	while (currMark < maxPos) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		
		if (theType != 'CASE') {
			if (caseCount == 1) {
				// The type at this point should normally be 'CASE'
				error = err_TmplMalformedCaseSection;
				return error;
			} else {
				// We went too far. Reposition the stream marker.
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
				break;
			}
		} 
		caseCount++;
		currMark = mTemplateStream->GetMarker();
	}

	return error;
}


// ---------------------------------------------------------------------------
//	� SelectKeyValueFromKeyCases										[private]
// ---------------------------------------------------------------------------

OSErr
CTmplEditorWindow::SelectKeyValueFromKeyCases(Str255 inLabelString,
										   Str255 outKeyString)
{
	OSErr			error = noErr;
	Str255			theString;
	ResType			theType;
	Boolean			selected = false;
	Boolean 		inPickerLoop = true;
	UInt16			countCases = 0;
	Str255 * 		rightPtr;
	SInt16			i, index = 0;
	SInt32			currMark, origMark, totalLength = mTemplateStream->GetLength();

	StDialogBoxHandler	theHandler(rPPob_TmplKeyPickerPicker, this);
	LDialogBox *		theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	
	UMiscUtils::OSTypeToPString(mOwnerDoc->GetSubstType(), theString);
	
	LStaticText * theTypeField = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_TmplKeyPickerType ));
	ThrowIfNil_(theTypeField);
	
	LStaticText * theLabelField = dynamic_cast<LStaticText *>(theDialog->FindPaneByID( item_TmplKeyPickerLabel ));
	ThrowIfNil_(theLabelField);
	
	LPopupButton * thePopup = dynamic_cast<LPopupButton *>(theDialog->FindPaneByID( item_TmplKeyPickerMenu ));
	ThrowIfNil_(thePopup);
	
	theTypeField->SetDescriptor(theString);
	theLabelField->SetDescriptor(inLabelString);

	// Populate the popup with all the successive cases
	currMark = mTemplateStream->GetMarker();
	origMark = currMark;
	while (currMark < totalLength) {
		*mTemplateStream >> theString;
		*mTemplateStream >> theType;
		if (theType != 'CASE') {
			if (countCases == 0) {
				error = err_TmplNoCaseInKeySection;
				return error;
			} else {
				// We went too far. Reposition the stream marker.
				mTemplateStream->SetMarker(currMark, streamFrom_Start);
				break;
			}
		} 
		countCases++;
		currMark = mTemplateStream->GetMarker();
		if ( SplitCaseValue(theString, &rightPtr) ) {
			thePopup->InsertMenuItem(theString, index, true);
			index++;
		} 
	}
	
	if (index == 0) {
		// Means that SplitCaseValue() failed on all cases
		return err_TmplMalformedCaseSection;
	} 
	
	// If there is only one CASE, choose it without asking
	if (countCases == 1) {
		LString::CopyPStr(*rightPtr, outKeyString);
		return noErr;
	} 

	while (inPickerLoop) {
		MessageT theMessage;
		
		theDialog->Show();
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage) {
				break;
			} else if (msg_Cancel == theMessage) {
				inPickerLoop = false;
				error = userCanceledErr;
				break;
			} else if (msg_TmplKeyPickerMenu == theMessage) {
				// Retrieve the menu item and write it in the edit field
				index = thePopup->GetValue();
				break;  // Breaks out from the inner 'while' but still in the inPickerLoop 'while'
			} 
		}
		
		// If the default button was hit, try to open the rezmaps
		if (msg_OK == theMessage) {
			// Use the index to retreive the value of the key
			mTemplateStream->SetMarker(origMark, streamFrom_Start);
			for (i = 0; i < index; i++) {
				*mTemplateStream >> theString;
				*mTemplateStream >> theType;
			}
			SplitCaseValue(theString, &rightPtr);
			LString::CopyPStr(*rightPtr, outKeyString);
			// Now get out of the outer 'while'
			inPickerLoop = false;
		} 
	}
	mTemplateStream->SetMarker(currMark, streamFrom_Start);
	return error;
}


// ---------------------------------------------------------------------------
//	� SplitCaseValue												[static]
// ---------------------------------------------------------------------------
// This function makes two adjacent Pascal strings out of one. For instance:
//         9abcde=fgh will become 5abcde3fgh.
// On output, it stores a pointer to the RH string. If splitting was successful, 
// the function returns true.

Boolean
CTmplEditorWindow::SplitCaseValue(Str255 inString, Str255 ** outRightPtr)
{
	Boolean split = false;

	if (inString[0]) {
		register char *	p;
		char 	str[256];
		SInt32	len;
		
		CopyPascalStringToC(inString, str);
		p = strrchr((char *) str, '=');
		if (p != nil) {
			split = true;
			len = p - (char *) str;
			inString[len+1] = inString[0] - len - 1;
			inString[0] = len;
			*outRightPtr = (Str255 *) &inString[len+1];
		} 
	}	
	return split;
}

