// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"


// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



// ---------------------------------------------------------------------------
TfrmMain *frmMain;
struct udtOptions gudtOptions;
bool gbProcess = false;
bool gbStop = false;


// ---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner)
{
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	TCHAR acPath[MAX_PATH];
	//SYSTEM_INFO udtSystemInfo;


	clsUtil::LoadForm(this);
	rbnMain->Minimized = clsUtil::GetIni(Name.c_str(), _T("RibbonMinimized"), rbnMain->Minimized);
	grdFiles->ColWidths[KI_GRID_FILE] = clsUtil::GetIni(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[KI_GRID_FILE]);
	grdFiles->ColWidths[KI_GRID_EXTENSION] = clsUtil::GetIni(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[KI_GRID_EXTENSION]);
	grdFiles->ColWidths[KI_GRID_ORIGINAL] = clsUtil::GetIni(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[KI_GRID_ORIGINAL]);
	grdFiles->ColWidths[KI_GRID_OPTIMIZED] = clsUtil::GetIni(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[KI_GRID_OPTIMIZED]);
	grdFiles->ColWidths[KI_GRID_STATUS] = clsUtil::GetIni(Name.c_str(), _T("Col4Width"), grdFiles->ColWidths[KI_GRID_STATUS]);
	gudtOptions.bBMPCopyMetadata = clsUtil::GetIni(_T("Options"), _T("BMPCopyMetadata"), false);
	gudtOptions.bCSSEnableTidy = clsUtil::GetIni(_T("Options"), _T("CSSEnableTidy"), false);
	_tcscpy(gudtOptions.acCSSTemplate, clsUtil::GetIni(_T("Options"), _T("CSSTemplate"), _T("low")));
	gudtOptions.bEXEDisablePETrim = clsUtil::GetIni(_T("Options"), _T("EXEDisablePETrim"), false);
	gudtOptions.bGIFCopyMetadata = clsUtil::GetIni(_T("Options"), _T("GIFCopyMetadata"), false);
	gudtOptions.bGZCopyMetadata = clsUtil::GetIni(_T("Options"), _T("GZCopyMetadata"), false);
	gudtOptions.bHTMLEnableTidy = clsUtil::GetIni(_T("Options"), _T("HTMLEnableTidy"), false);
	gudtOptions.bJPEGCopyMetadata = clsUtil::GetIni(_T("Options"), _T("JPEGCopyMetadata"), false);
	gudtOptions.bJPEGUseArithmeticEncoding = clsUtil::GetIni(_T("Options"), _T("JPEGUseArithmeticEncoding"), false);
	gudtOptions.bJSEnableJSMin = clsUtil::GetIni(_T("Options"), _T("JSEnableJSMin"), false);
	gudtOptions.bLUAEnableLeanify = clsUtil::GetIni(_T("Options"), _T("LUAEnableLeanify"), false);
	gudtOptions.bMiscCopyMetadata = clsUtil::GetIni(_T("Options"), _T("MiscCopyMetadata"), false);
	gudtOptions.bMP3CopyMetadata = clsUtil::GetIni(_T("Options"), _T("MP3CopyMetadata"), false);
	gudtOptions.bPCXCopyMetadata = clsUtil::GetIni(_T("Options"), _T("PCXCopyMetadata"), false);
	_tcscpy(gudtOptions.acPDFProfile, clsUtil::GetIni(_T("Options"), _T("PDFProfile"), _T("ebook")));
	gudtOptions.iPDFCustomDPI = clsUtil::GetIni(_T("Options"), _T("PDFCustomDPI"), 150);
	gudtOptions.bPNGCopyMetadata = clsUtil::GetIni(_T("Options"), _T("PNGCopyMetadata"), false);
	gudtOptions.bPNGAllowLossy = clsUtil::GetIni(_T("Options"), _T("PNGAllowLossy"), false);
	gudtOptions.bTIFFCopyMetadata = clsUtil::GetIni(_T("Options"), _T("TIFFCopyMetadata"), false);
	gudtOptions.bXMLEnableLeanify = clsUtil::GetIni(_T("Options"), _T("XMLEnableLeanify"), false);
	gudtOptions.bZIPCopyMetadata = clsUtil::GetIni(_T("Options"), _T("ZIPCopyMetadata"), false);
	gudtOptions.bZIPRecurse = clsUtil::GetIni(_T("Options"), _T("ZIPRecurse"), false);
	gudtOptions.bKeepAttributes = clsUtil::GetIni(_T("Options"), _T("KeepAttributes"), false);
	gudtOptions.bDoNotUseRecycleBin = clsUtil::GetIni(_T("Options"), _T("DoNotUseRecycleBin"), false);
	_tcscpy(gudtOptions.acExcludeMask, clsUtil::GetIni(_T("Options"), _T("ExcludeMask"), _T("")));
	gudtOptions.bBeepWhenDone = clsUtil::GetIni(_T("Options"), _T("BeepWhenDone"), false);
	gudtOptions.bAlwaysOnTop = clsUtil::GetIni(_T("Options"), _T("AlwaysOnTop"), false);
	gudtOptions.iLevel = clsUtil::GetIni(_T("Options"), _T("Level"), 5);
	gudtOptions.iProcessPriority = clsUtil::GetIni(_T("Options"), _T("ProcessPriority"), IDLE_PRIORITY_CLASS);
	gudtOptions.iCheckForUpdates = clsUtil::GetIni(_T("Options"), _T("CheckForUpdates"), 1);
	gudtOptions.iLogLevel = clsUtil::GetIni(_T("Options"), _T("LogLevel"), 0);
	gudtOptions.iFilenameFormat = clsUtil::GetIni(_T("Options"), _T("FilenameFormat"), 0);
	//Use Windows 10 theme by default on Windows 10 and newer
	if (!IsWindows10OrGreater())
	{
		_tcscpy(gudtOptions.acTheme, clsUtil::GetIni(_T("Options"), _T("Theme"), _T("Windows 10")));
	}
	else
	{
		_tcscpy(gudtOptions.acTheme, clsUtil::GetIni(_T("Options"), _T("Theme"), _T("Windows")));
	}
	//_tcscpy(gudtOptions.acVersion, clsUtil::GetIni(_T("Options"), _T("Version"), clsUtil::ExeVersion(Application->ExeName.c_str())));
	_tcscpy(gudtOptions.acTempDirectory, clsUtil::GetIni(_T("Options"), _T("TempDirectory"), _T("")));
	
	GetModuleFileName(NULL, acPath, sizeof(acPath) - 1);
	_tcscpy(acPath, clsUtil::ExeVersion(acPath));

	_tcscpy(gudtOptions.acVersion, clsUtil::GetIni(_T("Options"), _T("Version"), acPath));
	if (gudtOptions.bAlwaysOnTop)
	{
		FormStyle = fsStayOnTop;
	}
	else
	{
		FormStyle = fsNormal;
	}

	//Hide recent documents in ribbon application menu
	rbnMain->ApplicationMenu->Caption = " ";
	rbnMain->ApplicationMenu->CommandType = ctCommands;

	clsUtil::GetFileVersionField(Application->ExeName.c_str(), (TCHAR *) _T("LegalCopyright"), acPath, sizeof(acPath) / sizeof(TCHAR));
	rbnMain->Caption = acPath;

	pgbProgress->Parent = stbMain;
	mnuFilesClearClick(NULL);

	FormResize(Sender);


	SetPriorityClass(GetCurrentProcess(), (unsigned long) gudtOptions.iProcessPriority);
	//GetSystemInfo(&udtSystemInfo);
	//udtSystemInfo.dwNumberOfProcessors;

	UpdateTheme(gudtOptions.acTheme);
}


// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	clsUtil::SaveForm(this);

	clsUtil::SetIni(Name.c_str(), _T("RibbonMinimized"), rbnMain->Minimized);
	clsUtil::SetIni(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[KI_GRID_FILE]);
	clsUtil::SetIni(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[KI_GRID_EXTENSION]);
	clsUtil::SetIni(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[KI_GRID_ORIGINAL]);
	clsUtil::SetIni(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[KI_GRID_OPTIMIZED]);
	clsUtil::SetIni(Name.c_str(), _T("Col4Width"), grdFiles->ColWidths[KI_GRID_STATUS]);
	clsUtil::SetIni(_T("Options"), _T("BMPCopyMetadata"), gudtOptions.bBMPCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("CSSEnableTidy"), gudtOptions.bCSSEnableTidy);
	clsUtil::SetIni(_T("Options"), _T("CSSTemplate"), gudtOptions.acCSSTemplate);
	clsUtil::SetIni(_T("Options"), _T("EXEDisablePETrim"), gudtOptions.bEXEDisablePETrim);
	clsUtil::SetIni(_T("Options"), _T("GIFCopyMetadata"), gudtOptions.bGIFCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("GZCopyMetadata"), gudtOptions.bGZCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("HTMLEnableTidy"), gudtOptions.bHTMLEnableTidy);
	clsUtil::SetIni(_T("Options"), _T("JPEGCopyMetadata"), gudtOptions.bJPEGCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("JPEGUseArithmeticEncoding"), gudtOptions.bJPEGUseArithmeticEncoding);
	clsUtil::SetIni(_T("Options"), _T("JSEnableJSMin"), gudtOptions.bJSEnableJSMin);
	clsUtil::SetIni(_T("Options"), _T("LUAEnableLeanify"), gudtOptions.bLUAEnableLeanify);
	clsUtil::SetIni(_T("Options"), _T("MiscCopyMetadata"), gudtOptions.bMiscCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("MP3CopyMetadata"), gudtOptions.bMP3CopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PCXCopyMetadata"), gudtOptions.bPCXCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PDFProfile"), gudtOptions.acPDFProfile);
	clsUtil::SetIni(_T("Options"), _T("PDFCustomDPI"), gudtOptions.iPDFCustomDPI);
	clsUtil::SetIni(_T("Options"), _T("PNGCopyMetadata"), gudtOptions.bPNGCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PNGAllowLossy"), gudtOptions.bPNGAllowLossy);
	clsUtil::SetIni(_T("Options"), _T("TIFFCopyMetadata"), gudtOptions.bTIFFCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("XMLEnableLeanify"), gudtOptions.bXMLEnableLeanify);
	clsUtil::SetIni(_T("Options"), _T("ZIPCopyMetadata"), gudtOptions.bZIPCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("ZIPRecurse"), gudtOptions.bZIPRecurse);
	clsUtil::SetIni(_T("Options"), _T("KeepAttributes"), gudtOptions.bKeepAttributes);
	clsUtil::SetIni(_T("Options"), _T("DoNotUseRecycleBin"), gudtOptions.bDoNotUseRecycleBin);
	clsUtil::SetIni(_T("Options"), _T("ExcludeMask"), gudtOptions.acExcludeMask);
	clsUtil::SetIni(_T("Options"), _T("BeepWhenDone"), gudtOptions.bBeepWhenDone);
	clsUtil::SetIni(_T("Options"), _T("AlwaysOnTop"), gudtOptions.bAlwaysOnTop);
	clsUtil::SetIni(_T("Options"), _T("Level"), gudtOptions.iLevel);
	clsUtil::SetIni(_T("Options"), _T("ProcessPriority"), gudtOptions.iProcessPriority);
	clsUtil::SetIni(_T("Options"), _T("CheckForUpdates"), gudtOptions.iCheckForUpdates);
	clsUtil::SetIni(_T("Options"), _T("LogLevel"), gudtOptions.iLogLevel);
	clsUtil::SetIni(_T("Options"), _T("FilenameFormat"), gudtOptions.iFilenameFormat);
	clsUtil::SetIni(_T("Options"), _T("Theme"), gudtOptions.acTheme);
	clsUtil::SetIni(_T("Options"), _T("TempDirectory"), gudtOptions.acTempDirectory);
	clsUtil::SetIni(_T("Options"), _T("Version"), gudtOptions.acVersion);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	bool bRunning;
	HANDLE hFindFile;
	WIN32_FIND_DATA udtFindFileData;
	TCHAR acPluginsDirectory[MAX_PATH];

	if (!gbStop)
	{
		GetModuleFileName(NULL, acPluginsDirectory, sizeof(acPluginsDirectory) - 1);
		*_tcsrchr(acPluginsDirectory, '\\') = NULL;
		#if defined(_WIN64)
			_tcscat(acPluginsDirectory, _T("\\Plugins64\\"));
		#else
			_tcscat(acPluginsDirectory, _T("\\Plugins32\\"));
		#endif

		bRunning = false;
		hFindFile = FindFirstFile((((String) acPluginsDirectory) + "*.exe").c_str(), &udtFindFileData);
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

		if ((bRunning) && (clsUtil::MsgBox(Handle, ("Optimization are still being running. Do you want to stop them, and exit " + Application->Name + "?").c_str(), _T("Exit"), MB_YESNO | MB_ICONQUESTION) == ID_NO))
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
	static int iSortField = -1;
	static unsigned int iSortOrder = 0;
	unsigned int iRow;
	unsigned int iRows;


	iRows = (unsigned int) grdFiles->RowCount;
	if (iRows > 1)
	{
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
		for (iRow = 1; iRow < iRows; iRow++)
		{
			if ((iSortField == KI_GRID_ORIGINAL) || (iSortField == KI_GRID_OPTIMIZED))
			{
				sValue = FormatFloat("0000000000000000000", ParseNumberThousand(grdFiles->Cells[iSortField][iRow]));
			}
			else
			{
				sValue = grdFiles->Cells[iSortField][iRow];
			}
			sValue += "|" + grdFiles->Cells[KI_GRID_FILE][iRow] + "|" + grdFiles->Cells[KI_GRID_EXTENSION][iRow] + "|" + grdFiles->Cells[KI_GRID_ORIGINAL][iRow] + "|" + grdFiles->Cells[KI_GRID_OPTIMIZED][iRow] + "|" + grdFiles->Cells[KI_GRID_STATUS][iRow];
			lstTemp->Add(sValue);
		}

		lstTemp->Sort();

		TStringDynArray asValue;
		for (iRow = 1; iRow < iRows; iRow++)
		{
			if (iSortOrder == 0)
			{
				asValue = SplitString(lstTemp->Strings[iRow - 1], "|");
			}
			else
			{
				asValue = SplitString(lstTemp->Strings[iRows - iRow - 1], "|");
			}
			grdFiles->Rows[iRow]->BeginUpdate();
			grdFiles->Cells[KI_GRID_FILE][iRow] = asValue[1];
			grdFiles->Cells[KI_GRID_EXTENSION][iRow] = asValue[2];
			grdFiles->Cells[KI_GRID_ORIGINAL][iRow] = asValue[3];
			grdFiles->Cells[KI_GRID_OPTIMIZED][iRow] = asValue[4];
			grdFiles->Cells[KI_GRID_STATUS][iRow] = asValue[5];
			grdFiles->Rows[iRow]->EndUpdate();
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
	unsigned int iRow, iCol;


	iRow = grdFiles->Row;
	iCol = grdFiles->Col;
	if ((iRow > 0) && (iCol == KI_GRID_FILE))
	{
		ShellExecute(NULL, _T("open"), GetCellValue(grdFiles->Cells[KI_GRID_FILE][iRow], 1).c_str(), _T(""), _T(""), SW_SHOWNORMAL);
	}
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


unsigned int iPercentBytes;
unsigned long long lSavedBytes, lTotalBytes;
String sPluginsDirectory;


//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptimizeClick(TObject *Sender)
{
	unsigned int iCount, iRows;
	TCHAR acTmpFile[MAX_PATH];


	gbProcess = true;
	gbStop = false;
	RefreshStatus();

	GetModuleFileName(NULL, acTmpFile, sizeof(acTmpFile) - 1);
	*_tcsrchr(acTmpFile, '\\') = NULL;
	#if defined(_WIN64)
		_tcscat(acTmpFile, _T("\\Plugins64\\"));
	#else
		_tcscat(acTmpFile, _T("\\Plugins32\\"));
	#endif
	sPluginsDirectory = GetShortName(acTmpFile);

	lSavedBytes = 0;
	lTotalBytes = 0;
	iRows = grdFiles->RowCount;


	//Use multithreaded parallel for (PPL)
	if (false)
	{
		TParallel::For(this, 1, iRows - 1, mnuFilesOptimizeForThread);
	}
	//Use regular for loop
	else
	{
		for (iCount = 1; iCount < iRows; iCount++)
		{
			if (!gbStop)
			{
				mnuFilesOptimizeFor(NULL, iCount);
			}
			else
			{
				break;
			}
		}
	}

	//grdFiles->Enabled = true;
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
	gbProcess = false;
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptimizeForThread(TObject *Sender, int AIndex, TParallel::TLoopState *LoopState)
{
	mnuFilesOptimizeFor(Sender, AIndex);
	if (gbStop)
	{
	    LoopState->Break();
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptimizeFor(TObject *Sender, int iCount)
{
	int iLevel;
	unsigned int iFileAttributes;
	FILETIME udtFileCreated, udtFileAccessed, udtFileModified;
	String sInputFile, sFlags, sExtensionByContent;


	sInputFile = GetCellValue(grdFiles->Cells[KI_GRID_FILE][iCount], 1);

	//Add Syncrhonize
	//http://docwiki.embarcadero.com/RADStudio/Seattle/en/Using_the_Main_VCL_Thread

	stbMain->Panels->Items[0]->Text = "Processing " + sInputFile + "...";
	stbMain->Hint = stbMain->Panels->Items[0]->Text;
	pgbProgress->Position = iCount;
	clsUtil::SetTaskListProgress(pgbProgress->Position, pgbProgress->Max);
	grdFiles->Row = iCount;
	Application->ProcessMessages();


	bool bExcluded = false;
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


	//Check file still exists and is not to be excluded
	if ((clsUtil::ExistsFile(sInputFile.c_str())) && (!bExcluded))
	{
		sExtensionByContent = " " + GetExtensionByContent(sInputFile) + " ";

		if (!gudtOptions.bDoNotUseRecycleBin)
		{
			grdFiles->Cells[KI_GRID_STATUS][iCount] = "Copying to Recyclebin...";
			clsUtil::CopyToRecycleBin(sInputFile.c_str());
		}

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

		//Each extension can correspond to more than one engine, so use if instead of else if
		// BMP: ImageMagick, ImageWorsener
		if (PosEx(sExtensionByContent, KS_EXTENSION_BMP) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bBMPCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress RLE " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 -outfmt bmp -compress \"rle\" \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// CSS: CSSTidy
		if (PosEx(sExtensionByContent, KS_EXTENSION_CSS) > 0)
		{
			if (gudtOptions.bCSSEnableTidy)
			{
				RunPlugin(iCount, "CSSTidy", (sPluginsDirectory + "csstidy.exe \"%INPUTFILE%\" --template=" + gudtOptions.acCSSTemplate + " \"\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// DLL: PETrim, strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_DLL) > 0)
		{
			if (!gudtOptions.bEXEDisablePETrim)
			{
				RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
			RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// EXE: Leanify, PETrim, strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_EXE) > 0)
		{
			sFlags = "";
			//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (!IsSFX(sInputFile.c_str()))
			{
				if (!gudtOptions.bEXEDisablePETrim)
				{
					RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe /StripFixups:Y \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
				RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// FLAC: FLACOut
		if (PosEx(sExtensionByContent, KS_EXTENSION_FLAC) > 0)
		{
			RunPlugin(iCount, "FLACOut", (sPluginsDirectory + "flacout.exe /q /y " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// GIF: gifsicle
		if (PosEx(sExtensionByContent, KS_EXTENSION_GIF) > 0)
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
			RunPlugin(iCount, "gifsicle", (sPluginsDirectory + "gifsicle.exe -b -w -o \"%TMPOUTPUTFILE%\" --crop-transparency " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// GZ: Leanify , advdef, zRecompress, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_GZ) > 0)
		{
			if (!gudtOptions.bGZCopyMetadata)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "-i " + (String) iLevel + " ";
				if (gudtOptions.bJPEGCopyMetadata)
				{
					sFlags += "--keep-exif ";
				}
				RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "advdef", (sPluginsDirectory + "advdef.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tgz \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (gudtOptions.bGZCopyMetadata)
			{
				sFlags += "/c ";
			}
			RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// HTML: tidy-html5
		if (PosEx(sExtensionByContent, KS_EXTENSION_HTML) > 0)
		{
			if (gudtOptions.bHTMLEnableTidy)
			{
				RunPlugin(iCount, "tidy-html5", (sPluginsDirectory + "tidy.exe -config tidy.config -quiet -output \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\" ").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// ICO: ImageMagick, Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_ICO) > 0)
		{
			RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (gudtOptions.bPNGCopyMetadata)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// JPEG: jhead, Leanify, jpegoptim, jpegtran, mozjpegtran
		if (PosEx(sExtensionByContent, KS_EXTENSION_JPG) > 0)
		{
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "-autorot -zt -q ";
			}
			else
			{
				sFlags += "-autorot -purejpg -di -dx -dt -zt -q ";
			}	
			RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe " + sFlags + " \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);		
			
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			//Seems to cause some loss of quality
			//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -interlace Plane -define jpeg:optimize-coding=true " +sFlags +"\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);

			sFlags = "";
			if (!gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--strip-all ";
			}
			RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

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
			RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// JS: jsmin
		if (PosEx(sExtensionByContent, KS_EXTENSION_JS) > 0)
		{
			if (gudtOptions.bJSEnableJSMin)
			{
				RunPlugin(iCount, "jsmin", (sPluginsDirectory + "jsmin.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// LUA: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_LUA) > 0)
		{
			if (gudtOptions.bLUAEnableLeanify)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// MKV: mkclean
		if (PosEx(sExtensionByContent, KS_EXTENSION_MKV) > 0)
		{
			RunPlugin(iCount, "mkclean", (sPluginsDirectory + "mkclean.exe --optimize --unsafe --quiet \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MNG: advmng
		if (PosEx(sExtensionByContent, KS_EXTENSION_MNG) > 0)
		{
			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "advmng", (sPluginsDirectory + "advmng.exe -z -r -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MP3: MP3packer
		if (PosEx(sExtensionByContent, KS_EXTENSION_MP3) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bMP3CopyMetadata)
			{
				sFlags += "-t -s ";
			}
			RunPlugin(iCount, "MP3packer", (sPluginsDirectory + "mp3packer.exe " + sFlags + "-z -a \"\" -A -f \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MP4: mp4v2
		if (PosEx(sExtensionByContent, KS_EXTENSION_MP4) > 0)
		{
			RunPlugin(iCount, "mp4v2", (sPluginsDirectory + "mp4file.exe --optimize -q \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OBJ: strip
		if (PosEx(sExtensionByContent, KS_EXTENSION_OBJ) > 0)
		{
			RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OGG: rehuff
		if (PosEx(sExtensionByContent, KS_EXTENSION_OGG) > 0)
		{
			RunPlugin(iCount, "rehuff", (sPluginsDirectory + "rehuff.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// OGV: rehuff_theora
		if (PosEx(sExtensionByContent, KS_EXTENSION_OGV) > 0)
		{
			RunPlugin(iCount, "rehuff_theora", (sPluginsDirectory + "rehuff_theora.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// Microsoft OLE Compound Files: Document Press
		if (PosEx(sExtensionByContent, KS_EXTENSION_OLE) > 0)
		{
			RunPlugin(iCount, "Document Press", (sPluginsDirectory + "docprc.exe -opt \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// PCX: PCXLite, ImageMagick
		if (PosEx(sExtensionByContent, KS_EXTENSION_PCX) > 0)
		{
			RunPlugin(iCount, "PCXLite", (sPluginsDirectory + "PCXLite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (!gudtOptions.bPCXCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// PDF: ghostcript
		if (PosEx(sExtensionByContent, KS_EXTENSION_PDF) > 0)
		{
			sFlags = "-dColorImageDownsampleType=/Bicubic -dGrayImageDownsampleType=/Bicubic -dMonoImageDownsampleType=/Bicubic -dOptimize=true -dConvertCMYKImagesToRGB=true -dColorConversionStrategy=/sRGB -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dDetectDuplicateImages=true -dCompatibilityLevel=1.5 ";
			//Custom mode
			if (_tcscmp(gudtOptions.acPDFProfile, _T("Custom")) == 0)
			{
				sFlags += "-dPDFSETTINGS=/ebook -dDownsampleColorImages=true -dColorImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " -dColorImageDownsampleType=/Bicubic -dDownsampleGrayImages=true -dGrayImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " -dGrayImageDownsampleType=/Bicubic -dDownsampleMonoImages=true -dMonoImageResolution=" + (String) gudtOptions.iPDFCustomDPI + " -dMonoImageDownsampleType=/Bicubic ";
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
			#if defined(_WIN64)
				RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin64c.exe " + sFlags + "-sOutputFile=\"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			#else
				RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin32c.exe " + sFlags + "-sOutputFile=\"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			#endif
		}
		// PNG: PngOptimizer, TruePNG, pngout, optipng, pngwolf, Leanify, advpng, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_PNG) > 0)
		{
			bool bIsAPNG;
			bool bIs9Patch;

			//Android 9-patch images get broken with advpng, deflopt, optipng, pngoptimizer, pngout, pngrewrite and truepng. Only pngwolf, defluff and leanify seem to be safe. At the moment, detect them by extension .9.png.
			bIs9Patch = EndsStr(".9.png", sInputFile);
			bIsAPNG = IsAPNG(sInputFile.c_str());

			if (bIsAPNG)
			{
				RunPlugin(iCount, "apngopt", (sPluginsDirectory + "apngopt.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if (!bIs9Patch)
			{
				if (gudtOptions.bPNGAllowLossy)
				{
					RunPlugin(iCount, "pngquant", (sPluginsDirectory + "pngquant.exe --speed 1 256 --ext .png --force \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}

				RunPlugin(iCount, "PngOptimizer", (sPluginsDirectory + "PngOptimizer.exe -file:\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if ((!bIsAPNG) && (!bIs9Patch))
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
				RunPlugin(iCount, "TruePNG", (sPluginsDirectory + "truepng.exe " + sFlags + "/i0 /tz /quiet /y /out \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}

			if (!bIs9Patch)
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
				RunPlugin(iCount, "PNGOut", (sPluginsDirectory + "pngout.exe /q /y /r /d0 /mincodes0 " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}


			if (!bIs9Patch)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 6 / 9, 6);
				sFlags += "-o" + (String) iLevel + " ";
				if (bIsAPNG)
				{
					// For some reason -strip all -protect acTL,fcTL,fdAT is not keeping APNG chunks
					RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -protect acTL,fcTL,fdAT -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
				else
				{
					if (!gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "-strip all ";
					}
					RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}

			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if (!bIsAPNG)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "--zopfli-iterations=" + (String) iLevel + " ";
				RunPlugin(iCount, "pngwolf", (sPluginsDirectory + "pngwolf.exe " + sFlags + "--in=\"%INPUTFILE%\" --out=\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

				if (!bIs9Patch)
				{
					RunPlugin(iCount, "pngrewrite", (sPluginsDirectory + "pngrewrite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}

				//iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"" + grdFiles->Cells[0][iCount] + "\" \"" + acTmpFile + "\"").c_str(), acPluginsDirectory, acTmpFile);

				if (!bIs9Patch)
				{
					sFlags = "";
					iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
					iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
					sFlags += "-i " + (String) iLevel + " ";
					RunPlugin(iCount, "advpng", (sPluginsDirectory + "advpng.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}

				if (!bIs9Patch)
				{
					sFlags = "";
					if (gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "/k ";
					}
					RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				}
			}

			RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			if ((!bIsAPNG) && (!bIs9Patch))
			{
				RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// SWF: Leanfy, flasm, zRecompress
		if (PosEx(sExtensionByContent, KS_EXTENSION_SWF) > 0)
		{
			RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -x \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			if (clsUtil::SizeFile(sInputFile.c_str()) >= ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]))
			{
				//CopyFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), sInputFile.c_str(), false);
				clsUtil::CopyFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")), sInputFile.c_str());
			}
			//DeleteFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));
			DeleteFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")));

			RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -u \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			if (clsUtil::SizeFile(sInputFile.c_str()) >= ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]))
			{
				//CopyFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), sInputFile.c_str(), false);
				clsUtil::CopyFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")), sInputFile.c_str());
			}
			//DeleteFile(StringReplace(sInputFile, ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));
			DeleteFile(clsUtil::ReplaceString(sInputFile.c_str(), _T(".swf"), _T(".$wf")));

			RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tswf-lzma \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// TAR: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_TAR) > 0)
		{
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
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
			RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe " + sFlags + " \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);		

			RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (!gudtOptions.bTIFFCopyMetadata)
			{
				sFlags += "--strip-all ";
			}
			RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

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
			RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// XML: Leanify
		if (PosEx(sExtensionByContent, KS_EXTENSION_XML) > 0)
		{
			if (gudtOptions.bXMLEnableLeanify)
			{
				sFlags = "";
				//iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
				sFlags += "-i " + (String) iLevel + " ";
				RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
			}
		}
		// WEBP: dwebp + cwebp, ImageWorsener
		if (PosEx(sExtensionByContent, KS_EXTENSION_WEBP) > 0)
		{
			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 5 / 9, 5) + 1;
			sFlags += "-m " + (String) iLevel + " ";

			TCHAR acTmpFileWebp[MAX_PATH];
			_tcscpy(acTmpFileWebp, sInputFile.c_str());
			_tcscat(acTmpFileWebp, _T(".png"));

			if (RunPlugin(iCount, "dwebp", (sPluginsDirectory + "dwebp.exe -mt \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0) == 0)
			{
				RunPlugin(iCount, "cwebp", (sPluginsDirectory + "cwebp.exe -mt -quiet -lossless " + sFlags + "\"" + acTmpFileWebp + "\" -o \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
				if (clsUtil::SizeFile(acTmpFileWebp) < clsUtil::SizeFile(sInputFile.c_str()))
				{
					clsUtil::CopyFile(acTmpFileWebp, sInputFile.c_str());
				}
			}
			DeleteFile(acTmpFileWebp);

			RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// ZIP: Leanify, advzip, deflopt, defluff, deflopt
		if (PosEx(sExtensionByContent, KS_EXTENSION_ZIP) > 0)
		{
			sFlags = "";
			if (gudtOptions.bJPEGCopyMetadata)
			{
				sFlags += "--keep-exif ";
			}
			iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			//Limit ZIP no recurse to ZIP extension
			if ((!gudtOptions.bZIPRecurse) && (sExtensionByContent == ".zip"))
			{
				//sFlags += "-d 0 ";
				sFlags += "-f ";
			}
			RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
			iLevel = ((iLevel * iLevel * iLevel) / 25) + 1; //1, 1, 2, 3, 6, 9, 14, 21, 30
			sFlags += "-i " + (String) iLevel + " ";
			RunPlugin(iCount, "advzip", (sPluginsDirectory + "advzip.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			sFlags = "";
			if (gudtOptions.bZIPCopyMetadata)
			{
				sFlags += "/c ";
			}
			RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);

			RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
		}
		// MISC: ImageMagick
		if (PosEx(sExtensionByContent, KS_EXTENSION_MISC) > 0)
		{
			sFlags = "";
			if (!gudtOptions.bMiscCopyMetadata)
			{
				sFlags += "-strip ";
			}
			RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "", 0, 0);
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
		}
	}
	//If file was not processed, mark it as skipped
	if (grdFiles->Cells[KI_GRID_STATUS][iCount] == "Pending")
	{
		grdFiles->Cells[KI_GRID_STATUS][iCount] = "Skipped";
	}
	else
	{
		iPercentBytes = ((unsigned int) ((double) ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][iCount]) / ParseNumberThousand(grdFiles->Cells[KI_GRID_ORIGINAL][iCount]) * 100));
		grdFiles->Cells[KI_GRID_STATUS][iCount] = grdFiles->Cells[KI_GRID_STATUS][iCount].sprintf(_T("Done (%3d%%)."), iPercentBytes);
	}
	RefreshStatus(true, lTotalBytes, lSavedBytes);

	//Abort for loop if operation is cancelled
	if (gbStop)
	{
		return;
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesStopClick(TObject *Sender)
{
	gbStop = true;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesAddClick(TObject *Sender)
{
	int iCount;


	//Add files
	if (dlgAddFiles->Execute())
	{
		Screen->Cursor = crAppStart;
		Application->ProcessMessages();

		TStrings *strFiles = dlgAddFiles->Files;
		for (iCount = strFiles->Count; iCount > 0; iCount--)
		{
			AddFiles(strFiles->Strings[iCount - 1].c_str());
		}
		RefreshStatus();
		Screen->Cursor = crDefault;
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesClearClick(TObject *Sender)
{
	grdFiles->RowCount = 1;
	RefreshStatus();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesRemoveClick(TObject *Sender)
{
	int iRow, iRows;
	int iSelectedRow1, iSelectedRow2;


	iSelectedRow1 = grdFiles->Selection.Top;
	iSelectedRow2 = grdFiles->Selection.Bottom;

	iRows = grdFiles->RowCount - 1;
	for (iRow = iSelectedRow1; iRow < iRows; iRow++)
	{
		grdFiles->Rows[iRow]->BeginUpdate();
		grdFiles->Rows[iRow] = grdFiles->Rows[iRow + (iSelectedRow2 - iSelectedRow1 + 1)];
		grdFiles->Rows[iRow]->EndUpdate();
	}
	grdFiles->RowCount -= (iSelectedRow2 - iSelectedRow1 + 1);
	RefreshStatus();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptionsClick(TObject *Sender)
{
	frmOptions = new TfrmOptions(Application);
	frmOptions->PopupParent = this;
	frmOptions->ShowModal();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesHelpClick(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), Application->HelpFile.c_str(), _T(""), _T(""), SW_SHOWNORMAL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesAboutClick(TObject *Sender)
{
	frmAbout = new TfrmAbout(Application);
	frmAbout->PopupParent = this;
	frmAbout->ShowModal();
	delete frmAbout;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesDonateClick(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), KS_APP_DONATE_URL, _T(""), _T(""), SW_SHOWMAXIMIZED);
}




//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesExitClick(TObject *Sender)
{
	gbStop = true;
	Hide();
	Close();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrMainTimer(TObject *Sender)
{
	unsigned int iCount;


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
			for (iCount = 1; iCount < (unsigned int) _argc; iCount++)
			{
				AddFiles(_targv[iCount]);
			}
			RefreshStatus();
			Screen->Cursor = crDefault;
			mnuFilesOptimizeClick(NULL);
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
	unsigned int iCount, iFiles;
	HDROP hDrop;
	TCHAR acBuffer[MAX_PATH];


	hDrop = (HDROP) udtMessage.Drop;
	if (hDrop)
	{
		iFiles = DragQueryFile(hDrop, -1, NULL, NULL);
		if (iFiles > 0)
		{
			Screen->Cursor = crAppStart;
			Application->ProcessMessages();
			for (iCount = 0; iCount < iFiles; iCount++)
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
	unsigned int iRow, iRows;
	unsigned long long lSize;
	String sExtension, sExtensionByContent;
	HANDLE hFindFile;
	WIN32_FIND_DATA udtFindFileData;
	WIN32_FILE_ATTRIBUTE_DATA udtFileAttribute;


	if (GetFileAttributesEx(pacFile, GetFileExInfoStandard, (void*) &udtFileAttribute))
	{
		if (udtFileAttribute.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			hFindFile = FindFirstFile((((String) pacFile) + "\\*.*").c_str(), &udtFindFileData);
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
		}
		else
		{
			iRows = grdFiles->RowCount;
			//Check if already added
			for (iRow = 1; iRow < iRows; iRow++)
			{
				if (GetCellValue(grdFiles->Cells[KI_GRID_FILE][iRow], 1) == pacFile)
				{
					return;
				}
			}
			lSize = clsUtil::SizeFile(pacFile);
			//We will only add files with more than 0 bytes
			if (lSize > 0)
			{
				sExtension = " " + GetExtension(pacFile) + " ";
				sExtensionByContent = " " + GetExtensionByContent(pacFile) + " ";
				if (sExtensionByContent != "")
				{
					//We store the name to show concatenated with the full name
					grdFiles->Rows[iRows]->BeginUpdate();
					grdFiles->Cells[KI_GRID_FILE][iRows] = SetCellFileValue(pacFile);
					grdFiles->Cells[KI_GRID_EXTENSION][iRows] = sExtension;
					grdFiles->Cells[KI_GRID_ORIGINAL][iRows] = FormatNumberThousand(lSize);
					grdFiles->Cells[KI_GRID_OPTIMIZED][iRows] = "";
					grdFiles->Cells[KI_GRID_STATUS][iRows] = "Pending";
					grdFiles->Rows[iRows]->EndUpdate();
					grdFiles->RowCount++;
				}
			}
		}
	}
	RefreshStatus();
}



// ---------------------------------------------------------------------------
int __fastcall TfrmMain::RunPlugin(unsigned int piCurrent, String psStatus, String psCommandLine, String psDirectory, String psInputFile, String psOutputFile, int piErrorMin, int piErrorMax)
{
	int iError;
	unsigned int iRandom;
	unsigned long long lSize, lSizeNew;
	String sInputFile, sOutputFile, sTmpInputFile, sTmpOutputFile, sCommandLine;
	TCHAR acTmp[MAX_PATH];
	TCHAR acTempPath[MAX_PATH] = _T("");


	if (gbStop)
	{
		//Close();
		return (0);
	}

	sInputFile = psInputFile;
	sOutputFile = psOutputFile;
	sCommandLine = psCommandLine;

	//Avoid temporary name collisions across different instances
	iRandom = clsUtil::Random(0, 9999);
	
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
	clsUtil::DirectoryCreate(gudtOptions.acTempDirectory);
	
	_stprintf(acTmp, _T("%s%s"), acTempPath, (Application->Name + "_Input_" + (String) iRandom + "_" + GetFilename(sInputFile)).c_str());
	sTmpInputFile = acTmp;

	_stprintf(acTmp, _T("%s%s"), acTempPath, (Application->Name + "_Output_" + (String) iRandom + "_" + GetFilename(sInputFile)).c_str());
	sTmpOutputFile = acTmp;
	
	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());
	
	grdFiles->Cells[KI_GRID_STATUS][piCurrent] = "Running " + psStatus + "...";
	lSize = clsUtil::SizeFile(sInputFile.c_str());
	grdFiles->Cells[KI_GRID_OPTIMIZED][piCurrent] = FormatNumberThousand(lSize);

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

	iError = RunProcess(sCommandLine.c_str(), psDirectory.c_str(), NULL, 0, true);
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
				lSize = lSizeNew;
				clsUtil::CopyFile(sTmpOutputFile.c_str(), sInputFile.c_str());
			}
		}
		else if ((PosEx("%OUTPUTFILE%", psCommandLine) == 0) && (PosEx("%TMPOUTPUTFILE%", psCommandLine) == 0))
		{
			lSizeNew = clsUtil::SizeFile(sTmpInputFile.c_str());
			if ((lSizeNew > 0) && (lSizeNew < lSize))
			{
				lSize = lSizeNew;
				clsUtil::CopyFile(sTmpInputFile.c_str(), sInputFile.c_str());
				//sInputFile = sTmpOutputFile;
			}
		}	
	}

	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());

	//iPercent = (((unsigned long long) iSize) * 100) / ParseNumberThousand(grdFiles->Cells[KI_GRID_OPTIMIZED][piCurrent]);
	grdFiles->Cells[KI_GRID_OPTIMIZED][piCurrent] = FormatNumberThousand(lSize);

	return (iError);
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::CheckForUpdates(bool pbSilent)
{
	unsigned int iBuffer, iBufferLen;
	TCHAR acPath[MAX_PATH];
	TCHAR acBuffer[512];


	memset(acBuffer, 0, sizeof(acBuffer));
	if (clsUtil::DownloadFile(KS_APP_UPDATE_URL, acPath, sizeof(acPath)))
	{
		mbstowcs(acBuffer, (char *) acPath, (sizeof(acPath) / sizeof(TCHAR)) - 1);
		
		//Check we only got number and punctuation digits to detect router errors returning HTML
		iBufferLen = _tcslen(acBuffer);
		for (iBuffer = 0; iBuffer < iBufferLen; iBuffer++)
		{
			if ((!_istdigit(acBuffer[iBuffer])) && (!_istpunct(acBuffer[iBuffer])))
			{
				if (!pbSilent)
				{
					clsUtil::MsgBox(Handle, _T("Error checking for updates."), _T("Check updates"), MB_OK | MB_ICONINFORMATION);
				}
				return;
			}
		}
		
		GetModuleFileName(NULL, acPath, sizeof(acPath) - 1);
		if (_tcscmp(acBuffer, clsUtil::ExeVersion(acPath)) > 0)
		{
			if (clsUtil::MsgBox(Handle, (Application->Name + " version " + (String) acBuffer + " is available.\r\nDo you want to download it now?").c_str(), _T("Check updates"), MB_YESNO | MB_ICONQUESTION) == ID_YES)
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
		clsUtil::MsgBox(Handle, _T("Error checking for updates."), _T("Check updates"), MB_OK | MB_ICONINFORMATION);
	}
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetExtensionByContent (String psFilename)
{
	String sRes;
	unsigned char acBuffer[512];
	unsigned int iSize;


	sRes = GetExtension(psFilename);

	//If file extension is not known, get it by analyzing file contents
	if (PosEx(sRes, KS_EXTENSION_ALL) <= 0)
	{
		iSize = sizeof(acBuffer);
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
			//Check OGG / Check OGV
			else if (memcmp(&acBuffer[3], "OggS", 4) == 0)
			{
				sRes = ".ogg";
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
			{
                sRes = "";
            }
		}
	}
	return(sRes);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetExtension (String psFilename)
{
	//return (ExtractFileExt(psFilename));
	TCHAR acRes[MAX_PATH] = _T("");
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
unsigned long long __inline TfrmMain::ParseNumberThousand (String psNumber)
{
	//return (StrToIntDef(clsUtil::ReplaceString(psNumber.c_str(), FormatSettings.ThousandSeparator.c_str(), _T("")), 0));
	unsigned int iCount, iNumberLen, iResPos;
	TCHAR *acNumber, acRes[64];


	acNumber = psNumber.c_str();
	iNumberLen = _tcslen(acNumber);

	iResPos = 0;
	for (iCount = 0; iCount < iNumberLen; iCount++)
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
	STARTUPINFO udtSI;
	PROCESS_INFORMATION udtPI;
	SECURITY_ATTRIBUTES udtSA;
	HANDLE hRead, hWrite;


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

		memset(&udtSI, 0, sizeof(udtSI));
		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		udtSI.hStdInput = hRead;
		udtSI.hStdOutput = hWrite;
		udtSI.wShowWindow = SW_HIDE;
		memset(&udtPI, 0, sizeof(udtPI));

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

		memset(&udtSI, 0, sizeof(udtSI));
		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESHOWWINDOW;
		udtSI.wShowWindow = SW_HIDE;
		memset(&udtPI, 0, sizeof(udtPI));

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
	TCHAR acShortFile[MAX_PATH];

	GetShortPathName(psLongName.c_str(), acShortFile, sizeof(acShortFile));
	return ((String) acShortFile);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsAPNG(const TCHAR *pacFile)
{
	#pragma pack(push, 1)
	bool bRes;
	unsigned int iSize, iPos;
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


	bRes = false;
	iSize = (unsigned int) clsUtil::SizeFile(pacFile);
	if (iSize > 0)
	{
		acBuffer = new unsigned char[iSize];
		if (acBuffer)
		{
			clsUtil::ReadFile(pacFile, acBuffer, &iSize);
			iPos = 0;
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
bool __fastcall TfrmMain::IsSFX(const TCHAR *pacFile)
{
	bool bRes;
	unsigned int iSize;
	unsigned char *acBuffer;

	
	bRes = false;
	iSize = 256 * 1024;
	acBuffer = new unsigned char[iSize];
	if (acBuffer)
	{
		clsUtil::ReadFile(pacFile, acBuffer, &iSize);
		
		//Check if it is an Inno Setup Installer
		if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "Inno Setup", 10) != NULL)
		{
			bRes = true;
		}
		//Check if it is a RAR SFX
		else if (clsUtil::MemMem((const void *) acBuffer, iSize, (const void *) "\x52\x61\x72\x21\x1A\x07", 6) != NULL)
		{
			bRes = true;
		}
		
		delete[] acBuffer;
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsManagedNet(const TCHAR *pacFile)
{
	bool bIsManagedNet = false; //variable that indicates if managed or not.
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
							bIsManagedNet = true;
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
	return (bIsManagedNet);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateTheme(const TCHAR *pacTheme)
{
	//Check if something changed to avoid applying if unneeded
	if (TStyleManager::ActiveStyle->Name != (String) pacTheme)
	{
		//Prevent flickering
		LockWindowUpdate(Handle);

		//RefreshStatus();

		if (pacTheme[0] != NULL)
		{
			TStyleManager::TrySetStyle(pacTheme, false);
		}
		
		if (_tcscmp(pacTheme, _T("Metropolis UI Black")) == 0)
		{
			mgrMain->Style = RibbonObsidianStyle;
		}
		else if (_tcscmp(pacTheme, _T("Luna")) == 0)
		{
			mgrMain->Style = RibbonLunaStyle;
		}
		else
		{
			mgrMain->Style = NULL; //XPStyle
		}
		//rbnMain->UseCustomFrame = (_tcscmp(pacTheme, _T("Luna")) == 0);

		RefreshStatus();

		//Reenable form updates
		LockWindowUpdate(NULL);
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::RefreshStatus(bool pbUpdateStatusBar, unsigned long long plTotalBytes, unsigned long long plSavedBytes)
{
	unsigned int iPercentBytes;


	//Prevent flickering
	//LockWindowUpdate(Handle);

	if (gbProcess)
	{
		if (plTotalBytes != 0)
		{
			//iPercentBytes = ((unsigned long long) piTotalBytes - piSavedBytes) * 100 / piTotalBytes;
			iPercentBytes = ((unsigned int) ((double) (plTotalBytes - plSavedBytes) / plTotalBytes * 100));

		}
		else
		{
			iPercentBytes = 0;
		}
		stbMain->Panels->Items[0]->Text = FormatNumberThousand(grdFiles->Row) + " / " + FormatNumberThousand(grdFiles->RowCount - 1) + " files. " + FormatNumberThousand(plSavedBytes) + " bytes saved (" + FormatNumberThousand(iPercentBytes) + "%)";
		stbMain->Hint = stbMain->Panels->Items[0]->Text;
		Caption = stbMain->Hint + " - " + Application->Name;
		Application->Title = Caption;

		mnuFilesOptimize->Enabled = false;
		mnuFilesStop->Enabled = true;
		mnuFilesAdd->Enabled = false;
		mnuFilesClear->Enabled = false;
		mnuFilesRemove->Enabled = false;

		// Prevent grid sorting while optimizing
		grdFiles->Options = grdFiles->Options >> goFixedHotTrack >> goFixedRowClick >> goFixedColClick;
		DragAcceptFiles(Handle, false);
	}
	else
	{
		mnuFilesOptimize->Enabled = (grdFiles->RowCount > 1);
		mnuFilesStop->Enabled = false;
		mnuFilesAdd->Enabled = true;
		mnuFilesClear->Enabled = (grdFiles->RowCount > 1);
		mnuFilesRemove->Enabled = (grdFiles->Selection.Top > 0);

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
				clsUtil::SetTaskListProgress(pgbProgress->Position, pgbProgress->Max);
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
				clsUtil::SetTaskListProgress(pgbProgress->Position, pgbProgress->Max);
			}
		}
		else
		{
			Caption = Application->Name;
			Application->Title = Caption;
		}

	}
	actOptimize->Enabled = mnuFilesOptimize->Enabled;
	actStop->Enabled = mnuFilesStop->Enabled;
	actClear->Enabled = mnuFilesClear->Enabled;
	actRemove->Enabled = mnuFilesRemove->Enabled;

	//Reenable form updates
	//LockWindowUpdate(NULL);
}



//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetCellValue(String psValue, unsigned int piPos)
{
	//Decode the information in cell separating the value to show, with the value to parse
	TStringDynArray asValue;

	asValue = SplitString(psValue, "\n");
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



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actAddExecute(TObject *Sender)
{
	mnuFilesAddClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRemoveExecute(TObject *Sender)
{
	mnuFilesRemoveClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actClearExecute(TObject *Sender)
{
	mnuFilesClearClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actExitExecute(TObject *Sender)
{
	mnuFilesExitClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptimizeExecute(TObject *Sender)
{
	mnuFilesOptimizeClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actStopExecute(TObject *Sender)
{
	mnuFilesStopClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actOptionsExecute(TObject *Sender)
{
	mnuFilesOptionsClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actAboutExecute(TObject *Sender)
{
	mnuFilesAboutClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actInformationExecute(TObject *Sender)
{
	unsigned int iExtension, iExtensionLen;
	String sExtension;
	String sText = "";


	//Get all supported extensions
	TStringDynArray asExtension;
	asExtension = SplitString(KS_EXTENSION_ALL.UpperCase(), " ");
	iExtensionLen = asExtension.Length;

	//Sort them alphabetically
	TStringList *lstTemp = new TStringList();
	for (iExtension = 0; iExtension < iExtensionLen; iExtension++)
	{
		sExtension = asExtension[iExtension];
		//Dont push it if empty extension
		if (sExtension.Length() > 1)
		{
			lstTemp->Add(sExtension);
		}
	}
	lstTemp->Sort();

	iExtensionLen = lstTemp->Count;
	for (iExtension = 0; iExtension < iExtensionLen; iExtension++)
	{
		sExtension = lstTemp->Strings[iExtension];
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

	clsUtil::MsgBox(Handle, sText.c_str(), _T("Information"), MB_ICONINFORMATION | MB_OK);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::actDonateExecute(TObject *Sender)
{
	mnuFilesDonateClick(NULL);
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::rbnMainHelpButtonClick(TObject *Sender)
{
	mnuFilesHelpClick(NULL);
}

//---------------------------------------------------------------------------

