// ===========================================================================
// CCompResultWindow.h				
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-03-18 19:23:27
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>
#include <LListener.h>

class CRezObj;
class LScrollBar;
class CRezCompare;
class CRezTypId;
class CBiDataWE;
class CBroadcasterTableView;

enum
{	
	compare_oldhexpane = 0,
	compare_newhexpane
};

// 'RcrW': Rez comparison result window

class CCompResultWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'RcrW' };

	enum {	
		compare_undefinedTbl = 0,
		compare_onlyinOldTbl,
		compare_onlyinNewTbl,
		compare_differTbl
	};

	enum {	
		compare_displayAsHex = 0,
		compare_displayAsTxt
	};

							CCompResultWindow();
							CCompResultWindow( const SWindowInfo &inWindowInfo );
							CCompResultWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CCompResultWindow( LStream *inStream );
							~CCompResultWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	void			DoClose();

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	Boolean			IsDirty();
	
	void			FillTableView( TArray<CRezTypId *> inList, SInt16 inWhichList);
	
protected:
	CRezCompare *			mRezCompare;
	CBiDataWE *				mOldRezDataWE;
	CBiDataWE *				mNewRezDataWE;
	Handle					mOldData;
	Handle					mNewData;
	LScrollBar *			mScroller;
	CBroadcasterTableView *	mOnlyOldTable;
	CBroadcasterTableView *	mOnlyNewTable;
	CBroadcasterTableView *	mDifferTable;
	SInt16					mActiveTable;
	SInt16					mDisplayDataFormat;
	
	void				NameNewCompWindow();
	virtual void		SetMaxScrollerValue();
	SInt32				LineCount();
	SInt32				BytesPerLineCount();
	SInt32				BytesPerPaneCount();
	virtual void		FinishCreateSelf();
	void				InsertContentsFromLine(SInt32 inFromLine);
	void				EraseHexPanes();
};


