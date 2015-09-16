// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


// ---------------------------------------------------------------------------
TfrmAbout *frmAbout;


//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner): TForm(Owner)
{
}



//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
	TCHAR acName[256];


	Icon = Application->Icon;

	lblProduct->Caption = Application->Name;
	lblProduct->Caption = lblProduct->Caption +  " " + clsUtil::ExeVersion(Application->ExeName.c_str());
	#if defined(_WIN64)
		lblProduct->Caption = lblProduct->Caption + " (x64)";
	#else
		lblProduct->Caption = lblProduct->Caption + " (x86)";
	#endif
	lblDetail->Caption = __DATE__;

	GetFileVersionField(Application->ExeName.c_str(), (TCHAR *) _T("LegalCopyright"), acName, sizeof(acName));
	lblCopyright->Caption = acName;
    lblCopyright->Hint = KS_APP_URL;
}



//---------------------------------------------------------------------------
void __fastcall TfrmAbout::butCloseClick(TObject *Sender)
{
	Hide();
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblCopyrightClick(TObject *Sender)
{
	ShellExecute(0, _T("open"), KS_APP_URL, _T(""), _T(""), SW_SHOWNORMAL);
}


//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	//VCL does not handle default/cancel in the close button because of the focus on the memo, so let's simulate
	if ((Key == VK_ESCAPE) || (Key == VK_RETURN))
	{
		Close();
	}
}



//---------------------------------------------------------------------------
int __fastcall TfrmAbout::GetFileVersionField(const TCHAR *fn, const TCHAR *info, TCHAR *ret, int len)
{
	DWORD hVersion;
	DWORD vis = GetFileVersionInfoSize(fn, &hVersion);


	if (vis == 0)
	{
		return(0);
	}
	void *vData;
	vData = (void *) new TCHAR[(UINT) vis];

	if (!GetFileVersionInfo(fn, hVersion, vis, vData))
	{
		//delete vData;
		delete (TCHAR *) vData;
		return(0);
	}
	TCHAR vn[100];
	_tcscpy(vn, _T("\\VarFileInfo\\Translation"));

	LPVOID transblock;
	UINT vsize;

	BOOL res = VerQueryValue(vData, vn, &transblock, &vsize);
	if (!res)
	{
		//delete vData;
		delete (TCHAR *) vData;
		return 0;
	}
	// Swap the words so wsprintf will print the lang-charset in the correct format.
	*(DWORD *) transblock = MAKELONG(HIWORD(*(DWORD *) transblock), LOWORD(*(DWORD *) transblock));
	_stprintf(vn, _T("\\StringFileInfo\\%08lx\\%s"),*(DWORD *) transblock, info);
	TCHAR *ver;
	res = VerQueryValue(vData, vn, (LPVOID*) &ver, &vsize);
	if (!res)
	{
		//delete vData;
		delete (TCHAR *) vData;
		return(0);
	}
	int vlen = _tcsclen(ver);
	if (ret != NULL)
	{
		int clen = vlen+1;
		if (clen >= len-1)
			clen = len-1;
		// ie. we'll try to copy the \0 in vData, but we'll leave space
		// for the thing.
		for (int i = 0; i < clen; i++)
			ret[i] = ver[i];
		ret[len-1] = 0;
	}
  //delete vData;
  delete (TCHAR *) vData;
  return(vlen);
}


//---------------------------------------------------------------------------

