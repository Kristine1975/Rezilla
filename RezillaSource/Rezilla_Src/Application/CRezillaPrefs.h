// ===========================================================================
// CRezillaPrefs.h					
// 
//                       Created: 2004-05-17 08:52:16
//             Last modification: 2005-01-15 09:33:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRezillaPrefs
#define _H_CRezillaPrefs
#pragma once

#include <LPreferencesFile.h>
#include <LCommander.h>

//     General Prefs
struct SGeneralPrefs {
	SInt32			maxRecent;
	SInt32			newFork;
};

//     Export Prefs
struct SExportPrefs {
	Boolean			includeBinary;
	SInt32			formatDtd;
	SInt32			binaryEncoding;
	OSType			editorSig;
};

//     Comparison Prefs
struct SComparePrefs {
	Boolean			ignoreName;
	Boolean			ignoreAttributes;
	Boolean			ignoreData;
	SInt32			displayAs;
};

//     Interface Prefs
struct SInterfacePrefs {
	TextTraitsRecord	traitsRecord;
};

//     Editors Prefs
struct STemplatesPrefs {
	SInt32			hexSymbol;
	SInt32			hexCase;
	Boolean			displayFillers;
	Boolean			enableFillers;
};

//     Editors Prefs
// 	// 	One of these two should be #defined
// 			#define USE_LINES_FOR_ERASER
// 			//#define USE_RECTS_FOR_ERASER
struct SEditorsPrefs {
	Boolean			use8BitPicts;	// 8-bit instead of 32 ?
	Boolean			use8BitIcons;	// 8-bit instead of 32 ?
	Boolean			fullTables;		// default to 256 colors rather than 36 ?
	Boolean			doFontSubst;	// kTXNDoFontSubstitution in MLTE
};

//     Misc Prefs
struct SMiscPrefs {
	Boolean			setSigOnClose;
	Boolean			onlyRsrcExt;
	ResType			closingType;
	ResType			closingCreator;
	Boolean			setSigOnCreate;
};

struct SRezillaPrefs {
	SGeneralPrefs		general;
	SExportPrefs		exporting;
	SComparePrefs		compare;
	SInterfacePrefs		interface;
	STemplatesPrefs		templates;
	SEditorsPrefs		editors;
	SMiscPrefs			misc;
};

enum {
	kPref_compare_dataDisplayAs,
	kPref_compare_ignoreAttributes,
	kPref_compare_ignoreData,
	kPref_compare_ignoreName,
	kPref_editors_use8BitPicts,
	kPref_editors_use8BitIcons,
	kPref_editors_fullTables,
	kPref_editors_doFontSubst,
	kPref_export_dataEncoding,
	kPref_export_formatDtd,
	kPref_export_includeBinary,
	kPref_export_editorSig,
	kPref_interface_traitsRecord,
	kPref_general_newFork,
	kPref_general_maxRecent,
	kPref_misc_setSigOnClose,
	kPref_misc_onlyRsrcExt,
	kPref_misc_closingType,
	kPref_misc_closingCreator,
	kPref_misc_setSigOnCreate,
	kPref_templates_hexSymbol,
	kPref_templates_hexCase,
	kPref_templates_displayFillers,
	kPref_templates_enableFillers
};


class LDialogBox;
class LPopupButton;

class CRezillaPrefs : public LCommander, public LBroadcaster {

public:
	enum { 	prefsType_Temp = 0,
			prefsType_Curr = 1};

							CRezillaPrefs();
							CRezillaPrefs( LCommander* inSuper );
			virtual			~CRezillaPrefs();

	void				RunPrefsDialog();

	virtual SRezillaPrefs	GetRezillaPreferences() { return sCurrPrefs;}
	void					SetRezillaPreferences(SRezillaPrefs inRezillaPreferences) {
														sCurrPrefs = inRezillaPreferences ;}
				
	static SInt32		GetPrefValue(SInt32 inConstant, 
									 SInt32 inPrefType = prefsType_Curr);
	void				SetPrefValue(SInt32 inPrefValue, 
									 SInt32 inConstant, 
									 SInt32 inPrefType = prefsType_Curr);
	
	static TextTraitsRecord	GetStyleElement(SInt32 inPrefType = prefsType_Temp);
	
	void				SetStyleElement(SInt16 inStyleValue, 
										SInt32 inElementType,
										SInt32 inPrefType = prefsType_Curr);
	void				LoadStyleElement(TextTraitsPtr inTraitsRecPtr);

	LDialogBox *		GetPrefsWindow() { return sPrefsWindow;}
	void				SetPrefsWindow(LDialogBox * inPrefsWindow) {sPrefsWindow = inPrefsWindow ;}
	
	void				ValidateTempPrefs();
	void				InitTempPrefs();
	virtual void		StorePreferences();
	Boolean				PrefsHaveChanged();
	void				UpdateVars();
	
	static LDialogBox *		sPrefsWindow;
	static ArrayIndexT		sCurrentPrefsPane;
	static SRezillaPrefs	sTempPrefs;
	static SRezillaPrefs	sCurrPrefs;
	
protected:
	
	virtual void		Initialize();
	void                MakePrefsWindow();

private:
	void				SetDefaultPreferences();
	void				RetrievePreferences();
	void				ApplyStylePrefs();
};

#endif // _H_CRezillaPrefs