// ===========================================================================
// Rezilla_RidL.r
//                       Created: 2004-12-28 08:17:46
//             Last modification: 2004-12-28 08:55:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// � Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

// Resource ID List (long integers)
type 'RidL' {
	integer = $$CountOf(ResourceIDList);
	wide array ResourceIDList {
		longint;
	};
};


resource 'RidL' (300, "Icon editor broadcasters (tools)") {
	{	/* array ResourceIDList: 22 elements */
/* [1]  ok   */		1,
/* [2]  cncl */		2,
/* [3]  rev  */		3,
/* [4]  ENCL */		1162756940,
/* [5]  tLAS */		1951154515,
/* [6]  tSEL */		1951614284,
/* [7]  tTXT */		1951684692,
/* [8]  tPEN */		1951417678,
/* [9]  tERA */		1950700097,
/* [10] tBUC */		1950504259,
/* [11] tDRO */		1950634575,
/* [12] tLIN */		1951156558,
/* [13] tREC */		1951548739,
/* [14] tFRC */		1950765635,
/* [15] tRRC */		1951552067,
/* [16] tFRR */		1950765650,
/* [17] tOVL */		1951356492,
/* [18] tFOV */		1950764886,
/* [19] COOR */		1129271122,
/* [20] tPAT */		1951416660,
/* [21] tBCL */		1950499660,
/* [22] tFCL */		1950761804,
/* [23] tHOT */		1950895956
	}
};

resource 'RidL' (301, "Icon editor broadcasters (cicn)") {
	{	/* array ResourceIDList: 3 elements */
/* [1] cicn */	1667851118,
/* [2] ICON */	1229147982,
/* [3] MASK */	1296126795
	}
};

resource 'RidL' (302, "Icon editor broadcasters (fam)") {
	{	/*  array ResourceIDList: 12 elements */
/* [1] icl8 */	1768123448,
/* [2] icl4 */	1768123444,
/* [3] ICN# */	1229147683,
/* [4] MSK1 */	1297304369,
/* [5] ics8 */	1768125240,
/* [6] ics4 */	1768125236,
/* [7] ics# */	1768125219,
/* [8] MSK2 */	1297304370,
/* [9] icm8 */	1768123704,
/* [10] icm4 */	1768123700,
/* [11] icm# */	1768123683,
/* [12] MSK3 */	1297304371
	}
};


// resource 'RidL' (300, "Icon editor broadcasters (tools)") {
// 	{	/* array ResourceIDList: 22 elements */
// /* [1] PNTG */	1347310663,
// /* [2] LASS */	1279349587,
// /* [3] TEXT */	1413830740,
// /* [4] SELE */	1397050437,
// /* [5] ERAS */	1163018579,
// /* [6] PEN  */	1346719264,
// /* [7] EYED */	1163478340,
// /* [8] BUCK */	1112884043,
// /* [9] LINE */	1279872581,
// /* [10] RECT */	1380270932,
// /* [11] FREC */	1179796803,
// /* [12] RREC */	1381123395,
// /* [13] FRRE */	1179800133,
// /* [14] OVAL */	1331052876,
// /* [15] FOVA */	1179604545,
// /* [16] FORE */	1179603525,
// /* [17] BACK */	1111573323,
// /* [18] PAT  */	1346458656,
// /* [19] BWBW */	1113014871,
// /* [20] SWAP */	1398227280,
// /* [21] tBOX */	1950502744,
// /* [22] HOTS */	1213158483
// 	}
// };
