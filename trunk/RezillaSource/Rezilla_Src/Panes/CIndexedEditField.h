// ===========================================================================
// CIndexedEditField.h
// 
//                       Created: 2005-09-01 09:14:05
//             Last modification: 2005-09-03 10:07:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIndexedEditField
#define _H_CIndexedEditField
#pragma once

#include <LStaticText.h>
#include <LEditText.h>
#include <LView.h>
#include <LCommander.h>
#include <LBroadcaster.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

const SInt16	kStrxHeight		= 40;
const SInt16	kStrxIndexWidth	= 36;
const SInt16	kStrxHorizSep	= 4;
const SInt16	kStrxVertSep	= 3;

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------

class CIndexedEditField : public LView, 
						public LCommander {
public:
	enum { class_ID		= FOUR_CHAR_CODE('IXED')};

							CIndexedEditField(
								LStream*		inStream);

							CIndexedEditField(	
								const SPaneInfo& inPaneInfo,
								const SViewInfo& inViewInfo,
								UInt16 index,
								Str255 inString);

	virtual				~CIndexedEditField();

	virtual void		Click( SMouseDownEvent& inMouseDown );
	
	virtual void		DrawSelf();

// 	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );
	
	virtual void		DrawBorder();
	virtual void		EraseBorder();

	void				SetIndexField(UInt16 index);
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;
	virtual void		SetDescriptor( ConstStringPtr inDescriptor );
	
	virtual SInt32		GetIndex() { return mIndex;}
	void				SetIndex(SInt32 inIndex) {mIndex = inIndex;}

	virtual Boolean		IsSelected() { return mSelected;}
	void				SetSelected(Boolean inSelected) {mSelected = inSelected;}

protected:
	LStaticText *		mStaticText;
	LEditText *			mEditText;
	SInt32				mIndex;			// Starting at 1
	Boolean				mSelected;

	
	virtual void		FinishCreateSelf();

private:
	void				Initialize(Str255 inString);
	
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
