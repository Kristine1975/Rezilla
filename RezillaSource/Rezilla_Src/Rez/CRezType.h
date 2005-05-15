// ===========================================================================
// CRezType.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2005-05-14 06:58:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezType
#define _H_CRezType
#pragma once

#include <LModelObject.h>

class CRezMap;
class CRezObj;


class CRezType : public LModelObject {

public:
				CRezType(ResType inResType, 
						 CRezMap * inOwnerMap);
				~CRezType();
				
	OSErr	CountResources(short & outCount) const;
	
	OSErr	GetWithID(short inID, Handle & outHandle) const;
	OSErr	GetWithName(ConstStr255Param inName, Handle & outHandle) const;
	
	OSErr	GetAllResources( TArray<Handle>* & outArray );
	OSErr	GetAllRezIDs( TArray<short>* & outArray );

	CRezMap*		GetOwnerMap() const { return mOwnerMap;}
	void			SetOwnerMap(CRezMap* theOwnerMap) {mOwnerMap = theOwnerMap;}

	ResType			GetType() { return mType;}
	void			SetType(ResType theType) {mType = theType;}

	OSErr			GetResourceAtIndex(short inIdx, 
									   Handle & outHandle, 
									   Boolean loadIt = false) const;
	OSErr			GetNameAtIndex(short inIdx, Str255 & outName);
	
	// AppleEvents
	virtual void	MakeSelfSpecifier(
								AEDesc&			inSuperSpecifier,
								AEDesc&			outSelfSpecifier) const;

	virtual void	GetAEProperty(
								DescType		inProperty,
								const AEDesc&	inRequestedType,
								AEDesc&			outPropertyDesc) const;

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual StringPtr	GetModelName( Str255 outModelName ) const;

	virtual SInt32		CountSubModels( DescType inModelID ) const;

	virtual void		GetSubModelByPosition(
								DescType		inModelID,
								SInt32			inPosition,
								AEDesc&			outToken) const;

	virtual void		GetSubModelByName(
								DescType		inModelID,
								Str255			inName,
								AEDesc&			outToken) const;

	virtual void		GetSubModelByUniqueID(
								DescType		inModelID,
								const AEDesc	&inKeyData,
								AEDesc			&outToken) const;

	CRezObj *			GetOrCreateRezObjModel(Handle inHandle) const;
	
	TArray<CRezObj*>&	GetRezObjModels() { return mRezObjModels; }
								
	virtual void		HandleAppleEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
								SInt32				inAENumber);
									
	void				HandleResourceEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
								CRezObj *			inRezObj,
								long				inAENumber);
	
	virtual void		HandleEditEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
								short				inID);
									
	virtual void		HandleDeleteResourceEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
							    CRezObj *			inRezObj);
									
	virtual void		HandleDeleteTypeEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult);
									
protected:
		ResType				mType;
		CRezMap * 			mOwnerMap;
		TArray<CRezObj*>	mRezObjModels;

private:

};


#endif
