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
	for (int iControl = poControl->ControlCount - 1; iControl >= 0; iControl--)
	{
		TControl *oControl = poControl->Controls[iControl];
		String s = oControl->Name;

		if (oControl->ClassType() == __classid(TLabel))
		{
			((TLabel *) oControl)->Caption = Translate(((TLabel *) oControl)->Caption);
		}
		else if (oControl->ClassType() == __classid(TEdit))
		{
			((TEdit *) oControl)->Text = Translate(((TEdit *) oControl)->Text);
		}

		if (oControl->ClassType() == __classid(TWinControl))
		{
			EnumerateControls((TWinControl *) oControl);
		}
	}
}



// ---------------------------------------------------------------------------
String __fastcall clsLanguage::Translate(String psText)
{
	bool bFound = false;
	FILE *pLanguage;
	TCHAR acLine[2048];


	pLanguage = _tfopen(GetLanguagePath(), _T("r"));
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


