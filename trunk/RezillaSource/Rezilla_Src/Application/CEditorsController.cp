// ===========================================================================
// CEditorsController.cp					
// 
//                       Created: 2004-06-11 10:48:38
//             Last modification: 2004-11-08 15:35:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CEditorsController.h"
#include "CTEXT_EditorDoc.h"
#include "CTemplatesController.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezObj.h"
#include "CRezType.h"
#include "CRezTypeItem.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// // Standard headers
// #include <string.h>


CFPropertyListRef	CEditorsController::sAsTypeDictionary = NULL;


// ---------------------------------------------------------------------------
//	� CEditorsController					Constructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::CEditorsController()
{
	BuildAsTypeDictionary();
}


// ---------------------------------------------------------------------------
//	� ~CEditorsController					Destructor				  [public]
// ---------------------------------------------------------------------------

CEditorsController::~CEditorsController()
{	
}


// ---------------------------------------------------------------------------
//	� BuildAsTypeDictionary											[public]
// ---------------------------------------------------------------------------
// Create a CFDictionary whose keys are resource types and whose values are a
// type having an identical structure. This concerns resource types whose type
// is defined with a 'type as' statement in the Rez include files (with .r
// extension).

void
CEditorsController::BuildAsTypeDictionary()
{
	CFBundleRef 			mainBundleRef;
	CFURLRef 				typeasURL;
	OSErr	  				error = noErr;
	
	// Locate the Templates resource file inside the main bundle
	mainBundleRef = NULL;
	typeasURL = NULL;
	
	mainBundleRef = CFBundleGetMainBundle();
	
	typeasURL = CFBundleCopyResourceURL(mainBundleRef, CFSTR("TypeAs"), CFSTR("plist"), NULL);
	
	if (typeasURL) {
		CFDataRef		xmlRef;
		Boolean			status;
		
		// Read the XML file
		status = CFURLCreateDataAndPropertiesFromResource(kCFAllocatorDefault, typeasURL, 
														  &xmlRef, NULL, NULL, NULL);
		if (status) {
			CFStringRef errorString;
			// Reconstitute the dictionary using the XML data
			sAsTypeDictionary = CFPropertyListCreateFromXMLData(kCFAllocatorDefault, xmlRef, 
													   kCFPropertyListImmutable, &errorString);
			
			if (sAsTypeDictionary == NULL) CFShow(errorString);
			
			// Release the XML data
			CFRelease(xmlRef);
		}
		
		CFRelease(typeasURL);
	}	
}


// ---------------------------------------------------------------------------
//	� FindSubstitutionType											[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::FindSubstitutionType(ResType inType, ResType * outType)
{
	Boolean result = false;
	
	if (sAsTypeDictionary != NULL) {
		if ( CFGetTypeID(sAsTypeDictionary) == CFDictionaryGetTypeID() ) {
			Str255		theString;
			CFStringRef	inTypeRef, outTypeRef;
			
			UMiscUtils::OSTypeToPString(inType, theString);	
			inTypeRef = CFStringCreateWithPascalString(NULL, theString, kCFStringEncodingMacRoman);
			
			if (inTypeRef) {
				result = CFDictionaryGetValueIfPresent( (CFDictionaryRef) sAsTypeDictionary, 
													   inTypeRef, (const void**) &outTypeRef);
				
				if (result) {
					result = CFStringGetPascalString(outTypeRef, theString, 
													 sizeof(theString), kCFStringEncodingMacRoman);
					// Caveat: outTypeRef must not be released
					
					if (result) {
						UMiscUtils::PStringToOSType(theString, *outType);	
					} 
				}
				CFRelease(inTypeRef);
			}
		}
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  � HasEditorForType												[public]
// ---------------------------------------------------------------------------

Boolean
CEditorsController::HasEditorForType(ResType inType, ResType * substType)
{
	Boolean result = false;
	
	switch (inType) {
		case 'TEXT':
		case 'styl':
		case 'thng':
		case 'thga':
		result = true;
		break;
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//  � InvokeCustomEditor											[public]
// ---------------------------------------------------------------------------

void
CEditorsController::InvokeCustomEditor(CRezMapDoc* inRezMapDoc, 
									   CRezObjItem * inRezObjItem)
{
	CRezMapTable *	inSuperMap = inRezMapDoc->GetRezMapWindow()->GetRezMapTable();
	CRezObj *		inRezObj = inRezObjItem->GetRezObj();
	Boolean			inReadOnly = inRezMapDoc->IsReadOnly();
	ResType			theType = inRezObj->GetType();
	Size			theSize;
	
	switch (theType) {
		case 'styl':
		// Check if there is an associated TEXT resource
		CRezObj * textRezObj = NULL;
		OpenOrCreateWithTypeAndID(inSuperMap, 'TEXT', inRezObj->GetID(), &textRezObj);
		new CTEXT_EditorDoc( (LCommander *) inRezMapDoc, inSuperMap, textRezObj, 'TEXT', inReadOnly);
		break;

		case 'TEXT':
		  new CTEXT_EditorDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezObj, 'TEXT', inReadOnly);
		break;
		
		case 'thng':
		// A 'thng' resource has three different formats but contains 
		// no field to determine its version: 
		// - version 0 had fixed a size of 44 bytes,
		// - version 1 adds 10 bytes, a 4 bytes count and a list of 12 bytes items. 
		//      Size = 44 + 10 + 2 + 12*n
		// - version 2 adds 6 bytes. Size = 44 + 12*n + 2 + 6
		theSize = inRezObjItem->GetRezObj()->GetSize();
		if (theSize == 44) {
			theType = 'thn0';
		} else if ( ((theSize - 58) % 12) == 0 ) {
			theType = 'thn1';
		} 
		inRezMapDoc->TryEdit(inRezObjItem, cmd_TmplEditAsRez, theType);
		break;
		
		case 'thga':
		// A 'thga' resource has two different formats with fixed size.
		// Initial version had 64 bytes, current version has 72 bytes
		theSize = inRezObjItem->GetRezObj()->GetSize();
		if (theSize == 64) {
			theType = 'thg0';
		} 
		inRezMapDoc->TryEdit(inRezObjItem, cmd_TmplEditAsRez, theType);
		break;
		
	}
}


// ---------------------------------------------------------------------------
//  � OpenOrCreateWithTypeAndID											[public]
// ---------------------------------------------------------------------------

OSErr
CEditorsController::OpenOrCreateWithTypeAndID(CRezMapTable* inSuperMap, ResType inType, 
									  short inID, CRezObj** outRezObj)
{
	OSErr result = noErr;
	
	CRezTypeItem * theRezTypeItem = inSuperMap->GetRezTypeItem(inType);
	CRezObjItem * theRezObjItem;
	
	if (theRezTypeItem != nil) {
		if ( ! theRezTypeItem->IsExpanded() ) {
			theRezTypeItem->Expand();
		} 
	} 
	
	if (theRezTypeItem == nil || ! theRezTypeItem->ExistsItemForID(inID, theRezObjItem) ) {
		// The CreateNewRes function will take care of creating the RezTypeItem
		theRezObjItem = inSuperMap->GetOwnerDoc()->CreateNewRes(inType, inID, NULL, 0);
	}

	*outRezObj = theRezObjItem->GetRezObj();
	
	return (outRezObj == NULL);
}
 

// ---------------------------------------------------------------------------
//  � RegisterEditor												[public]
// ---------------------------------------------------------------------------

OSErr
CEditorsController::RegisterEditor()
{
	OSErr error = noErr;
	
	return error;
}





PP_End_Namespace_PowerPlant


