// ===========================================================================
// CAboutWindow.cp					
// 
//                       Created: 2005-03-08 14:22:24
//             Last modification: 2005-03-08 15:23:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CAboutWindow.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CStaticTextURL.h"

// #include <LWindow.h>
#include <LStaticText.h>
// #include <LPushButton.h>
// #include <LCheckBox.h>
// #include <LEditText.h>
// #include <UExtractFromAEDesc.h>
// #include <UAppleEventsMgr.h>
// #include <UCursor.h>

// #include <AppleHelp.h>

// #include <string.h>

// ---------------------------------------------------------------------------
//		� CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow()
{
}


// ---------------------------------------------------------------------------
//		� CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
	const SWindowInfo &inWindowInfo )
		: LDialogBox( inWindowInfo )
{
}


// ---------------------------------------------------------------------------
//		� CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: LDialogBox( inWINDid, inAttributes, inSuperCommander )
{
}


// ---------------------------------------------------------------------------
//		� CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::CAboutWindow(
			       LStream *inStream )
		: LDialogBox( inStream )
{
}


// ---------------------------------------------------------------------------
//		� ~CAboutWindow				[public]
// ---------------------------------------------------------------------------

CAboutWindow::~CAboutWindow()
{
}


// ---------------------------------------------------------------------------
//		� FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CAboutWindow::FinishCreateSelf()
{	
	Str255				theString;
	LStaticText *		theCaption;	
	CStaticTextURL *	theUrlCaption;	
	
	// Write the version number in the caption
	theCaption = dynamic_cast<LStaticText *>(this->FindPaneByID( item_AboutVersCaption ));
	theCaption->SetDescriptor( CRezillaApp::sVersionNumber);

	// Write the URLs
	for (UInt8 i = 0; i < 6; i++) {
		theUrlCaption = dynamic_cast<CStaticTextURL *>(this->FindPaneByID( item_AboutUrlsBase + i ));
	
		// Retrieve strings from STR# resource
		::GetIndString(theString, STRx_InternetUrls, 2*i+1);
		theUrlCaption->SetDescriptor(theString);
		
		::GetIndString(theString, STRx_InternetUrls, 2*i+2);
		theUrlCaption->SetUrlString(theString);
	}
		
	// Let window listen to its sub panes
    UReanimator::LinkListenerToControls( this, this, PPob_AboutWindow );

}


// ---------------------------------------------------------------------------------
//  � FindCommandStatus
// ---------------------------------------------------------------------------------

void
CAboutWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	// Disable all menu items
	outEnabled = false;
	return;
}


// ---------------------------------------------------------------------------
//		� ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CAboutWindow::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
#pragma unused( ioParam )
	
	switch (inMessage) {

		case msg_AboutOkButton:
		case msg_Close:
		DoClose();		
		break;
		
		case msg_AboutLicenceButton:
		WindowPtr theWinPtr = UWindows::FindNamedWindow("\pRezilla Licence");
		if (!theWinPtr) {
			LWindow* theWindow = LWindow::CreateWindow( PPob_LicenceWindow, this->GetSuperCommander() );
			ThrowIfNil_(theWindow);
			theWinPtr = theWindow->GetMacWindow();
		} 
		DoClose();		
		::SelectWindow(theWinPtr);
		break;	
		
	}
}	



