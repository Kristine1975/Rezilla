// ===========================================================================
// CRezCompare.h					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2004-03-02 12:42:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezCompare
#define _H_CRezCompare
#pragma once

class CRezMap;
class CRezType;
class CCompResultWindow;


// -------------------------------------------------------------------------------------------------

// Small class to wrap around (type, id) pairs
class CRezTypId {
public:
	CRezTypId(ResType inType, short inID) {
		mType = inType;
		mID = inID;
	}
	~CRezTypId();

	ResType	mType;
	short	mID;
};


// -------------------------------------------------------------------------------------------------

class CRezCompare : public LCommander {
	
public:
	enum {
		list_OnlyInOld,
		list_OnlyInNew,
		list_Differing
	};
	
				CRezCompare(LCommander* inSuper);
				CRezCompare(LCommander* inSuper,
							CRezMap * inOldMap, 
							CRezMap * inNewMap);
				CRezCompare(LCommander* inSuper,
							FSSpec& inOldFileSpec, 
							FSSpec& inNewFileSpec);
				~CRezCompare();

		virtual Boolean		AllowSubRemoval( LCommander* inSub );

		OSErr			RunRezCompareDialog();
		void			DoCompareRezMaps();
		void			CompareTypes(ResType inType);
		void			CompareTwoResources(CRezType * inOldRezType, 
											CRezType * inNewRezType, 
											short inID,
											SInt16 * outCompResult);

		Boolean			HasDifferences();
		void			DisplayResults();
		
		ConstStringPtr		GetOldPath() const;
		ConstStringPtr		GetNewPath() const;

		virtual TArray<CRezTypId*>*		GetOnlyInOldList() { return &mOnlyInOldList;}
		virtual TArray<CRezTypId*>*		GetOnlyInNewList() { return &mOnlyInNewList;}
		virtual TArray<CRezTypId*>*		GetDifferingList() { return &mDifferingList;}

		virtual CRezMap*		GetOldMap() {return mOldMap;}
		virtual CRezMap*		GetNewMap() {return mNewMap;}
		
		static Boolean		GetIgnoreNames() { return sIgnoreNames;}
        static void			SetIgnoreNames(Boolean inIgnoreNames) {sIgnoreNames = inIgnoreNames;}

		static Boolean		GetIgnoreAttrs() { return sIgnoreAttrs;}
		static void			SetIgnoreAttrs(Boolean inIgnoreAttrs) {sIgnoreAttrs = inIgnoreAttrs;}

		static FSSpec		sOldFSSpec;
		static FSSpec		sNewFSSpec;
		static Boolean		sIgnoreNames;
		static Boolean		sIgnoreAttrs;
		static Boolean		sIgnoreData;
		
protected:
		CCompResultWindow*	mResultWindow;
		CRezMap * 			mOldMap;
		CRezMap * 			mNewMap;
		TArray<CRezTypId *>	mOnlyInOldList;
		TArray<CRezTypId *>	mOnlyInNewList;
		TArray<CRezTypId *>	mDifferingList;
		TArray<CRezTypId *>	mIdenticalList;
		Str255				mOldPath;
		Str255				mNewPath;

		void		AddTypeToArray(ResType inType, SInt16 inWhichList);
		void		AddResourceToArray(ResType inType, short inID, SInt16 inWhichList);
};


// ---------------------------------------------------------------------------
//	� GetOldPath										 [inline] [public]
// ---------------------------------------------------------------------------

inline ConstStringPtr
CRezCompare::GetOldPath() const
{
	return mOldPath;
}


// ---------------------------------------------------------------------------
//	� GetNewPath										 [inline] [public]
// ---------------------------------------------------------------------------

inline ConstStringPtr
CRezCompare::GetNewPath() const
{
	return mNewPath;
}



#endif