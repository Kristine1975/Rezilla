// ===========================================================================
// UHexFilters.h					
//                       Created: 2003-05-07 18:35:01
//             Last modification: 2003-05-08 08:10:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// �� Copyright: Bernard Desgraupes 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_UHexFilters
#define _H_UHexFilters
#pragma once

#include <PP_Prefix.h>
#include <UKeyFilters.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------

class UHexFilters {

public:
	static EKeyStatus	HexadecimalField(const EventRecord	&inKeyEvent);

	static EKeyStatus	HexadecimalField(
								TEHandle		inMacTEH,
								UInt16			inKeyCode,
								UInt16			&ioCharCode,
								EventModifiers	inModifiers);

	static EKeyStatus	IntegerRangeField(const EventRecord	&inKeyEvent);

	static EKeyStatus	IntegerRangeField(
								TEHandle		inMacTEH,
								UInt16			inKeyCode,
								UInt16			&ioCharCode,
								EventModifiers	inModifiers);

	static bool			IsUpDownArrowKey(UInt16 inKey);
	static bool			IsLeftRightArrowKey(UInt16 inKey);

	static bool			IsHexadecimalChar(UInt16 inChar);

	static bool			IsIntegerRangeChar(UInt16 inChar);
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

