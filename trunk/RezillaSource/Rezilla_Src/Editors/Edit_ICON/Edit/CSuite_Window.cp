// ===========================================================================
// CSuite_Window.cp
//                       Created: 2005-01-10 21:23:57
//             Last modification: 2005-01-11 07:42:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CSuite_Window.h"
#include "CDraggableTargetView.h"
#include "CIcon_EditorDoc.h"
#include "CIcon_EditorWindow.h"
#include "CSuiteSlider.h"
#include "CWindow_Pattern.h"
#include "CPatternTargetView.h"
#include "COffscreen.h"
#include "CRezMap.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "UGraphicConversion.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResourceMgr.h"

#include <LStaticText.h>
#include <LPushButton.h>

// ---------------------------------------------------------------------------
// 	OpenPaintWindow
// ---------------------------------------------------------------------------
CSuite_Window*
CSuite_Window::OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResType inResType, ResIDT inResID )
{
	CSuite_Window *	theWindow = nil;

	try
	{
		theWindow = (CSuite_Window*) CIcon_EditorWindow::CreatePaintWindow( inPPobID );
		theWindow->InitializeFromResource( inMap, inResType, inResID );
	}
	catch( ... )
	{
		delete theWindow;
		throw;
	}
	
	return( theWindow );
}


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------
CSuite_Window::CSuite_Window( LStream *inStream ) 
		: CIcon_EditorWindow( inStream )
{
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------
CSuite_Window::~CSuite_Window()
{
}


// ---------------------------------------------------------------------------
// 	CreateFromStream
// ---------------------------------------------------------------------------
CSuite_Window *
CSuite_Window::CreateFromStream( LStream *inStream )
{
	return new CSuite_Window( inStream );
}


// ---------------------------------------------------------------------------
// 	InitializeFromResource
// ---------------------------------------------------------------------------
void
CSuite_Window::InitializeFromResource( CRezMap *inMap, ResType inResType, ResIDT inResID )
{
	StGWorldSaver		worldSaver;
	StRezRefSaver		refSaver;

	COffscreen			*bwImage = nil;
	Handle				h = nil;
	
	try
	{	
		// Get the raw resource handle
		CRezObj * theRes = inMap->FindResource( inResType, inResID, true );
		ThrowIfNil_( theRes );
		h = theRes->GetData();
		ThrowIfNil_( h );
		
		// Parse the resource to build the patterns array
		ParseBitmapSuite( h, &bwImage );
		
		SetNthBitmap(1);

		mSlider->SetValue(mCurrentIndex);
		mSlider->SetMinValue(1);
		mSlider->SetMaxValue(mTotalCount);
		AdjustSlider();
	}
	catch( ... )
	{
		delete( bwImage );
		( h );
		throw;
	}
	
	( h );
}


// ---------------------------------------------------------------------------
// 	SaveAsResource
// ---------------------------------------------------------------------------
void
CSuite_Window::SaveAsResource( CRezMap * /* inMap */, ResIDT /* inResID */ )
{
}


// ---------------------------------------------------------------------------
// 	FinishCreateSelf
// ---------------------------------------------------------------------------

void
CSuite_Window::FinishCreateSelf()
{
	CIcon_EditorWindow::FinishCreateSelf();

	mSlider = dynamic_cast<CSuiteSlider *>(this->FindPaneByID( item_IconSuiteSlider ));
	ThrowIfNil_( mSlider );

	mSlider->SetOwnerWindow(this);
	
	mCountField = (LStaticText *) this->FindPaneByID( item_IconCountField );
	ThrowIfNil_( mCountField );

	mPlusButton = (LPushButton *) this->FindPaneByID( item_PlusButton );
	ThrowIfNil_( mPlusButton );

	mMinusButton = (LPushButton *) this->FindPaneByID( item_MinusButton );
	ThrowIfNil_( mMinusButton );

	mSlider->AddListener(this);
	mPlusButton->AddListener(this);
	mMinusButton->AddListener(this);

}


// ---------------------------------------------------------------------------
//  ListenToMessage												[public]
// ---------------------------------------------------------------------------

void
CSuite_Window::ListenToMessage( MessageT inMessage, void *ioParam ) 
{
	switch( inMessage )
	{
		case msg_IconSuiteSlider:
		SInt32 val = mSlider->GetValue();
		SetCountField(val, mTotalCount);
		break;
		
		case msg_PlusButton:
		ArrayIndexT index = AddNewBitmap();
		SetNthBitmap(index);
		AdjustSlider();
		break;
		
		case msg_MinusButton:
		RemoveBitmap(mCurrentIndex);
		SetNthBitmap(mCurrentIndex);
		AdjustSlider();
		break;
		
		default:
		CIcon_EditorWindow::ListenToMessage(inMessage, ioParam);
		break;
	}
}


// ---------------------------------------------------------------------------
//	� HandleKeyPress												  [public]
// ---------------------------------------------------------------------------
// The PageUp and PageDown arrows move the slider by 1 unit (recall that
// the simple arrow keys are used by the Text tool to nudge the selection
// in the canvas). The Home key moves the slider to the min value, the End
// key to the max value. Pressing the + or - key together with the Command
// key simulate the plus and minus buttons.

Boolean
CSuite_Window::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	Boolean		keyHandled	= true;
	LControl*	keyButton	= nil;
	UInt8		theChar		= (UInt8) (inKeyEvent.message & charCodeMask);
	
	if (inKeyEvent.modifiers & cmdKey) {
		if ( theChar == 0x2B) {
			// The + char
			keyButton = dynamic_cast<LControl*>(mPlusButton);		
		} else if ( theChar == 0x2D ) {
			// The - char
			keyButton = dynamic_cast<LControl*>(mMinusButton);		
		} 
	} else {
		SInt32 theValue, oldValue;
		oldValue = mSlider->GetValue();
		theValue = oldValue;
		
		if (theChar == char_PageDown) {
			if (theValue > 1) {
				--theValue;
			} 
		} else if (theChar == char_PageUp) {
			if (theValue < mTotalCount) {
				++theValue;
			} 
		} else if ( theChar == char_Home ) {
			theValue = 1;
		} else if ( theChar == char_End ) {
			theValue = mTotalCount;
		} 
		
		if (theValue != oldValue) {
			mSlider->SetValue(theValue);
			SetNthBitmap(theValue);	
		} 
	}
	
	if (keyButton != nil) {
		keyButton->SimulateHotSpotClick(kControlButtonPart);
	} else {
		keyHandled = CIcon_EditorWindow::HandleKeyPress(inKeyEvent);
	}
	
	return keyHandled;
}


// ---------------------------------------------------------------------------
// 	ParseBitmapSuite
// ---------------------------------------------------------------------------

void
CSuite_Window::ParseBitmapSuite( Handle /* inHandle */, COffscreen ** /* outBW */  )
{
	// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	SetCountField
// ---------------------------------------------------------------------------

void
CSuite_Window::SetCountField( SInt32 inCurrIndex, SInt32 inTotalCount )
{
	Str255	theString;
	LStr255	theLine("\p");
	
	::NumToString( inCurrIndex, theString);
	theLine.Append(theString);
	theLine += "\p/";
	::NumToString( inTotalCount, theString);
	theLine.Append(theString);
	mCountField->SetDescriptor(theLine);
}


// ---------------------------------------------------------------------------
// 	AdjustSlider
// ---------------------------------------------------------------------------

void
CSuite_Window::AdjustSlider()
{
	if (mTotalCount <= 1) {
		mSlider->Hide();
	} else {
		mSlider->Show();
	}
	mSlider->SetValue(mCurrentIndex);
	SetCountField(mCurrentIndex, mTotalCount);
}


// ---------------------------------------------------------------------------
// 	SwitchToNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::SwitchToNthBitmap( SInt32 inBitmapIndex )
{
	if (mCurrentIndex == inBitmapIndex) {
		return;
	} 

	// Store the state of the current pattern
	ImageToNthBitmap(mCurrentIndex);
	
	// Set the new pattern
	SetNthBitmap(inBitmapIndex);
}


// ---------------------------------------------------------------------------
// 	SetNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::SetNthBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CSuite_Window::AddNewBitmap()
{
	ArrayIndexT index = 0;

// Subclasses must override
	
	return index;
}


// ---------------------------------------------------------------------------
// 	AddNewBitmap
// ---------------------------------------------------------------------------

ArrayIndexT
CSuite_Window::AddNewBitmap( SInt32 /* inAtIndex */ )
{
	ArrayIndexT index = 0;
	
// Subclasses must override

	return index;
}


// ---------------------------------------------------------------------------
// 	RemoveBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::RemoveBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}


// ---------------------------------------------------------------------------
// 	ImageToNthBitmap
// ---------------------------------------------------------------------------

void
CSuite_Window::ImageToNthBitmap( SInt32 /* inBitmapIndex */ )
{
// Subclasses must override
}



