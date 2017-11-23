// --------------------------------------------------------------------------
/*
 1.00. 22/11/2017. FileOptimizer. Initial version
 */
// ---------------------------------------------------------------------------
#include "clsLanguage.h"

static TStringList *mlstLanguage = NULL;


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



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsLanguage::LoadLanguage(String psPath)
{

	if (!mlstLanguage)
	{
		mlstLanguage = new TStringList();
		mlstLanguage->CaseSensitive = true;
		mlstLanguage->Duplicates = System::Classes::dupAccept;
		if (psPath == "")
		{
			psPath = GetLanguagePath();
		}
		mlstLanguage->LoadFromFile(psPath);
	}
}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::TranslateForm(TForm *pfrmForm)
{
	EnumerateControls(pfrmForm);
}



// ---------------------------------------------------------------------------
void clsLanguage::EnumerateControls(TWinControl *poControl)
{
    //Missing main menu and TLabel
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
	//TMainMenu
	{
		TMainMenu *oControl = dynamic_cast<TMainMenu *>(poControl);
		if (oControl)
		{
			for (int iMenu = oControl->Items->Count; iMenu >= 0; iMenu--)
			{
				/*
				TMenuItem *oMenu = dynamic_cast<TMenuItem *>(oControl->Items[iMenu]);
				if (oMenu)
				{
					oMenu->Caption = Get(oMenu->Caption);
					oMenu->Hint = Get(oMenu->Hint);
					EnumerateControls(oMenu);
				}
                */
			}
		}
	}
	//TToolBar
	{
		TToolBar *oControl = dynamic_cast<TToolBar *>(poControl);
		if (oControl)
		{
			for (int iButton = oControl->ButtonCount - 1; iButton >= 0; iButton--)
			{
				TToolButton *oButton = dynamic_cast<TToolButton *>(oControl->Buttons[iButton]);
				if (oButton)
				{
					TAction *oAction = dynamic_cast<TAction *>(oButton->Action);
					if (oAction)
					{
						oAction->Caption = Get(oAction->Caption);
						oAction->Hint = Get(oAction->Hint);
					}
				}
			}
		}
	}
	//TPageControl
	{
		TPageControl *oControl = dynamic_cast<TPageControl *>(poControl);
		if (oControl)
		{
			for (int iPage = oControl->PageCount - 1; iPage >= 0; iPage--)
			{
				TTabSheet *oPage = dynamic_cast<TTabSheet *>(oControl->Pages[iPage]);
				if (oPage)
				{
					oPage->Caption = Get(oPage->Caption);
					oPage->Hint = Get(oPage->Hint);
					EnumerateControls(oPage);
				}
			}
		}
	}


	//Childs
	for (int iControl = poControl->ControlCount - 1; iControl >= 0; iControl--)
	{
		TWinControl *oControl = dynamic_cast<TWinControl *>(poControl->Controls[iControl]);
		if (oControl)
		{
            String q = oControl->Name;
			EnumerateControls(oControl);
		}
	}
}


// ---------------------------------------------------------------------------
TCHAR * __fastcall clsLanguage::Get(TCHAR *pacText, TCHAR *pacPath)
{
	String sRes = Get((String) pacText, (String) pacPath);
	return(sRes.c_str());
}




// ---------------------------------------------------------------------------
String __fastcall clsLanguage::Get(String psText, String psPath)
{
	if (psPath == "")
	{
		psPath = GetLanguagePath();
	}
	if (psPath != "1033.po")
	{
		Set(psText);
	}


	if (!mlstLanguage)
	{
		LoadLanguage();
	}

	//Search for text to be translated
	String sSearch = "msgid \"" + psText + "\"";

	int iLine = mlstLanguage->IndexOf(sSearch);
	if (iLine >= 0)
	{
		String sLine;
		//Skip lines not starting with mgstr
		do
		{
			sLine = mlstLanguage->Strings[iLine];
			iLine++;
		}
		while ((PosEx("msgstr \"", sLine) <= 0) && (iLine < mlstLanguage->Count));
		psText = sLine;
		psText = psText.SubString(8, psText.Length() - 10);	//Remove first msgstr \" and last quote and return
		psText = ReplaceStr(psText, "\\\\", "\\");			//Unescape PO
		psText = ReplaceStr(psText, "\\n", "\n");
		psText = ReplaceStr(psText, "\\r", "\r");
		psText = ReplaceStr(psText, "\\t", "\t");
		psText = ReplaceStr(psText, "\\\"", "\"");
	}
}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::Set(String psText)
{
	if (psText != "")
	{
		if (Get(psText, "1033.po") != "")
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
				psText = ReplaceStr(psText, "\\", "\\\\");			//Escape PO
				psText = ReplaceStr(psText, "\n", "\\n");
				psText = ReplaceStr(psText, "\r", "\\r");
				psText = ReplaceStr(psText, "\t", "\\t");
				psText = ReplaceStr(psText, "\"", "\\\"");
				psText = "msgid \"" + psText + "\"\n";
				_fputts(psText.c_str(), pLanguage);
				_fputts(_T("msgstr \"\"\n\n"), pLanguage);
				fclose(pLanguage);
			}
		}
	}
}

