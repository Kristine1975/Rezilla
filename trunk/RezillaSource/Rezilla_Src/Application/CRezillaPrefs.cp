// ===========================================================================
// CRezillaPrefs.cp					
// 
//                       Created: 2004-05-17 08:52:16
//             Last modification: 2004-05-17 13:08:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


// Application Headers
#include "CRezillaPrefs.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UDialogBoxHandler.h"

// PowerPlant Headers
#include <PP_Messages.h>
#include <PP_Resources.h>

#include <LCaption.h>
#include <LCheckBox.h>
#include <LClipboard.h>
#include <LDialogBox.h>
#include <LMultiPanelView.h>
#include <LPageController.h>
#include <LPopupButton.h>
#include <LPopupGroupBox.h>
#include <LPushButton.h>
#include <LRadioGroupView.h>
#include <LRadioGroupView.h>
#include <LStaticText.h>
#include <LStdControl.h>
#include <LString.h>
#include <LTextGroupBox.h>
#include <LThemeTextBox.h>
#include <LWindow.h>

// Universal Headers
#include <CFPreferences.h>
#include <CFNumber.h>

// Standard Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


LDialogBox *	CRezillaPrefs::sWindow;


// ---------------------------------------------------------------------------
//	� CRezillaPrefs											[public]
// ---------------------------------------------------------------------------
//  Object constructor

CRezillaPrefs::CRezillaPrefs()
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	� CRezillaPrefs											[public]
// ---------------------------------------------------------------------------
//	Object constructor, specifying SuperCommander

CRezillaPrefs::CRezillaPrefs( LCommander* inSuper )
	: LCommander(inSuper)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	� ~CRezillaPrefs								[public, virtual]
// ---------------------------------------------------------------------------

CRezillaPrefs::~CRezillaPrefs()
{
}


// ---------------------------------------------------------------------------
//	� Initialize												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::Initialize()
{
	sWindow = nil;
	mFile = nil;

	mCurrPrefs.general.maxRecent		= 10;
	mCurrPrefs.exporting.formatDtd			= export_KeyDtd;
	mCurrPrefs.exporting.binaryEncoding	= export_Base64Enc;
	mCurrPrefs.compare.ignoreName		= false;
	mCurrPrefs.compare.ignoreAttributes	= true;
	mCurrPrefs.compare.ignoreData		= false;
	mCurrPrefs.compare.dataDisplay		= compare_hexDisplay;

		
	// Retrieve preferences stored on disk
	RetrievePreferences();
}


// ---------------------------------------------------------------------------
//	� MakePrefsWindow												  [public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::MakePrefsWindow()
{	
	sWindow = (LDialogBox *) (LWindow::CreateWindow( rPPob_PrefsWindow, this ));
	ThrowIfNil_(sWindow);
}


// ---------------------------------------------------------------------------
//	� StorePreferences												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::StorePreferences()
{
	CFStringRef 	theKey;
	CFNumberRef		theValue;
	SInt32			theNumber;

	theNumber = GetPrefValue( kPref_general_maxRecent );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue(CFSTR("pref_general_maxRecent"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_formatDtd );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_formatDtd"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_includeBinary );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_includeBinary"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_export_dataEncoding );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_export_dataEncoding"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_compare_ignoreName );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreName"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);

	theNumber = GetPrefValue( kPref_compare_ignoreAttributes );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreAttributes"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);
	
	theNumber = GetPrefValue( kPref_compare_ignoreData );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber); 
	CFPreferencesSetAppValue( CFSTR("pref_compare_ignoreData"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);	

	theNumber = GetPrefValue( kPref_compare_dataDisplay );
	theValue = CFNumberCreate(NULL, kCFNumberIntType, &theNumber);;
	CFPreferencesSetAppValue( CFSTR("pref_compare_dataDisplay"), theValue, kCFPreferencesCurrentApplication);
	if (theValue) CFRelease(theValue);
	
	// Flush the prefs to disk
	CFPreferencesAppSynchronize( CFSTR(kRezillaIdentifier) );
}


// ---------------------------------------------------------------------------
//	� RetrievePreferences												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::RetrievePreferences()
{
	Boolean 	valueValid, result;
	
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_general_maxRecent"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_general_maxRecent);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_export_formatDtd"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_formatDtd);
	}
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_export_includeBinary"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_includeBinary);
	}	
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_export_dataEncoding"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_export_dataEncoding);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreName"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreName);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreAttributes"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreAttributes);
	}	
	result = CFPreferencesGetAppBooleanValue(CFSTR("pref_compare_ignoreData"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_ignoreData);
	}
	result = CFPreferencesGetAppIntegerValue(CFSTR("pref_compare_dataDisplay"), CFSTR(kRezillaIdentifier), &valueValid);
	if (valueValid) {
		SetPrefValue( result, kPref_compare_dataDisplay);
	}
}


// ---------------------------------------------------------------------------
//	� SetPrefValue												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::SetPrefValue(SInt32 inPrefValue, SInt32 inConstant, SInt32 inPrefType)
{
	switch (inConstant) {
		
	  case kPref_general_maxRecent:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.general.maxRecent = inPrefValue ;
		} else {
			mCurrPrefs.general.maxRecent = inPrefValue ;
		}	
		break;
		
	  case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.formatDtd = inPrefValue ;
		} else {
			mCurrPrefs.exporting.formatDtd = inPrefValue ;
		}	
		break;
		
	  case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.includeBinary = inPrefValue ;
		} else {
			mCurrPrefs.exporting.includeBinary = inPrefValue ;
		}	
		break;
		
	  case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.exporting.binaryEncoding = inPrefValue ;
		} else {
			mCurrPrefs.exporting.binaryEncoding = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreName = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreName = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreAttributes = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreAttributes = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.ignoreData = inPrefValue ;
		} else {
			mCurrPrefs.compare.ignoreData = inPrefValue ;
		}	
		break;
		
	  case kPref_compare_dataDisplay:
		if (inPrefType == prefsType_Temp) {
			mTempPrefs.compare.dataDisplay = inPrefValue ;
		} else {
			mCurrPrefs.compare.dataDisplay = inPrefValue ;
		}	
		break;
	}	
}


// ---------------------------------------------------------------------------
//	� GetPrefValue												[public]
// ---------------------------------------------------------------------------

SInt32
CRezillaPrefs::GetPrefValue(SInt32 inConstant, SInt32 inPrefType)
{
	SInt32 theValue = 0;
	
	switch (inConstant) {
		
	  case kPref_general_maxRecent:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.general.maxRecent;
		} else {
			theValue = mCurrPrefs.general.maxRecent;
		}	
		break;
		
	  case kPref_export_formatDtd:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.formatDtd;
		} else {
			theValue = mCurrPrefs.exporting.formatDtd;
		}	
		break;
		
	  case kPref_export_includeBinary:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.includeBinary;
		} else {
			theValue = mCurrPrefs.exporting.includeBinary;
		}	
		break;
		
	  case kPref_export_dataEncoding:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.exporting.binaryEncoding;
		} else {
			theValue = mCurrPrefs.exporting.binaryEncoding;
		}	
		break;
		
	  case kPref_compare_ignoreName:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreName;
		} else {
			theValue = mCurrPrefs.compare.ignoreName;
		}	
		break;
		
	  case kPref_compare_ignoreAttributes:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreAttributes;
		} else {
			theValue = mCurrPrefs.compare.ignoreAttributes;
		}	
		break;
		
	  case kPref_compare_ignoreData:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.ignoreData;
		} else {
			theValue = mCurrPrefs.compare.ignoreData;
		}	
		break;
		
	  case kPref_compare_dataDisplay:
		if (inPrefType == prefsType_Temp) {
			theValue = mTempPrefs.compare.dataDisplay;
		} else {
			theValue = mCurrPrefs.compare.dataDisplay;
		}	
		break;
	}	
	
	return theValue;
}


// ---------------------------------------------------------------------------
//	� ValidateTempPrefs												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::ValidateTempPrefs() 
{
	if ( ! PrefsHaveChanged() ) return;
	::BlockMoveData(&mTempPrefs, &mCurrPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	� InitTempPrefs												[public]
// ---------------------------------------------------------------------------

void
CRezillaPrefs::InitTempPrefs() 
{
	::BlockMoveData(&mCurrPrefs, &mTempPrefs, sizeof(SRezillaPrefs));
}


// ---------------------------------------------------------------------------
//	� PrefsHaveChanged											[public]
// ---------------------------------------------------------------------------

Boolean
CRezillaPrefs::PrefsHaveChanged() 
{
	return ( memcmp( &mCurrPrefs, &mTempPrefs, sizeof(SRezillaPrefs) ) != 0);
}


// ---------------------------------------------------------------------------
//	� RunPrefsWindow											[public]
// ---------------------------------------------------------------------------
//	Display the preferences window for the application

void
CRezillaPrefs::RunPrefsWindow()
{
	LCheckBox *		theCheckBox;
	LPopupButton *	thePopup;
	SInt32 			theCurrStyleCategory,
					itemIndex,
					theSize,
					theFace = 0;
	SInt16			theFontNum;
	LStr255			theLine( "\p" );
	Str255			theStrName;
	Boolean 		inPrefsLoop = true;
	
	StDialogBoxHandler	theHandler(rPPob_PrefsWindow, this);
	LDialogBox *		theDialog = theHandler.GetDialog();
	Assert_(theDialog != nil);
	SetPrefsWindow(theDialog);

	InitTempPrefs();
	
	//    Get the elements
	// -------------------
	LPageController* thePageCtrl = dynamic_cast<LPageController*>(theDialog->FindPaneByID(item_PrefsPageController));
	ThrowIfNil_(thePageCtrl);
	
	LMultiPanelView* theMPV = dynamic_cast<LMultiPanelView*>(theDialog->FindPaneByID(item_PrefsMultiPanelView));
	ThrowIfNil_(theMPV);
	
	// Create the panels before we call them
	theMPV->CreateAllPanels();
	
	LView* theGeneralPane = theMPV->GetPanel(mpv_General);
	ThrowIfNil_(theGeneralPane);
	
	LView* theExportPane = theMPV->GetPanel(mpv_Export);
	ThrowIfNil_(theExportPane);
	
	LView* theComparePane = theMPV->GetPanel(mpv_Compare);
	ThrowIfNil_(theComparePane);
	
	LRadioGroupView * theDtdRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsDtdRgbx ));
	ThrowIfNil_(theDtdRGV);
	PaneIDT dtdRadioID = theDtdRGV->GetCurrentRadioID();
	
	LRadioGroupView * theDisplayRGV = dynamic_cast<LRadioGroupView *>(theExportPane->FindPaneByID( item_ExpPrefsEncRgbx ));
	ThrowIfNil_(theDisplayRGV);
	PaneIDT displayRadioID = theDisplayRGV->GetCurrentRadioID();
	
	//    Link Listeners and Broadcasters
	// ----------------------------------
	// Partly done in the StDialogBoxHandler constructor

	thePageCtrl->AddListener(theMPV);
	thePageCtrl->AddListener(&theHandler);
	
	// Note : the rRidL_PrefsWindow resource does not contain the controls of
	// the various MPV's subpanels. We have to do that explicitly.
	UReanimator::LinkListenerToBroadcasters( &theHandler, theGeneralPane, rPPob_PrefsGeneralPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theExportPane, rPPob_PrefsExportPane );
	UReanimator::LinkListenerToBroadcasters( &theHandler, theComparePane, rPPob_PrefsComparePane );
	
	
	while (inPrefsLoop) {
		
		//    Setup the controls values
		// ----------------------------		
// 		theDtdRGV->SetCurrentRadioID(  GetPrefValue( msg_Interaction ) + item_ModesBase );
// 		theDisplayRGV->SetCurrentRadioID(  GetPrefValue( msg_Interaction ) + item_ModesBase );
				
		theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( item_ExpPrefsInclBinData ));
		ThrowIfNil_( theCheckBox );
// 		theCheckBox->SetValue(  GetPrefValue( msg_PrefsStartDiff ) );

		theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( item_CompPrefsIgnName ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreName ) );

		theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( item_CompPrefsIgnAttr ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreAttributes ) );

		theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( item_CompPrefsIgnData ));
		ThrowIfNil_( theCheckBox );
		theCheckBox->SetValue(  GetPrefValue( kPref_compare_ignoreData ) );

		
		theDialog->Show();
		
		MessageT theMessage;
		while (true) {
			theMessage = theHandler.DoDialog();
			if (msg_OK == theMessage || msg_Cancel == theMessage) {
				inPrefsLoop = false;
				break;
			} else if (msg_RevertPrefs == theMessage) {
				break;  // Breaks out from the inner 'while' but still in the inPrefsLoop 'while'
			} else {
				theLine = "\p";
				switch (theMessage) {
					
				  case msg_CompPrefsIgnName:
				  case msg_CompPrefsIgnAttr:
				  case msg_CompPrefsIgnData:
// 					theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( theMessage - rPPob_PrefsWindow ));
// 					SetPrefValue( theCheckBox->GetValue(), theMessage, CRezillaPrefs::prefsType_Temp);
					break;
																				
				  case msg_ExpPrefsInclBinData:
// 					theCheckBox = dynamic_cast<LCheckBox *>(sWindow->FindPaneByID( theMessage - rPPob_PrefsWindow ));
// 					SetPrefValue( theCheckBox->GetValue(), theMessage, CRezillaPrefs::prefsType_Temp);
					break;
																				
				}	
			}
		}
		
		// if we hit ok, save the pref info
		if (msg_OK == theMessage)
		{
			Boolean validate = ( memcmp( &mCurrPrefs, &mTempPrefs, sizeof(STElement) ) != 0 );
			ValidateTempPrefs();
			if (validate) {
// 				ValidateStyleElements();
			}
		}
	}
}



