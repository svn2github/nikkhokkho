// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"


// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



// ---------------------------------------------------------------------------
TfrmMain *frmMain = NULL;
struct udtOptions gudtOptions  = {};
//SYSTEM_INFO gudtSystemInfo = {};
bool gbProcess = false;
bool gbStop = false;
unsigned int miStartTicks;


// ---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner)
{
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	TCHAR acPath[PATH_MAX];


	Icon = Application->Icon;
	clsUtil::LoadForm(this);
	grdFiles->ColWidths[KI_GRID_FILE] = GetOption(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[KI_GRID_FILE]);
	grdFiles->ColWidths[KI_GRID_EXTENSION] = GetOption(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[KI_GRID_EXTENSION]);
	grdFiles->ColWidths[KI_GRID_ORIGINAL] = GetOption(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[KI_GRID_ORIGINAL]);
	grdFiles->ColWidths[KI_GRID_OPTIMIZED] = GetOption(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[KI_GRID_OPTIMIZED]);
	grdFiles->ColWidths[KI_GRID_STATUS] = GetOption(Name.c_str(), _T("Col4Width"), grdFiles->ColWidths[KI_GRID_STATUS]);
	gudtOptions.bBMPCopyMetadata = GetOption(_T("Options"), _T("BMPCopyMetadata"), false);
	gudtOptions.bCSSEnableTidy = GetOption(_T("Options"), _T("CSSEnableTidy"), false);
	_tcscpy(gudtOptions.acCSSTemplate, GetOption(_T("Options"), _T("CSSTemplate"), _T("low")));
	gudtOptions.bEXEDisablePETrim = GetOption(_T("Options"), _T("EXEDisablePETrim"), false);
	gudtOptions.bEXEEnableUPX = GetOption(_T("Options"), _T("EXEEnableUPX"), false);
	gudtOptions.bGIFCopyMetadata = GetOption(_T("Options"), _T("GIFCopyMetadata"), false);
	gudtOptions.bGIFAllowLossy = GetOption(_T("Options"), _T("GIFAllowLossy"), false);
	gudtOptions.bGZCopyMetadata = GetOption(_T("Options"), _T("GZCopyMetadata"), false);
	gudtOptions.bHTMLEnableTidy = GetOption(_T("Options"), _T("HTMLEnableTidy"), false);
	gudtOptions.bJPEGCopyMetadata = GetOption(_T("Options"), _T("JPEGCopyMetadata"), false);
	gudtOptions.bJPEGUseArithmeticEncoding = GetOption(_T("Options"), _T("JPEGUseArithmeticEncoding"), false);
	gudtOptions.bJPEGAllowLossy = GetOption(_T("Options"), _T("JPEGAllowLossy"), false);
	gudtOptions.bJSEnableJSMin = GetOption(_T("Options"), _T("JSEnableJSMin"), false);
	_tcscpy(gudtOptions.acJSAdditionalExtensions, GetOption(_T("Options"), _T("JSAdditionalExtensions"), _T("")));
	gudtOptions.bLUAEnableLeanify = GetOption(_T("Options"), _T("LUAEnableLeanify"), false);
	gudtOptions.bMiscCopyMetadata = GetOption(_T("Options"), _T("MiscCopyMetadata"), false);
	gudtOptions.bMP3CopyMetadata = GetOption(_T("Options"), _T("MP3CopyMetadata"), false);
	gudtOptions.bPCXCopyMetadata = GetOption(_T("Options"), _T("PCXCopyMetadata"), false);
	_tcscpy(gudtOptions.acPDFProfile, GetOption(_T("Options"), _T("PDFProfile"), _T("none")));
	gudtOptions.iPDFCustomDPI = GetOption(_T("Options"), _T("PDFCustomDPI"), 150);
	gudtOptions.bPDFSkipLayered = GetOption(_T("Options"), _T("PDFSkipLayered"), false);
	gudtOptions.bPNGCopyMetadata = GetOption(_T("Options"), _T("PNGCopyMetadata"), false);
	gudtOptions.bPNGAllowLossy = GetOption(_T("Options"), _T("PNGAllowLossy"), false);
	gudtOptions.bTIFFCopyMetadata = GetOption(_T("Options"), _T("TIFFCopyMetadata"), false);
	gudtOptions.bXMLEnableLeanify = GetOption(_T("Options"), _T("XMLEnableLeanify"), false);
	gudtOptions.bZIPCopyMetadata = GetOption(_T("Options"), _T("ZIPCopyMetadata"), false);
	gudtOptions.bZIPRecurse = GetOption(_T("Options"), _T("ZIPRecurse"), false);
	gudtOptions.bKeepAttributes = GetOption(_T("Options"), _T("KeepAttributes"), false);
	gudtOptions.bDoNotUseRecycleBin = GetOption(_T("Options"), _T("DoNotUseRecycleBin"), false);
	_tcscpy(gudtOptions.acIncludeMask, GetOption(_T("Options"), _T("IncludeMask"), _T("")));
	_tcscpy(gudtOptions.acExcludeMask, GetOption(_T("Options"), _T("ExcludeMask"), _T("")));
	_tcscpy(gudtOptions.acDisablePluginMask, GetOption(_T("Options"), _T("DisablePluginMask"), _T("")));
	gudtOptions.bBeepWhenDone = GetOption(_T("Options"), _T("BeepWhenDone"), false);
	gudtOptions.bShutdownWhenDone = GetOption(_T("Options"), _T("ShutdownWhenDone"), false);
	gudtOptions.bAlwaysOnTop = GetOption(_T("Options"), _T("AlwaysOnTop"), false);
	gudtOptions.bAllowDuplicates = GetOption(_T("Options"), _T("AllowDuplicates"), false);
	gudtOptions.iLevel = GetOption(_T("Options"), _T("Level"), 5);
	gudtOptions.iProcessPriority = GetOption(_T("Options"), _T("ProcessPriority"), IDLE_PRIORITY_CLASS);
	gudtOptions.iCheckForUpdates = GetOption(_T("Options"), _T("CheckForUpdates"), 1);
	gudtOptions.iLogLevel = GetOption(_T("Options"), _T("LogLevel"), 0);
	gudtOptions.iFilenameFormat = GetOption(_T("Options"), _T("FilenameFormat"), 0);
	gudtOptions.iLeanifyIterations = GetOption(_T("Options"), _T("LeanifyIterations"), -1);
	//Embarcadero themes have conflicts with Windows 10 Anniversay update, so we get back to default Windows one.
	_tcscpy(gudtOptions.acTheme, GetOption(_T("Options"), _T("Theme"), _T("Windows")));

	//_tcscpy(gudtOptions.acVersion, GetOption(_T("Options"), _T("Version"), clsUtil::ExeVersion(Application->ExeName.c_str())));

	_tcscpy(gudtOptions.acTempDirectory, GetOption(_T("Options"), _T("TempDirectory"), _T("")));

	miStartTicks = GetTickCount();
	gudtOptions.lStatTime = (unsigned long long) GetOption(_T("Statistics"), _T("Time"), 0);
	gudtOptions.iStatOpens = (unsigned int) GetOption(_T("Statistics"), _T("Opens"), 0);
	gudtOptions.iStatOpens++;
	gudtOptions.iStatFiles = (unsigned int) GetOption(_T("Statistics"), _T("Files"), 0);
	gudtOptions.lStatTotalBytes = (unsigned long long) GetOption(_T("Statistics"), _T("TotalBytes"), 0);
	gudtOptions.lStatSavedBytes = (unsigned long long) GetOption(_T("Statistics"), _T("SavedBytes"), 0);
	randomize();
	gudtOptions.iStatSession = (unsigned int) GetOption(_T("Statistics"), _T("Session"), random(INT_MAX));

	GetModuleFileName(NULL, acPath, sizeof(acPath) - 1);
	_tcscpy(acPath, clsUtil::ExeVersion(acPath));

	_tcscpy(gudtOptions.acVersion, GetOption(_T("Options"), _T("Version"), acPath));
	
	clsUtil::GetFileVersionField(Application->ExeName.c_str(), (TCHAR *) _T("LegalCopyright"), acPath, sizeof(acPath) / sizeof(TCHAR));
	lblCopyright->Caption = acPath;

	pgbProgress->Parent = stbMain;
	actClearExecute(Sender);

	FormResize(Sender);

	SetPriorityClass(GetCurrentProcess(), (unsigned long) gudtOptions.iProcessPriority);

	//GetSystemInfo(&gudtSystemInfo);

	UpdateTheme(gudtOptions.acTheme);
}


// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	clsUtil::SaveForm(this);

	clsUtil::SetIni(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[KI_GRID_FILE]);
	clsUtil::SetIni(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[KI_GRID_EXTENSION]);
	clsUtil::SetIni(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[KI_GRID_ORIGINAL]);
	clsUtil::SetIni(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[KI_GRID_OPTIMIZED]);
	clsUtil::SetIni(Name.c_str(), _T("Col4Width"), grdFiles->ColWidths[KI_GRID_STATUS]);
	clsUtil::SetIni(_T("Options"), _T("BMPCopyMetadata"), gudtOptions.bBMPCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("CSSEnableTidy"), gudtOptions.bCSSEnableTidy, _T("Boolean. Default: false. Enable tidy. Results in smaller files, but can happen they are not editable anymore."));
	clsUtil::SetIni(_T("Options"), _T("CSSTemplate"), gudtOptions.acCSSTemplate, _T("String. Default 'low'. Compression template, from safer and worse compression, to highest compression."));
	clsUtil::SetIni(_T("Options"), _T("EXEDisablePETrim"), gudtOptions.bEXEDisablePETrim, _T("Boolean. Default: false. Disable PETrim. When enabled, PETrim will not be used, resulting in less EXE corruption at the cost of larger file size."));
	clsUtil::SetIni(_T("Options"), _T("EXEEnableUPX"), gudtOptions.bEXEEnableUPX, _T("Boolean. Default: false. Enable UPX executable compression. When enabled, UPX will not be used, resulting EXE and DLL size reduction at the cost of runtime decompression."));
	clsUtil::SetIni(_T("Options"), _T("GIFCopyMetadata"), gudtOptions.bGIFCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("GIFAllowLossy"), gudtOptions.bGIFAllowLossy, _T("Boolean. Default: false. Allowing lossy optimizations will get higher files reduction at the cost of some quality loss, even if visually unnoticeable or not."));
	clsUtil::SetIni(_T("Options"), _T("GZCopyMetadata"), gudtOptions.bGZCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("HTMLEnableTidy"), gudtOptions.bHTMLEnableTidy, _T("Boolean. Default: false. Enable Tidy. Results in smaller files, but can happen they are not editable anymore. Note that this applies to both SVG and HTML file types."));
	clsUtil::SetIni(_T("Options"), _T("JPEGCopyMetadata"), gudtOptions.bJPEGCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information"));
	clsUtil::SetIni(_T("Options"), _T("JPEGUseArithmeticEncoding"), gudtOptions.bJPEGUseArithmeticEncoding, _T("Boolean. Default: false. Arithmetic encoding gives additional saving reductions, but is incompatible with most programs."));
	clsUtil::SetIni(_T("Options"), _T("JPEGAllowLossy"), gudtOptions.bJPEGAllowLossy, _T("Boolean. Default: false. Allowing lossy optimizations will get higher files reduction at the cost of some quality loss, even if visually unnoticeable or not."));
	clsUtil::SetIni(_T("Options"), _T("JSEnableJSMin"), gudtOptions.bJSEnableJSMin, _T("Boolean. Default: false. Enable jsmin. Results in smaller files, but can happen they are not editable anymore."));
	clsUtil::SetIni(_T("Options"), _T("JSAdditionalExtensions"), gudtOptions.acJSAdditionalExtensions, _T("String. Default: ''. Add extra extensions to be threated as JS/JSON."));
	clsUtil::SetIni(_T("Options"), _T("LUAEnableLeanify"), gudtOptions.bLUAEnableLeanify, _T("Boolean. Default: false. Enable Leanify. Results in smaller files, but can happen they are not editable anymore."));
	clsUtil::SetIni(_T("Options"), _T("MiscCopyMetadata"), gudtOptions.bMiscCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("MP3CopyMetadata"), gudtOptions.bMP3CopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("PCXCopyMetadata"), gudtOptions.bPCXCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information."));
	clsUtil::SetIni(_T("Options"), _T("PDFProfile"), gudtOptions.acPDFProfile, _T("String. Default 'none'. Compression profile, from less size, to best quality."));
	clsUtil::SetIni(_T("Options"), _T("PDFCustomDPI"), gudtOptions.iPDFCustomDPI, _T("Number. Default: 150. When custom profile is choosen, it allows you to specify a custom DPI for downsampling images"));
	clsUtil::SetIni(_T("Options"), _T("PDFSkipLayered"), gudtOptions.bPDFSkipLayered, _T("Boolean. Default: false. Skip processing of PDF files containing layered objects. Results in more compatible files with higher size."));
	clsUtil::SetIni(_T("Options"), _T("PNGCopyMetadata"), gudtOptions.bPNGCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information"));
	clsUtil::SetIni(_T("Options"), _T("PNGAllowLossy"), gudtOptions.bPNGAllowLossy, _T("Boolean. Default: false. Allowing lossy optimizations will get higher files reduction at the cost of some quality loss, even if visually unnoticeable or not."));
	clsUtil::SetIni(_T("Options"), _T("TIFFCopyMetadata"), gudtOptions.bTIFFCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information"));
	clsUtil::SetIni(_T("Options"), _T("XMLEnableLeanify"), gudtOptions.bXMLEnableLeanify, _T("Boolean. Default: false. Enable Leanify. Results in smaller files, but can happen they are not editable anymore."));
	clsUtil::SetIni(_T("Options"), _T("ZIPCopyMetadata"), gudtOptions.bZIPCopyMetadata, _T("Boolean. Default: false. Copy file metadata. Else strip all unneded information"));
	clsUtil::SetIni(_T("Options"), _T("ZIPRecurse"), gudtOptions.bZIPRecurse, _T("Boolean. Default: false. Enable optimization inside archives (recursive optimization)."));
	clsUtil::SetIni(_T("Options"), _T("KeepAttributes"), gudtOptions.bKeepAttributes, _T("Boolean. Default: false. Keep original readonly, system, hidden and archive attributes as well as creation and modification timestamps."));
	clsUtil::SetIni(_T("Options"), _T("DoNotUseRecycleBin"), gudtOptions.bDoNotUseRecycleBin, _T("Boolean. Default: false. When checked original files will not be backed up in the system trashcan."));
	clsUtil::SetIni(_T("Options"), _T("IncludeMask"), gudtOptions.acIncludeMask, _T("String. Default: ''. If not empty, only files containing this mask (substring) on name or path will be included from optimization. You can use semicolon to specify more than one substring being included"));
	clsUtil::SetIni(_T("Options"), _T("ExcludeMask"), gudtOptions.acExcludeMask, _T("String. Default: ''. Files containing this mask (substring) on name or path will be excluded from optimization. You can use semicolon to specify more than one substring being excluded"));
	clsUtil::SetIni(_T("Options"), _T("DisablePluginMask"), gudtOptions.acDisablePluginMask, _T("String. Default: ''. Allow excluding execution of certain plugins. It is case insensitive, and allows more than one item to be specified by using semicolon as separator."));
	clsUtil::SetIni(_T("Options"), _T("BeepWhenDone"), gudtOptions.bBeepWhenDone, _T("Boolean. Default: false. Beep the speaker when optimization completes."));
	clsUtil::SetIni(_T("Options"), _T("ShutdownWhenDone"), gudtOptions.bShutdownWhenDone, _T("Boolean. Default: false. Shutdown computer when optimization completes."));
	clsUtil::SetIni(_T("Options"), _T("AlwaysOnTop"), gudtOptions.bAlwaysOnTop, _T("Boolean. Default: false. Show main window always on top"));
	clsUtil::SetIni(_T("Options"), _T("AllowDuplicates"), gudtOptions.bAllowDuplicates, _T("Boolean. Default: false. Allow adding same file more than once. If enabled, adding to the grid will be much faster, specially on very large grids."));
	clsUtil::SetIni(_T("Options"), _T("Level"), gudtOptions.iLevel, _T("Number. Default: 5. Optimization level from best speed to best compression."));
	clsUtil::SetIni(_T("Options"), _T("ProcessPriority"), gudtOptions.iProcessPriority, _T("Number. Default: 1. Process priority from most conservative to best performance."));
	clsUtil::SetIni(_T("Options"), _T("CheckForUpdates"), gudtOptions.iCheckForUpdates, _T("Number. Default: 1. Automatically check for program updates."));
	clsUtil::SetIni(_T("Options"), _T("LogLevel"), gudtOptions.iLogLevel, _T("Number. Default: 0. Debugging level to output on program log."));
	clsUtil::SetIni(_T("Options"), _T("FilenameFormat"), gudtOptions.iFilenameFormat, _T("Number. Default: 0."));
	clsUtil::SetIni(_T("Options"), _T("LeanifyIterations"), gudtOptions.iLeanifyIterations, _T("Number. Default: -1."));
	clsUtil::SetIni(_T("Options"), _T("Theme"), gudtOptions.acTheme, _T("String. Default: 'Windows'. Visual theme."));
	clsUtil::SetIni(_T("Options"), _T("TempDirectory"), gudtOptions.acTempDirectory, _T("String. Default: ''."));
	clsUtil::SetIni(_T("Options"), _T("Version"), gudtOptions.acVersion, _T("String. Default: ''."));
	
	gudtOptions.lStatTime += ((GetTickCount() - miStartTicks) / 1000);
	clsUtil::SetIni(_T("Statistics"), _T("Time"), (long long) gudtOptions.lStatTime);
	clsUtil::SetIni(_T("Statistics"), _T("Opens"), (int) gudtOptions.iStatOpens);
	clsUtil::SetIni(_T("Statistics"), _T("Files"), (int) gudtOptions.iStatFiles);
	clsUtil::SetIni(_T("Statistics"), _T("TotalBytes"), (long long) gudtOptions.lStatTotalBytes);
	clsUtil::SetIni(_T("Statistics"), _T("SavedBytes"), (long long) gudtOptions.lStatSavedBytes);
	clsUtil::SetIni(_T("Statistics"), _T("Session"), (int) gudtOptions.iStatSession);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	WIN32_FIND_DATA udtFindFileData;
	TCHAR acPluginsDirectory[PATH_MAX];
	

	if (!gbStop)
	{
		GetModuleFileName(NULL, acPluginsDirectory, sizeof(acPluginsDirectory) - 1);
		*_tcsrchr(acPluginsDirectory, '\\') = NULL;
		if (clsUtil::IsWindows64())
		{
			_tcscat(acPluginsDirectory, _T("\\Plugins64\\"));
		}
		else
		{
			_tcscat(acPluginsDirectory, _T("\\Plugins32\\"));
		}

		bool bRunning = false;
		HANDLE hFindFile = FindFirstFile((((String) acPluginsDirectory) + "*.exe").c_str(), &udtFindFileData);
		do
		{
			if (clsUtil::FindProcess(udtFindFileData.cFileName))
			{
				bRunning = true;
				break;
			}
		}
		while (FindNextFile(hFindFile, &udtFindFileData) != 0);
		FindClose(hFindFile);

		if ((bRunning) && (clsUtil::MsgBox(Handle, ("Optimization is still running. Do you want to stop and exit " + Application->Name + "?").c_str(), _T("Exit"), MB_YESNO | MB_ICONQUESTION) == ID_NO))
		{
			CanClose = false;
		}
		else
		{
			gbStop = true;
			Hide();
			CanClose = true;
		}
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender)
{
	static unsigned int iOldWidth = 0;


	//Recalculate column widths only if window width changed
	if (iOldWidth != (unsigned int) Width)
	{
		iOldWidth = (unsigned int) Width;

		//Prevent flickering
		LockWindowUpdate(Handle);

		grdFiles->ColWidths[KI_GRID_FILE] = grdFiles->Width >> 1;
		grdFiles->ColWidths[KI_GRID_EXTENSION] = (grdFiles->Width - grdFiles->ColWidths[KI_GRID_FILE]) >> 2;
		grdFiles->ColWidths[KI_GRID_ORIGINAL] = (grdFiles->Width - grdFiles->ColWidths[KI_GRID_FILE]) >> 2;
		grdFiles->ColWidths[KI_GRID_OPTIMIZED] = (grdFiles->Width - grdFiles->ColWidths[KI_GRID_FILE]) >> 2;
		grdFiles->ColWidths[KI_GRID_STATUS] = (grdFiles->Width - grdFiles->ColWidths[KI_GRID_FILE]) >> 2;

		//Reenable form updates
		LockWindowUpdate(NULL);
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	grdFiles->Rows[ARow]->BeginUpdate();
	if (ARow == 0)
	{
		grdFiles->Canvas->Brush->Color = clBtnFace;
	}
	else if (ARow & 1)
	{
		grdFiles->Canvas->Brush->Color = clGradientInactiveCaption;
	}
	else
	{
		grdFiles->Canvas->Brush->Color = clGradientActiveCaption;
	}

	if ((ARow > 0) && (ACol == KI_GRID_FILE))
	{
		grdFiles->Canvas->Font->Color = clHotLight;
		grdFiles->Canvas->Font->Style = grdFiles->Canvas->Font->Style << fsUnderline;
	}
	else
	{
		grdFiles->Canvas->Font->Color = clWindowText;
	}

	Rect.left -= 2;
	grdFiles->Canvas->FillRect(Rect);

	String sValue = GetCellValue(grdFiles->Cells[ACol][ARow], 0);

	//Left aligned
	if ((ACol == KI_GRID_FILE) || (ACol == KI_GRID_EXTENSION) || (ACol == KI_GRID_STATUS))
	{
		grdFiles->Canvas->TextRect(Rect, Rect.left + 4, Rect.top + 4, sValue);
	}
	//Right aligned
	else
	{
		grdFiles->Canvas->TextRect(Rect, Rect.right - Canvas->TextWidth(sValue) - 4, Rect.top + 4, sValue);
	}
	grdFiles->Rows[ARow]->EndUpdate();
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesFixedCellClick(TObject *Sender, int ACol, int ARow)
{
	unsigned int iRows = (unsigned int) grdFiles->RowCount;
	if (iRows > 1)
	{
		static int iSortField = -1;
		static unsigned int iSortOrder = 0;
		
		Screen->Cursor = crAppStart;
		Application->ProcessMessages();

		if (ACol == iSortField)
		{
			iSortOrder = (iSortOrder + 1) & 1;
		}
		else
		{
			iSortOrder = 0;
		}
		iSortField = ACol;

		TStringList *lstTemp = new TStringList();
		String sValue;
		for (unsigned int iRow = 1; iRow < iRows; iRow++)
		{
			if ((iSortField == KI_GRID_ORIGINAL) || (iSortField == KI_GRID_OPTIMIZED))
			{
				sValue = FormatFloat("0000000000000000000", ParseNumberThousand(grdFiles->Cells[iSortField][(int) iRow]));
			}
			else
			{
				sValue = grdFiles->Cells[iSortField][(int) iRow];
			}
			sValue += "|" + grdFiles->Cells[KI_GRID_FILE][(int) iRow] + "|" + grdFiles->Cells[KI_GRID_EXTENSION][(int) iRow] + "|" + grdFiles->Cells[KI_GRID_ORIGINAL][(int) iRow] + "|" + grdFiles->Cells[KI_GRID_OPTIMIZED][(int) iRow] + "|" + grdFiles->Cells[KI_GRID_STATUS][(int) iRow];
			lstTemp->Add(sValue);
		}

		lstTemp->Sort();

		TStringDynArray asValue;
		for (unsigned int iRow = 1; iRow < iRows; iRow++)
		{
			if (iSortOrder == 0)
			{
				asValue = SplitString(lstTemp->Strings[(int) iRow - 1], "|");
			}
			else
			{
				asValue = SplitString(lstTemp->Strings[(int) (iRows - iRow - 1)], "|");
			}
			grdFiles->Rows[(int) iRow]->BeginUpdate();
			grdFiles->Cells[KI_GRID_FILE][(int) iRow] = asValue[1];
			grdFiles->Cells[KI_GRID_EXTENSION][(int) iRow] = asValue[2];
			grdFiles->Cells[KI_GRID_ORIGINAL][(int) iRow] = asValue[3];
			grdFiles->Cells[KI_GRID_OPTIMIZED][(int) iRow] = asValue[4];
			grdFiles->Cells[KI_GRID_STATUS][(int) iRow] = asValue[5];
			grdFiles->Rows[(int) iRow]->EndUpdate();
		}
		delete lstTemp;
		
		RefreshStatus();
		Screen->Cursor = crDefault;
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	int iRow, iCol;
	

	grdFiles->MouseToCell(X, Y, iCol, iRow);
	if ((iRow >= 0) && (iCol >=0))
	{
		Application->CancelHint();
		grdFiles->Hint = GetCellValue(grdFiles->Cells[iCol][iRow], 1);
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesDblClick(TObject *Sender)
{
	actOpenExecute(Sender);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::stbMainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect)
{
	if (Panel == StatusBar->Panels->Items[1])
	{
		pgbProgress->Top = Rect.top;
		pgbProgress->Left = Rect.left;
		pgbProgress->Width = Rect.right - Rect.left;
		pgbProgress->Height = Rect.bottom - Rect.top;
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	//Ctrl-F5 reload grid
	if ((Key == VK_F5) && (Shift.Contains(ssCtrl)))
	{
		unsigned int iRows = (unsigned int) grdFiles->RowCount;
		if (iRows > 1)
		{
			Screen->Cursor = crAppStart;
			Application->ProcessMessages();
			for (int iRow = (int) iRows; iRow > 0; iRow--)
			{
				//Remove already optimized files
				if (PosEx("Done", grdFiles->Cells[KI_GRID_STATUS][(int) iRow]) > 0)
				{
					for (int iSelectedRow = iRow; iSelectedRow < (int) iRows - 1; iSelectedRow++)
					{
						grdFiles->Rows[iSelectedRow]->BeginUpdate();
						grdFiles->Rows[iSelectedRow] = grdFiles->Rows[iSelectedRow + 1];
						grdFiles->Rows[iSelectedRow]->EndUpdate();
					}
					iRows--;
				}
			}
			grdFiles->RowCount = (int) iRows;
			RefreshStatus();
			Screen->Cursor = crDefault;
		}
	}

	//F5 refresh grid
	if (Key == VK_F5)
	{
		unsigned int iRows = (unsigned int) grdFiles->RowCount;
		if (iRows > 1)
		{
			Screen->Cursor = crAppStart;
			Application->ProcessMessages();
			for (unsigned int iRow = 1; iRow < iRows; iRow++)
			{
				grdFiles->Rows[(int) iRow]->BeginUpdate();
				//grdFiles->Cells[KI_GRID_FILE][(int) iRow] = asValue[1];
				//grdFiles->Cells[KI_GRID_EXTENSION][(int) iRow] = asValue[2];
				grdFiles->Cells[KI_GRID_ORIGINAL][(int) iRow] = FormatNumberThousand(clsUtil::SizeFile(GetCellValue(grdFiles->Cells[KI_GRID_FILE][iRow], 1).c_str()));
				//grdFiles->Cells[KI_GRID_OPTIMIZED][(int) iRow] = asValue[4];
				//grdFiles->Cells[KI_GRID_STATUS][(int) iRow] = asValue[5];
				grdFiles->Rows[(int) iRow]->EndUpdate();
			}
			RefreshStatus();
			Screen->Cursor = crDefault;
		}
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actAddExecute(TObject *Sender)
{
	//Add files
	if (dlgAddFiles->Execute())
	{
		Screen->Cursor = crAppStart;
		Application->ProcessMessages();

		TStrings *strFiles = dlgAddFiles->Files;
		for (int iCount = strFiles->Count; iCount > 0; iCount--)
		{
			AddFiles(strFiles->Strings[iCount - 1].c_str());
		}
		RefreshStatus();
		Screen->Cursor = crDefault;
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRemoveExecute(TObject *Sender)
{
	int iSelectedRow1 = grdFiles->Selection.Top;
	int iSelectedRow2 = grdFiles->Selection.Bottom;

	int iRows = grdFiles->RowCount - 1;
	for (int iRow = iSelectedRow1; iRow < iRows; iRow++)
	{
		grdFiles->Rows[iRow]->BeginUpdate();
		grdFiles->Rows[iRow] = grdFiles->Rows[iRow + (iSelectedRow2 - iSelectedRow1 + 1)];
		grdFiles->Rows[iRow]->EndUpdate();
	}
	grdFiles->RowCount -= (iSelectedRow2 - iSelectedRow1 + 1);
	RefreshStatus();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actClearExecute(TObject *Sender)
{
	grdFiles->RowCount = 1;
	RefreshStatus();
}




//---------------------------------------------------------------------------
void __fastcall TfrmMain::actHelpExecute(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), Application->HelpFile.c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOpenExecute(TObject *Sender)
{
	unsigned int iRow = (unsigned int) grdFiles->Row;
	unsigned int iCol = (unsigned int) grdFiles->Col;
	if ((iRow > 0) && (iCol == KI_GRID_FILE))
	{
		ShellExecute(NULL, _T("open"), GetCellValue(grdFiles->Cells[KI_GRID_FILE][(int) iRow], 1).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOpenFolderExecute(TObject *Sender)
{
	unsigned int iRow = (unsigned int) grdFiles->Row;
	unsigned int iCol = (unsigned int) grdFiles->Col;
	if ((iRow > 0) && (iCol == KI_GRID_FILE))
	{
		ShellExecute(NULL, _T("open"), ExtractFilePath(GetCellValue(grdFiles->Cells[KI_GRID_FILE][(int) iRow], 1)).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
	}
}



//---------------------------------------------------------------------------
static struct udtOptimizeProgress
{
	unsigned long long lSavedBytes;
	unsigned long long lTotalBytes;
	unsigned int iCurrentFile;
	unsigned int iProcessedFiles;
	unsigned int iTotalFiles;
	String sFileStatusText;
	String sWindowCaptionText;
	String sStatusbarText;
} mudtOptimizeProgress;
static CRITICAL_SECTION mudtCriticalSection;



//---------------------------------------------------------------------------
static unsigned long long lSavedBytes, lTotalBytes;
static String sPluginsDirectory;



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptimizeExecute(TObject *Sender)
{
	unsigned int iCount;
	TCHAR acTmpFile[PATH_MAX];


	gbProcess = true;
	gbStop = false;
	RefreshStatus();

	GetModuleFileName(NULL, acTmpFile, sizeof(acTmpFile) - 1);
	*_tcsrchr(acTmpFile, '\\') = NULL;
	if (clsUtil::IsWindows64())
	{
		_tcscat(acTmpFile, _T("\\Plugins64\\"));
	}
	else
	{
		_tcscat(acTmpFile, _T("\\Plugins32\\"));
	}
	sPluginsDirectory = GetShortName(acTmpFile);

	lSavedBytes = 0;
	lTotalBytes = 0;
	unsigned int iRows = (unsigned int) grdFiles->RowCount;


	InitializeCriticalSection(&mudtCriticalSection);

	//Use multithreaded parallel for (PPL)
	if ((false) && (iRows > 2))
	{
		TParallel::For(this, 1, (int) (iRows - 1), actOptimizeForThread);
	}
	//Use regular for loop
	else
	{
		for (iCount = 1; iCount < iRows; iCount++)
		{
			if (!gbStop)
			{
				actOptimizeFor(NULL, (int) iCount);
			}
			else
			{
				break;
			}
		}
	}

	gbProcess = false;
	//grdFiles->Enabled = true;
	unsigned int iPercentBytes;
	if (lTotalBytes != 0)
	{
		//iPercentBytes = ((unsigned long long) lTotalBytes - lSavedBytes) * 100 / lTotalBytes;
		iPercentBytes = ((unsigned int) ((double) (lTotalBytes - lSavedBytes) / lTotalBytes * 100));
	}
	else
	{
		iPercentBytes = 0;
	}

	stbMain->Panels->Items[0]->Text = FormatNumberThousand(iCount - 1) + " files processed. " + FormatNumberThousand(lSavedBytes) + " bytes saved (" + FormatNumberThousand(iPercentBytes) + "%)";
	stbMain->Hint = stbMain->Panels->Items[0]->Text;

	RefreshStatus(false);

	if (gudtOptions.bBeepWhenDone)
	{
		FlashWindow(Handle, false);
		MessageBeep(0xFFFFFFFF);
	}

	if (gudtOptions.bShutdownWhenDone)
	{
		if (!clsUtil::ShutdownWindows())
		{
			clsUtil::MsgBox(Handle, _T("Error trying to automatically shutdown the system."), _T("Shutdown"), MB_OK | MB_ICONERROR);
		}
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actStopExecute(TObject *Sender)
{
	gbStop = true;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptionsExecute(TObject *Sender)
{
	frmOptions = new TfrmOptions(Application);

	//Set child window as on top, of current window already is
	if (FormStyle == fsStayOnTop)
	{
		FormStyle = fsNormal;
		frmOptions->FormStyle = fsStayOnTop;
	}
	frmOptions->PopupParent = this;
	frmOptions->ShowModal();
	if (gudtOptions.bAlwaysOnTop)
	{
		FormStyle = fsStayOnTop;
	}
	delete frmOptions;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actAboutExecute(TObject *Sender)
{
	frmAbout = new TfrmAbout(Application);

	//Set child window as on top, of current window already is
	if (FormStyle == fsStayOnTop)
	{
		FormStyle = fsNormal;
		frmAbout->FormStyle = fsStayOnTop;
	}
	frmAbout->PopupParent = this;
	frmAbout->ShowModal();
	if (gudtOptions.bAlwaysOnTop)
	{
		FormStyle = fsStayOnTop;
	}
	delete frmAbout;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actExitExecute(TObject *Sender)
{
	gbStop = true;
	Hide();
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actInformationExecute(TObject *Sender)
{
	String sExtension;
	String sText = "";


	//Get all supported extensions
	TStringDynArray asExtension;
	
	asExtension = SplitString((KS_EXTENSION_ALL + " " + ((String) clsUtil::ReplaceString(gudtOptions.acJSAdditionalExtensions, _T(";"), _T(" "))).UpperCase() + " "), " ");
	unsigned int iExtensionLen = (unsigned int) asExtension.Length;

	//Sort them alphabetically
	TStringList *lstTemp = new TStringList();
	for (unsigned int iExtension = 0; iExtension < iExtensionLen; iExtension++)
	{
		sExtension = asExtension[iExtension];
		//Dont push it if empty extension
		if (sExtension.Length() > 1)
		{
			lstTemp->Add(sExtension);
		}
	}
	lstTemp->Sort();

	iExtensionLen = (unsigned int) lstTemp->Count;
	for (unsigned int iExtension = 0; iExtension < iExtensionLen; iExtension++)
	{
		sExtension = lstTemp->Strings[(int) iExtension];
		//Check if we already have it
		if (PosEx(sExtension, sText) <= 0)
		{
			//Check if it is not the last extension
			if (iExtension != (iExtensionLen - 1))
			{
				sText += sExtension + ", ";
			}
			else
			{
				sText += "and " + sExtension + " file formats among others.";
			}
		}
	}
	delete lstTemp;
	
	sText = Application->Name + " is an advanced file optimizer featuring a lossless (no quality loss) file size reduction that supports: " + sText;

	sText += "\n\nUsage Statistics\n"
		"- Time: " + FormatNumberThousand(gudtOptions.lStatTime) + " seconds\n"
		"- Opens: " + FormatNumberThousand(gudtOptions.iStatOpens) + "\n"
		"- Files: " + FormatNumberThousand(gudtOptions.iStatFiles) + "\n"
		"- Total: " + FormatNumberThousandUnit(gudtOptions.lStatTotalBytes) + "\n"
		"- Saved: " + FormatNumberThousandUnit(gudtOptions.lStatSavedBytes) + "\n";
	clsUtil::MsgBox(Handle, sText.c_str(), _T("Information"), MB_ICONINFORMATION | MB_OK);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDonateExecute(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), KS_APP_DONATE_URL, _T(""), _T(""), SW_SHOWMAXIMIZED);
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::OptimizeProgressThread(struct udtOptimizeProgress pudtOptimizeProgress)
{
	EnterCriticalSection(&mudtCriticalSection);
	
	//memcpy(&mudtOptimizeProgress, &pudtOptimizeProgress, sizeof(mudtOptimizeProgress));
	mudtOptimizeProgress.iCurrentFile = pudtOptimizeProgress.iCurrentFile;
	mudtOptimizeProgress.iProcessedFiles = pudtOptimizeProgress.iProcessedFiles;
	mudtOptimizeProgress.iTotalFiles = pudtOptimizeProgress.iTotalFiles;
	mudtOptimizeProgress.lSavedBytes = pudtOptimizeProgress.lSavedBytes;
	mudtOptimizeProgress.lTotalBytes = pudtOptimizeProgress.lTotalBytes;
	mudtOptimizeProgress.sFileStatusText = pudtOptimizeProgress.sFileStatusText;
	mudtOptimizeProgress.sWindowCaptionText = pudtOptimizeProgress.sWindowCaptionText;
	mudtOptimizeProgress.sStatusbarText = pudtOptimizeProgress.sStatusbarText;


	//http://docwiki.embarcadero.com/RADStudio/Seattle/en/Using_the_Main_VCL_Thread
	//TThread::Synchronize((TThreadMethod) OptimizeProgressVCL);
	//Use a timer to refresh?

	LeaveCriticalSection(&mudtCriticalSection);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::OptimizeProgressVCL(void)
{
	//Status bar text
	if (mudtOptimizeProgress.sStatusbarText != "NULL")
	{	
		stbMain->Panels->Items[0]->Text = mudtOptimizeProgress.sStatusbarText;
		stbMain->Hint = stbMain->Panels->Items[0]->Text;
	}
	
	//Progress
	if (mudtOptimizeProgress.iCurrentFile != UINT_MAX)
	{	
		pgbProgress->Position = (int) mudtOptimizeProgress.iCurrentFile;
		clsUtil::SetTaskListProgress((unsigned int) pgbProgress->Position, (unsigned int) pgbProgress->Max);
		grdFiles->Row = (int) mudtOptimizeProgress.iCurrentFile;
	}
	
	Application->ProcessMessages();
	
	//RunPlugin
	
	//RefreshStatus
	
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptimizeForThread(TObject *Sender, int AIndex, TParallel::TLoopState *LoopState)
{
	actOptimizeFor(Sender, AIndex);
	if (gbStop)
	{
		LoopState->Break();
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptimizeFor(TObject *Sender, int iCount)
{
	FILETIME udtFileCreated, udtFileAccessed, udtFileModified;
	String sInputFile, sFlags, sExtensionByContent;


	sInputFile = GetCellValue(grdFiles->Cells[KI_GRID_FILE][iCount], 1);

	struct udtOptimizeProgress a =
	{
			ULLONG_MAX, //unsigned long long lSavedBytes;
			ULLONG_MAX, //unsigned long long lTotalBytes;
			UINT_MAX, //unsigned int iCurrentFile;
			UINT_MAX, //unsigned int iProcessedFiles;
			UINT_MAX, //unsigned int iTotalFiles;
			"NULL", //String sFileStatusText;
			"NULL", //String sWindowCaptionText;
			"NULL", //String sStatusbarText;
	};
	//OptimizeProgressThread(a);

	stbMain->Panels->Items[0]->Text = "Processing " + sInputFile + "...";
	stbMain->Hint = stbMain->Panels->Items[0]->Text;
	pgbProgress->Position = iCount;
	clsUtil::SetTaskListProgress((unsigned int) pgbProgress->Position, (unsigned int) pgbProgress->Max);
	grdFiles->Row = iCount;
	Application->ProcessMessages();


	bool bExcluded = false;

	//If include mask is specified, by default all files are excluded, except the specified
	if (gudtOptions.acIncludeMask[0] != NULL)
	{
		bExcluded = true;
		TCHAR *acToken = _tcstok(((String) gudtOptions.acIncludeMask).UpperCase().c_str(), _T(";"));
		while (acToken)
		{
			if (PosEx((String) acToken, sInputFile.UpperCase()) != 0)
			{
				bExcluded = false;
				break;
			}
			acToken = _tcstok(NULL, _T(";"));
		}
	}

	if (gudtOptions.acExcludeMask[0] != NULL)
	{
		TCHAR *acToken = _tcstok(((String) gudtOptions.acExcludeMask).UpperCase().c_str(), _T(";"));
		while (acToken)
		{
			if (PosEx((String) acToken, sInputFile.UpperCase()) != 0)
			{
				bExcluded = true;
				break;
			}
			acToken = _tcstok(NULL, _T(";"));
		}
	}

	//Check file still exists and is not to be excluded
	if ((clsUtil::ExistsFile(sInputFile.c_str())) && (!bExcluded))
	{
		sExtensionByContent = " " + GetExtensionByContent(sInputFile) + " ";

		if (!gudtOptions.bDoNotUseRecycleBin)
		{
			grdFiles->Cells[KI_GRID_STATUS][iCount] = "Copying to Recyclebin...";
			clsUtil::CopyToRecycleBin(sInputFile.c_str());
		}

		unsigned int iFileAttributes = INVALID_FILE_ATTRIBUTES;
		if (gudtOptions.bKeepAttributes)
		{
			//If get timestamp fails, set to null
			if (!clsUtil::GetFileTimestamp(sInputFile.c_str(), &udtFileCreated, &udtFileAccessed, &udtFileModified))
			{
				udtFileCreated.dwLowDateTime = 0;
				udtFileCreated.dwHighDateTime = 0;
				/* udtFileAccessed.dwLowDateTime = 0;
				udtFileAccessed.dwHighDateTime = 0;
				udtFileModified.dwLowDateTime = 0;
				udtFileModified.dwHighDateTime = 0; */
			}
			iFileAttributes = GetFileAttributes(sInputFile.c_str());
		}
		SetFileAttributes(sInputFile.c_str(), FILE_ATTRIBUTE_NORMAL);


		int iLevel;
		//Each extension can correspond to more than one engine, so use if instead of else if
		// BMP: ImageMagick, ImageWorsener
		if (PosEx(sExtensionByContent, KS_EXTENSION_BMP) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bBMPCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet -compress RLE " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 -outfmt bmp -compress \"rle\" \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// CSS: CSSTidy
		if (PosEx(sExtensionByContent, KS_EXTENSION_CSS) > 0)
		{
			if (gudtOptions.bCSSEnableTidy)
			{
				RunPlugin((unsigned int) iCount, "CSSTidy", (sPluginsDirectory + "csstidy.exe \"%INPUTFILE%\" --template=" + gudtOptions.acCSSTemplate + " \"\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// DLL: PETrim, strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_DLL) > 0)
		{
			if (!gudtOptions.bEXEDisablePETrim)
			{
				RunPlugin((unsigned int) iCount, "PETrim", (sPluginsDirectory + "petrim.exe \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			RunPlugin((unsigned int) iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			if (gudtOptions.bEXEEnableUPX)
			{
				sFlags = "--no-backup --force ";
				if (gudtOptions.iLevel < 3)
				{
					sFlags += "-1 ";
				}
				else if (gudtOptions.iLevel < 5)
				{
					sFlags += "-9 ";
				}
				else if (gudtOptions.iLevel < 7)
				{
					sFlags += "-9 --best ";
				}
				else if (gudtOptions.iLevel < 9)
				{
					sFlags += "-9 --best --lzma ";
				}
				else
				{
					sFlags += "-9 --best --lzma --ultra-brute --crp-ms=999999 ";
				}	
				RunPlugin((unsigned int) iCount, "UPX", (sPluginsDirectory + "upx.exe " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// EXE: Leanify, PETrim, strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_EXE) > 0)
		{
			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (!IsEXESFX(sInputFile.c_str()))
			{
				if (!gudtOptions.bEXEDisablePETrim)
				{
					RunPlugin((unsigned int) iCount, "PETrim", (sPluginsDirectory + "petrim.exe /StripFixups:Y \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
				RunPlugin((unsigned int) iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				if (gudtOptions.bEXEEnableUPX)
				{
					sFlags = "--no-backup --force ";
					if (gudtOptions.iLevel < 3)
					{
						sFlags += "-1 ";
					}
					else if (gudtOptions.iLevel < 5)
					{
						sFlags += "-9 ";
					}
					else if (gudtOptions.iLevel < 7)
					{
						sFlags += "-9 --best ";
					}
					else if (gudtOptions.iLevel < 9)
					{
						sFlags += "-9 --best --lzma ";
					}
					else
					{
						sFlags += "-9 --best --lzma --ultra-brute --crp-ms=999999 ";
					}	
					RunPlugin((unsigned int) iCount, "UPX", (sPluginsDirectory + "upx.exe " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}
		}
		// FLAC: FLACOut
		if (PosEx(sExtensionByContent, KS_EXTENSION_FLAC) > 0)
		{
			RunPlugin((unsigned int) iCount, "FLACOut", (sPluginsDirectory + "flacout.exe /q /y \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// GIF: gifsicle-lossy, gifsicle
		if (PosEx(sExtensionByContent, KS_EXTENSION_GIF) > 0)
		{
			
			if (gudtOptions.bGIFAllowLossy)
			{			
				sFlags = "";
				if (!gudtOptions.bGIFCopyMetadata)
				{
					sFlags += "-strip ";
				}

				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 3 / 9, 3);
				iLevel = 3;
				sFlags += "-O" + (String) iLevel + " ";
				if (!gudtOptions.bGIFCopyMetadata)
				{
					sFlags += "--no-comments --no-extensions --no-names ";
				}
				RunPlugin((unsigned int) iCount, "gifsicle-lossy", (sPluginsDirectory + "gifsicle-lossy.exe --lossy=30 -b -w -o \"%TMPOUTPUTFILE%\" " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			
			sFlags = "";
			if (!gudtOptions.bGIFCopyMetadata)
			{
				sFlags += "-strip ";
			}

			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 3 / 9, 3);
			iLevel = 3;
			sFlags += "-O" + (String) iLevel + " ";
			if (!gudtOptions.bGIFCopyMetadata)
			{
				sFlags += "--no-comments --no-extensions --no-names ";
			}
			RunPlugin((unsigned int) iCount, "gifsicle", (sPluginsDirectory + "gifsicle.exe -b -w -o \"%TMPOUTPUTFILE%\" " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// GZ: Leanify, ect, advdef, zRecompress, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_GZ) > 0)
		{
			if (!gudtOptions.bGZCopyMetadata)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				if (gudtOptions.bJPEGCopyMetadata)
				{
					sFlags += "--keep-exif ";
				}
				RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			
			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
			iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "advdef", (sPluginsDirectory + "advdef.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tgz \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			sFlags += "--allfilters --mt-deflate ";
			if (!gudtOptions.bGZCopyMetadata)
			{
				sFlags += "-s ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			sFlags += "-" + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "ECT", (sPluginsDirectory + "ECT.exe -quiet " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (gudtOptions.bGZCopyMetadata)
			{
				sFlags += "/c ";
			}
			RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// HTML: tidy-html5, Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_HTML) > 0)
		{
			if (gudtOptions.bHTMLEnableTidy)
			{
				RunPlugin((unsigned int) iCount, "tidy", (sPluginsDirectory + "tidy.exe -config tidy.config -quiet -output \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\" ").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// ICO: ImageMagick, Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_ICO) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bPNGCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (gudtOptions.bPNGCopyMetadata)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				//Temporary disable Leanify because it removed IPTC metadata
				if (!gudtOptions.bPNGCopyMetadata)
				{
					RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}
		}
		// JPEG: Guetzli, jpeg-recompress, jhead, Leanify, ect, pingo, jpegoptim, jpegtran, mozjpegtran
		if (PosEx(sExtensionByContent, KS_EXTENSION_JPG) > 0)
		{
			if ((gudtOptions.bJPEGAllowLossy) && (!gudtOptions.bJPEGCopyMetadata))
			{
				RunPlugin((unsigned int) iCount, "Guetzli", (sPluginsDirectory + "guetzli.exe --quality 95 " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);			
			}
			
			if (gudtOptions.bJPEGAllowLossy)
			{
				sFlags = "";
				if (!gudtOptions.bJPEGCopyMetadata)
				{
					sFlags += "--strip ";
				}
				if (gudtOptions.iLevel >= 5)
				{
					sFlags += "--accurate ";
				}
				RunPlugin((unsigned int) iCount, "jpeg-recompress", (sPluginsDirectory + "jpeg-recompress.exe --method smallfry --quality veryhigh --min 60 --subsample disable --quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "-autorot -zt -q ";
			}
			else
			{
				sFlags += "-autorot -purejpg -di -dx -dt -zt -q ";
			}	
			RunPlugin((unsigned int) iCount, "jhead", (sPluginsDirectory + "jhead.exe " + sFlags + " \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif --keep-icc-profile --jpeg-keep-all-metadata ";
			}
			if (gudtOptions.bJPEGUseArithmeticEncoding)
			{
				sFlags += "--jpeg-arithmetic-coding ";
			}		
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		
			//Seems to cause some loss of quality
			//iError = RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet -interlace Plane -define jpeg:optimize-coding=true " +sFlags +"\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);

			sFlags = "";
			if (!gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--strip-all ";
			}
			RunPlugin((unsigned int) iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (gudtOptions.bJPEGUseArithmeticEncoding)
			{
				sFlags += "-arithmetic ";
			}
			else
			{
				sFlags += "-optimize ";
			}
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "-copy all ";
			}
			else
			{
				sFlags += "-copy none ";
			}
			RunPlugin((unsigned int) iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			
			sFlags = "";
			sFlags += "--allfilters --mt-deflate ";			
			if (!gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "-s ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			sFlags += "-" + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "ECT", (sPluginsDirectory + "ECT.exe -progressive -quiet " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (!gudtOptions.bJPEGCopyMetadata)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 4 / 9, 4);
				sFlags += "-s" + (String) iLevel + " ";
				if (gudtOptions.bJPEGAllowLossy)
				{
					sFlags += "-lossy ";
				}
				RunPlugin((unsigned int) iCount, "pingo", (sPluginsDirectory + "pingo.exe -optimize -smaller " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// JS: jsmin
		if ((PosEx(sExtensionByContent, KS_EXTENSION_JS) > 0) ||
			(PosEx(sExtensionByContent, " " + (String) clsUtil::ReplaceString(gudtOptions.acJSAdditionalExtensions, _T(";"), _T(" ")) + " ") > 0))
		{
			//If JSMin is enabled or it is a custom extension (we assume custom extensions always enable it)
			if ((gudtOptions.bJSEnableJSMin) || (PosEx(sExtensionByContent, " " + (String) clsUtil::ReplaceString(gudtOptions.acJSAdditionalExtensions, _T(";"), _T(" ")) + " ") > 0))
			{
				RunPlugin((unsigned int) iCount, "jsmin", (sPluginsDirectory + "jsmin.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// LUA: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_LUA) > 0)
		{
			if (gudtOptions.bLUAEnableLeanify)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// MIME: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_MIME) > 0)
		{
			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MKV: mkclean
		if (PosEx(sExtensionByContent, KS_EXTENSION_MKV) > 0)
		{
			RunPlugin((unsigned int) iCount, "mkclean", (sPluginsDirectory + "mkclean.exe --optimize --unsafe --quiet \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MNG: advmng
		if (PosEx(sExtensionByContent, KS_EXTENSION_MNG) > 0)
		{
			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
			iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "advmng", (sPluginsDirectory + "advmng.exe -z -r -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MP3: ECT, MP3packer
		if (PosEx(sExtensionByContent, KS_EXTENSION_MP3) > 0)
		{
			sFlags = "";
			sFlags += "--allfilters --mt-deflate ";
			if (!gudtOptions.bMP3CopyMetadata)
			{
				sFlags += "-s ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			sFlags += "-" + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "ECT", (sPluginsDirectory + "ECT.exe -quiet " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			
			sFlags = "";
			if (!gudtOptions.bMP3CopyMetadata)
			{
				sFlags += "-t -s ";
			}
			RunPlugin((unsigned int) iCount, "MP3packer", (sPluginsDirectory + "mp3packer.exe " + sFlags + "-z -a \"\" -A -f \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MP4: mp4v2
		if (PosEx(sExtensionByContent, KS_EXTENSION_MP4) > 0)
		{
			RunPlugin((unsigned int) iCount, "mp4v2", (sPluginsDirectory + "mp4file.exe --optimize -q \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OBJ: strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_OBJ) > 0)
		{
			RunPlugin((unsigned int) iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OGG: rehuff
		if (PosEx(sExtensionByContent, KS_EXTENSION_OGG) > 0)
		{
			RunPlugin((unsigned int) iCount, "rehuff", (sPluginsDirectory + "rehuff.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OGV: rehuff_theora
		if (PosEx(sExtensionByContent, KS_EXTENSION_OGV) > 0)
		{
			RunPlugin((unsigned int) iCount, "rehuff_theora", (sPluginsDirectory + "rehuff_theora.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// Microsoft OLE Compound Files: Document Press
		if (PosEx(sExtensionByContent, KS_EXTENSION_OLE) > 0)
		{
			RunPlugin((unsigned int) iCount, "Document Press", (sPluginsDirectory + "docprc.exe -opt \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// PCX: PCXLite, ImageMagick
		if (PosEx(sExtensionByContent, KS_EXTENSION_PCX) > 0)
		{
			RunPlugin((unsigned int) iCount, "PCXLite", (sPluginsDirectory + "PCXLite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (!gudtOptions.bPCXCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// PDF: mutool, ghostcript, cpdf
		if (PosEx(sExtensionByContent, KS_EXTENSION_PDF) > 0)
		{
			bool bIsPDFLayered = IsPDFLayered(sInputFile.c_str());
			
			//Skip Ghostcript on PDF with layers, or if no downsampling is selected, because GS always downsample images.
			if ((!bIsPDFLayered) || (!gudtOptions.bPDFSkipLayered) || (_tcscmp(gudtOptions.acPDFProfile, _T("none")) == 0))
			{		
				RunPlugin((unsigned int) iCount, "mutool", (sPluginsDirectory + "mutool.exe clean -ggg -z \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				
				//Do not use Ghoscript for Adobe Illustrator (AI) files
				if (!EndsText(".ai", sInputFile))
				{
					sFlags = "";
					//Custom mode
					if (_tcscmp(gudtOptions.acPDFProfile, _T("Custom")) == 0)
					{
						sFlags += "-dPDFSETTINGS=/ebook -dDownsampleColorImages=true -dColorImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " -dDownsampleGrayImages=true -dGrayImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " -dDownsampleMonoImages=true -dMonoImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " ";
					}
					//No downsampling
					else if (_tcscmp(gudtOptions.acPDFProfile, _T("none")) == 0)
					{
						sFlags += "-dPDFSETTINGS=/default -dDownsampleColorImages=false -dDownsampleGrayImages=false -dDownsampleMonoImages=false ";
					}				
					//Built in downsample modes: screen, ebook, printer, prepress
					else
					{
						sFlags += "-dPDFSETTINGS=/" + (String) gudtOptions.acPDFProfile + " ";
					}
					
					sFlags += "-dColorImageDownsampleType=/Bicubic -dGrayImageDownsampleType=/Bicubic -dMonoImageDownsampleType=/Bicubic -dOptimize=true -dConvertCMYKImagesToRGB=true -dColorConversionStrategy=/sRGB -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dDetectDuplicateImages=true -dCompatibilityLevel=1.5 ";
					
					TCHAR acTmpFilePdf[PATH_MAX];
					_tcscpy(acTmpFilePdf, sInputFile.c_str());
					_tcscat(acTmpFilePdf, _T(".pdf"));

					//RunPlugin((unsigned int) iCount, "Ghostcript", (sPluginsDirectory + "cwebp.exe -mt -quiet -lossless " + sFlags + "\"" + acTmpFileWebp + "\" -o \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
					if (clsUtil::IsWindows64())
					{
						RunPlugin((unsigned int) iCount, "Ghostcript", (sPluginsDirectory + "gswin64c.exe " + sFlags + "-sOutputFile=\"" + acTmpFilePdf + "\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
					}
					else
					{
						RunPlugin((unsigned int) iCount, "Ghostcript", (sPluginsDirectory + "gswin32c.exe " + sFlags + "-sOutputFile=\"" + acTmpFilePdf + "\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
					}
					//If there is size reduction check it is not so high to detect corrupted encrypted PDF
					if (clsUtil::SizeFile(acTmpFilePdf) < clsUtil::SizeFile(sInputFile.c_str()))
					{
						if ((clsUtil::SizeFile(acTmpFilePdf) > 3000) && (clsUtil::SizeFile(sInputFile.c_str()) > 20000))
						{
							clsUtil::CopyFile(acTmpFilePdf, sInputFile.c_str());
						}
					}
					DeleteFile(acTmpFilePdf);
				}
					
				RunPlugin((unsigned int) iCount, "cpdf", (sPluginsDirectory + "cpdf.exe -squeeze \"%INPUTFILE%\" -o \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// PNG: PngOptimizer, TruePNG, pngout, optipng, pngwolf, Leanify, ect, pingo, advpng, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_PNG) > 0)
		{
			bool bIsAPNG = IsAPNG(sInputFile.c_str());
			bool bIsPNG9Patch = EndsText(".9.png", sInputFile);

			//Android 9-patch images get broken with advpng, deflopt, optipng, pngoptimizer, pngout, pngrewrite and truepng. Only pngwolf, defluff and leanify seem to be safe. At the moment, detect them by extension .9.png.
			if (bIsAPNG)
			{
				RunPlugin((unsigned int) iCount, "apngopt", (sPluginsDirectory + "apngopt.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if (!bIsPNG9Patch)
			{
				if (gudtOptions.bPNGAllowLossy)
				{
					sFlags = "";
					if (!gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "--strip ";
					}
					RunPlugin((unsigned int) iCount, "pngquant", (sPluginsDirectory + "pngquant.exe " + sFlags + "--speed 1 256 --ext .png --force \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}

				RunPlugin((unsigned int) iCount, "PngOptimizer", (sPluginsDirectory + "PngOptimizer.exe -file:\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if ((!bIsAPNG) && (!bIsPNG9Patch))
			{
				//Disable TruePNG on ICO files because it crashes
				if (PosEx(sExtensionByContent, KS_EXTENSION_ICO) == 0)
				{
					sFlags = "";
					iLevel = min(gudtOptions.iLevel * 3 / 9, 3) + 1;
					sFlags += "/o" + (String) iLevel + " ";
					if (gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "/md keep all ";
					}
					else
					{
						sFlags += "/md remove all /g0 ";
					}
					if (gudtOptions.bPNGAllowLossy)
					{
						sFlags += "/l ";
					}
					RunPlugin((unsigned int) iCount, "TruePNG", (sPluginsDirectory + "truepng.exe " + sFlags + "/i0 /tz /quiet /y /out \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}

			if ((!bIsAPNG) && (!bIsPNG9Patch))
			{
				sFlags = "";
				if (gudtOptions.bPNGCopyMetadata)
				{
					sFlags += "/k1 ";
				}
				else
				{
					sFlags += "/kacTL,fcTL,fdAT ";
				}
				iLevel = max((gudtOptions.iLevel * 3 / 9) - 3, 0);
				sFlags += "/s" + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "PNGOut", (sPluginsDirectory + "pngout.exe /q /y /r /d0 /mincodes0 " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			
			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 6 / 9, 6);
			if (bIsAPNG)
			{
				sFlags += "-o" + (String) iLevel + " ";
				// For some reason -strip all -protect acTL,fcTL,fdAT is not keeping APNG chunks
				RunPlugin((unsigned int) iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -protect acTL,fcTL,fdAT -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			else
			{
				if (!gudtOptions.bPNGCopyMetadata)
				{
					sFlags += "-strip all ";
				}
				RunPlugin((unsigned int) iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if (!bIsAPNG)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				//Temporary disable Leanify because it removed IPTC metadata
				if (!gudtOptions.bPNGCopyMetadata)
				{
					RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
				
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "--out-deflate=zopfli,iter=" + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "pngwolf", (sPluginsDirectory + "pngwolf.exe " + sFlags + "--in=\"%INPUTFILE%\" --out=\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

				if (!bIsPNG9Patch)
				{
					RunPlugin((unsigned int) iCount, "pngrewrite", (sPluginsDirectory + "pngrewrite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

					//iError = RunPlugin((unsigned int) iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"" + grdFiles->Cells[0][iCount] + "\" \"" + acTmpFile + "\"").c_str(), acPluginsDirectory, acTmpFile);

					sFlags = "";
					//iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
					sFlags += "-i " + (String) iLevel + " ";
					RunPlugin((unsigned int) iCount, "advpng", (sPluginsDirectory + "advpng.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
	
					sFlags = "";
					sFlags += "--allfilters --mt-deflate ";
					if (!gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "-s ";
					}
					iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
					sFlags += "-" + (String) iLevel + " ";
					RunPlugin((unsigned int) iCount, "ECT", (sPluginsDirectory + "ECT.exe -quiet " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
					
					if (!gudtOptions.bPNGCopyMetadata)
					{
						sFlags = "";
						iLevel = min(gudtOptions.iLevel * 4 / 9, 4);
						sFlags += "-s" + (String) iLevel + " ";
						if (gudtOptions.bPNGAllowLossy)
						{
							sFlags += "-x0 ";
						}
						RunPlugin((unsigned int) iCount, "pingo", (sPluginsDirectory + "pingo.exe " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
					}
	
					sFlags = "";
					if (gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "/k ";
					}
					RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}

			RunPlugin((unsigned int) iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if ((!bIsAPNG) && (!bIsPNG9Patch))
			{
				RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// SWF: Leanfy, flasm, zRecompress
		if (PosEx(sExtensionByContent, KS_EXTENSION_SWF) > 0)
		{
			RunPlugin((unsigned int) iCount, "flasm", (sPluginsDirectory + "flasm.exe -x \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			if (clsUtil::SizeFile(sInputFile.c_str()) >= ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]))
			{
				//CopyFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), sInputFile.c_str(), false);
				clsUtil::CopyFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")), sInputFile.c_str());
			}
			//DeleteFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));
			DeleteFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")));

			RunPlugin((unsigned int) iCount, "flasm", (sPluginsDirectory + "flasm.exe -u \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			if (clsUtil::SizeFile(sInputFile.c_str()) >= ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]))
			{
				//CopyFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), sInputFile.c_str(), false);
				clsUtil::CopyFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")), sInputFile.c_str());
			}
			//DeleteFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));
			DeleteFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")));

			RunPlugin((unsigned int) iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tswf-lzma \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// TAR: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_TAR) > 0)
		{
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif ";
			}
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// TIFF: jhead, ImageMagick, jpegoptim, jpegtran, mozjpegtran
		if (PosEx(sExtensionByContent, KS_EXTENSION_TIF) > 0)
		{
			sFlags = "";
			if (gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "-autorot -zt -q ";
			}
			else
			{
				sFlags += "-autorot -purejpg -di -dx -dt -zt -q ";
			}	
			RunPlugin((unsigned int) iCount, "jhead", (sPluginsDirectory + "jhead.exe " + sFlags + " \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (!gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (!gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "--strip-all ";
			}
			RunPlugin((unsigned int) iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "-arithmetic ";
			}
			else
			{
				sFlags += "-optimize ";
			}
			if (gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "-copy all ";
			}
			else
			{
				sFlags += "-copy none ";
			}
			RunPlugin((unsigned int) iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// XML: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_XML) > 0)
		{
			if (gudtOptions.bXMLEnableLeanify)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				//Overwrite Leanify iterations
				if (gudtOptions.iLeanifyIterations != -1)
				{
					iLevel = gudtOptions.iLeanifyIterations;
				}
				else
				{
					iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				}
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// WEBP: dwebp + cwebp, ImageWorsener
		if (PosEx(sExtensionByContent, KS_EXTENSION_WEBP) > 0)
		{
			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 5 / 9, 5) + 1;
			sFlags += "-m " + (String) iLevel + " ";

			TCHAR acTmpFileWebp[PATH_MAX];
			_tcscpy(acTmpFileWebp, sInputFile.c_str());
			_tcscat(acTmpFileWebp, _T(".png"));

			if (RunPlugin((unsigned int) iCount, "dwebp", (sPluginsDirectory + "dwebp.exe -mt \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0) == 0)
			{
				RunPlugin((unsigned int) iCount, "cwebp", (sPluginsDirectory + "cwebp.exe -mt -quiet -lossless " + sFlags + "\"" + acTmpFileWebp + "\" -o \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				if (clsUtil::SizeFile(acTmpFileWebp) < clsUtil::SizeFile(sInputFile.c_str()))
				{
					clsUtil::CopyFile(acTmpFileWebp, sInputFile.c_str());
				}
			}
			DeleteFile(acTmpFileWebp);

			//RunPlugin((unsigned int) iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// ZIP: Leanify, ect, advzip, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_ZIP) > 0)
		{
			bool bIsZIPSFX = IsZIPSFX(sInputFile.c_str());
			
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif ";
			}
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			//Overwrite Leanify iterations
			if (gudtOptions.iLeanifyIterations != -1)
			{
				iLevel = gudtOptions.iLeanifyIterations;
			}
			else
			{
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			}
			sFlags += "-i " + (String) iLevel + " ";
			//Limit ZIP no recurse to ZIP extension
			if ((!gudtOptions.bZIPRecurse) && (PosEx(sExtensionByContent, " .zip ") > 0))
			{
				sFlags += "-d 1 ";
				//sFlags += "-f ";
			}
			RunPlugin((unsigned int) iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			
			sFlags = "";
			sFlags += "--mt-deflate ";			
			if (!gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "-s ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			sFlags += "-" + (String) iLevel + " ";
			RunPlugin((unsigned int) iCount, "ECT", (sPluginsDirectory + "ECT.exe -quiet -zip " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);			

			//AdvZip strips header on ZIP files
			if (!bIsZIPSFX)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				iLevel = ((gudtOptions.iLevel * gudtOptions.iLevel * gudtOptions.iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin((unsigned int) iCount, "advzip", (sPluginsDirectory + "advzip.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			
			sFlags = "";
			if (gudtOptions.bZIPCopyMetadata)
			{
				sFlags += "/c ";
			}
			RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin((unsigned int) iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MISC: ImageMagick
		if (PosEx(sExtensionByContent, KS_EXTENSION_MISC) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bMiscCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin((unsigned int) iCount, "ImageMagick", (sPluginsDirectory + "magick.exe convert -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// VIDEO: ffmpeg
		if (PosEx(sExtensionByContent, (StringReplace((KS_EXTENSION_MP4 KS_EXTENSION_OGV), "  ", " ", TReplaceFlags() << rfReplaceAll)))> 0)
		{
			RunPlugin((unsigned int) iCount, "ffmpeg", (sPluginsDirectory + "ffmpeg.exe -i \"%INPUTFILE%\" -vcodec copy -acodec copy \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}

		if (gudtOptions.bKeepAttributes)
		{
			if (iFileAttributes != INVALID_FILE_ATTRIBUTES)
			{
				SetFileAttributes(sInputFile.c_str(), iFileAttributes);
			}
			//Restore timestamp if we were able to get it
			if ((udtFileCreated.dwLowDateTime != 0) && (udtFileCreated.dwHighDateTime != 0))
			{
				clsUtil::SetFileTimestamp(sInputFile.c_str(), &udtFileCreated, &udtFileAccessed, &udtFileModified);
			}
		}

		//Make sure the file was indeed processed because asuming we got gains. This is to solve Pending items being counted as 0 bytes
		if (grdFiles->Cells[KI_GRID_OPTIMIZED][iCount] != "")
		{
			lTotalBytes += ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]);
			lSavedBytes += (ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]) - ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]));

			gudtOptions.lStatTotalBytes += ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]);
			gudtOptions.lStatSavedBytes += (ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]) - ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]));
			gudtOptions.iStatFiles++;

		}
	}
	//If file was not processed, mark it as skipped because not supported extension, or skipped because user preference (do not process JS for instance)
	if ((grdFiles->Cells[KI_GRID_STATUS][iCount] == "Pending") || (grdFiles->Cells[KI_GRID_STATUS][iCount] == "Copying to Recyclebin..."))
	{
		grdFiles->Cells[KI_GRID_STATUS][iCount] = "Skipped";
	}
	else
	{
		unsigned int iPercentBytes = ((unsigned int) ((double) ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]) / ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]) * 100));
		grdFiles->Cells[KI_GRID_STATUS][iCount] = grdFiles->Cells[KI_GRID_STATUS][iCount].sprintf(_T("Done (%3d%%)."), iPercentBytes);
	}
	RefreshStatus(true, (unsigned int) iCount, lTotalBytes, lSavedBytes);

	//Abort for loop if operation is cancelled
	if (gbStop)
	{
		return;
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrMainTimer(TObject *Sender)
{
	if (tmrMain->Interval >= 30000)
	{
		tmrMain->Enabled = false;
		if (gudtOptions.iCheckForUpdates < 0)
		{
			gudtOptions.iCheckForUpdates = (clsUtil::MsgBox(Handle, ("Do you want " + Application->Name + " to automatically check for updates?").c_str(), _T("Check for updates"), MB_YESNO | MB_ICONQUESTION) == ID_YES);
		}
		else if (gudtOptions.iCheckForUpdates == 1)
		{
			CheckForUpdates(true);
		}
	}
	else if (tmrMain->Interval >= 1000)
	{
		tmrMain->Interval = 30000;
		
		if (_argc > 1)
		{
			Screen->Cursor = crAppStart;
			Application->ProcessMessages();
			for (unsigned int iCount = 1; iCount < (unsigned int) _argc; iCount++)
			{
				//Skip options starting with /
				if (_targv[iCount][0] != '/')
				{
					AddFiles(_targv[iCount]);
				}
			}
			RefreshStatus();
			Screen->Cursor = crDefault;
			actOptimizeExecute(Sender);
			Hide();
			Close();
		}
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::lblCopyrightClick(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), KS_APP_URL, _T(""), _T(""), SW_SHOWNORMAL);
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::WMDropFiles(TWMDropFiles &udtMessage)
{
	TCHAR acBuffer[PATH_MAX];


	HDROP hDrop = (HDROP) udtMessage.Drop;
	if (hDrop)
	{
		unsigned int iFiles = DragQueryFile(hDrop, -1, NULL, NULL);
		if (iFiles > 0)
		{
			Screen->Cursor = crAppStart;
			Application->ProcessMessages();
			for (unsigned int iCount = 0; iCount < iFiles; iCount++)
			{
				if (DragQueryFile(hDrop, iCount, acBuffer, sizeof(acBuffer)))
				{
					AddFiles(acBuffer);
				}
			}
			RefreshStatus();
			Screen->Cursor = crDefault;
		}
	}
	DragFinish(hDrop);
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::AddFiles(const TCHAR *pacFile)
{
	String sExtension, sExtensionByContent;
	WIN32_FIND_DATA udtFindFileData;
	WIN32_FILE_ATTRIBUTE_DATA udtFileAttribute;


	if (GetFileAttributesEx(pacFile, GetFileExInfoStandard, (void*) &udtFileAttribute))
	{
		//If it is a directory, recurse
		if (udtFileAttribute.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			Application->ProcessMessages();
			HANDLE hFindFile = FindFirstFile((((String) pacFile) + "\\*.*").c_str(), &udtFindFileData);
			do
			{
				if ((_tcscmp(udtFindFileData.cFileName, _T(".")) != 0) &&
					(_tcscmp(udtFindFileData.cFileName, _T("..")) != 0))
				{
					AddFiles((((String) pacFile) + "\\" + udtFindFileData.cFileName).c_str());
				}
			}
			while (FindNextFile(hFindFile, &udtFindFileData) != 0);
			FindClose(hFindFile);
			RefreshStatus();
		}
		//It it is a file, parse it
		else
		{
			String sCellFile = SetCellFileValue(pacFile);
			//Check if already added
			if (!gudtOptions.bAllowDuplicates)
			{
				if (grdFiles->Cols[KI_GRID_FILE]->IndexOf(sCellFile) != -1)
				{
					return;
				}
			}
			unsigned long long lSize = clsUtil::SizeFile(pacFile);
			//We will only add files with more than 0 bytes
			if (lSize > 0)
			{
				sExtensionByContent = " " + GetExtensionByContent(pacFile) + " ";
				if (sExtensionByContent != "")
				{
					//We store the name to show concatenated with the full name
					unsigned int iRows = (unsigned int) grdFiles->RowCount;
					grdFiles->Rows[(int) iRows]->BeginUpdate();
					grdFiles->Cells[KI_GRID_FILE][(int) iRows] = sCellFile;
					grdFiles->Cells[KI_GRID_EXTENSION][(int) iRows] = GetExtension(pacFile);
					grdFiles->Cells[KI_GRID_ORIGINAL][(int) iRows] = FormatNumberThousand(lSize);
					grdFiles->Cells[KI_GRID_OPTIMIZED][(int) iRows] = "";
					grdFiles->Cells[KI_GRID_STATUS][(int) iRows] = "Pending";
					grdFiles->RowCount = (int) iRows + 1;
					grdFiles->Rows[(int) iRows]->EndUpdate();
				}
			}
		}
	}
}



// ---------------------------------------------------------------------------
int __fastcall TfrmMain::RunPlugin(unsigned int piCurrent, String psStatus, String psCommandLine, String psDirectory, String psInputFile, String psOutputFile, int piErrorMin, int piErrorMax)
{
	String sInputFile, sOutputFile, sTmpInputFile, sTmpOutputFile, sCommandLine;
	TCHAR acTmp[PATH_MAX];
	TCHAR acTempPath[PATH_MAX] = _T("");


	if (gbStop)
	{
		//Close();
		return (0);
	}
	
	//Check if it is an excluded plugins
	TCHAR *acToken = _tcstok(((String) gudtOptions.acDisablePluginMask).UpperCase().c_str(), _T(";"));
	while (acToken)
	{
		if (PosEx((String) acToken, psCommandLine.UpperCase()) != 0)
		{
			return(0);
		}
		acToken = _tcstok(NULL, _T(";"));
	}

	sInputFile = psInputFile;
	sOutputFile = psOutputFile;
	sCommandLine = psCommandLine;
	
	//Avoid temporary name collisions across different instances
	unsigned int iRandom = (unsigned int) clsUtil::Random(0, 9999);
	
	//Use specified option temp directory if exists
	if (gudtOptions.acTempDirectory[0] != NULL)
	{
		//Add final slash if it has not
		if (gudtOptions.acTempDirectory[_tcslen(gudtOptions.acTempDirectory) - 1] != '\\')
		{
			_tcscat(gudtOptions.acTempDirectory, _T("\\"));
		}
		_tcscpy(acTempPath, gudtOptions.acTempDirectory);
	}
	else
	{
		GetTempPath(sizeof(acTempPath), acTempPath);
	}
	
	//Create temporary directory just in case it did not existed
	if (gudtOptions.acTempDirectory[0] != NULL)
	{
		clsUtil::DirectoryCreate(gudtOptions.acTempDirectory);
	}
	_stprintf(acTmp, _T("%s%s"), acTempPath, (Application->Name + "_Input_" + (String) iRandom + "_" + GetFilename(sInputFile)).c_str());
	sTmpInputFile = acTmp;

	_stprintf(acTmp, _T("%s%s"), acTempPath, (Application->Name + "_Output_" + (String) iRandom + "_" + GetFilename(sInputFile)).c_str());
	sTmpOutputFile = acTmp;
	
	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());
	
	grdFiles->Cells[KI_GRID_STATUS][(int) piCurrent] = "Running " + psStatus + "...";
	unsigned long long lSize = clsUtil::SizeFile(sInputFile.c_str());
	unsigned long long lSizeNew = lSize;
	grdFiles->Cells[KI_GRID_OPTIMIZED][(int) piCurrent] = FormatNumberThousand(lSize);

	Application->ProcessMessages();
	
	//Handle copying original file, if there is not Output nor Tmp for commands that only accept 1 file
	if ((PosEx("%OUTPUTFILE%", psCommandLine) == 0) && (PosEx("%TMPOUTPUTFILE%", psCommandLine) == 0))
	{
		clsUtil::CopyFile(sInputFile.c_str(), sTmpInputFile.c_str());
		//sInputFile = sTmpOutputFile;
	}

	//sCommandLine = StringReplace(sCommandLine, "%INPUTFILE%", sInputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = clsUtil::ReplaceString(sCommandLine.c_str(), _T("%INPUTFILE%"), sInputFile.c_str());
	
	//sCommandLine = StringReplace(sCommandLine, "%OUTPUTFILE%", sOutputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = clsUtil::ReplaceString(sCommandLine.c_str(), _T("%OUTPUTFILE%"), sOutputFile.c_str());
	
	//sCommandLine = StringReplace(sCommandLine, "%TMPINPUTFILE%", sTmpInputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = clsUtil::ReplaceString(sCommandLine.c_str(), _T("%TMPINPUTFILE%"), sTmpInputFile.c_str());
	
	//sCommandLine = StringReplace(sCommandLine, "%TMPOUTPUTFILE%", sTmpOutputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = clsUtil::ReplaceString(sCommandLine.c_str(), _T("%TMPOUTPUTFILE%"), sTmpOutputFile.c_str());

	int iError = (int) RunProcess(sCommandLine.c_str(), psDirectory.c_str(), NULL, 0, true);
	Log(3, ("Return: " + ((String) iError) + ". Process: " + sCommandLine).c_str());

	//Check exit errorlevel
	if ((iError >= piErrorMin) && (iError <= piErrorMax))
	{
		//We did get a TMP output file, so if smaller, make it overwrite input file
		if (PosEx("%TMPOUTPUTFILE%", psCommandLine) != 0)
		{
			lSizeNew = clsUtil::SizeFile(sTmpOutputFile.c_str());
			if ((lSizeNew > 0) && (lSizeNew < lSize))
			{
				clsUtil::CopyFile(sTmpOutputFile.c_str(), sInputFile.c_str());
			}
		}
		else if ((PosEx("%OUTPUTFILE%", psCommandLine) == 0) && (PosEx("%TMPOUTPUTFILE%", psCommandLine) == 0))
		{
			lSizeNew = clsUtil::SizeFile(sTmpInputFile.c_str());
			if ((lSizeNew > 0) && (lSizeNew < lSize))
			{
				clsUtil::CopyFile(sTmpInputFile.c_str(), sInputFile.c_str());
				//sInputFile = sTmpOutputFile;
			}
		}	
	}

	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());

	if ((lSizeNew == 0) || (lSizeNew > lSize))
	{
		lSizeNew = lSize;
	}
	//iPercent = (((unsigned long long) iSize) * 100) / ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][piCurrent]);
	grdFiles->Cells[KI_GRID_OPTIMIZED][(int) piCurrent] = FormatNumberThousand(lSizeNew);
	Log(3, ("Original Size: " + ((String) lSize) + ". Optimized Size: " + ((String) lSizeNew)).c_str());

	return (iError);
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::CheckForUpdates(bool pbSilent)
{

	TCHAR *acWide = new TCHAR[KI_BUFFER_SIZE];
	char *acPath = new char[KI_BUFFER_SIZE];
	char *acBuffer = new char[KI_BUFFER_SIZE];
	unsigned int iSize;



	wcstombs(acPath, KS_APP_UPDATE_URL, sizeof(KS_APP_UPDATE_URL));
	strcat(acPath, "?ini=");
	iSize = 0;
	clsUtil::ReadFile(clsUtil::GetIniPath(), (void *) acBuffer, &iSize);
	strcpy(acBuffer, ((AnsiString) StringReplace(acBuffer, "\r\n", "%0D", TReplaceFlags() << rfReplaceAll)).c_str());
	strcat(acPath, acBuffer);
	//strcat(acPath, "&log=");
	//iSize = 0;
	//clsUtil::ReadFile(clsUtil::GetLogPath(), (void *) acBuffer, &iSize);
	//strcat(acPath, acBuffer);

	mbstowcs(acWide, acPath, KI_BUFFER_SIZE);
	if (clsUtil::DownloadFile(acWide, acBuffer, KI_BUFFER_SIZE))
	{
		mbstowcs(acWide, acBuffer, KI_BUFFER_SIZE);
		//Check we only got number and punctuation digits to detect router errors returning HTML
		size_t iWideLen = _tcslen(acWide);
		for (unsigned int iWide = 0; iWide < iWideLen; iWide++)
		{
			if ((!_istdigit(acWide[iWide])) && (!_istpunct(acWide[iWide])))
			{
				if (!pbSilent)
				{
					clsUtil::MsgBox(Handle, _T("Error checking for updates."), _T("Check updates"), MB_OK | MB_ICONERROR);
				}
				return;
			}
		}

		GetModuleFileName(NULL, (TCHAR *) acPath, KI_BUFFER_SIZE);
		if (_tcscmp(acWide, clsUtil::ExeVersion((TCHAR *) acPath)) > 0)
		{
			if (clsUtil::MsgBox(Handle, (Application->Name + " version " + (String) acWide + " is available.\r\nDo you want to download it now?").c_str(), _T("Check updates"), MB_YESNO | MB_ICONQUESTION) == ID_YES)
			{
				ShellExecute(NULL, _T("open"), KS_APP_URL, _T(""), _T(""), SW_SHOWNORMAL);
			}
		}
		else if (!pbSilent)
		{
			clsUtil::MsgBox(Handle, ("You already have latest " + Application->Name + " version.").c_str(), _T("Check updates"), MB_OK|MB_ICONINFORMATION);
		}
	}

	else if (!pbSilent)
	{
		clsUtil::MsgBox(Handle, _T("Error checking for updates."), _T("Check updates"), MB_OK | MB_ICONERROR);
	}

	delete[] acPath;
	delete[] acWide;
	delete[] acBuffer;
}




//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetExtensionByContent (String psFilename)
{
	String sRes;
	unsigned char acBuffer[512];


	sRes = GetExtension(psFilename);

	//If file extension is not known, get it by analyzing file contents
	if (PosEx(sRes, KS_EXTENSION_ALL + " " + (String) clsUtil::ReplaceString(gudtOptions.acJSAdditionalExtensions, _T(";"), _T(" ")) + " ") <= 0)
	{
		unsigned int iSize = sizeof(acBuffer);
		if (clsUtil::ReadFile(psFilename.c_str(), acBuffer, &iSize))
		{
			//ToDo: Optimize to use regular comparisons instead of memcmp for short comparisons.

			//Check BMP
			if ((memcmp(acBuffer, "BM", 2) == 0) || (memcmp(acBuffer, "BA", 2) == 0) || (memcmp(acBuffer, "CI", 2) == 0) || (memcmp(acBuffer, "CP", 2) == 0) || (memcmp(acBuffer, "IC", 2) == 0) || (memcmp(acBuffer, "PT", 2) == 0))
			{
				sRes = ".bmp";
			}
			//Check EXE
			//Check DLL
			else if ((memcmp(acBuffer, "MZ", 2) == 0) || (memcmp(acBuffer, "ZM", 2) == 0))
			{
				sRes = ".dll";
			}
			//Check FLAC
			else if (memcmp(acBuffer, "fLaC", 4) == 0)
			{
				sRes = ".flac";
			}
			//Check GIF
			else if (memcmp(acBuffer, "GIF8", 4) == 0)
			{
				sRes = ".gif";
			}
			//Check GZ
			else if (memcmp(acBuffer, "\x1F\x8B", 2) == 0)
			{
				sRes = ".gz";
			}
			//Check ICO
			else if (memcmp(acBuffer, "\x00\x00\x01\x00", 4) == 0)
			{
				sRes = ".ico";
			}
			//Check JPEG
			else if (memcmp(acBuffer, "\xFF\xD8\xFF", 3) == 0)
			{
				sRes = ".jpg";
			}
			//Check MKV
			else if (memcmp(acBuffer, ".RTS", 4) == 0)
			{
				sRes = ".mkv";
			}
			//Check MNG
			else if (memcmp(acBuffer, "\x8A\x4D\x4E\x47\x0D\x0A\x1A\x0A", 8) == 0)
			{
				sRes = ".mng";
			}
			//Check MP3
			else if (memcmp(acBuffer, "ID3", 3) == 0)
			{
				sRes = ".mp3";
			}
			//Check MP4
			else if (memcmp(&acBuffer[3], "ftyp", 4) == 0)
			{
				sRes = ".mp4";
			}
			//Check OBJ
			else if ((memcmp(acBuffer, "\x4C\x01", 2) == 0) ||
				(acBuffer[0] == 0x80))
			{
				sRes = ".obj";
			}
			//Check OGG / Check OGV
			else if (memcmp(&acBuffer[3], "OggS", 4) == 0)
			{
				sRes = ".ogg";
			}
			//Check OLE/OLE Beta
			else if ((memcmp(acBuffer, "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", 8) == 0) ||
					(memcmp(acBuffer, "\x0E\x11\xFC\x0D\xD0\xCF\x11\x0E", 8) == 0))
			{
				sRes = ".ole";
			}
			//Check PCX
			else if ((acBuffer[0] == 10) && (acBuffer[2] == 1) && (acBuffer[64] == 0) && (acBuffer[74] == 0))
			{
				sRes = ".pcx";
			}
			//Check PDF
			else if (memcmp(acBuffer, "%PDF-", 5) == 0)
			{
				sRes = ".pdf";
			}
			//Check PNG
			else if (memcmp(acBuffer, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8) == 0)
			{
				sRes = ".png";
			}
			//Check SWF
			else if ((memcmp(acBuffer, "FWS", 3) == 0) || (memcmp(acBuffer, "CWS", 3) == 0) || (memcmp(acBuffer, "ZWS", 3) == 0))
			{
				sRes = ".swf";
			}
			//Check TAR
			else if (memcmp(&acBuffer[257], "\x75\x73\x74\x61\x72", 5) == 0)
			{
				sRes = ".tar";
			}
			//Check TIF
			else if ((memcmp(acBuffer, "\x0C\xED", 2) == 0) || (memcmp(acBuffer, "\x49\x20\x49", 3) == 0) || (memcmp(acBuffer, "\x49\x49\x2A\x00", 4) == 0) || (memcmp(acBuffer, "\x4D\x4D\x00\x2B", 4) == 0))
			{
				sRes = ".tif";
			}
			//Check WEBP
			else if (memcmp(&acBuffer[7], "WEBP", 4) == 0)
			{
				sRes = ".webp";
			}
			//Check ZIP
			else if (memcmp(acBuffer, "\x50\x4B\x03\x04", 4) == 0)
			{
				sRes = ".zip";
			}
			//Unsupported extension
			else
			{
				//Do nothing. Use regular file extension
            }
		}
	}
	return(sRes);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetExtension (String psFilename)
{
	//return (ExtractFileExt(psFilename));
	TCHAR acRes[PATH_MAX] = _T("");
	TCHAR *pacDot;


	pacDot = _tcsrchr(psFilename.c_str(), '.');
	if (pacDot)
	{
		_tcscpy(acRes, pacDot);
		_tcslwr(acRes);
	}
	return ((String) acRes);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetFilename (String psFilename)
{
	TCHAR *pacSource;
	String sRes = "";

	pacSource = _tcsrchr(psFilename.c_str(), '\\');
	if (pacSource)
	{
		sRes = (pacSource + 1);
	}
	return (sRes);
}



//---------------------------------------------------------------------------
String __inline TfrmMain::FormatNumberThousand (unsigned long long plNumber)
{
	String sRes;
	

	sRes = FormatFloat("###,###,###,###,###,###,###", plNumber);
	if (sRes == "")
	{
		sRes = "0";
	}
	return (sRes);
}


//---------------------------------------------------------------------------
String __inline TfrmMain::FormatNumberThousandUnit (unsigned long long plNumber)
{
	String sRes;
	String sUnit = "bytes";

	
	//GiB
	if (plNumber > 10 * 1024 * 1024 * 1024ULL)
	{
		plNumber = plNumber >> 30;
		sUnit = "GiB";
	}
	//MiB
	else if (plNumber > 10 * 1024 * 1024)
	{
		plNumber = plNumber >> 20;
		sUnit = "MiB";
	}
	//KiB
	else if (plNumber > 10 * 1024)
	{
		plNumber = plNumber >> 10;
		sUnit = "KiB";
	}
	sRes = FormatFloat("###,###,###,###,###,###,###", plNumber);
	if (sRes == "")
	{
		sRes = "0";
	}
	
	sRes += " " + sUnit;
	return (sRes);
}




//---------------------------------------------------------------------------
unsigned long long __inline TfrmMain::ParseNumberThousand (String psNumber)
{
	//return (StrToIntDef(clsUtil::ReplaceString(psNumber.c_str(), FormatSettings.ThousandSeparator.c_str(), _T("")), 0));
	TCHAR *acNumber, acRes[64];


	acNumber = psNumber.c_str();
	size_t iNumberLen = _tcslen(acNumber);

	unsigned int iResPos = 0;
	for (unsigned int iCount = 0; iCount < iNumberLen; iCount++)
	{
		//If it is a digit, we add it to the result
		if (_istdigit(acNumber[iCount]))
		{
			acRes[iResPos] = acNumber[iCount];
			iResPos++;
		}
	}
	acRes[iResPos] = NULL;
	return((unsigned long long) _ttoi64(acRes));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long __fastcall TfrmMain::RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait)
{
	unsigned long lExitCode;
	STARTUPINFO udtSI = {};
	PROCESS_INFORMATION udtPI = {};
	SECURITY_ATTRIBUTES udtSA;
	HANDLE hRead = NULL, hWrite = NULL;


	if (gbStop)
	{
		return (0);
	}

	Screen->Cursor = crAppStart;
	if ((pacOutput != NULL) && (piOutputLen > 0))
	{
		udtSA.nLength = sizeof(udtSA);
		udtSA.bInheritHandle = true;
		udtSA.lpSecurityDescriptor = NULL;
		CreatePipe(&hRead, &hWrite, &udtSA, 0);

		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		udtSI.hStdInput = hRead;
		udtSI.hStdOutput = hWrite;
		udtSI.wShowWindow = SW_HIDE;

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, false, (unsigned long) gudtOptions.iProcessPriority, NULL, (TCHAR *) pacDirectory, &udtSI, &udtPI))
		{
			//_stprintf(acTmp, _T("Cannot launch %s"), pacProcess);
		}
	}
	else
	{
		udtSA.nLength = sizeof(udtSA);
		udtSA.bInheritHandle = true;
		udtSA.lpSecurityDescriptor = NULL;

		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESHOWWINDOW;
		udtSI.wShowWindow = SW_HIDE;

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, false, (unsigned long) gudtOptions.iProcessPriority, NULL, (TCHAR *) pacDirectory, &udtSI, &udtPI))
		{
			//_stprintf(acTmp, _T("Cannot launch %s"), pacProcess);
			//MsgBox(NULL, acTmp, _T("Error"), MB_OK | MB_ICONASTERISK);
		}
	}

	if (pbWait)
	{
		do
		{
			Application->ProcessMessages();
			if (gbStop)
			{
				TerminateProcess(udtPI.hProcess, 0);
			}
			if (GetExitCodeProcess(udtPI.hProcess, &lExitCode))
			{
				if ((lExitCode == STILL_ACTIVE) && (WaitForSingleObject(udtPI.hProcess, 100) == WAIT_OBJECT_0))
				{
					lExitCode = 0;
				}
			}
		}
		while (lExitCode == STILL_ACTIVE);
	}
	else
	{
		GetExitCodeProcess(udtPI.hProcess, &lExitCode);
	}

	if ((pacOutput != NULL) && (piOutputLen > 0))
	{
		memset(pacOutput, 0, piOutputLen);
		unsigned long lRead;
		PeekNamedPipe(hRead, NULL, NULL, NULL, &lRead, NULL);
		if (lRead > 0)
		{
			::ReadFile(hRead, pacOutput, piOutputLen, &lRead, NULL);
		}
		CloseHandle(hRead);
		CloseHandle(hWrite);
	}

	CloseHandle(udtPI.hProcess);
	CloseHandle(udtPI.hThread);

	Screen->Cursor = crDefault;

	return (lExitCode);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
String __fastcall TfrmMain::GetShortName(String psLongName)
{
	TCHAR acShortFile[PATH_MAX];


	GetShortPathName(psLongName.c_str(), acShortFile, sizeof(acShortFile));
	return ((String) acShortFile);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsAPNG(const TCHAR *pacFile)
{
	#pragma pack(push, 1)
	unsigned char *acBuffer;
	struct
	{
		unsigned char acSignature[8];
	} udtPNGHeader;
	struct
	{
		unsigned int iLength;
		unsigned char acType[4];
	} udtPNGChunk;
	#pragma pack(pop)


	bool bRes = false;
	unsigned int iSize = (unsigned int) clsUtil::SizeFile(pacFile);
	if (iSize > 0)
	{
		acBuffer = new unsigned char[iSize];
		if (acBuffer)
		{
			clsUtil::ReadFile(pacFile, acBuffer, &iSize);
			unsigned int iPos = 0;
			memcpy(&udtPNGHeader, &acBuffer[iPos], sizeof(udtPNGHeader));
			iPos += sizeof(udtPNGHeader);
			if (memcmp(udtPNGHeader.acSignature, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", sizeof(udtPNGHeader.acSignature)) == 0)
			{
				do
				{
					memcpy(&udtPNGChunk, &acBuffer[iPos], sizeof(udtPNGChunk));
					iPos += sizeof(udtPNGChunk);
					udtPNGChunk.iLength = ((udtPNGChunk.iLength >> 24) & 0xFF) | ((udtPNGChunk.iLength << 8) & 0xFF0000) | ((udtPNGChunk.iLength >> 8) & 0xFF00) | ((udtPNGChunk.iLength << 24) & 0xFF000000);
					if ((memcmp(udtPNGChunk.acType, "fcTL", sizeof(udtPNGChunk.acType)) == 0) || (memcmp(udtPNGChunk.acType, "acTL", sizeof(udtPNGChunk.acType)) == 0) || (memcmp(udtPNGChunk.acType, "fdAT", sizeof(udtPNGChunk.acType)) == 0))
					{
						bRes = true;
						break;
					}
					else
					{
						iPos += udtPNGChunk.iLength + 4;
					}
				}
				while (iPos < iSize);
			}
			delete[] acBuffer;
		}
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsEXESFX(const TCHAR *pacFile)
{
	bool bRes = false;
	unsigned char *acBuffer;

	
	unsigned int iSize = 256 * 1024;
	acBuffer = new unsigned char[iSize];
	if (acBuffer)
	{
		clsUtil::ReadFile(pacFile, acBuffer, &iSize);
		
		//Check if it is an Inno Setup Installer
		if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "Inno Setup", 10) != NULL)
		{
			bRes = true;
		}
		//Check if it is an InstallShield Wizard
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "InstallShield", 13) != NULL)
		{
			bRes = true;
		}
		//Check if it is an NSIS
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "Nullsoft Install System", 23) != NULL)
		{
			bRes = true;
		}
		//Check if it is an RTPatch Updater
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "RTPatch", 7) != NULL)
		{
			bRes = true;
		}
		//Check if it is a RAR SFX
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "\x52\x61\x72\x21\x1A\x07", 6) != NULL)
		{
			bRes = true;
		}
		//Check if it is a ZIP SFX
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "\x50\x4B\x03\x04", 4) != NULL)
		{
			bRes = true;
		}
		//Check if it is a 7-ZIP SFX
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "7z@NArchive@", 12) != NULL)
		{
			bRes = true;
		}	
		delete[] acBuffer;
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsZIPSFX(const TCHAR *pacFile)
{
	bool bRes = false;
	unsigned char *acBuffer;

	
	unsigned int iSize = 1 * 1024;
	acBuffer = new unsigned char[iSize];
	if (acBuffer)
	{
		clsUtil::ReadFile(pacFile, acBuffer, &iSize);
		//Assuming it is already a ZIP variant (by extension) check if at zero bytes offset we have ZIP header
		bRes = (memcmp(acBuffer, "\x50\x4B\x03\x04", 4) != 0);
		delete[] acBuffer;
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsEXEManagedNet(const TCHAR *pacFile)
{
	bool bRes = false; //variable that indicates if managed or not.
	HANDLE hFile = CreateFile(pacFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		//succeeded
		HANDLE hOpenFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		if (hOpenFileMapping)
		{
			//Map the file , so it can be simply be acted on as a contiguous array of unsigned chars
			unsigned char* pacBaseAddress = (unsigned char*) MapViewOfFile(hOpenFileMapping, FILE_MAP_READ, 0, 0, 0);
			if (pacBaseAddress)
			{
				//having mapped the executable ,now start navigating through the sections
				//DOS header is straightforward. It is the topmost structure in the PE file
				//i.e. the one at the lowest offset into the file
				IMAGE_DOS_HEADER* udtDOSHeader = (IMAGE_DOS_HEADER*) pacBaseAddress;
				//the only important data in the DOS header is the e_lfanew
				//the e_lfanew points to the offset of the beginning of NT Headers data
				IMAGE_NT_HEADERS* udtNTHeaders = (IMAGE_NT_HEADERS*) ((unsigned char*) udtDOSHeader + udtDOSHeader->e_lfanew);
				//store the section header for future use. This will later be need to check to see if metadata lies within
				//the area as indicated by the section headers
				IMAGE_SECTION_HEADER* udtSectionHeader = (IMAGE_SECTION_HEADER*) ((unsigned char*) udtNTHeaders + sizeof(IMAGE_NT_HEADERS));
				//Now, start parsing
				//check if it is a PE file first of all. All assemblies are PE files
				if (udtNTHeaders->Signature == IMAGE_NT_SIGNATURE)
				{
					//start parsing COM table ( this is what points to the metadata and other information )
					unsigned int iNETHeaderTableLocation = udtNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress;
					if (iNETHeaderTableLocation)
					{
						//.Net header data does exist for this module, find it's location in one of the sections
						unsigned int iActualAddressFromRVA = 0;
						unsigned int iSections = udtNTHeaders->FileHeader.NumberOfSections;
						for (unsigned int iSection = 0; iSection < iSections; iSection++, udtSectionHeader++)
						{
							unsigned int iMaxOnDisk = min(udtSectionHeader->Misc.VirtualSize, udtSectionHeader->SizeOfRawData);
							unsigned int iStartSectRVA = udtSectionHeader->VirtualAddress;
							unsigned int iEndSectRVA = iStartSectRVA + iMaxOnDisk;
							if ((iNETHeaderTableLocation >= iStartSectRVA) && (iNETHeaderTableLocation < iEndSectRVA))
							{
								iActualAddressFromRVA = (udtSectionHeader->PointerToRawData) + (iNETHeaderTableLocation - iStartSectRVA);
								break;
							}
						}
						IMAGE_COR20_HEADER* udtNETHeader = (IMAGE_COR20_HEADER*) ((unsigned char*) udtDOSHeader + iActualAddressFromRVA);
						if (udtNETHeader)
						{
							//valid address obtained. Suffices to say , this is good enough to identify this as a
							//valid managed component
							bRes = true;
						}
					}
				}
				//cleanup
				UnmapViewOfFile(pacBaseAddress);
			}
			//cleanup
			CloseHandle(hOpenFileMapping);
		}
		//cleanup
		CloseHandle(hFile);
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsPDFLayered(const TCHAR *pacFile)
{
	bool bRes = false;
	unsigned char *acBuffer;

	
	unsigned int iSize = 512 * 1024;
	acBuffer = new unsigned char[iSize];
	if (acBuffer)
	{
		clsUtil::ReadFile(pacFile, acBuffer, &iSize);
		//Look for a OCG (Optional Content Groups)
		bRes = (clsUtil::MemMem(acBuffer, iSize, "<< /Type /OCG /Name", 20) != NULL);
		delete[] acBuffer;
	}
	return (bRes);
}




// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateTheme(const TCHAR *pacTheme)
{
	//Prevent flickering
	LockWindowUpdate(Handle);

	//Check if something changed to avoid applying if unneeded
	if (TStyleManager::ActiveStyle->Name != (String) pacTheme)
	{

		//RefreshStatus();

		if (pacTheme[0] != NULL)
		{
			TStyleManager::TrySetStyle(pacTheme, false);
		}
		else
		{
			mgrMain->Style = NULL; //XPStyle
		}
		RefreshStatus();
	}

	//Change instructions depending on Recycle Bin settins
	if (gudtOptions.bDoNotUseRecycleBin)
	{
		lblInstructions->Caption = "Drag on the list below files you want to optimize, and when ready, click on the right button context menu to proceed. No backups will be created, but you can enable moving to Recycle Bin if you like. Double click an item to preview it.";
	}
	else
	{
		lblInstructions->Caption = "Drag on the list below files you want to optimize, and when ready, click on the right button context menu to proceed. All processed files are copied to Recycle Bin, so you can easily restore them. You can disable moving to Recycle Bin if you like. Double click an item to preview it.";
	}

	if (gudtOptions.bAlwaysOnTop)
	{
		FormStyle = fsStayOnTop;
	}
	else
	{
		FormStyle = fsNormal;
	}


	//Reenable form updates
	LockWindowUpdate(NULL);
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::RefreshStatus(bool pbUpdateStatusBar, unsigned int piCurrent, unsigned long long plTotalBytes, unsigned long long plSavedBytes)
{
	//Prevent flickering
	//LockWindowUpdate(Handle);

    //ProcessMessages is required before changing DragAcceptFiles
	Application->ProcessMessages();

	if (gbProcess)
	{
		unsigned int iPercentBytes;
		if (plTotalBytes != 0)
		{
			//iPercentBytes = ((unsigned long long) piTotalBytes - piSavedBytes) * 100 / piTotalBytes;
			iPercentBytes = ((unsigned int) ((double) (plTotalBytes - plSavedBytes) / plTotalBytes * 100));

		}
		else
		{
			iPercentBytes = 0;
		}
		stbMain->Panels->Items[0]->Text = FormatNumberThousand(piCurrent) + " / " + FormatNumberThousand(grdFiles->RowCount - 1) + " files. " + FormatNumberThousand(plSavedBytes) + " bytes saved (" + FormatNumberThousand(iPercentBytes) + "%)";
		stbMain->Hint = stbMain->Panels->Items[0]->Text;
		Caption = stbMain->Hint + " - " + Application->Name;
		Application->Title = Caption;

		actOpen->Enabled = false;
		actOpenFolder->Enabled = false;
		actOptimize->Enabled = false;
		actStop->Enabled = true;
		actAdd->Enabled = false;
		actClear->Enabled = false;
		actRemove->Enabled = false;

		// Prevent grid sorting while optimizing
		grdFiles->Options = grdFiles->Options >> goFixedHotTrack >> goFixedRowClick >> goFixedColClick;
		DragAcceptFiles(Handle, false);
	}
	else
	{
		actOpen->Enabled = (grdFiles->RowCount > 1);
		actOpenFolder->Enabled = (grdFiles->RowCount > 1);
		actOptimize->Enabled = (grdFiles->RowCount > 1);
		actStop->Enabled = false;
		actAdd->Enabled = true;
		actClear->Enabled = (grdFiles->RowCount > 1);
		actRemove->Enabled = (grdFiles->RowCount > 1);

		grdFiles->Options = grdFiles->Options << goFixedHotTrack << goFixedRowClick << goFixedColClick;
		DragAcceptFiles(Handle, true);

		if (pbUpdateStatusBar)
		{
			if (grdFiles->RowCount > 1)
			{
				stbMain->Panels->Items[0]->Text = "0 / " + FormatNumberThousand(grdFiles->RowCount - 1) + " files";
				stbMain->Hint = stbMain->Panels->Items[0]->Text;
				Caption = stbMain->Hint + " - " + Application->Name;
				Application->Title = Caption;
				grdFiles->FixedRows = 1;
				pgbProgress->Position = 0;
				pgbProgress->Max = grdFiles->RowCount - 1;
				clsUtil::SetTaskListProgress((unsigned int) pgbProgress->Position, (unsigned int) pgbProgress->Max);
			}
			else
			{
				grdFiles->ColCount = 5;
				grdFiles->Rows[0]->BeginUpdate();
				grdFiles->Cells[KI_GRID_FILE][0] = "File";
				grdFiles->Cells[KI_GRID_EXTENSION][0] = "Extension";
				grdFiles->Cells[KI_GRID_ORIGINAL][0] = "Original size";
				grdFiles->Cells[KI_GRID_OPTIMIZED][0] = "Optimized size";
				grdFiles->Cells[KI_GRID_STATUS][0] = "Status";
				grdFiles->Rows[0]->EndUpdate();

				stbMain->Panels->Items[0]->Text = "";
				stbMain->Hint = stbMain->Panels->Items[0]->Text;
				pgbProgress->Position = 0;
				clsUtil::SetTaskListProgress((unsigned int) pgbProgress->Position, (unsigned int) pgbProgress->Max);
			}
		}
		else
		{
			Caption = Application->Name;
			Application->Title = Caption;
		}

	}
	//Reenable form updates
	//LockWindowUpdate(NULL);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetCellValue(String psValue, unsigned int piPos)
{
	//Decode the information in cell separating the value to show, with the value to parse
	TStringDynArray asValue = SplitString(psValue, "\n");
	if ((unsigned int) asValue.Length > piPos)
	{
		psValue = asValue[piPos];
	}
	return(psValue);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::SetCellFileValue(String psValue)
{
	String sRes = "";


	//only filename
	if (gudtOptions.iFilenameFormat == 1)
	{
		sRes = ExtractFileName(psValue);
	}
	//ToDo: driveletter + “:\”+partial path + filename
	else if (gudtOptions.iFilenameFormat == 2)
	{
		sRes = psValue;
	}
	//ToDo: driveletter + “:\”+partial path if fits+”...” last part of filename
	else if (gudtOptions.iFilenameFormat == 3)
	{
		sRes = psValue;
	}
	//full path+filename
	else
	{
		sRes = psValue;
	}
	sRes += "\n" + psValue;
	return(sRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall TfrmMain::GetOptionCommandLine(void)
{
	static TCHAR acCommandLine[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acCommandLine[0] == NULL)
	{
		_tcscpy(acCommandLine, GetCommandLine());
	}
	return (acCommandLine);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall TfrmMain::GetOptionArgument(const TCHAR *pacKey)
{
	TCHAR acArgument[PATH_MAX];
	TCHAR acRes[PATH_MAX] = _T("");
	TCHAR *pcStart;
	

	acArgument[0] = '/';
	_tcscpy(&acArgument[1], pacKey);
	pcStart = StrStrI(GetOptionCommandLine(), acArgument);
	if (pcStart)
	{
		TCHAR *pcEnd = _tcsstr(pcStart + _tcslen(pacKey) + 2, _T(" "));
		if (pcEnd == NULL)
		{
			pcEnd = pcStart + _tcslen(GetOptionCommandLine());
		}
		_tcsncpy(acRes, pcStart + _tcslen(pacKey) + 2, (size_t) (pcEnd - pcStart) - _tcslen(pacKey) - 2);
	}
	return (acRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall TfrmMain::GetOption(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacDefault)
{
	TCHAR acRes[2048];


	_tcscpy(acRes, GetOptionArgument(pacKey));
	if (acRes[0] == NULL)
	{
		_tcscpy(acRes, clsUtil::GetIni(pacSection, pacKey, pacDefault));
	}
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall TfrmMain::GetOption(const TCHAR *pacSection, const TCHAR *pacKey, int piDefault)
{
	TCHAR acDefault[2048];
	int iRes;


	_tcscpy(acDefault, GetOptionArgument(pacKey));
	if (acDefault[0] == NULL)
	{
		iRes = clsUtil::GetIni(pacSection, pacKey, piDefault);
	}
	else
	{
		iRes = _ttoi(acDefault);
	}
	return (iRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long __fastcall TfrmMain::GetOption(const TCHAR *pacSection, const TCHAR *pacKey, long long plDefault)
{
	TCHAR acDefault[2048];
	long long lRes;


	_tcscpy(acDefault, GetOptionArgument(pacKey));
	if (acDefault[0] == NULL)
	{
		lRes = clsUtil::GetIni(pacSection, pacKey, plDefault);
	}
	else
	{
		lRes = _ttoi64(acDefault);
	}
	return (lRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double __fastcall TfrmMain::GetOption(const TCHAR *pacSection, const TCHAR *pacKey, double pdDefault)
{
	TCHAR acDefault[2048];
	double dRes;


	_tcscpy(acDefault, GetOptionArgument(pacKey));
	if (acDefault[0] == NULL)
	{
		dRes = clsUtil::GetIni(pacSection, pacKey, pdDefault);
	}
	else
	{
		dRes = _ttof(acDefault);
	}
	return (dRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::GetOption(const TCHAR *pacSection, const TCHAR *pacKey, bool pbDefault)
{
	TCHAR acDefault[2048];
	bool bRes;


	_tcscpy(acDefault, GetOptionArgument(pacKey));
	if (acDefault[0] == NULL)
	{
		bRes = clsUtil::GetIni(pacSection, pacKey, pbDefault);
	}
	else
	{
		bRes = (_tcsicmp(acDefault, _T("true")) == 0);
	}
	return (bRes);
}



//---------------------------------------------------------------------------

