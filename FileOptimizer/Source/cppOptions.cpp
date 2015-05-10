// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
TfrmOptions *frmOptions;



//---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner): TForm(Owner)
{
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCreate(TObject *Sender)
{
	pagGeneral->Hint = "General program options affecting all extensions";
	pagCSS->Hint = "Extensions affected: " + (String) KS_EXTENSION_CSS;
	pagEXE->Hint = "Extensions affected: " + (String) KS_EXTENSION_EXE KS_EXTENSION_DLL;
	pagGZ->Hint = "Extensions affected: " + (String) KS_EXTENSION_GZ;
	pagHTML->Hint = "Extensions affected: " + (String) KS_EXTENSION_HTML;
	pagJPEG->Hint = "Extensions affected: " + (String) KS_EXTENSION_JPG KS_EXTENSION_TIF;
	pagJS->Hint = "Extensions affected: " + (String) KS_EXTENSION_JS;
	pagLUA->Hint = "Extensions affected: " + (String) KS_EXTENSION_LUA;
	pagMP3->Hint = "Extensions affected: " + (String) KS_EXTENSION_MP3;
	pagPDF->Hint = "Extensions affected: " + (String) KS_EXTENSION_PDF;
	pagPNG->Hint = "Extensions affected: " + (String) KS_EXTENSION_PNG KS_EXTENSION_ICO;
	pagXML->Hint = "Extensions affected: " + (String) KS_EXTENSION_XML KS_EXTENSION_HTML;
	pagZIP->Hint = "Extensions affected: " + (String) KS_EXTENSION_ZIP;

	cboOptimizationLevel->ItemIndex = gudtOptions.iLevel;

	if (gudtOptions.iProcessPriority == BELOW_NORMAL_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 1;
	}
	else if (gudtOptions.iProcessPriority == NORMAL_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 2;
	}
	else if (gudtOptions.iProcessPriority == ABOVE_NORMAL_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 3;
	}
	else if (gudtOptions.iProcessPriority == HIGH_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 4;
	}
	else if (gudtOptions.iProcessPriority == REALTIME_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 5;
	}
	else //IDLE_PRIORITY_CLASS
	{
		cboProcessPriority->ItemIndex = 0;
	}
	

	//Check for updates
	if (gudtOptions.iCheckForUpdates < 0)
	{
		cboCheckForUpdates->ItemIndex = 0;
	}
	else if (gudtOptions.iCheckForUpdates == 0)
	{
		cboCheckForUpdates->ItemIndex = 2;
	}
	else //iCheckForUpdates == 1
	{
		cboCheckForUpdates->ItemIndex = 1;
	}
	

	if (_tcscmp(gudtOptions.acTheme, _T("Metropolis UI Black")) == 0)
	{
		cboTheme->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acTheme, _T("Luna")) == 0)
	{
		cboTheme->ItemIndex = 2;
	}
	else //Windows
	{
		cboTheme->ItemIndex = 0;
	}
	

	cboLogLevel->ItemIndex = gudtOptions.iLogLevel;

	chkKeepAttributes->Checked = gudtOptions.bKeepAttributes;
	chkDoNotUseRecycleBin->Checked = gudtOptions.bDoNotUseRecycleBin;
	txtExcludeMask->Text = gudtOptions.acExcludeMask;

	chkCSSEnableTidy->Checked = gudtOptions.bCSSEnableTidy;
	if (_tcscmp(gudtOptions.acCSSTemplate, _T("high")) == 0)
	{
		cboCSSTemplate->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acCSSTemplate, _T("highest")) == 0)
	{
		cboCSSTemplate->ItemIndex = 2;
	}
	else //low
	{
		cboCSSTemplate->ItemIndex = 0;
	}
	

	chkEXEDisablePETrim->Checked = gudtOptions.bEXEDisablePETrim;
	chkGZCopyMetadata->Checked = gudtOptions.bGZCopyMetadata;
	chkHTMLEnableTidy->Checked = gudtOptions.bHTMLEnableTidy;
	chkJPEGCopyMetadata->Checked = gudtOptions.bJPEGCopyMetadata;
	chkJPEGUseArithmeticEncoding->Checked = gudtOptions.bJPEGUseArithmeticEncoding;
	chkJSEnableJSMin->Checked = gudtOptions.bJSEnableJSMin;
	chkLUAEnableLeanify->Checked = gudtOptions.bLUAEnableLeanify;
	chkMP3CopyMetadata->Checked = gudtOptions.bMP3CopyMetadata;

	if (_tcscmp(gudtOptions.acPDFProfile, _T("none")) == 0)
	{
		cboPDFProfile->ItemIndex = 0;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("screen")) == 0)
	{
		cboPDFProfile->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("printer")) == 0)
	{
		cboPDFProfile->ItemIndex = 3;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("prepress")) == 0)
	{
		cboPDFProfile->ItemIndex = 4;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("Custom")) == 0)
	{
		cboPDFProfile->ItemIndex = 5;
	}
	else //ebook
	{
		cboPDFProfile->ItemIndex = 2;
	}
	
	spnPDFCustomDPI->Value = gudtOptions.iPDFCustomDPI;
	cboPDFProfileChange(NULL);

	chkPNGCopyMetadata->Checked = gudtOptions.bPNGCopyMetadata;
	chkPNGAllowLossy->Checked = gudtOptions.bPNGAllowLossy;
	chkXMLEnableLeanify->Checked = gudtOptions.bXMLEnableLeanify;
	chkZIPCopyMetadata->Checked = gudtOptions.bZIPCopyMetadata;
	chkZIPRecurse->Checked = gudtOptions.bZIPRecurse;
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butOKClick(TObject *Sender)
{
	Hide();

	gudtOptions.iLevel = cboOptimizationLevel->ItemIndex;

	if (cboProcessPriority->ItemIndex == 1)
	{
		gudtOptions.iProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
	}
	else if (cboProcessPriority->ItemIndex == 2)
	{
		gudtOptions.iProcessPriority = NORMAL_PRIORITY_CLASS;
	}
	else if (cboProcessPriority->ItemIndex == 3)
	{
		gudtOptions.iProcessPriority = ABOVE_NORMAL_PRIORITY_CLASS;
	}
	else if (cboProcessPriority->ItemIndex == 4)
	{
		gudtOptions.iProcessPriority = HIGH_PRIORITY_CLASS;
	}
	else if (cboProcessPriority->ItemIndex == 5)
	{
		gudtOptions.iProcessPriority = REALTIME_PRIORITY_CLASS;
	}
	else //0
	{
		gudtOptions.iProcessPriority = IDLE_PRIORITY_CLASS;
	}
	

	if (cboCheckForUpdates->ItemIndex == 0)
	{
		gudtOptions.iCheckForUpdates = -1;
	}
	else if (cboCheckForUpdates->ItemIndex == 2)
	{
		gudtOptions.iCheckForUpdates = 0;
	}
	else //1
	{
		gudtOptions.iCheckForUpdates = 1;
	}
	

	if (cboTheme->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acTheme, _T("Metropolis UI Black"));
	}
	else if (cboTheme->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acTheme, _T("Luna"));
	}
	else //0
	{
		_tcscpy(gudtOptions.acTheme, _T("Windows"));
	}
	


	gudtOptions.iLogLevel = cboLogLevel->ItemIndex;
	gudtOptions.bKeepAttributes = chkKeepAttributes->Checked;
	gudtOptions.bDoNotUseRecycleBin = chkDoNotUseRecycleBin->Checked;
	_tcscpy(gudtOptions.acExcludeMask, txtExcludeMask->Text.c_str());

	gudtOptions.bCSSEnableTidy = chkCSSEnableTidy->Checked;
	if (cboCSSTemplate->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("high"));
	}
	else if (cboCSSTemplate->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("highest"));
	}
	else //0
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("low"));
	}


	gudtOptions.bEXEDisablePETrim = chkEXEDisablePETrim->Checked;
	gudtOptions.bGZCopyMetadata = chkGZCopyMetadata->Checked;
	gudtOptions.bHTMLEnableTidy = chkHTMLEnableTidy->Checked;
	gudtOptions.bJPEGCopyMetadata = chkJPEGCopyMetadata->Checked;
	gudtOptions.bJPEGUseArithmeticEncoding = chkJPEGUseArithmeticEncoding->Checked;
	gudtOptions.bJSEnableJSMin = chkJSEnableJSMin->Checked;
	gudtOptions.bLUAEnableLeanify = chkLUAEnableLeanify->Checked;
	gudtOptions.bMP3CopyMetadata = chkMP3CopyMetadata->Checked;

	if (cboPDFProfile->ItemIndex == 0)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("none"));
	}
	else if (cboPDFProfile->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("screen"));
	}
	else if (cboPDFProfile->ItemIndex == 3)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("printer"));
	}
	else if (cboPDFProfile->ItemIndex == 4)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("prepress"));
	}
	else if (cboPDFProfile->ItemIndex == 5)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("Custom"));
	}
	else //2
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("ebook"));
	}
	
	gudtOptions.iPDFCustomDPI = spnPDFCustomDPI->Value;

	gudtOptions.bPNGCopyMetadata = chkPNGCopyMetadata->Checked;
	gudtOptions.bPNGAllowLossy = chkPNGAllowLossy->Checked;
	gudtOptions.bXMLEnableLeanify = chkXMLEnableLeanify->Checked;
	gudtOptions.bZIPCopyMetadata = chkZIPCopyMetadata->Checked;
	gudtOptions.bZIPRecurse = chkZIPRecurse->Checked;

	frmMain->UpdateTheme(gudtOptions.acTheme);
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkCSSEnableTidyClick(TObject *Sender)
{
	cboCSSTemplate->Enabled = chkCSSEnableTidy->Checked;
}


//---------------------------------------------------------------------------
void __fastcall TfrmOptions::cboPDFProfileChange(TObject *Sender)
{
	spnPDFCustomDPI->Enabled = (cboPDFProfile->ItemIndex == 5);
}


//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butCancelClick(TObject *Sender)
{
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butRestoreDefaultsClick(TObject *Sender)
{
	DeleteFile(clsUtil::GetIniPath());
	frmMain->FormCreate(Sender);
	FormCreate(Sender);
}


//---------------------------------------------------------------------------

