// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-14 12:17:10
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

class CTmplEditorDoc;
class CRezObj;


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

	void			ParseWithTemplate(Handle inHandle);
	Handle			ReadValues();
	
	Boolean			IsDirty();
		
	void			InstallReadOnlyIcon();

	void				CreateTemplateStream();
	
	virtual SInt32		GetCurrFirstID() { return mCurrFirstID;}
	void				SetCurrFirstID(SInt32 theCurrFirstLine) {mCurrFirstID = theCurrFirstLine ;}

// 	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
// 	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

protected:
	LView *				mContentsView;
	SInt32				mCurrFirstID;
	SInt32				mCurrentID;
	SInt32				mItemsCount;
	SInt32				mIndent;
	SInt32				mXCoord;
	SInt32				mYCoord;
	SPaneInfo			mEditPaneInfo;
	SPaneInfo			mStaticPaneInfo;
	LHandleStream		mTemplateStream;
	LHandleStream		mRezStream;
	ResIDT				mLabelTraitsID;
	ResIDT				mEditTraitsID;
	
	virtual void	FinishCreateSelf();

private:
	OSErr			ParseDataForType(ResType inType, Str255 inString);
	void			AddStaticField(Str255 inLabel);
	void			AddEditField(Str255 inValue, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes = 0,
								TEKeyFilterFunc inKeyFilter = NULL);
	void			AddWasteField(OSType inType);
	void			AddRectField(SInt16 inTop, 
									SInt16 inLeft, 
									SInt16 inBottom, 
									SInt16 inRight, 
									OSType inType,
									MessageT inMessage,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter);
// 	void			AdvanceCounters();
	ExceptionCode	AlignBytes(UInt8 inStep);

};


