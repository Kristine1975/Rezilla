// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-15 20:44:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
#include <LActiveScroller.h>

class CTmplEditorDoc;
class CRezObj;
class CTmplList;

enum {
	tmpl_titleYesNo = 0,
	tmpl_titleOnOff,
	tmpl_flushRight = 0,
	tmpl_flushLeft
};

enum {
	tmpl_listLSTZ = 0,		// Zero List
	tmpl_listLSTC,			// Count List
	tmpl_listLSTB			// Plain List
};


class CTmplEditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'TmpW' };
	friend class CTmplList;

							CTmplEditorWindow();
							CTmplEditorWindow( const SWindowInfo &inWindowInfo );
							CTmplEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CTmplEditorWindow( LStream *inStream );
							~CTmplEditorWindow();

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

	void			ParseWithTemplate(Handle inHandle);
	Handle			ReadValues();
	
	Boolean			IsDirty();
		
	void			InstallReadOnlyIcon();

	void				CreateTemplateStream();
	
// 	void				SetTemplateMarker(SInt32 inPos) { mTemplateStream->SetMarker(inPos, streamFrom_Start); }
	
	virtual SInt32		GetCurrFirstID() { return mCurrFirstID;}
	void				SetCurrFirstID(SInt32 theCurrFirstLine) {mCurrFirstID = theCurrFirstLine ;}

	LView*		GetContentsView() const { return mContentsView;}

// 	static LHandleStream*		GetTemplateStream() { return mTemplateStream;}

// 	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
// 	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

protected:
	LView *				mContentsView;
	LActiveScroller *	mContentsScroller;
	SInt32				mCurrFirstID;
	SInt32				mCurrentID;
	SInt32				mItemsCount;
	SInt32				mIndent;
	SInt32				mXCoord;
	SInt32				mYCoord;
	SInt16				mListType;
	short				mListCount;
	SPaneInfo			mEditPaneInfo;
	SPaneInfo			mStaticPaneInfo;
	SPaneInfo			mRgvPaneInfo;
	SPaneInfo			mRadioPaneInfo;
	SPaneInfo			mRectLabelInfo;
	SPaneInfo			mRectPaneInfo;
	SPaneInfo			mScrollPaneInfo;
	SPaneInfo			mTgbPaneInfo;
	SPaneInfo			mWastePaneInfo;
	LHandleStream *		mTemplateStream;
	LHandleStream *		mRezStream;
	ResIDT				mLeftLabelTraitsID;
	ResIDT				mRightLabelTraitsID;
	ResIDT				mEditTraitsID;

	virtual void	FinishCreateSelf();

private:
	OSErr			ParseDataForType(ResType inType, Str255 inString);
	
	void			AddStaticField(Str255 inLabel, 
								   SInt16 inJustification = tmpl_flushRight);
	
	void			AddEditField(Str255 inValue, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes = 0,
								TEKeyFilterFunc inKeyFilter = NULL);
	
	void			AddBooleanControls(Boolean inValue,
									  OSType inType,
									  SInt16 inTitleType);
	
	void			AddWasteField(OSType inType);
	
	void			AddHexDumpField(OSType inType);
	
	void			AddRectField(SInt16 inTop, 
									SInt16 inLeft, 
									SInt16 inBottom, 
									SInt16 inRight, 
									OSType inType,
									MessageT inMessage,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter);

	ExceptionCode	AlignBytes(UInt8 inStep);
	
	void			DoParseTemplate();
	
};


// Utility class to handle iteration lists
// =======================================

class CTmplList {
public:
	friend class CTmplEditorWindow;

							CTmplList(SInt32 inStartPos,
									  SInt32 inEndPos,
									  LHandleStream * inTmplStream,
									  SInt16 inListType,
									  SInt8 inNestingLevel = 1);
							~CTmplList();

	virtual SInt32		GetStartPos() { return mStartPos;}
	void				SetStartPos(SInt32 inStartPos) {mStartPos = inStartPos;}

	virtual SInt32		GetEndPos() { return mEndPos;}
	void				SetEndPos(SInt32 inEndPos) {mEndPos = inEndPos;}

	virtual SInt32		GetCount() { return mCount;}
	void				SetCount(SInt32 inCount) {mCount = inCount;}

	virtual SInt8		GetNestingLevel() { return mNestingLevel;}
	void				SetNestingLevel(SInt8 inNestingLevel) {mNestingLevel = inNestingLevel;}

protected:
	SInt32			mStartPos;
	SInt32			mEndPos;
	SInt32			mCount;
	SInt16			mListType;
	SInt8			mNestingLevel;  // level=1 means a first level list
	LHandleStream *	mTmplStream;
	CTmplList *		mParent;
	
	OSErr		Process();
	OSErr		ProcessFromPos(SInt32 inPos);
	

};

