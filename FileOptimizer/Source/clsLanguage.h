// ---------------------------------------------------------------------------
#pragma once
#ifndef clsLanguageH
#define clsLanguageH
#include "FileOptimizerPCH1.h"
#include "clsUtil.h"
#include "cppMain.h"


//#define _(psText)		#ifdef (_DEBUG) #pragma message ("msgid \"" || psText || "\"\nmsgstr: \"\"") #endif (clsLanguage::Get((psText)))
#define _(psText)		(clsLanguage::Get((psText)))


// ---------------------------------------------------------------------------
class clsLanguage
{
	public:
		static void __fastcall Load(unsigned int piLanguage = 0, bool pbForce = false);
		static void __fastcall Save(void);
		static void __fastcall TranslateForm(TForm *pfrmForm);
		static String __fastcall Get(String psText);
		static const TCHAR * __fastcall Get(TCHAR *pacText);
	private:
		static void EnumerateControls(TComponent *poControl);
		static String __fastcall Search(String psText, THashedStringList *plstLanguage);
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
