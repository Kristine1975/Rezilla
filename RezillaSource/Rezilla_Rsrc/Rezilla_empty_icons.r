// ===========================================================================
// File: "Rezilla_empty_icons.r"
//                        Created: 2005-02-14 09:10:24
//              Last modification: 2005-03-01 12:11:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Empty icons used by the Bitmap editor when creating new bitmap resources.

#ifdef crsr_RezTemplateVersion
#undef crsr_RezTemplateVersion
#endif
#define crsr_RezTemplateVersion 0

#ifdef ppat_RezTemplateVersion
#undef ppat_RezTemplateVersion
#endif
#define ppat_RezTemplateVersion 0


#include <Carbon/Carbon.r>


// Icons
// -----
resource 'ICON' (9200, "Default ICON") {
	$""
};

resource 'SICN' (9200, "Default SICN") {
	{	
		$""
	}
};

resource 'cicn' (9200, "Default cicn") {
	4,
	{0, 0, 32, 32},
	1,
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF",
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000",
	{	/* array ColorSpec */
		65535, 65535, 65535
	},
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000"
};


// Patterns
// --------
resource 'PAT ' (9200, "Default PAT ") {
	$""
};

resource 'PAT#' (9200, "Default PAT#") {
	{	/* PatArray */
		$""
	}
};

resource 'ppat' (9200, "Default ppat") {
	newPattern,
	$"",
	1,
	{0, 0, 8, 8},
	0,
	unpacked,
	0,
	0x480000,
	0x480000,
	chunky,
	1,
	1,
	1,
	0,
	$"0000 0000 0000 0000",
	0x0,
	0,
	{	/* array ColorSpec */
		0, 65535, 65535, 65535
	}
};


// Cursors
// -------
resource 'CURS' (9200, "Default CURS") {
	$"",
	$"",
	{0, 0}
};

resource 'crsr' (9200, "Default crsr") {
	colorCursor,
	$"",
	$"",
	{0, 0},
	2,
	{0, 0, 16, 16},
	0,
	unpacked,
	0,
	0x480000,
	0x480000,
	chunky,
	1,
	1,
	1,
	0,
	$"0000 0000 0000 0000 0000 0000 0000 0000"
	$"0000 0000 0000 0000 0000 0000 0000 0000",
	0x0,
	0,
	{	/* array ColorSpec */
		0, 65535, 65535, 65535,
		1, 0, 0, 0
	}
};


// Icon family
// -----------
resource 'ics#' (9200, "Default ics#") {
	{	
		/* [1] */
		$"",
		/* [2] */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	}
};

resource 'ics8' (9200, "Default ics8") {
	$""
};

resource 'ics4' (9200, "Default ics4") {
	$""
};

resource 'icm#' (9200, "Default icm#") {
	{	
		/* [1] */
		$"",
		/* [2] */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF"
	}
};

resource 'icm4' (9200, "Default icm4") {
	$""
};

resource 'icm8' (9200, "Default icm8") {
	$""
};

resource 'ICN#' (9200, "Default ICN#") {
	{	
		/* [1] */
		$"",
		/* [2] */
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
		$"FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF"
	}
};

resource 'icl4' (9200, "Default icl4") {
	$""
};

resource 'icl8' (9200, "Default icl8") {
	$""
};


// Picture
// -------
resource 'PICT' (9200, "Default PICT") {
	773,
	{0, 0, 240, 320},
	$"1101 0100 0A00 0000 0000 F001 4098 0028"
	$"0000 0000 00F0 0140 0000 0000 00F0 0140"
	$"0000 0000 00F0 0140 0000 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 02D9 0002 D900"
	$"02D9 0002 D900 02D9 0002 D900 02D9 0002"
	$"D900 02D9 0002 D900 02D9 0002 D900 02D9"
	$"0002 D900 02D9 0002 D900 FF"
};
