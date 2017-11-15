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



// ---------------------------------------------------------------------------
__fastcall TfrmOptions::~TfrmOptions()
{
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCreate(TObject *Sender)
{
	Icon = Application->Icon;

	tabOptions->ActivePageIndex = 0;
	pagGeneral1->Hint = "General program options affecting all extensions (1/2)";
	pagGeneral2->Hint = "General program options affecting all extensions (2/2)";
	pagBMP->Hint = "Extensions affected: " + (String) KS_EXTENSION_BMP;
	pagCSS->Hint = "Extensions affected: " + (String) KS_EXTENSION_CSS;
	pagEXE->Hint = "Extensions affected: " + (String) KS_EXTENSION_EXE KS_EXTENSION_DLL;
	pagGIF->Hint = "Extensions affected: " + (String) KS_EXTENSION_GIF;
	pagGZ->Hint = "Extensions affected: " + (String) KS_EXTENSION_GZ;
	pagHTML->Hint = "Extensions affected: " + (String) KS_EXTENSION_HTML;
	pagJPEG->Hint = "Extensions affected: " + (String) KS_EXTENSION_JPG KS_EXTENSION_TIFF;
	pagJS->Hint = "Extensions affected: " + (String) KS_EXTENSION_JS;
	pagLUA->Hint = "Extensions affected: " + (String) KS_EXTENSION_LUA;
	pagMisc->Hint = "Extensions affected: " + (String) KS_EXTENSION_MISC;
	pagMP3->Hint = "Extensions affected: " + (String) KS_EXTENSION_MP3;
	pagMP4->Hint = "Extensions affected: " + (String) KS_EXTENSION_MP4;
	pagPCX->Hint = "Extensions affected: " + (String) KS_EXTENSION_PCX;
	pagPDF->Hint = "Extensions affected: " + (String) KS_EXTENSION_PDF;
	pagPNG->Hint = "Extensions affected: " + (String) KS_EXTENSION_PNG KS_EXTENSION_ICO;
	pagTGA->Hint = "Extensions affected: " + (String) KS_EXTENSION_TGA;
	pagTIFF->Hint = "Extensions affected: " + (String) KS_EXTENSION_TIFF;
	pagXML->Hint = "Extensions affected: " + (String) KS_EXTENSION_XML KS_EXTENSION_HTML;
	pagZIP->Hint = "Extensions affected: " + (String) KS_EXTENSION_ZIP;

	chkAllowDuplicates->Checked = gudtOptions.bAllowDuplicates;
	chkAllowMultipleInstances->Checked = gudtOptions.bAllowMultipleInstances;
	chkAlwaysOnTop->Checked = gudtOptions.bAlwaysOnTop;
	chkBeepWhenDone->Checked = gudtOptions.bBeepWhenDone;

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

	chkClearWhenComplete->Checked = gudtOptions.bClearWhenComplete;
	txtDisablePluginMask->Text = gudtOptions.acDisablePluginMask;
	txtDonator->Text = gudtOptions.acDonator;
	chkDoNotUseRecycleBin->Checked = gudtOptions.bDoNotUseRecycleBin;
	chkEnableCache->Checked = gudtOptions.bEnableCache;
	txtExcludeMask->Text = gudtOptions.acExcludeMask;
	cboFilenameFormat->ItemIndex = gudtOptions.iFilenameFormat;
	txtIncludeMask->Text = gudtOptions.acIncludeMask;
	chkKeepAttributes->Checked = gudtOptions.bKeepAttributes;
	spnLeanifyIterations->Value = gudtOptions.iLeanifyIterations;
	cboLogLevel->ItemIndex = gudtOptions.iLogLevel;
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

	chkShowToolBar->Checked = gudtOptions.bShowToolBar;
	chkHideAds->Checked = gudtOptions.bHideAds;
	chkShutdownWhenDone->Checked = gudtOptions.bShutdownWhenDone;
	txtTempDirectory->Text = gudtOptions.acTempDirectory;

	if (_tcscmp(gudtOptions.acTheme, _T("Metropolis UI Black")) == 0)
	{
		cboTheme->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acTheme, _T("Luna")) == 0)
	{
		cboTheme->ItemIndex = 2;
	}
	else if (_tcscmp(gudtOptions.acTheme, _T("Windows10")) == 0)
	{
		cboTheme->ItemIndex = 3;
	}
	else //Windows
	{
		cboTheme->ItemIndex = 0;
	}

	chkBMPCopyMetadata->Checked = gudtOptions.bBMPCopyMetadata;
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
	chkEXEEnableUPX->Checked = gudtOptions.bEXEEnableUPX;
	chkGIFCopyMetadata->Checked = gudtOptions.bGIFCopyMetadata;
	chkGIFAllowLossy->Checked = gudtOptions.bGIFAllowLossy;
	chkGZCopyMetadata->Checked = gudtOptions.bGZCopyMetadata;
	chkHTMLEnableTidy->Checked = gudtOptions.bHTMLEnableTidy;
	chkJPEGCopyMetadata->Checked = gudtOptions.bJPEGCopyMetadata;
	chkJPEGUseArithmeticEncoding->Checked = gudtOptions.bJPEGUseArithmeticEncoding;
	chkJPEGAllowLossy->Checked = gudtOptions.bJPEGAllowLossy;
	txtJSAdditionalExtensions->Text = gudtOptions.acJSAdditionalExtensions;
	chkJSEnableJSMin->Checked = gudtOptions.bJSEnableJSMin;
	chkLUAEnableLeanify->Checked = gudtOptions.bLUAEnableLeanify;
	chkMiscCopyMetadata->Checked = gudtOptions.bMiscCopyMetadata;
	chkMP3CopyMetadata->Checked = gudtOptions.bMP3CopyMetadata;
	chkMP4CopyMetadata->Checked = gudtOptions.bMP4CopyMetadata;
	chkPCXCopyMetadata->Checked = gudtOptions.bPCXCopyMetadata;

	if (_tcscmp(gudtOptions.acPDFProfile, _T("screen")) == 0)
	{
		cboPDFProfile->ItemIndex = 1;
	}
	else if (_tcscmp(gudtOptions.acPDFProfile, _T("ebook")) == 0)
	{
		cboPDFProfile->ItemIndex = 2;
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
	//if (_tcscmp(gudtOptions.acPDFProfile, _T("none")) == 0)
	else
	{
		cboPDFProfile->ItemIndex = 0;
	}

	spnPDFCustomDPI->Value = gudtOptions.iPDFCustomDPI;
	chkPDFSkipLayered->Checked = gudtOptions.bPDFSkipLayered;
	cboPDFProfileChange(NULL);

	chkPNGCopyMetadata->Checked = gudtOptions.bPNGCopyMetadata;
	chkPNGAllowLossy->Checked = gudtOptions.bPNGAllowLossy;
	chkTGACopyMetadata->Checked = gudtOptions.bTGACopyMetadata;
	chkTIFFCopyMetadata->Checked = gudtOptions.bTIFFCopyMetadata;
	chkXMLEnableLeanify->Checked = gudtOptions.bXMLEnableLeanify;
	chkZIPCopyMetadata->Checked = gudtOptions.bZIPCopyMetadata;
	chkZIPRecurse->Checked = gudtOptions.bZIPRecurse;
}



//---------------------------------------------------------------------------
void __fastcall TfrmOptions::butOKClick(TObject *Sender)
{
	Hide();

	gudtOptions.bAllowDuplicates = chkAllowDuplicates->Checked;
	gudtOptions.bAllowMultipleInstances = chkAllowMultipleInstances->Checked;
	gudtOptions.bAlwaysOnTop = chkAlwaysOnTop->Checked;
	gudtOptions.bBeepWhenDone = chkBeepWhenDone->Checked;

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

	gudtOptions.bClearWhenComplete = chkClearWhenComplete->Checked;
	gudtOptions.bEnableCache = chkEnableCache->Checked;
	gudtOptions.bKeepAttributes = chkKeepAttributes->Checked;
	gudtOptions.bDoNotUseRecycleBin = chkDoNotUseRecycleBin->Checked;
	_tcscpy(gudtOptions.acDisablePluginMask, txtDisablePluginMask->Text.c_str());
	_tcscpy(gudtOptions.acDonator, txtDonator->Text.c_str());
	_tcscpy(gudtOptions.acExcludeMask, txtExcludeMask->Text.c_str());
	gudtOptions.iFilenameFormat = cboFilenameFormat->ItemIndex;
	_tcscpy(gudtOptions.acIncludeMask, txtIncludeMask->Text.c_str());
	gudtOptions.bKeepAttributes = chkKeepAttributes->Checked;
	gudtOptions.iLeanifyIterations = spnLeanifyIterations->Value;
	gudtOptions.iLogLevel = cboLogLevel->ItemIndex;
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

	gudtOptions.bShutdownWhenDone = chkShutdownWhenDone->Checked;
	gudtOptions.bShowToolBar = chkShowToolBar->Checked;
	gudtOptions.bHideAds = chkHideAds->Checked;

	_tcscpy(gudtOptions.acTempDirectory, txtTempDirectory->Text.c_str());

	if (cboTheme->ItemIndex == 1)
	{
		_tcscpy(gudtOptions.acTheme, _T("Metropolis UI Black"));
	}
	else if (cboTheme->ItemIndex == 2)
	{
		_tcscpy(gudtOptions.acTheme, _T("Luna"));
	}
	else if (cboTheme->ItemIndex == 3)
	{
		_tcscpy(gudtOptions.acTheme, _T("Windows10"));
	}
	else //0
	{
		_tcscpy(gudtOptions.acTheme, _T("Windows"));
	}

	gudtOptions.bBMPCopyMetadata = chkBMPCopyMetadata->Checked;

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
	gudtOptions.bEXEEnableUPX = chkEXEEnableUPX->Checked;
	gudtOptions.bGIFCopyMetadata = chkGIFCopyMetadata->Checked;
	gudtOptions.bGIFAllowLossy = chkGIFAllowLossy->Checked;
	gudtOptions.bGZCopyMetadata = chkGZCopyMetadata->Checked;
	gudtOptions.bHTMLEnableTidy = chkHTMLEnableTidy->Checked;
	gudtOptions.bJPEGCopyMetadata = chkJPEGCopyMetadata->Checked;
	gudtOptions.bJPEGUseArithmeticEncoding = chkJPEGUseArithmeticEncoding->Checked;
	gudtOptions.bJPEGAllowLossy = chkJPEGAllowLossy->Checked;
	_tcscpy(gudtOptions.acJSAdditionalExtensions, txtJSAdditionalExtensions->Text.c_str());
	gudtOptions.bJSEnableJSMin = chkJSEnableJSMin->Checked;
	gudtOptions.bLUAEnableLeanify = chkLUAEnableLeanify->Checked;
	gudtOptions.bMiscCopyMetadata = chkMiscCopyMetadata->Checked;
	gudtOptions.bMP3CopyMetadata = chkMP3CopyMetadata->Checked;
	gudtOptions.bMP4CopyMetadata = chkMP4CopyMetadata->Checked;
	gudtOptions.bPCXCopyMetadata = chkPCXCopyMetadata->Checked;

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
	gudtOptions.bPDFSkipLayered = chkPDFSkipLayered->Checked;

	gudtOptions.bPNGCopyMetadata = chkPNGCopyMetadata->Checked;
	gudtOptions.bPNGAllowLossy = chkPNGAllowLossy->Checked;
	gudtOptions.bTGACopyMetadata = chkTGACopyMetadata->Checked;
	gudtOptions.bTIFFCopyMetadata = chkTIFFCopyMetadata->Checked;
	gudtOptions.bXMLEnableLeanify = chkXMLEnableLeanify->Checked;
	gudtOptions.bZIPCopyMetadata = chkZIPCopyMetadata->Checked;
	gudtOptions.bZIPRecurse = chkZIPRecurse->Checked;

	frmMain->SaveOptions();
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
	Hide();
	DeleteFile(clsUtil::GetIniPath());
	frmMain->LoadOptions();
	frmMain->UpdateTheme(gudtOptions.acTheme);
	Close();
}


//---------------------------------------------------------------------------

