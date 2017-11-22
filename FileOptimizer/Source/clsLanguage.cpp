// --------------------------------------------------------------------------
/*
 1.00. 22/11/2017. FileOptimizer. Initial version
 */
// ---------------------------------------------------------------------------
#include "clsLanguage.h"



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsLanguage::GetLanguagePath(void)
{
	static TCHAR acPath[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		LANGID iLanguage = GetSystemDefaultUILanguage();

		_itot(iLanguage, acPath, 10);
		_tcscat(acPath, _T(".po"));

		if (!clsUtil::ExistsFile(acPath))
		{
			_itot(PRIMARYLANGID(iLanguage), acPath, 10);
			_tcscat(acPath, _T(".po"));
			if (!clsUtil::ExistsFile(acPath))
			{
				_tcscpy(acPath, _T("0.po"));
			}
		}
	}
	return (acPath);
}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::TranslateForm(TForm *pfrmForm)
{
	EnumerateControls(pfrmForm);
}



// ---------------------------------------------------------------------------
void clsLanguage::EnumerateControls(TWinControl *poControl)
{
	if (poControl->ClassType() == __classid(TForm))
	{
		((TForm *) poControl)->Caption = Get(((TForm *) poControl)->Caption);
		((TForm *) poControl)->Hint = Get(((TForm *) poControl)->Hint);
	}

	for (int iControl = poControl->ControlCount - 1; iControl >= 0; iControl--)
	{
		TControl *oControl = poControl->Controls[iControl];
		String s = oControl->Name;

		if (oControl->ClassType() == __classid(TLabel))
		{
			((TLabel *) oControl)->Caption = Get(((TLabel *) oControl)->Caption);
			((TLabel *) oControl)->Hint = Get(((TLabel *) oControl)->Hint);
		}
		else if (oControl->ClassType() == __classid(TEdit))
		{
			((TEdit *) oControl)->Text = Get(((TEdit *) oControl)->Text);
			((TEdit *) oControl)->Hint = Get(((TEdit *) oControl)->Hint);
		}
		else if (oControl->ClassType() == __classid(TCheckBox))
		{
	        ((TCheckBox *) oControl)->Caption = Get(((TCheckBox *) oControl)->Caption);
			((TCheckBox *) oControl)->Hint = Get(((TCheckBox *) oControl)->Hint);
		}
		else if (oControl->ClassType() == __classid(TImage))
		{
			((TImage *) oControl)->Hint = Get(((TImage *) oControl)->Hint);
		}
		else if (oControl->ClassType() == __classid(TButton))
		{
			((TButton *) oControl)->Caption = Get(((TButton *) oControl)->Caption);
			((TButton *) oControl)->Hint = Get(((TButton *) oControl)->Hint);
		}
		else if (oControl->ClassType() == __classid(TWinControl))
		{
			EnumerateControls((TWinControl *) oControl);
		}
	}
}



// ---------------------------------------------------------------------------
String __fastcall clsLanguage::Get(String psText, String psPath)
{
	bool bFound = false;
	FILE *pLanguage;
	TCHAR acLine[2048];


	if (psPath == "")
	{
		psPath = GetLanguagePath();
	}
	if (psPath != "1033.po")
	{
		Set(psText);
	}


	pLanguage = _tfopen(psPath.c_str(), _T("r"));
	if (pLanguage)
	{
		String sSearch = "msgid \"" + psText + "\"\n";
		//sSearch = ReplaceStr((sSearch, "\t", " ");
		//sSearch = ReplaceStr((sSearch, "  ", " ");
		do
		{
			_fgetts(acLine, sizeof(acLine) / sizeof(TCHAR) - 1, pLanguage);
			if ((String) acLine == sSearch)
			{
				_fgetts(acLine, sizeof(acLine) / sizeof(TCHAR) - 1, pLanguage);
                bFound = true;
				break;
			}
		}
		while (!feof(pLanguage));
		fclose(pLanguage);
	}

	if (bFound)
	{
        //Eliminate msgstr:
		return((String) acLine);
	}
	else
	{
        return(psText);
	}

}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::Set(String psText)
{
	FILE *pLanguage;


	if (psText != "")
	{
		if (Get(psText, "1033.po") != "msgstr \"\"\n")
		{
			pLanguage = _tfopen(_T("1033.po"), _T("a"));
			if (pLanguage)
			{
				_fputts(((String) "msgid \"" + psText + "\"\n").c_str(), pLanguage);
				_fputts(_T("msgstr \"\"\n\n"), pLanguage);
			}
		}
		fclose(pLanguage);
    }
}

