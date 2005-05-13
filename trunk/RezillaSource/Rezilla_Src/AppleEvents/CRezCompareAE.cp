// ===========================================================================
// CRezCompareAE.cp
// 
//                       Created: 2005-05-12 07:51:22
//             Last modification: 2005-05-12 10:22:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//  AppleEvent Object Model Support. These methods are part of the CRezCompare 
//  class (inheriting from LModelObject).

#include "CRezCompare.h"
#include "CRezillaApp.h"
#include "CCompResultWindow.h"
// #include "CRezMap.h"
// #include "UResources.h"
#include "RezillaConstants.h"

#include <LCommander.h>


// ---------------------------------------------------------------------------
//	 MakeSelfSpecifier
// ---------------------------------------------------------------------------
//	Make an Object Specifier for a RezMaps comparison object

void
CRezCompare::MakeSelfSpecifier(
	AEDesc&	inSuperSpecifier,
	AEDesc&	outSelfSpecifier) const
{
		OSErr			err;
		StAEDescriptor	keyData;
		SInt32			position = GetAEPosition(this);
		
		keyData.Assign(position);

		// Make ospec for the rezmap
		err = ::CreateObjSpecifier(rzom_cMapsComp, &inSuperSpecifier, formUniqueID,
										keyData, false, &outSelfSpecifier);
		ThrowIfOSErr_(err);

}



// ---------------------------------------------------------------------------
//	 GetAEProperty
// ---------------------------------------------------------------------------
//	Return a descriptor for the specified Property
//	rzom_pCompCriteria		= 'pCRI';	// Comparison criteria
// 	rzom_pIgnoreName		= 'IgnN';	// IgnoreNameDiff
// 	rzom_pIgnoreAttr		= 'IgnA';	// IgnoreAttrDiff
// 	rzom_pIgnoreData		= 'IgnD';	// IgnoreDataDiff
// 	rzom_pOnlyInOld			= 'OldR';	// Only in old map resources (list)
// 	rzom_pOnlyInNew			= 'NewR';	// Only in new map resources (list)
// 	rzom_pDiffering			= 'Diff';	// In both but different (list)
// 	rzom_pIdentical			= 'Iden';	// In both and identical (list)

void
CRezCompare::GetAEProperty(
	DescType		inProperty,
	const AEDesc&	inRequestedType,
	AEDesc&			outPropertyDesc) const
{
	OSErr		error = noErr;
	
	switch (inProperty) {
		
		case rzom_pCompCriteria:
		error = ::AECreateDesc(typeAERecord, NULL, 0, &outPropertyDesc);
		ThrowIfOSErr_(error);
		
		error = ::AEPutParamPtr(&outPropertyDesc, rzom_pIgnoreName, typeBoolean,
						&mIgnoreNames, sizeof(Boolean));
		ThrowIfOSErr_(error);
		error = ::AEPutParamPtr(&outPropertyDesc, rzom_pIgnoreAttr, typeBoolean,
						&mIgnoreAttrs, sizeof(Boolean));
		ThrowIfOSErr_(error);
		error = ::AEPutParamPtr(&outPropertyDesc, rzom_pIgnoreData, typeBoolean,
						&mIgnoreData, sizeof(Boolean));
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIgnoreName:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreNames,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIgnoreAttr:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreAttrs,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pIgnoreData:
		error = ::AECreateDesc(typeBoolean, (Ptr) &mIgnoreData,
									sizeof(Boolean), &outPropertyDesc);
		ThrowIfOSErr_(error);
		break;

		
		case rzom_pOnlyInOld:
		break;

		
		case rzom_pOnlyInNew:
		break;

		
		case rzom_pDiffering:
		break;

		
		case rzom_pIdentical:
		break;

		
		default:
		LModelObject::GetAEProperty(inProperty, inRequestedType,
									outPropertyDesc);
		break;
	}
}


// // ---------------------------------------------------------------------------
// //	 GetAERezMapAttribute
// // ---------------------------------------------------------------------------
// 
// void
// CRezCompare::GetAERezMapAttribute(
// 	short		inFlag,
// 	AEDesc&		outPropertyDesc) const
// {
// 	Boolean		attrIsSet;
// 	short		theAttrs;
// 	OSErr		error;
// 	
// 	GetMapAttributes(theAttrs);
// 	attrIsSet = ((theAttrs & inFlag) > 0);
// 	
// 	error = ::AECreateDesc(typeBoolean, (Ptr) &attrIsSet,
// 								sizeof(Boolean), &outPropertyDesc);
// 	ThrowIfOSErr_(error);
// }
// 
// 
// // ---------------------------------------------------------------------------
// //	 SetAERezMapAttribute
// // ---------------------------------------------------------------------------
// 
// void
// CRezCompare::SetAERezMapAttribute(const AEDesc& inValue, short inFlag)
// {
// 	short		theAttrs;
// 	Boolean		setIt;
// 	
// 	UExtractFromAEDesc::TheBoolean(inValue, setIt);
// 	GetMapAttributes(theAttrs);
// 
// 	if (setIt) {
// 		theAttrs &= inFlag;
// 	} else {
// 		theAttrs &= ~inFlag;
// 	}
// 	SetMapAttributes(theAttrs);
// }


// ---------------------------------------------------------------------------
//	 AEPropertyExists
// ---------------------------------------------------------------------------

bool
CRezCompare::AEPropertyExists(
	DescType	inProperty) const
{
	bool	exists = false;

	switch (inProperty) {

		case rzom_pCompCriteria:
		case rzom_pIgnoreName:
		case rzom_pIgnoreAttr:
		case rzom_pIgnoreData:
		case rzom_pOnlyInOld:
		case rzom_pOnlyInNew:
		case rzom_pDiffering:
		case rzom_pIdentical:
			exists = true;
			break;

		default:
			exists = LModelObject::AEPropertyExists(inProperty);
			break;
	}

	return exists;
}


// ---------------------------------------------------------------------------
//	� GetAEPosition
// ---------------------------------------------------------------------------

SInt32
CRezCompare::GetAEPosition(const CRezCompare * inComp) {
	
	WindowPtr	windowP = ::GetWindowList();
	LWindow*	ppWindow = nil;
	CCompResultWindow * compWindow;
	SInt32		position = 0, count = 0;
	
	while (windowP) {
		ppWindow = LWindow::FetchWindowObject(windowP);
		
		if (ppWindow != nil && ppWindow->GetModelKind() == rzom_cCompWindow) {
			count++;
			compWindow = dynamic_cast<CCompResultWindow*>(ppWindow);

			if (compWindow && compWindow->GetRezCompare() == inComp) {
				position = count;
				break;
			} 
		} 
		windowP = MacGetNextWindow(windowP);
	}
	
	if (position == 0) {
		ThrowOSErr_(errAENoSuchObject);
	}
	
	return position;
}
