// ---------------------------------------------------------------------------
#pragma once
#ifndef clsLanguageH
#define clsLanguageH
#include "FileOptimizerPCH1.h"
#include "clsUtil.h"


// ---------------------------------------------------------------------------
class clsLanguage
{
	public:
		static const TCHAR * __fastcall GetLanguagePath(void);
		static void __fastcall TranslateForm(TForm *pfrmForm);
		static void EnumerateControls(TWinControl *poControl);
        static String __fastcall Translate(String psText);
	private:
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
