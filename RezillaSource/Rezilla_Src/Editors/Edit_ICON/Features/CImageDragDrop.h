// ===========================================================================
// CImageDragDrop.h
//                       Created: 2004-12-11 18:57:42
//             Last modification: 2004-12-17 10:47:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CImageDragDrop
#define _H_CImageDragDrop
#pragma once

class COffscreen;

class CImageDragDrop : public LDragAndDrop {
	public:
							CImageDragDrop( GrafPtr, LPane * );
		
	protected:
		virtual Boolean		ItemIsAcceptable( DragReference, ItemReference );
		virtual void		ReceiveDragItem( DragReference, DragAttributes, ItemReference, Rect & );

		virtual void		HandleDroppedPicture( PicHandle, DragReference = 0, DragAttributes = 0 ) = 0;
		virtual void		HandleDroppedOffscreen( COffscreen *, DragReference = 0, DragAttributes = 0 ) = 0;
		virtual void		HandleDroppedPictureFile( const FSSpec &, DragReference = 0, DragAttributes = 0 );

		virtual void		HiliteDropArea( DragReference );
		virtual void		UnhiliteDropArea( DragReference );
};

#endif // _H_CImageDragDrop
