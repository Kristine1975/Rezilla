// ===========================================================================
// UGraphicConversion.cp
//                       Created: 2004-12-11 18:52:47
//             Last modification: 2004-12-15 10:49:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UGraphicConversion.h"
#include "COffscreen.h"
#include "CColorTableBuilder.h"
#include "CColorUtils.h"
#include "CDisposeOnExit.h"
#include "CPrefs.h"
#include "CSaveResFile.h"
#include "RezillaConstants.h"
#include "UFileUtils.h"
#include "UIconMisc.h"
#include "UResources.h"

#include <stdio.h>


// ============================================================
// 	OffscreenToPicture
// ============================================================
// The selection region is relative to the painting itself and not the
// selection buffer. This allows us to restore the original image position
// on a "paste".

PicHandle UGraphicConversion::OffscreenToPicture( COffscreen *inBuffer, RgnHandle inSelectionRgn )
{
	StGWorldSaver		aSaver;					// save/restore gworld
	PicHandle			thePict = nil;
	Rect				sourceR, destR, bounds;
	GrafPtr				aSparePort;
	RgnHandle			maskRgn = nil;
	COffscreen	*		downSampledBuffer = nil;

	try
	{
		// Downsample the buffer if we can
		downSampledBuffer = CColorTableBuilder::DownSampleBuffer( inBuffer, 
																	32,			// max depth
																	true, 		// b&w included
																	true, 		// minimize tbl
																	true );		// larger inverse
		if ( downSampledBuffer )
			inBuffer = downSampledBuffer;
		 
		if ( inSelectionRgn )
		{
			maskRgn = UIconMisc::NewRegionFromRegion( inSelectionRgn );
			::GetRegionBounds(maskRgn, &bounds);
			::OffsetRgn( maskRgn, -bounds.left, -bounds.top );
			sourceR = bounds;
			destR = sourceR;
			//OffsetRect( &destR, -destR.left, -destR.top );
		}
		else		// use the entire buffer
		{
			::SetRect( &sourceR, 0, 0, inBuffer->GetWidth(), inBuffer->GetHeight() );
			destR = sourceR;
			maskRgn = nil;
		}
		
		aSparePort = USparePort::GetSparePort();
		UIconMisc::SetPort( aSparePort );
		
		thePict = ::OpenPicture( &destR );
		ThrowIfNil_( thePict );

		::ClipRect( &destR );
		inBuffer->CopyTo( aSparePort, &destR, &sourceR, srcCopy, maskRgn );
		::ClosePicture();
		
	}
	catch( ... )
	{
		delete downSampledBuffer;
		if ( maskRgn ) ::DisposeRgn( maskRgn );
		if ( thePict ) ::KillPicture( thePict );
		throw;
	}
	
	if ( maskRgn ) ::DisposeRgn( maskRgn );
	delete downSampledBuffer;
	return( thePict );
}


// ============================================================
// 	OffscreenToClipboard
// ============================================================

void UGraphicConversion::OffscreenToClipboard( COffscreen *inBuffer, RgnHandle inSelection )
{
	PicHandle			thePict = nil;
	LClipboard			*theClipboard = LClipboard::GetClipboard();
	StGWorldSaver		aSaver;				// save/restore gworld
	
	// Convert the offscreen buffer to a picture
	thePict = OffscreenToPicture( inBuffer, inSelection );
	
	// Delete the picture on exit (handles case when errors are thrown)
	StDisposeHandle		aDeleter( (Handle) thePict );  // StHandleBlock ?
	
	// Write the picture 
	theClipboard->SetData( ImageType_Picture, (Handle) thePict, true /* reset */ );

	if ( inSelection )
		theClipboard->SetData( ResourceType_Region, (Handle) inSelection, false );
}


// ============================================================
// 	GetPictFromClipboard
// ============================================================
// Throws an error if there's no pict on the clipboard.

PicHandle UGraphicConversion::GetPictFromClipboard()
{
	PicHandle		thePict = nil;
	SInt32			numBytes;
	LClipboard		*theClipboard = LClipboard::GetClipboard();

	try
	{
		thePict = (PicHandle) ::NewHandle( 0 );
		ThrowIfMemFail_( thePict );
		
		numBytes = theClipboard->GetData( ImageType_Picture, (Handle) thePict );
		if ( numBytes < sizeof(Picture) )
			Throw_( noTypeErr );
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( (Handle) thePict );
		throw;	
	}
	
	return( thePict );
}


// ============================================================
// 	GetRegionFromClipboard
// ============================================================
// Returns nil if the clipboard doesn't have a region rather than throwing
// an error.

RgnHandle UGraphicConversion::GetRegionFromClipboard()
{
	RgnHandle		theRegion = nil;
	SInt32			numBytes;
	LClipboard		*theClipboard = LClipboard::GetClipboard();

	numBytes = theClipboard->GetData( ResourceType_Region, nil );
	if ( numBytes <= 0 ) return( nil );
	
	try
	{
		theRegion = (RgnHandle) ::NewHandle( numBytes );
		ThrowIfMemFail_( theRegion );
		
		numBytes = theClipboard->GetData( ResourceType_Region, (Handle) theRegion );
		if ( numBytes <= 0 )
			Throw_( noTypeErr );
	}
	catch( ... )
	{
		UIconMisc::DisposeHandle( (Handle) theRegion );
		throw;	
	}
	
	return( theRegion );
}


// ============================================================
// 	GetPictFromFile
// ============================================================

PicHandle UGraphicConversion::GetPictFromFile( const FSSpec &inSpec )
{
	PicHandle	thePict = nil;
	long		numBytes;
	OSErr		err = noErr;
	short		fileID = 0;
	
	try
	{
		err = ::FSpOpenDF( &inSpec, fsRdPerm, &fileID );
		if ( err ) 
		{
			fileID = 0;
			Throw_( err );
		}

		err = ::GetEOF( fileID, &numBytes );
		ThrowIfOSErr_( err );
		
		numBytes -= 512;
		if ( numBytes <= 0 ) 
			Throw_( err_IconCorruptedFile );
			
		thePict = (PicHandle) ::NewHandle( numBytes );
		ThrowIfMemFail_( thePict );
		
		err = ::SetFPos( fileID, fsFromStart, 512 );
		ThrowIfOSErr_( err );
		
		err = ::FSRead( fileID, &numBytes, *thePict );
		ThrowIfOSErr_( err );
	}
	catch( ... )
	{
		if ( fileID )
			::FSClose( fileID );
		throw;
	}	

	if ( fileID )
		FSClose( fileID );	
	
	return( thePict );
}


// // ============================================================
// // 	SaveOffscreenAsResource
// // ============================================================
// // Saves the passed offscreen buffer as a raw image resource. This is
// // useful for ICON, icl8, icl4, etc.
// // Throws an error on i/o problem. May unlock the resource if it already
// // is present in RAM.
// 
// void UGraphicConversion::SaveOffscreenAsResource( 
// 								RFMap *inMap, ResType inResType, ResIDT inResID,
// 								COffscreen *inBuffer, SInt32 rowBytes,
// 								COffscreen *inMask, SInt32 maskOffset, SInt32 maskRowBytes )
// {
// 	UInt8				**h = nil;
// 	SInt32				numBytes;
// 	
// 			// save/restore various states
// 
// 	StRezRefSaver		saver1;
// 	StGWorldSaver		saver2;
// 	
// 			// if the rowBytes (or maskRowBytes) isn't specified, use the
// 		// buffer's rowBytes
// 
// 	if ( rowBytes == -1 )
// 		rowBytes = inBuffer->GetRowBytes();
// 	
// 	if ( inMask && (maskRowBytes == -1) )
// 	{
// 		maskRowBytes = inMask->GetRowBytes();
// 	}
// 
// 	try
// 	{
// 				// Allocate the buffer to write
// 
// 		numBytes = (rowBytes + maskRowBytes) * inBuffer->GetHeight();
// 		h = (Uint8**) ::NewHandle( numBytes );
// 		ThrowIfMemFail_( h );
// 		::HLock( (Handle) h );
// 		
// 				// Copy the raw image & mask data to the resource
// 
// 		inBuffer->CopyToRawData( *h, rowBytes );
// 		if ( inMask )
// 			inMask->CopyToRawData( *h + maskOffset, maskRowBytes );
// 
// 				// Write out the resource
// 
// 		RFResource *theResource = inMap->FindResource( inResType, inResID, true );
// 		ThrowIfNil_( theResource );
// 		
// 		theResource->SetResData( (Handle) h );
// 	}
// 	catch( ... )
// 	{
// 		UIconMisc::DisposeHandle( h );
// 		throw;
// 	}
// 	
// 	UIconMisc::DisposeHandle( h );
// }


// ============================================================
// 	PictureToOffscreen
// ============================================================
// 	Creates an offscreen buffer and draws the picture into it.

COffscreen *UGraphicConversion::PictureToOffscreen( PicHandle inPict )
{
	StGWorldSaver	aSaver;
	
	SInt32	width = (**inPict).picFrame.right - (**inPict).picFrame.left;
	SInt32	height = (**inPict).picFrame.bottom - (**inPict).picFrame.top;
	SInt32	depth;
	
	if ( (width <= 0) || (height <= 0) ) 
		throw( err_IconInvalidImageSize );
	
	Rect	r;
	SetRect( &r, 0, 0, width, height );
	
	if ( CPrefs::Use32BitBuffersForPicts() )
		depth = 32;
	else
		depth = 8;
	
	COffscreen *theBuffer = COffscreen::CreateBuffer( width, height, depth );
	
	theBuffer->BeginDrawing();
		::DrawPicture( inPict, &r );
	theBuffer->EndDrawing();
	
	return( theBuffer );
}



