// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-07-02 06:44:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "RezillaConstants.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
/* #include <LActiveScroller.h> */

class CTmplEditorDoc;
class CRezObj;
class LStaticText;
class LScrollerView;


enum {
	tmpl_titleYesNo = 0,
	tmpl_titleOnOff
};


class CTmplListItemView;


class CTmplEditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'TmpW' };

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

	void			ParseDataWithTemplate(Handle inHandle);
	Handle			RetrieveDataWithTemplate();
	
	Boolean			IsDirty();
		
	void			InstallReadOnlyIcon();

	void			AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta);
	
	LView*			GetContentsView() const { return mContentsView;}
	
	LHandleStream*		GetOutStream() { return mOutStream;}


protected:
	LView *				mContentsView;
	LScrollerView *		mContentsScroller;
	SInt32				mYCoord;
	PaneIDT				mCurrentID;
	PaneIDT				mLastID;
	SInt32				mIndent;
	short				mItemsCount;
	SPaneInfo			mEditPaneInfo,
						mStaticPaneInfo,
						mRgvPaneInfo,
						mRadioPaneInfo,
						mCheckPaneInfo,
						mRectLabelInfo,
						mRectPaneInfo,
						mScrollPaneInfo,
						mTgbPaneInfo,
						mWastePaneInfo,
						mPushPaneInfo,
						mListItemInfo,
						mSeparatorPaneInfo,
						mBevelPaneInfo;
	LHandleStream *		mTemplateStream;
	LHandleStream *		mRezStream;
	LHandleStream *		mOutStream;
	ResIDT				mLeftLabelTraitsID,
						mRightLabelTraitsID,
						mHeaderTraitsID,
						mEditTraitsID;

	virtual void	FinishCreateSelf();

	void			CreateTemplateStream();
		
private:
	OSErr			ParseDataForType(ResType inType, Str255 inLabelString, LView * inContainer);
	OSErr			RetrieveDataForType(ResType inType);
	
	void			ParseList(SInt32 inStartMark, 
							  ResType inType, 
							  SInt32 inCount, 
							  LView * inContainer);

	void			RetrieveList(SInt32 inStartMark, 
								 ResType inType, 
								 SInt32 inCount);

	Boolean			EndOfList(ResType inType);
	
	void			AddStaticField(Str255 inLabel, 
								   LView * inContainer, 
								   ResIDT inTextTraitsID = Txtr_GenevaTenBoldUlRight);
	
	void			AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer);
	
	void			AddBooleanField(Boolean inValue,
									OSType inType,
									SInt16 inTitleType, 
									LView * inContainer);
	
	void			AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer);
	
	void			AddWasteField(OSType inType, 
								  LView * inContainer);
	
	void			AddHexDumpField(OSType inType, 
									LView * inContainer);
	
	void			AddRectField(SInt16 inTop, 
									SInt16 inLeft, 
									SInt16 inBottom, 
									SInt16 inRight, 
									OSType inType,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter, 
								 	LView * inContainer);

	void			AddListHeaderField(OSType inType, 
								  Str255 inLabel, 
								  short inCount, 
								  Str255 inCountLabel, LView * inContainer);
	
	CTmplListItemView *	AddListItemView(CTmplListItemView * inPrevListItemView, LView * inContainer);
	
	void				AddSeparatorLine(LView * inContainer);

	void				AddPopupField(ResType inType, 
									  Str255 inLabel, 
									  LView * inContainer);
	
	ExceptionCode	AlignBytesRead(UInt8 inStep);
	
	ExceptionCode	AlignBytesWrite(UInt8 inStep);
	
	void			DoParseWithTemplate(SInt32 inRecursionMark, Boolean inDrawControls, LView * inContainer);
	void			DoRetrieveWithTemplate(SInt32 inRecursionMark);
	
	void			RenumberSubPanes(LView * inView, 
									 PaneIDT inOldLastID, 
									 PaneIDT inNewFirstID, 
									 Boolean adding);
	
	void			RecalcPositions(LView * inView, 
									SInt32 inVertPos, 
									SInt32 inPosDelta);
};


