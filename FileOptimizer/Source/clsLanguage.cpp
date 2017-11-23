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
	String s = poControl->Name;

	//TForm
	{
		TForm *oControl = dynamic_cast<TForm *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TLabel
	{
		TLabel *oControl = dynamic_cast<TLabel *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TEdit
	{
		TEdit *oControl = dynamic_cast<TEdit *>(poControl);
		if (oControl)
		{
			oControl->Text = Get(oControl->Text);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TMemo
	{
		TMemo *oControl = dynamic_cast<TMemo *>(poControl);
		if (oControl)
		{
			oControl->Text = Get(oControl->Text);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TSpinEdit
	{
		TSpinEdit *oControl = dynamic_cast<TSpinEdit *>(poControl);
		if (oControl)
		{
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TCheckBox
	{
		TCheckBox *oControl = dynamic_cast<TCheckBox *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TComboBox
	{
		TComboBox *oControl = dynamic_cast<TComboBox *>(poControl);
		if (oControl)
		{
			oControl->Hint = Get(oControl->Hint);
			for (int iItem = oControl->Items->Count - 1; iItem >= 0; iItem--)
			{
				oControl->Items->Strings[iItem] = Get(oControl->Items->Strings[iItem]);
			}

		}
	}
	//TImage
	{
		TImage *oControl = dynamic_cast<TImage *>(poControl);
		if (oControl)
		{
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TMenuItem
	{
		TMenuItem *oControl = dynamic_cast<TMenuItem *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TButton
	{
		TButton *oControl = dynamic_cast<TButton *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//Childs
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
		if (Get(psText, "1033.po") != "\"\n")
		{
			//Check if already exists
			FILE *pLanguage = _tfopen(_T("1033.po"), _T("r"));
			if (pLanguage)
			{
				fclose(pLanguage);
				pLanguage = _tfopen(_T("1033.po"), _T("a"));
			}
			else
			{
				//Write header
				pLanguage = _tfopen(_T("1033.po"), _T("a"));
				if (pLanguage)
				{
					String sHeader = "# Language ID: 1033 (0x0409)\n# Language Name: English - United States\n\"Project-Id-Version: " + Application->Name + " " + (String) clsUtil::ExeVersion(Application->ExeName.c_str()) + "\"\n\"POT-Creation-Date: " + (String) __DATE__ + "\"\n\"Language: en_US\"\n""Last-Translator: Javier Gutiérrez Chamorro\"\n\"Language-Team: Javier Gutiérrez Chamorro\"\n\"Plural-Forms: nplurals=2; plural=(n != 1);\"\n\n";
					_fputts(sHeader.c_str(), pLanguage);
				}
			}
			//Write text
			if (pLanguage)
			{
				_fputts(((String) "msgid \"" + psText + "\"\n").c_str(), pLanguage);
				_fputts(_T("msgstr \"\"\n\n"), pLanguage);
				fclose(pLanguage);
			}
		}
	}
}

