// ---------------------------------------------------------------------------
#pragma once
#ifndef clsLanguageH
#define clsLanguageH
#include "FileOptimizerPCH1.h"
#include "clsUtil.h"


#define _(psText)		(clsLanguage::Get((psText)))


// ---------------------------------------------------------------------------
class clsLanguage
{
	public:
		static void __fastcall SaveLanguage(void);
		static void __fastcall TranslateForm(TForm *pfrmForm);
		static String __fastcall Get(String psText);
		static TCHAR * __fastcall Get(TCHAR *pacText);
	private:
		static void __fastcall LoadLanguages(void);
		static void EnumerateControls(TComponent *poControl);
		static String __fastcall Search(String psText, THashedStringList *plstLanguage);
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
