// ===========================================================================
// CEditorDoc.h				
// 
//                       Created: 2004-02-23 17:57:59
//             Last modification: 2004-06-11 10:47:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>
#include "UResources.h"

class	CRezMapTable;
class	CRezObj;


class CEditorDoc : public LDocument, public LListener {
public:
					CEditorDoc(LCommander* inSuper, 
							   CRezMapTable* inSuperMap, 
							   CRezObj* inRezObj,
							   Boolean inReadOnly);
					~CEditorDoc();

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);
	
	virtual Boolean	IsModified();
	
	virtual Boolean	AllowSubRemoval( LCommander* inSub );
	virtual SInt16	AskSaveChanges( bool inQuitting );

	virtual void	AttemptClose( Boolean inRecordIt );
	virtual void	DoSaveChanges();

	CRezObj *		GetRezObj() { return mRezObj; }
		
	Boolean			GetReadOnlyDoc() { return mReadOnlyDoc;}
	void			SetReadOnlyDoc(Boolean inReadOnlyDoc) {mReadOnlyDoc = inReadOnlyDoc;}

protected:
	CRezObj *				mRezObj;
	CRezMapTable *			mOwnerRezMapTable;
	short					mRefNum;
	Boolean					mReadOnlyDoc;

	virtual Handle	GetModifiedResource();
	virtual void	NameNewEditorDoc();
	void			Register();
	void			Unregister();
};


