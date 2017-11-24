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
		static const TCHAR * __fastcall GetLanguagePath(void);
		static void __fastcall LoadLanguage(String psPath = "");
		static void __fastcall SaveLanguage(void);
		static void __fastcall TranslateForm(TForm *pfrmForm);
		static void EnumerateControls(TComponent *poControl);
		static String __fastcall Get(String psText, String psPath = "");
		static TCHAR * __fastcall Get(TCHAR *pacText, TCHAR *pacPath = NULL);
		static void __fastcall Set(String psText);
	private:
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
