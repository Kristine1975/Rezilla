// ===========================================================================
// CStaticEditCombo.h
// 
//                       Created: 2005-03-17 09:36:42
//             Last modification: 2005-07-03 16:59:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CStaticEditCombo
#define _H_CStaticEditCombo
#pragma once

#include <LStaticText.h>
#include <LEditText.h>
#include <LView.h>
#include <LCommander.h>
#include <LBroadcaster.h>



PP_Begin_Namespace_PowerPlant



// ---------------------------------------------------------------------------

class CStaticEditCombo : public LView, 
						public LCommander,
						public LBroadcaster {
public:
	enum { class_ID		= FOUR_CHAR_CODE('SECV')};

							CStaticEditCombo(
								LStream*		inStream);

							CStaticEditCombo(	
								const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo);

	virtual				~CStaticEditCombo();

	virtual void		Click( SMouseDownEvent& inMouseDown );
	
	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );
	
	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;
	virtual void		SetDescriptor( ConstStringPtr inDescriptor );
	
protected:
	LStaticText *			mStaticText;
	LEditText *				mEditText;
	Str255					mCurrentTitle;
	Boolean					mIsEditing;

	
	virtual void		FinishCreateSelf();

private:
	void				InitCombo();
	void				SwapPanes();
	
};

PP_End_Namespace_PowerPlant




#endif
