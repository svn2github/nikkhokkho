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

	clsUtil::GetFileVersionField(Application->ExeName.c_str(), (TCHAR *) _T("LegalCopyright"), acName, sizeof(acName) / sizeof(TCHAR));
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

