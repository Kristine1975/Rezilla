// ===========================================================================
// UDialogBoxHandler.h				
// 
//                       Created: 2002-05-09 18:35:37
//             Last modification: 2004-02-22 19:50:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// � Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// StDialogBoxHandler is derived from StDialogHandler


#ifndef _H_UDialogBoxHandler
#define _H_UDialogBoxHandler
#pragma once

#include <LCommander.h>
#include <LEventDispatcher.h>
#include <LListener.h>
#include <LPeriodical.h>

#include <Dialogs.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LDialogBox;

// ===========================================================================
#pragma mark StDialogBoxHandler

class StDialogBoxHandler : public LEventDispatcher,
						  public LCommander,
						  public LListener {
public:
						StDialogBoxHandler(
								ResIDT			inDialogResID,
								LCommander*		inSuper);

						StDialogBoxHandler(
								LDialogBox*		inWindow,
								LCommander*		inSuper);

	virtual				~StDialogBoxHandler();

	virtual MessageT	DoDialog();

	LDialogBox*			GetDialog() const	{ return mDialog; }

	void				SetSleepTime(
								UInt32			inSleepTime)
							{
								mSleepTime = inSleepTime;
							}

	virtual Boolean		AllowSubRemoval(
								LCommander*		inSub);

	virtual void		FindCommandStatus(
								CommandT		inCommand,
								Boolean&		outEnabled,
								Boolean&		outUsesMark,
								UInt16&			outMark,
								Str255			outName);

	virtual void		ListenToMessage(
								MessageT		inMessage,
								void*			ioParam);

protected:
	LDialogBox *	mDialog;
	MessageT		mMessage;
	UInt32			mSleepTime;

	void				InitDialogHandler();
};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif