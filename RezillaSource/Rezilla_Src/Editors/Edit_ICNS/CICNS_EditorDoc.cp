// ===========================================================================
// CICNS_EditorDoc.cp
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CICNS_EditorDoc.h"
#include "CICNS_EditorWindow.h"
#include "CEditorsController.h"
#include "RezillaConstants.h"
#include "CRezMap.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "CRezObj.h"
#include "CRezillaPrefs.h"
#include "UCodeTranslator.h"
#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LWindow.h>
#include <LFile.h>
#include <UStandardDialogs.h>
#include <LRadioGroupView.h>
#include <LCheckBox.h>
#include <LEditField.h>
#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>

// // Standard headers
// #include <string.h>




// ---------------------------------------------------------------------------
//  CICNS_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CICNS_EditorDoc::CICNS_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//  ~CICNS_EditorDoc							Destructor		  [public]
// ---------------------------------------------------------------------------

CICNS_EditorDoc::~CICNS_EditorDoc()
{
	if (mIcnsEditWindow != nil) {
		delete mIcnsEditWindow;
	} 
}


// ---------------------------------------------------------------------------
//  Initialize													[public]
// ---------------------------------------------------------------------------

void
CICNS_EditorDoc::Initialize()
{
	OSErr error = noErr;
	
	// Create a window for our document and set this doc as its SuperCommander
	mIcnsEditWindow = dynamic_cast<CICNS_EditorWindow *>(LWindow::CreateWindow( PPob_StandardEditorWindow, this ));
	Assert_( mIcnsEditWindow != nil );
	
	SetMainWindow( dynamic_cast<CEditorWindow *>(mIcnsEditWindow) );
	NameNewEditorDoc();
	mIcnsEditWindow->FinalizeEditor(this);
	
	try {
		// Install the data
		if (mRezObj != nil) {
			Handle rezData = mRezObj->GetData();
			
			if (rezData != nil) {
				// Work with a copy of the handle
				::HandToHand(&rezData);
				
				error = mIcnsEditWindow->InstallResourceData(rezData);			
			} 
			ThrowIfError_(error);			
		} 
	} catch (...) {
		delete this;
		if (error == err_MoreDataThanExpected) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ResourceLongerThanExpected"), PPob_SimpleMessage);
		} else if (error != userCanceledErr) {
			UMessageDialogs::SimpleMessageFromLocalizable(CFSTR("ErrorWhileParsingResource"), error);
		} 
		return;
	}
	
	// Make the window visible.
	mIcnsEditWindow->Show();
	// Enable all the subpanes
	mIcnsEditWindow->GetContentsView()->Enable();
}


// ---------------------------------------------------------------------------
//  GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
CICNS_EditorDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIcnsEditWindow != nil) {
		// Use name of its window
		mIcnsEditWindow->GetDescriptor(outDescriptor);
	} else {
		// No window, document name is empty string
		outDescriptor[0] = 0;		
	}

	return outDescriptor;
}


// ---------------------------------------------------------------------------------
//   FindCommandStatus
// ---------------------------------------------------------------------------------

void
CICNS_EditorDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName )
{
	switch ( inCommand ) {
	
	  default:
			// Call inherited.
		CEditorDoc::FindCommandStatus( inCommand,
				outEnabled, outUsesMark, outMark, outName );
		break;

	}
}


// ---------------------------------------------------------------------------
//  AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
CICNS_EditorDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mIcnsEditWindow) {
		AttemptClose(false);
		return false;
	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//   GetModifiedResource										[protected]
// ---------------------------------------------------------------------------
// The returned handle should not be released by the caller so leave
// releaseIt to false (its default).

Handle
CICNS_EditorDoc::GetModifiedResource(Boolean &releaseIt) 
{
#pragma unused(releaseIt)
	
	return mIcnsEditWindow->CollectResourceData();
}



PP_End_Namespace_PowerPlant
