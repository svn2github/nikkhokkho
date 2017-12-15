// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 1.00. 22/11/2017. FileOptimizer. Initial version
 */
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "clsLanguage.h"


THashedStringList *mlstLanguage = NULL;   //Could not use THashedStringList because they are limited to a length of 256 chars
THashedStringList *mlst1033 = NULL;


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsLanguage::Load(unsigned int piLanguage, bool pbForce)
{
	if ((pbForce) && (mlstLanguage))
	{
		delete mlstLanguage;
        mlstLanguage = NULL;
	}
	
	//If not yet loaded	
	if (!mlstLanguage)
	{
		mlstLanguage = new THashedStringList();
		mlstLanguage->CaseSensitive = true;
		mlstLanguage->Duplicates = System::Classes::dupAccept;

		TCHAR acPath[PATH_MAX] = _T("");
		if (piLanguage != 0)
		{
			//Try to load locale
			_itot(piLanguage, acPath, 10);
			_tcscat(acPath, _T(".po"));
			if (clsUtil::ExistsFile(acPath))
			{
				mlstLanguage->LoadFromFile(acPath, TEncoding::UTF8);
			}
		}
		else
		{
			// Check if we already have it cached
			LANGID iLanguage = GetSystemDefaultUILanguage();
			//Never load en-US because is built-int
			if (iLanguage != 1033)
			{
				//Try to load locale
				_itot(iLanguage, acPath, 10);
				_tcscat(acPath, _T(".po"));
				if (clsUtil::ExistsFile(acPath))
				{
					mlstLanguage->LoadFromFile(acPath, TEncoding::UTF8);
				}
				else
				{
					//Try to load primary language
					_itot(PRIMARYLANGID(iLanguage), acPath, 10);
					_tcscat(acPath, _T(".po"));
					if (clsUtil::ExistsFile(acPath))
					{
						mlstLanguage->LoadFromFile(acPath, TEncoding::UTF8);
					}
				}
			}
		}
	}

	//Need to load language?
	if ((!mlst1033) && (StrStrI(GetCommandLine(), _T("/SAVELANGUAGE")) != NULL))
	{
		mlst1033 = new THashedStringList();
		mlst1033->CaseSensitive = true;
		mlst1033->Duplicates = System::Classes::dupAccept;
		if (clsUtil::ExistsFile(_T("1033.po")))
		{
			mlst1033->LoadFromFile("1033.po", TEncoding::UTF8);
		}
	}
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsLanguage::Save(void)
{
    //Need to save language?
	if (mlst1033)
	{
		try
		{
			mlst1033->SaveToFile("1033.po", TEncoding::UTF8);
		}
		catch (EFCreateError &excE)
		{
		}	
	}
}


// ---------------------------------------------------------------------------
const TCHAR * __fastcall clsLanguage::Get(TCHAR *pacText)
{
	static TCHAR acRes[2048];

	String sRes = Get((String) pacText);
	_tcsncpy(acRes, sRes.c_str(), (sizeof(acRes) / sizeof(TCHAR)) - 1);
	return(acRes);
}



// ---------------------------------------------------------------------------
String __fastcall clsLanguage::Search(String psText, THashedStringList *plstLanguage)
{
	if ((plstLanguage) && (plstLanguage->Count > 0))
	{
		//Search for text to be translated
		String sSearch = "msgid \"" + psText + "\"";

		//int iLine = 0;
		int iLine = plstLanguage->IndexOf(sSearch);
		if (iLine >= 0)
		{
			String sLine;
			//Skip lines not starting with mgstr
			do
			{
				iLine++;
				sLine = plstLanguage->Strings[iLine];
			}
			while ((PosEx("msgstr \"", sLine) <= 0) && (iLine < plstLanguage->Count));
			psText = sLine;
			psText = ReplaceStr(psText, "\n", "");
			psText = psText.SubString(9, psText.Length() - 9);	//Remove first msgstr \" and last quote
			psText = ReplaceStr(psText, "\\\\", "\\");			//Unescape PO
			psText = ReplaceStr(psText, "\\n", "\n");
			psText = ReplaceStr(psText, "\\r", "\r");
			psText = ReplaceStr(psText, "\\t", "\t");
			psText = ReplaceStr(psText, "\\\"", "\"");
		}
		else
		{
			psText = "NOT_FOUND";
		}
	}
	else
	{
		psText = "NOT_FOUND";
	}
	return(psText);
}



// ---------------------------------------------------------------------------
String __fastcall clsLanguage::Get(String psText)
{
	if (!psText.IsEmpty())
	{
		String sTranslated;
		//If need to update 1033.po
		if (mlst1033)
		{
			//Not found in 1033.po
			sTranslated = Search(psText, mlst1033);
			if (sTranslated == "NOT_FOUND")
			{
				//Check if already exists
				if (mlst1033->Count <= 0)
				{
					//Write header
					mlst1033->Add("# \"Language ID: 1033 (0x0409)\"");
					mlst1033->Add("# \"Language Name: English - United States\"");
					mlst1033->Add("# \"Project-Id-Version: " + Application->Name + " " + (String) clsUtil::ExeVersion(Application->ExeName.c_str()) + "\"");
					mlst1033->Add("# \"POT-Creation-Date: " + (String) __DATE__ + "\"");
					mlst1033->Add("# \"MIME-Version: 1.0\"");
					mlst1033->Add("# \"Content-Type: text/plain; charset=ISO-8859-1\"");
					mlst1033->Add("# \"Content-Transfer-Encoding: 8bit\"");
					mlst1033->Add("# \"Language: en_US\"");
					mlst1033->Add("# \"Last-Translator: Javier Gutiérrez Chamorro\"");
					mlst1033->Add("# \"Language-Team: Javier Gutiérrez Chamorro\"");
					mlst1033->Add("# \"Plural-Forms: nplurals=2; plural=(n != 1);\"\n");
				}
				//Write text
				sTranslated = psText;
				sTranslated = ReplaceStr(sTranslated, "\\", "\\\\");			//Escape PO
				sTranslated = ReplaceStr(sTranslated, "\n", "\\n");
				sTranslated = ReplaceStr(sTranslated, "\r", "\\r");
				sTranslated = ReplaceStr(sTranslated, "\t", "\\t");
				sTranslated = ReplaceStr(sTranslated, "\"", "\\\"");
				sTranslated = "msgid \"" + sTranslated + "\"";
				mlst1033->Add(sTranslated);
				mlst1033->Add("msgstr \"\"\n");
			}
		}
		//Look on regular PO dictionary
		sTranslated = Search(psText, mlstLanguage);
		if (sTranslated != "NOT_FOUND")
		{
			psText = sTranslated;
		}
	}
	return(psText);
}



// ---------------------------------------------------------------------------
void __fastcall clsLanguage::TranslateForm(TForm *pfrmForm)
{
	EnumerateControls(pfrmForm);
}



// ---------------------------------------------------------------------------
void clsLanguage::EnumerateControls(TComponent *poControl)
{
	//TForm
	if (poControl->InheritsFrom(__classid(TForm)))
	{
		TForm *oControl = dynamic_cast<TForm *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TLabel
	else if (poControl->InheritsFrom(__classid(TLabel)))
	{
		TLabel *oControl = dynamic_cast<TLabel *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TEdit
	else if (poControl->InheritsFrom(__classid(TEdit)))
	{
		TEdit *oControl = dynamic_cast<TEdit *>(poControl);
		if (oControl)
		{
			oControl->Text = Get(oControl->Text);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TMemo
	else if (poControl->InheritsFrom(__classid(TMemo)))
	{
		TMemo *oControl = dynamic_cast<TMemo *>(poControl);
		if (oControl)
		{
			oControl->Lines->Text = Get(oControl->Lines->Text);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TSpinEdit
	else if (poControl->InheritsFrom(__classid(TSpinEdit)))
	{
		TSpinEdit *oControl = dynamic_cast<TSpinEdit *>(poControl);
		if (oControl)
		{
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TCheckBox
	else if (poControl->InheritsFrom(__classid(TCheckBox)))
	{
		TCheckBox *oControl = dynamic_cast<TCheckBox *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TComboBox
	else if (poControl->InheritsFrom(__classid(TComboBox)))
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
	else if (poControl->InheritsFrom(__classid(TImage)))
	{
		TImage *oControl = dynamic_cast<TImage *>(poControl);
		if (oControl)
		{
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TMenuItem
	else if (poControl->InheritsFrom(__classid(TMenuItem)))
	{
		TMenuItem *oControl = dynamic_cast<TMenuItem *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TButton
	else if (poControl->InheritsFrom(__classid(TButton)))
	{
		TButton *oControl = dynamic_cast<TButton *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TAction
	else if (poControl->InheritsFrom(__classid(TAction)))
	{
		TAction *oControl = dynamic_cast<TAction *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}
	//TTabSheet
	else if (poControl->InheritsFrom(__classid(TTabSheet)))
	{
		TTabSheet *oControl = dynamic_cast<TTabSheet *>(poControl);
		if (oControl)
		{
			oControl->Caption = Get(oControl->Caption);
			oControl->Hint = Get(oControl->Hint);
		}
	}

	//Childs
	for (int iControl = poControl->ComponentCount - 1; iControl >= 0; iControl--)
	{
		TComponent *oControl = dynamic_cast<TComponent *>(poControl->Components[iControl]);
		if (oControl)
		{
			EnumerateControls(oControl);
		}
	}
}
