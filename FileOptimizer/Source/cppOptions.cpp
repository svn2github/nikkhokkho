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
	cboOptimizationLevel->ItemIndex = gudtOptions.iLevel;

	if (gudtOptions.iProcessPriority == IDLE_PRIORITY_CLASS)
	{
		cboProcessPriority->ItemIndex = 0;
	}
	else if (gudtOptions.iProcessPriority == BELOW_NORMAL_PRIORITY_CLASS)
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

	//Check for updates
	if (gudtOptions.iCheckForUpdates < 0)
	{
		cboCheckForUpdates->ItemIndex = 0;
	}
	else if (gudtOptions.iCheckForUpdates == 1)
	{
		cboCheckForUpdates->ItemIndex = 1;
	}
	else if (gudtOptions.iCheckForUpdates == 0)
	{
		cboCheckForUpdates->ItemIndex = 2;
	}

	if (_tcscmp(gudtOptions.acTheme, _T("Windows")) == 0)
	{
		cboTheme->ItemIndex = 0;
	}
	else if (_tcscmp(gudtOptions.acTheme, _T("Metropolis UI Black")) == 0)
	{
		cboTheme->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acTheme, _T("Luna")) == 0)
	{
		cboTheme->ItemIndex = 2;
	}

	cboLogLevel->ItemIndex = gudtOptions.iLogLevel;

	chkKeepAttributes->Checked = gudtOptions.bKeepAttributes;
    chkDoNotUseRecycleBin->Checked = gudtOptions.bDoNotUseRecycleBin;

	chkCSSEnableTidy->Checked = gudtOptions.bCSSEnableTidy;
	if (_tcscmp(gudtOptions.acCSSTemplate, _T("low")) == 0)
	{
		cboCSSTemplate->ItemIndex = 0;
	}
	else if (_tcscmp(gudtOptions.acCSSTemplate, _T("high")) == 0)
	{
		cboCSSTemplate->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acCSSTemplate, _T("highest")) == 0)
	{
		cboCSSTemplate->ItemIndex = 2;
	}

	chkEXEDisablePETrim->Checked = gudtOptions.bEXEDisablePETrim;
	chkGZCopyMetadata->Checked = gudtOptions.bGZCopyMetadata;
	chkHTMLEnableTidy->Checked = gudtOptions.bHTMLEnableTidy;
	chkJPEGCopyMetadata->Checked = gudtOptions.bJPEGCopyMetadata;
	chkJPEGUseArithmeticEncoding->Checked = gudtOptions.bJPEGUseArithmeticEncoding;
	chkJSEnableJSMin->Checked = gudtOptions.bJSEnableJSMin;
	chkMP3CopyMetadata->Checked = gudtOptions.bMP3CopyMetadata;

	if (_tcscmp(gudtOptions.acPDFProfile, _T("none")) == 0)
	{
		cboPDFProfile->ItemIndex = 0;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("screen")) == 0)
	{
		cboPDFProfile->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("100 dpi")) == 0)
	{
		cboPDFProfile->ItemIndex = 2;
	}	
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("ebook")) == 0)
	{
		cboPDFProfile->ItemIndex = 3;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("200 dpi")) == 0)
	{
		cboPDFProfile->ItemIndex = 4;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("printer")) == 0)
	{
		cboPDFProfile->ItemIndex = 5;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("prepress")) == 0)
	{
		cboPDFProfile->ItemIndex = 6;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("600 dpi")) == 0)
	{
		cboPDFProfile->ItemIndex = 7;
	}
	chkPNGCopyMetadata->Checked = gudtOptions.bPNGCopyMetadata;
	chkZIPCopyMetadata->Checked = gudtOptions.bZIPCopyMetadata;
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butOKClick(TObject *Sender)
{
	Hide();

	gudtOptions.iLevel = cboOptimizationLevel->ItemIndex;

	if (cboProcessPriority->ItemIndex == 0)
	{
		gudtOptions.iProcessPriority = IDLE_PRIORITY_CLASS;
	}
	else if (cboProcessPriority->ItemIndex == 1)
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

	if (cboCheckForUpdates->ItemIndex == 0)
	{
		gudtOptions.iCheckForUpdates = -1;
	}
	else if (cboCheckForUpdates->ItemIndex == 1)
	{
		gudtOptions.iCheckForUpdates = 1;
	}
	else if (cboCheckForUpdates->ItemIndex == 2)
	{
		gudtOptions.iCheckForUpdates = 0;
	}

	if (cboTheme->ItemIndex == 0)
	{
		_tcscpy(gudtOptions.acTheme, _T("Windows"));
	}
	else if (cboTheme->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acTheme, _T("Metropolis UI Black"));
	}
	else if (cboTheme->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acTheme, _T("Luna"));
	}


	gudtOptions.iLogLevel = cboLogLevel->ItemIndex;
	gudtOptions.bKeepAttributes = chkKeepAttributes->Checked;
	gudtOptions.bDoNotUseRecycleBin = chkDoNotUseRecycleBin->Checked;

	gudtOptions.bCSSEnableTidy = chkCSSEnableTidy->Checked;
	if (cboCSSTemplate->ItemIndex == 0)
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("low"));
	}
	else if (cboCSSTemplate->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("high"));
	}
	else if (cboCSSTemplate->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acCSSTemplate, _T("highest"));
	}

	gudtOptions.bEXEDisablePETrim = chkEXEDisablePETrim->Checked;
	gudtOptions.bGZCopyMetadata = chkGZCopyMetadata->Checked;
	gudtOptions.bHTMLEnableTidy = chkHTMLEnableTidy->Checked;
	gudtOptions.bJPEGCopyMetadata = chkJPEGCopyMetadata->Checked;
	gudtOptions.bJPEGUseArithmeticEncoding = chkJPEGUseArithmeticEncoding->Checked;
	gudtOptions.bJSEnableJSMin = chkJSEnableJSMin->Checked;
	gudtOptions.bMP3CopyMetadata = chkMP3CopyMetadata->Checked;

	if (cboPDFProfile->ItemIndex == 0)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("none"));
	}
	else if (cboPDFProfile->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("screen"));
	}
	else if (cboPDFProfile->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("100 dpi"));
	}
	else if (cboPDFProfile->ItemIndex == 3)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("ebook"));
	}
	else if (cboPDFProfile->ItemIndex == 4)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("200 dpi"));
	}
	else if (cboPDFProfile->ItemIndex == 5)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("printer"));
	}
	else if (cboPDFProfile->ItemIndex == 6)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("prepress"));
	}
	else if (cboPDFProfile->ItemIndex == 7)
	{
		_tcscpy(gudtOptions.acPDFProfile, _T("600 dpi"));
	}
	gudtOptions.bPNGCopyMetadata = chkPNGCopyMetadata->Checked;
	gudtOptions.bZIPCopyMetadata = chkZIPCopyMetadata->Checked;

	frmMain->UpdateTheme(gudtOptions.acTheme);
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkCSSEnableTidyClick(TObject *Sender)
{
	cboCSSTemplate->Enabled = chkCSSEnableTidy->Checked;
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butCancelClick(TObject *Sender)
{
	Close();
}


//---------------------------------------------------------------------------

