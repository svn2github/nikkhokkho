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
	//ToDo: Memo, ...
	if (poControl->ClassType() == __classid(TForm))
	{
		((TForm *) poControl)->Caption = Get(((TForm *) poControl)->Caption);
		((TForm *) poControl)->Hint = Get(((TForm *) poControl)->Hint);
	}
	else if (poControl->ClassType() == __classid(TLabel))
	{
		((TLabel *) poControl)->Caption = Get(((TLabel *) poControl)->Caption);
		((TLabel *) poControl)->Hint = Get(((TLabel *) poControl)->Hint);
	}
	else if (poControl->ClassType() == __classid(TEdit))
	{
		((TEdit *) poControl)->Text = Get(((TEdit *) poControl)->Text);
		((TEdit *) poControl)->Hint = Get(((TEdit *) poControl)->Hint);
	}
	else if (poControl->ClassType() == __classid(TCheckBox))
	{
		((TCheckBox *) poControl)->Caption = Get(((TCheckBox *) poControl)->Caption);
		((TCheckBox *) poControl)->Hint = Get(((TCheckBox *) poControl)->Hint);
	}
	else if (poControl->ClassType() == __classid(TComboBox))
	{
		((TComboBox *) poControl)->Hint = Get(((TComboBox *) poControl)->Hint);
		for (int iItem = ((TComboBox *) poControl)->Items->Count - 1; iItem >= 0; iItem--)
		{
			//((TComboBox *) poControl)->Items[iItem].Text = Get(((TComboBox *) poControl)->Items[iItem].Text);
		}
	}
	else if (poControl->ClassType() == __classid(TImage))
	{
		((TImage *) poControl)->Hint = Get(((TImage *) poControl)->Hint);
	}
	else if (poControl->ClassType() == __classid(TButton))
	{
		((TButton *) poControl)->Caption = Get(((TButton *) poControl)->Caption);
		((TButton *) poControl)->Hint = Get(((TButton *) poControl)->Hint);
	}


	for (int iControl = poControl->ControlCount - 1; iControl >= 0; iControl--)
	{
		TWinControl *oControl = dynamic_cast<TWinControl *>(poControl->Controls[iControl]);
		if (oControl)
		{
			EnumerateControls(oControl);
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
		psText = acLine;
		psText = ReplaceStr(psText, "msgstr \"", "");
		return(psText);
	}
	else
	{
        return(psText);
	}

}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::Set(const String psText)
{
	if (psText != "")
	{
		FILE *pLanguage;
		if (Get(psText, "1033.po") != "\"\n")
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

