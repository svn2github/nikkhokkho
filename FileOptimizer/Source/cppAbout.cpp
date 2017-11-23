// ---------------------------------------------------------------------------
#include "cppAbout.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


// ---------------------------------------------------------------------------
TfrmAbout *frmAbout;


//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner): TForm(Owner)
{
}



// ---------------------------------------------------------------------------
__fastcall TfrmAbout::~TfrmAbout()
{
}




//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
	TCHAR acName[256];


	clsLanguage::TranslateForm(this);

	Icon = Application->Icon;

	lblProduct->Caption = Application->Name;
	lblProduct->Caption = lblProduct->Caption +  " " + clsUtil::ExeVersion(Application->ExeName.c_str());
	#if defined(_WIN64)
		lblProduct->Caption = lblProduct->Caption + " (x64)";
	#else
		lblProduct->Caption = lblProduct->Caption + " (x86)";
	#endif
	lblDetail->Caption = __DATE__;

	clsUtil::GetFileVersionField(Application->ExeName.c_str(), (TCHAR *) _T("LegalCopyright"), acName, (sizeof(acName) / sizeof(TCHAR)) - 1);
	lblCopyright->Caption = acName;
	lblCopyright->Hint = KS_APP_URL;

	#if ((__BORLANDC__ >= 0x0630) && (__BORLANDC__ <= 0x0639))
		imgAbout->Hint = "Embarcadero C++ Builder XE";
	#elif ((__BORLANDC__ >= 0x0640) && (__BORLANDC__ <= 0x0649))
		imgAbout->Hint = "Embarcadero C++ Builder XE2";
	#elif ((__BORLANDC__ >= 0x0650) && (__BORLANDC__ <= 0x0659))
		imgAbout->Hint = "Embarcadero C++ Builder XE3";
	#elif ((__BORLANDC__ >= 0x0660) && (__BORLANDC__ <= 0x0669))
		imgAbout->Hint = "Embarcadero C++ Builder XE4";
	#elif ((__BORLANDC__ >= 0x0670) && (__BORLANDC__ <= 0x0679))
		imgAbout->Hint = "Embarcadero C++ Builder XE5";
	#elif ((__BORLANDC__ >= 0x0680) && (__BORLANDC__ <= 0x0689))
		imgAbout->Hint = "Embarcadero C++ Builder XE6";
	#elif ((__BORLANDC__ >= 0x0690) && (__BORLANDC__ <= 0x0699))
		imgAbout->Hint = "Embarcadero C++ Builder XE7";
	#elif ((__BORLANDC__ >= 0x0700) && (__BORLANDC__ <= 0x0709))
		imgAbout->Hint = "Embarcadero C++ Builder XE8";
	#elif ((__BORLANDC__ >= 0x0710) && (__BORLANDC__ <= 0x0719))
		imgAbout->Hint = "Embarcadero C++ Builder 10 Seattle";
	#elif ((__BORLANDC__ >= 0x0720) && (__BORLANDC__ <= 0x0729))
		imgAbout->Hint = "Embarcadero C++ Builder 10.1 Berlin";
	#elif ((__BORLANDC__ >= 0x0730) && (__BORLANDC__ <= 0x0739))
		imgAbout->Hint = "Embarcadero C++ Builder 10.2 Tokyo";
	#elif ((__BORLANDC__ >= 0x0740) && (__BORLANDC__ <= 0x0749))
		imgAbout->Hint = "Embarcadero C++ Builder 10.3";
	#else
		imgAbout->Hint = "Borland/Inprise/CodeGear/Embarcadero C++ Builder";
	#endif
	imgAbout->Hint += " (" + (String) __BORLANDC__ + ")";

	#if defined (__clang__)
		imgAbout->Hint += ". Clang " + (String) __clang_version__;
	#endif

	#if defined (_DEBUG)
		imgAbout->Hint += ". DEBUG";
	#endif
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

