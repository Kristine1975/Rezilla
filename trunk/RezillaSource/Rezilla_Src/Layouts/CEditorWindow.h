// ===========================================================================
// CEditorWindow.h				
// 
//                       Created: 2004-06-10 14:44:33
//             Last modification: 2004-06-12 08:50:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "UResources.h"

#include <LWindow.h>

class CEditorDoc;
class CRezObj;


class CEditorWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'EdiW' };

							CEditorWindow();
							CEditorWindow( const SWindowInfo &inWindowInfo );
							CEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CEditorWindow( LStream *inStream );
							~CEditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	DoClose();

// 	virtual void	InstallContentsFromLine(SInt32 inFromLine);
	
	Boolean			IsDirty();
	
	void			InstallReadOnlyIcon();

	virtual CEditorDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CEditorDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

protected:
	CEditorDoc *		mOwnerDoc;
	
	virtual void		FinishCreateSelf();
};


