// ===========================================================================
// CIconBucketAction.cp
//                       Created: 2004-12-11 18:52:12
//             Last modification: 2004-12-22 15:50:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

// 	Based on Graphics Gems I algorithm.
// 	
// 	The original algorithm didn't handle pattern fills -- just fixed
// 	colors. Moreover, simply modifying the "writepixel" routine to use
// 	patterns screwed up other parts of the algorithm (with infinite loops).
// 	  
// 	Since we have a spare buffer available, we'll do the following: (1)
// 	Copy the image into the spare buffer (2) The "readpixel" code always
// 	reads from the spare buffer (3) The "writepixel" code writes a fixed
// 	color to the spare buffer AND a patterned color into the image buffer.
// 	     
// 	The algorithm thinks it is filling the spare buffer, but we fill both.
// 	
// 	Should we just rewrite the algorithm? Maybe. But it works fine.
// 	
// 	Also, the algorithm can't fill if the user clicks on a pixel in the
// 	current foreground color. This shows up in the case where the user
// 	selects a pattern and then clicks on a pixel in the foreground color --
// 	they expect foreground colored pixels to be replaced by the pattern. We
// 	will fill the spare buffer with a different color than the foreground
// 	and the the image buffer with the correct color.

#include "RezillaConstants.h"
#include "CIcon_EditorView.h"
#include "CIcon_EditorWindow.h"
#include "COffscreen.h"
#include "CIconActions.h"
#include "UIconMisc.h"


// ---------------------------------------------------------------------------
// 	FillArea  -- used by the fill algorithm
// ---------------------------------------------------------------------------

typedef struct 
{		/* window: a discrete 2-D rectangle */
    short x0, y0;			/* xmin and ymin */
    short x1, y1;			/* xmax and ymax (inclusive) */
} FillArea;


// ---------------------------------------------------------------------------
// 	PatternMap -- maps a pixel in an 8x8 grid to a color
// ---------------------------------------------------------------------------

typedef PixelValue		PatternMap[8][8];		// maps row/col to a color in a pattern



// ---------------------------------------------------------------------------
// 	Internal routines
// ---------------------------------------------------------------------------

static void seedfillgem( COffscreen *, COffscreen *, short x, short y, FillArea *win, PixelValue nv, PatternMap );



// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CIconBucketAction::CIconBucketAction( const SPaintAction &inAction ) : CIconTrackingPaintAction( inAction, index_UndoBucket )
{
	this->ThrowIfFileLocked();
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CIconBucketAction::~CIconBucketAction()
{
}


// ---------------------------------------------------------------------------
// 	HandleMouseDown
// ---------------------------------------------------------------------------

void
CIconBucketAction::HandleMouseDown( const SMouseDownEvent &inEvent )
{
	StGWorldSaver	aWorldSaver;
	SInt32			h, v;
	FillArea		theFillArea;
	
		// get the initial cell hit by the user	
	if ( !mSettings.theCanvas->MapPointToCell( inEvent.whereLocal, &h, &v ) )
		return;								// missed it by *that* much

		// we're undoable, so copy the current image to the undo buffer
	mSettings.thePaintView->CopyToUndo();

		// copy the current image to a spare buffer
	COffscreen *theImageBuffer = mSettings.currentBuffer;
	COffscreen *theSpareBuffer = mSettings.scratchBuffer;
	
	theSpareBuffer->CopyFrom( theImageBuffer );

	/*
		we need to deal in raw pixel values
	*/
	PixelValue		theForePixelValue = theImageBuffer->Color32ToPixelValue( mSettings.theForeColor );
	PixelValue		theBackPixelValue = theImageBuffer->Color32ToPixelValue( mSettings.theBackColor );

	SInt32			theWidth = theImageBuffer->GetWidth();
	SInt32			theHeight = theImageBuffer->GetHeight();

	/*
		create a pattern map for use during filling.
		each entry has a color value -- either the foreground or background.
	*/
	PatternMap	thePatternMap;
	UInt8		*patternPtr = (UInt8*) &mSettings.thePattern;
	for ( long rowCount = 0; rowCount < 8; rowCount++ )
	{
		UInt8	patternByte = *patternPtr++;
	
		thePatternMap[ 0 ][ rowCount ] = (patternByte & 0x80) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 1 ][ rowCount ] = (patternByte & 0x40) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 2 ][ rowCount ] = (patternByte & 0x20) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 3 ][ rowCount ] = (patternByte & 0x10) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 4 ][ rowCount ] = (patternByte & 0x08) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 5 ][ rowCount ] = (patternByte & 0x04) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 6 ][ rowCount ] = (patternByte & 0x02) ? theForePixelValue : theBackPixelValue;
		thePatternMap[ 7 ][ rowCount ] = (patternByte & 0x01) ? theForePixelValue : theBackPixelValue;
	}
	
		// call the modified GEM code to fill the buffer
	theFillArea.x0 = 0;
	theFillArea.y0 = 0;
	theFillArea.x1 = theWidth - 1;
	theFillArea.y1 = theHeight - 1;
	
	seedfillgem( theImageBuffer, theSpareBuffer, h, v, &theFillArea, theForePixelValue, thePatternMap );

		// update the screen & return
	mSettings.theCanvas->DrawFrom( theImageBuffer );
	this->PostAsAction();				// so we can be undone
}


// ---------------------------------------------------------------------------
// 	seedfillgem
// 	
// 	Description:
// 	Does a MacPaint-like bucket fill.
// 	
// 	Note:
// 	See Graphics Gems I. Modified to handle patterns.
// 	This really should do compares in rgb space for indexed buffers
// 	if we support custom color tables, since they can have duplicated colors
// 	with different index values.
// ---------------------------------------------------------------------------

static void seedfillgem( COffscreen *theImageBuffer, COffscreen *theSpareBuffer, short x, short y, 
							FillArea *win, PixelValue nv, PatternMap patmap )
{
	// ----------------------------------------
	#define FILLSTACKSIZE 2000		

	#define PUSH(Y, XL, XR, DY)	/* push new segment on stack */ \
	    if (sp<stack+FILLSTACKSIZE && Y+(DY)>=win->y0 && Y+(DY)<=win->y1) \
	    {sp->y = Y; sp->xl = XL; sp->xr = XR; sp->dy = DY; sp++;}
	
	#define POP(Y, XL, XR, DY)	/* pop segment off stack */ \
	    {sp--; Y = sp->y+(DY = sp->dy); XL = sp->xl; XR = sp->xr;}

	typedef struct {
		short	y, xl, xr, dy;
	} Segment;

	/*
		A few notes about pixelread:
		(1) We clear the high byte since the code does long-integer compares and
			it's possible that the high byte contains garbage in 32-bit pixmaps
			because QuickDraw won't guarantee not to set it.
		(2) The compare isn't a very good one for indexed pixmaps, because it 
			won't notice that two colors in the color table are the same.
			We should probably call GetPixelColor() instead, but this routine
			is much slower. See if anyone complains, I guess.
	*/
	#define pixelread(xxx,yyy)			(theSpareBuffer->GetPixel(xxx,yyy) & 0x00FFFFFF)
	
	#define pixelwrite(xxx,yyy,vvv)		{																	\
											theSpareBuffer->SetPixel(xxx,yyy, vvv );						\
											theImageBuffer->SetPixel(xxx,yyy, patmap[x & 0x07][y & 0x07] );	\
										}
											
 	// ----------------------------------------
	short 			l, x1, x2, dy;
    PixelValue 		ov;							/* old pixel value */
    Segment 		*stack, *sp;				/* stack of filled segments */

	stack = (Segment*) NewPtr( sizeof(Segment) * (long)FILLSTACKSIZE );
	ThrowIfMemFail_( stack );
	sp = stack;
	
    ov = pixelread(x, y);		/* read pv at seed point */
    
    /*
    	if we are filling with the foreground color, the algorithm must be
    	fooled by using a phony color in the spare buffer. The actual pixel
    	value we use is not important -- we'll use 1 or nv - 1 because they
    	work in all depths. The correct color is put into the image buffer.
    */
    if ( ov == nv )
    {
		if ( nv == 0 )
			nv = 1;
		else
			nv = nv - 1;
    }
  
   	if ( ov==nv || x<win->x0 || x>win->x1 || y<win->y0 || y>win->y1) goto DONE;

    PUSH(y, x, x, 1);			/* needed in some cases */
    PUSH(y+1, x, x, -1);		/* seed segment (popped 1st) */

    while (sp>stack) 
    {
		/* pop segment off stack and fill a neighboring scan line */
		POP(y, x1, x2, dy);
		/*
		 * segment of scan line y-dy for x1<=x<=x2 was previously filled,
		 * now explore adjacent pixels in scan line y
		 */
		for (x=x1; x>=win->x0 && pixelread(x, y)==ov; x--)
			pixelwrite(x, y, nv);
			
		if (x>=x1) goto skip;
		l = x+1;
		if (l<x1) PUSH(y, l, x1-1, -dy);		/* leak on left? */
		x = x1+1;
	
		do 
		{
			for (; x<=win->x1 && pixelread(x, y)==ov; x++)
				pixelwrite(x, y, nv);
				
			PUSH(y, l, x-1, dy);
			if (x>x2+1) PUSH(y, x2+1, x-1, -dy);	/* leak on right? */
			
		skip:
			for (x++; x<=x2 && pixelread(x, y)!=ov; x++) 
					;
		
			l = x;
		} while (x<=x2);
	}
	
	DONE:
	if ( stack )
		DisposePtr( (Ptr) stack );
}

