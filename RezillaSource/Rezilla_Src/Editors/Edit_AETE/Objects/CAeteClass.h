// ===========================================================================
// CAeteClass.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 11:02:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteClass
#define _H_CAeteClass
#pragma once

class CAeteStream;
class CAeteProperty;
class CAeteElement;


class CAeteClass {

public:
				CAeteClass();
				CAeteClass(	Str255	inName,
							OSType	inID,
							Str255	inDescription);
				CAeteClass(CAeteStream *	inStream);
				~CAeteClass();

		void		AddProperty();
		void		AddProperty( CAeteProperty * inProperty );
		void		AddProperty(Str255	inName,
								OSType	inID, 
								OSType	inType, 
								Str255	inDescription, 
								UInt16	inFlags);
		void		RemoveProperty( ArrayIndexT inAtIndex );

		void		AddElement();
		void		AddElement( CAeteElement * inElement );
		void		AddElement( OSType inKeyForms[], UInt16 inCount = 1 );
		void		RemoveElement( ArrayIndexT inAtIndex );

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

		void		GetValues(Str255 outName, OSType & outID, Str255 outDescription);
		
		void 		SetValues(Str255 inName, OSType inID, Str255 inDescription);

		ArrayIndexT		GetPropertyIndex() { return mPropertyIndex;}
		void			SetPropertyIndex(ArrayIndexT inPropertyIndex) {mPropertyIndex = inPropertyIndex;}

		ArrayIndexT		GetElementIndex() { return mElementIndex;}
		void			SetElementIndex(ArrayIndexT inElementIndex) {mElementIndex = inElementIndex;}

		TArray<CAeteProperty*> *	GetProperties() { return &mProperties;}

		TArray<CAeteElement*> *		GetElements() { return &mElements;}

protected:
		Str255					mName;
		OSType					mID;		// like capp, docu, cwin etc.
		Str255					mDescription;
		
		ArrayIndexT				mPropertyIndex;
		ArrayIndexT				mElementIndex;
		TArray<CAeteProperty*>	mProperties;
		TArray<CAeteElement*>	mElements;


private:


};


#endif