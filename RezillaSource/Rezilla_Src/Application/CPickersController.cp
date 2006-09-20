// ===========================================================================
// CPickersController.cp					
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-09-20 10:20:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickersController.h"
#include "TPickerDoc.h"
#include "TPickerView.h"
#include "CRezillaApp.h"
#include "CIconFamily_PickerStamp.h"
#include "Ccicn_PickerStamp.h"
#include "CICON_PickerStamp.h"
#include "CSICN_PickerStamp.h"
#include "CMENU_PickerStamp.h"
#include "CSTRx_PickerStamp.h"
#include "CTEXT_PickerStamp.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezTypeItem.h"
#include "CRezType.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"



// ---------------------------------------------------------------------------
//   CPickersController					Constructor				  [public]
// ---------------------------------------------------------------------------

CPickersController::CPickersController()
{
}


// ---------------------------------------------------------------------------
//     ~CPickersController					Destructor				  [public]
// ---------------------------------------------------------------------------

CPickersController::~CPickersController()
{	
}


// ---------------------------------------------------------------------------
//   HasPickerForType												[public]
// ---------------------------------------------------------------------------

Boolean
CPickersController::HasPickerForType(ResType inType)
{
	Boolean result = false;
	
	switch (inType) {
		case 'TEXT':
		case 'MENU':
		case 'STR#':
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
		case 'cicn':
		case 'ICON':
		case 'SICN':
		case 'ICN#':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		result = true;
		break;
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//   InvokeCustomPicker											[public]
// ---------------------------------------------------------------------------
// 		case 'CURS':
// 		case 'ICON':
// 		case 'PAT ':
// 		case 'PAT#':
// 		case 'SICN':
// 		case 'cicn':
// 		case 'crsr':
// 		case 'ppat':

void
CPickersController::InvokeCustomPicker(CRezMapDoc* inRezMapDoc, 
									   CRezTypeItem * inRezTypeItem)
{
	CRezMapTable *	inSuperMap = inRezMapDoc->GetRezMapWindow()->GetRezMapTable();
	Boolean			inReadOnly = inRezMapDoc->IsReadOnly();
	ResType			theType = inRezTypeItem->GetRezType()->GetType();
	
	switch (theType) {

		case 'TEXT':
		  new TPickerDoc<CTEXT_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;

		
		case 'PICT':
// 		  new TPickerDoc<CPICT_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'MENU':
		  new TPickerDoc<CMENU_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'STR#':
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
		  new TPickerDoc<CSTRx_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'cicn':
		  new TPickerDoc<Ccicn_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'ICON':
		  new TPickerDoc<CICON_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'SICN':
		  new TPickerDoc<CSICN_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'ICN#':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
// 		new CIcon_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		  new TPickerDoc<CIconFamily_PickerStamp>( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
	  break;
	  
	}
}



PP_End_Namespace_PowerPlant

