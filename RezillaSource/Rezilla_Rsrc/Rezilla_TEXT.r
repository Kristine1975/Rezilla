// ===========================================================================
// Rezilla_TEXT.r
//                       Created: 2004-02-28 22:51:23
//             Last modification: 2004-12-11 11:51:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// � Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";

data 'TEXT' (250, "About Text", purgeable) {
$$Format("Resource map editor\n\n� 2003-%d", $$YEAR)
};

data 'TEXT' (251, "Free software", purgeable) {
"Rezilla is a free software"
};
