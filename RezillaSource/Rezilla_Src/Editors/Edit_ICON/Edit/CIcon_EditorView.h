// ===========================================================================
// CIcon_EditorView.h
// 
//                       Created: 2004-12-10 17:23:05
//             Last modification: 2004-12-10 17:23:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIcon_EditorView
#define _H_CIcon_EditorView
#pragma once


#include <LTextEditView.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CIcon_EditorWindow;

// ---------------------------------------------------------------------------

class CIcon_EditorView :	public LView {
public:
	enum { class_ID = FOUR_CHAR_CODE('ICNV') };

							CIcon_EditorView();
							CIcon_EditorView(
											 const SPaneInfo&	inPaneInfo,
											 const SViewInfo&	inViewInfo);
							CIcon_EditorView(
									LStream*			inStream );
	virtual					~CIcon_EditorView();

	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
	virtual void			UserChangedBitmap();

	CIcon_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CIcon_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	virtual Handle			GetModifiedBitmap();

protected:
		CIcon_EditorWindow *	mOwnerWindow;

	virtual void			ClickSelf(
									const SMouseDownEvent&	inMouseDown);
									

};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
