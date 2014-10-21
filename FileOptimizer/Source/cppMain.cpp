// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>
#include <StrUtils.hpp>
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
	SYSTEM_INFO udtSystemInfo;


	clsUtil::LoadForm(this);
	rbnMain->Minimized = clsUtil::GetIni(Name.c_str(), _T("RibbonMinimized"), rbnMain->Minimized);
	grdFiles->ColWidths[0] = clsUtil::GetIni(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[0]);
	grdFiles->ColWidths[1] = clsUtil::GetIni(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[1]);
	grdFiles->ColWidths[2] = clsUtil::GetIni(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[2]);
	grdFiles->ColWidths[3] = clsUtil::GetIni(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[3]);
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
	gudtOptions.bMiscCopyMetadata = clsUtil::GetIni(_T("Options"), _T("MiscCopyMetadata"), false);
	gudtOptions.bMP3CopyMetadata = clsUtil::GetIni(_T("Options"), _T("MP3CopyMetadata"), false);
	gudtOptions.bPCXCopyMetadata = clsUtil::GetIni(_T("Options"), _T("PCXCopyMetadata"), false);
	gudtOptions.bPNGCopyMetadata = clsUtil::GetIni(_T("Options"), _T("PNGCopyMetadata"), false);
	gudtOptions.bTIFFCopyMetadata = clsUtil::GetIni(_T("Options"), _T("TIFFCopyMetadata"), false);
	gudtOptions.bZIPCopyMetadata = clsUtil::GetIni(_T("Options"), _T("ZIPCopyMetadata"), false);
	_tcscpy(gudtOptions.acPDFProfile, clsUtil::GetIni(_T("Options"), _T("PDFProfile"), _T("ebook")));
	gudtOptions.bKeepAttributes = clsUtil::GetIni(_T("Options"), _T("KeepAttributes"), false);
	gudtOptions.bDoNotUseRecycleBin = clsUtil::GetIni(_T("Options"), _T("DoNotUseRecycleBin"), false);
	gudtOptions.iLevel = clsUtil::GetIni(_T("Options"), _T("Level"), 9);
	gudtOptions.iProcessPriority = clsUtil::GetIni(_T("Options"), _T("ProcessPriority"), IDLE_PRIORITY_CLASS);
	gudtOptions.iCheckForUpdates = clsUtil::GetIni(_T("Options"), _T("CheckForUpdates"), 1);
	gudtOptions.iLogLevel = clsUtil::GetIni(_T("Options"), _T("LogLevel"), 0);
	_tcscpy(gudtOptions.acTheme, clsUtil::GetIni(_T("Options"), _T("Theme"), _T("Windows")));
	//_tcscpy(gudtOptions.acVersion, clsUtil::GetIni(_T("Options"), _T("Version"), clsUtil::ExeVersion(Application->ExeName.c_str())));
	GetModuleFileName(NULL, acPath, sizeof(acPath) - 1);
	_tcscpy(acPath, clsUtil::ExeVersion(acPath));
	_tcscpy(gudtOptions.acVersion, clsUtil::GetIni(_T("Options"), _T("Version"), acPath));

	FormResize(Sender);
	pgbProgress->Parent = stbMain;
	mnuFilesClearClick(NULL);

	//Hide recent documents in ribbon application menu
	rbnMain->ApplicationMenu->Caption = " ";
	rbnMain->ApplicationMenu->CommandType = ctCommands;

	SetPriorityClass(GetCurrentProcess(), (unsigned long) gudtOptions.iProcessPriority);
	GetSystemInfo(&udtSystemInfo);
	//udtSystemInfo.dwNumberOfProcessors;

	UpdateTheme(gudtOptions.acTheme);
}


// ---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	clsUtil::SaveForm(this);
	clsUtil::SetIni(Name.c_str(), _T("RibbonMinimized"), rbnMain->Minimized);
	clsUtil::SetIni(Name.c_str(), _T("Col0Width"), grdFiles->ColWidths[0]);
	clsUtil::SetIni(Name.c_str(), _T("Col1Width"), grdFiles->ColWidths[1]);
	clsUtil::SetIni(Name.c_str(), _T("Col2Width"), grdFiles->ColWidths[2]);
	clsUtil::SetIni(Name.c_str(), _T("Col3Width"), grdFiles->ColWidths[3]);
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
	clsUtil::SetIni(_T("Options"), _T("MiscCopyMetadata"), gudtOptions.bMiscCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("MP3CopyMetadata"), gudtOptions.bMP3CopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PCXCopyMetadata"), gudtOptions.bPCXCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PNGCopyMetadata"), gudtOptions.bPNGCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("TIFFCopyMetadata"), gudtOptions.bTIFFCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("ZIPCopyMetadata"), gudtOptions.bZIPCopyMetadata);
	clsUtil::SetIni(_T("Options"), _T("PDFProfile"), gudtOptions.acPDFProfile);
	clsUtil::SetIni(_T("Options"), _T("DoNotUseRecycleBin"), gudtOptions.bDoNotUseRecycleBin);
	clsUtil::SetIni(_T("Options"), _T("KeepAttributes"), gudtOptions.bKeepAttributes);
	clsUtil::SetIni(_T("Options"), _T("Level"), gudtOptions.iLevel);
	clsUtil::SetIni(_T("Options"), _T("ProcessPriority"), gudtOptions.iProcessPriority);
	clsUtil::SetIni(_T("Options"), _T("CheckForUpdates"), gudtOptions.iCheckForUpdates);
	clsUtil::SetIni(_T("Options"), _T("LogLevel"), gudtOptions.iLogLevel);
	clsUtil::SetIni(_T("Options"), _T("Theme"), gudtOptions.acTheme);
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

		if ((bRunning) && (clsUtil::MsgBox(NULL, ("Optimization are still being running. Do you want to stop them, and exit " + Application->Name + "?").c_str(), _T("Exit"), MB_YESNO | MB_ICONQUESTION) == ID_NO))
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
	//Prevent flickering
	LockWindowUpdate(Handle);	

	grdFiles->ColWidths[0] = grdFiles->Width >> 1;
	grdFiles->ColWidths[1] = (grdFiles->Width - grdFiles->ColWidths[0]) / 3;
	grdFiles->ColWidths[2] = (grdFiles->Width - grdFiles->ColWidths[0]) / 3;
	grdFiles->ColWidths[3] = (grdFiles->Width - grdFiles->ColWidths[0]) / 3;

	//Reenable form updates
	LockWindowUpdate(NULL);	
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	if (ARow & 1)
	{
		grdFiles->Canvas->Brush->Color = clGradientInactiveCaption;
	}
	else
	{
		grdFiles->Canvas->Brush->Color = clWindow;
	}

	if ((ARow > 0) && (ACol == 0))
	{
		grdFiles->Canvas->Font->Color = clHotLight;
		grdFiles->Canvas->Font->Style = grdFiles->Canvas->Font->Style << fsUnderline;
	}

	Rect.left -= 2;
	grdFiles->Canvas->FillRect(Rect);

	//Left aligned
	if ((ACol == 0) || (ACol == 3))
	{
		grdFiles->Canvas->TextRect(Rect, Rect.left + 4, Rect.top + 4, grdFiles->Cells[ACol][ARow]);
	}
	//Right aligned
	else
	{
		grdFiles->Canvas->TextRect(Rect, Rect.right - Canvas->TextWidth(grdFiles->Cells[ACol][ARow]) - 4, Rect.top + 4, grdFiles->Cells[ACol][ARow]);
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesFixedCellClick(TObject *Sender, int ACol, int ARow)
{
	static int iSortField = -1;
	static unsigned int iSortOrder = 0;
	unsigned int iRow;
	unsigned int iRows;


	iRows = grdFiles->RowCount;
	if (iRows > 1)
	{
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
			if ((iSortField == 1) || (iSortField == 2))
			{
				sValue = FormatFloat("0000000000", ParseNumberThousand(grdFiles->Cells[1][iRow]));
			}
			else
			{
				sValue = grdFiles->Cells[1][iRow];
			}
			sValue += "|" + grdFiles->Cells[0][iRow] + "|" + grdFiles->Cells[1][iRow] + "|" + grdFiles->Cells[2][iRow] + "|" + grdFiles->Cells[3][iRow];
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
			grdFiles->Cells[0][iRow] = asValue[1];
			grdFiles->Cells[1][iRow] = asValue[2];
			grdFiles->Cells[2][iRow] = asValue[3];
			grdFiles->Cells[3][iRow] = asValue[4];
		}
		delete lstTemp;
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	int iRow, iCol;

	grdFiles->MouseToCell(X, Y, iCol, iRow);
	if ((iRow >= 0) && (iCol >=0))
	{
		//grdFiles->Row = iRow;
		//grdFiles->Col = iCol;
		Application->CancelHint();
		grdFiles->Hint = grdFiles->Cells[iCol][iRow];
		//RefreshStatus();
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::grdFilesDblClick(TObject *Sender)
{
	unsigned int iRow, iCol;


	iRow = grdFiles->Row;
	iCol = grdFiles->Col;
	if ((iRow > 0) && (iCol == 0))
	{
		ShellExecute(NULL, _T("open"), grdFiles->Cells[0][iRow].c_str(), _T(""), _T(""), SW_SHOWNORMAL);
	}
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::stbMainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect)
{
	if (Panel == stbMain->Panels->Items[1])
	{
		pgbProgress->Top = Rect.top;
		pgbProgress->Left = Rect.left;
		pgbProgress->Width = Rect.right - Rect.left;
		pgbProgress->Height = Rect.bottom - Rect.top;
	}
}


//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptimizeClick(TObject *Sender)
{
	unsigned int iCount, iRows;
	int iError;
	int iLevel;
	unsigned int iFileAttributes, iSavedBytes, iTotalBytes, iPercentBytes;
	FILETIME udtFileCreated, udtFileModified;
	String sFlags;
	String sExtension;
	TCHAR acTmpFile[MAX_PATH];
	String sPluginsDirectory;
	//String sTmpFile, sShortFile; //To be deleted when migrated to RunPluginNew;
	String sInputFile;


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

	iSavedBytes = 0;
	iTotalBytes = 0;
	iRows = grdFiles->RowCount;
	for (iCount = 1; iCount < iRows; iCount++)
	{
		stbMain->Panels->Items[0]->Text = "Processing " + grdFiles->Cells[0][iCount] + "...";
		stbMain->Hint = stbMain->Panels->Items[0]->Text;
		pgbProgress->Position = iCount;
		clsUtil::SetTaskListProgress(pgbProgress->Position, pgbProgress->Max);
		grdFiles->Row = iCount;
		Application->ProcessMessages();


		sInputFile = grdFiles->Cells[0][iCount];
		
		//Check file still exists
		if (clsUtil::ExistsFile(sInputFile.c_str())
		{			
			sExtension = " " + GetExtension(sInputFile).LowerCase() + " ";

			if (!gudtOptions.bDoNotUseRecycleBin)
			{
				clsUtil::CopyToRecycleBin(grdFiles->Cells[0][iCount].c_str());
			}

			if (gudtOptions.bKeepAttributes)
			{
				clsUtil::GetFileTimestamp(sInputFile.c_str(), &udtFileCreated, &udtFileModified);
				iFileAttributes = GetFileAttributes(sInputFile.c_str());
			}
			SetFileAttributes(sInputFile.c_str(), FILE_ATTRIBUTE_NORMAL);

			//Each extension can correspond to more than one engine, so use if instead of else if
			// BMP: ImageMagick, ImageWorsener
			if (PosEx(sExtension, KS_EXTENSION_BMP) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bBMPCopyMetadata)
				{
					sFlags += "-strip ";
				}
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress RLE " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress RLE " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 -outfmt bmp -compress \"rle\" \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 -outfmt bmp -compress \"rle\" \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// CSS: CSSTidy
			if (PosEx(sExtension, KS_EXTENSION_CSS) > 0)
			{
				if (gudtOptions.bCSSEnableTidy)
				{
					//iError = RunPlugin(iCount, "CSSTidy", (sPluginsDirectory + "csstidy.exe \"" + sShortFile + "\" --template=" + gudtOptions.acCSSTemplate + " \"" + acTmpFile + " \"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "CSSTidy", (sPluginsDirectory + "csstidy.exe \"%INPUTFILE%\" --template=" + gudtOptions.acCSSTemplate + " \"\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				else
				{
					grdFiles->Cells[2][iCount] = grdFiles->Cells[1][iCount];
					grdFiles->Cells[3][iCount] = "Done (100%).";
				}
			}
			// DLL: PETrim, strip
			if (PosEx(sExtension, KS_EXTENSION_DLL) > 0)
			{
				if (!gudtOptions.bEXEDisablePETrim)
				{
					//iError = RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				//iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// EXE: PETrim, strip
			if (PosEx(sExtension, KS_EXTENSION_EXE) > 0)
			{
				if (!IsInnoSetup(sInputFile.c_str()))
				{
					if (!gudtOptions.bEXEDisablePETrim)
					{
						//iError = RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe /StripFixups:Y \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
						iError = RunPlugin(iCount, "PETrim", (sPluginsDirectory + "petrim.exe /StripFixups:Y \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
					}
					//iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				else
				{
					grdFiles->Cells[2][iCount] = grdFiles->Cells[1][iCount];
					grdFiles->Cells[3][iCount] = "Done (100%).";
				}
			}
			// FLAC: FLACOut
			if (PosEx(sExtension, KS_EXTENSION_FLAC) > 0)
			{
				iError = RunPlugin(iCount, "FLACOut", (sPluginsDirectory + "flacout.exe /q /y " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// GIF: ImageMagick, gifsicle
			if (PosEx(sExtension, KS_EXTENSION_GIF) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bGIFCopyMetadata)
				{
					sFlags += "-strip ";
				}
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -coalesce -layers optimize " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -coalesce -layers optimize " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 3 / 9, 3);
				sFlags += "-O" + (String) iLevel + " ";
				if (!gudtOptions.bGIFCopyMetadata)
				{
					sFlags += "--no-comments --no-extensions --no-names ";
				}
				//iError = RunPlugin(iCount, "gifsicle", (sPluginsDirectory + "gifsicle.exe -b -w " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "gifsicle", (sPluginsDirectory + "gifsicle.exe -b -w -o \"%TMPOUTPUTFILE%\" --crop-transparency " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// GZ: Leanify , advdef, zRecompress, deflopt, defluff, deflopt
			if (PosEx(sExtension, KS_EXTENSION_GZ) > 0)
			{
				if (gudtOptions.bGZCopyMetadata)
				{
					sFlags = "";
					iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
					sFlags += "-i " + (String) iLevel + " ";
					iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				//iError = RunPlugin(iCount, "advdef", (sPluginsDirectory + "advdef.exe -z -q -4 " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "advdef", (sPluginsDirectory + "advdef.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tgz \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tgz \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				if (gudtOptions.bGZCopyMetadata)
				{
					sFlags += "/c ";
				}
				//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat " + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// HTML: tidy-html5
			if (PosEx(sExtension, KS_EXTENSION_HTML) > 0)
			{
				if (gudtOptions.bHTMLEnableTidy)
				{
					//iError = RunPlugin(iCount, "tidy-html5", (sPluginsDirectory + "tidy.exe -config tidy.config -quiet -output \"" + acTmpFile + "\" \"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "tidy-html5", (sPluginsDirectory + "tidy.exe -config tidy.config -quiet -output \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\" ").c_str(), sPluginsDirectory, sInputFile, "");
				}
				else
				{
					grdFiles->Cells[2][iCount] = grdFiles->Cells[1][iCount];
					grdFiles->Cells[3][iCount] = "Done (100%).";
				}
			}			
			// ICO: ImageMagick, Leanify
			if (PosEx(sExtension, KS_EXTENSION_ICO) > 0)
			{
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// JPEG: jhead jpegoptim, jpegtran, mozjpegtran
			if (PosEx(sExtension, KS_EXTENSION_JPG) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bJPEGCopyMetadata)
				{
					//iError = RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe -purejpg -di -dx -dt -q \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");		
					iError = RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe -purejpg -di -dx -dt -q \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
					sFlags += "-strip ";
				}
				
				//Seems to cause some loss of quality
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -interlace Plane -define jpeg:optimize-coding=true " +sFlags +"\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);

				sFlags = "";
				if (!gudtOptions.bJPEGCopyMetadata)
				{
					sFlags += "--strip-all ";
				}
				//iError = RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

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
				//iError = RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"" + acTmpFile + "\" -progressive " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// JS: jsmin
			if (PosEx(sExtension, KS_EXTENSION_JS) > 0)
			{
				if (gudtOptions.bJSEnableJSMin)
				{
					//iError = RunPlugin(iCount, "jsmin", (sPluginsDirectory + "jsmin.bat \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "jsmin", (sPluginsDirectory + "jsmin.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				else
				{
					grdFiles->Cells[2][iCount] = grdFiles->Cells[1][iCount];
					grdFiles->Cells[3][iCount] = "Done (100%).";
				}
			}
			// MNG: advmng
			if (PosEx(sExtension, KS_EXTENSION_MNG) > 0)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				//iError = RunPlugin(iCount, "advmng", (sPluginsDirectory + "advmng.exe -z -r -q -4 " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "advmng", (sPluginsDirectory + "advmng.exe -z -r -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// MP3: MP3packer
			if (PosEx(sExtension, KS_EXTENSION_MP3) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bMP3CopyMetadata)
				{
					sFlags += "-t -s ";
				}
				//iError = RunPlugin(iCount, "MP3packer", (sPluginsDirectory + "mp3packer.exe " + sFlags + "-z -a \"\" -A -f \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "MP3packer", (sPluginsDirectory + "mp3packer.exe " + sFlags + "-z -a \"\" -A -f \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// OBJ: strip
			if (PosEx(sExtension, KS_EXTENSION_OBJ) > 0)
			{
				//iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "strip", (sPluginsDirectory + "strip.exe --strip-all -o \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// OGG: rehuff
			if (PosEx(sExtension, KS_EXTENSION_OGG) > 0)
			{
				//iError = RunPlugin(iCount, "rehuff", (sPluginsDirectory + "rehuff.exe \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "rehuff", (sPluginsDirectory + "rehuff.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// OGV: rehuff_theora
			if (PosEx(sExtension, KS_EXTENSION_OGV) > 0)
			{
				//iError = RunPlugin(iCount, "rehuff_theora", (sPluginsDirectory + "rehuff_theora.exe \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "rehuff_theora", (sPluginsDirectory + "rehuff_theora.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// Microsoft OLE Compound Files: Document Press
			if (PosEx(sExtension, KS_EXTENSION_OLE) > 0)
			{
				//iError = RunPlugin(iCount, "Document Press", (sPluginsDirectory + "docprc.exe -opt \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "Document Press", (sPluginsDirectory + "docprc.exe -opt \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// PCX: PCXLite, ImageMagick
			if (PosEx(sExtension, KS_EXTENSION_PCX) > 0)
			{
				//iError = RunPlugin(iCount, "PCXLite", (sPluginsDirectory + "PCXLite.exe \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "PCXLite", (sPluginsDirectory + "PCXLite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				if (!gudtOptions.bPCXCopyMetadata)
				{
					sFlags += "-strip ";
				}
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// PDF: ghostcript
			if (PosEx(sExtension, KS_EXTENSION_PDF) > 0)
			{
				#if defined(_WIN64)
					//iError = RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin64c -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dPDFSETTINGS=/" + (String) gudtOptions.acPDFProfile + " -dCompatibilityLevel=1.5 -sOutputFile=\"" + acTmpFile + "\" \"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin64c -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dPDFSETTINGS=/" + (String) gudtOptions.acPDFProfile + " -dCompatibilityLevel=1.5 -sOutputFile=\"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				#else
					//iError = RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin32c -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dPDFSETTINGS=/" + (String) gudtOptions.acPDFProfile + " -dCompatibilityLevel=1.5 -sOutputFile=\"" + acTmpFile + "\" \"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "Ghostcript", (sPluginsDirectory + "gswin32c -q -dBATCH -dNOPAUSE -dSAFER -dDELAYSAFER -dQUIET -dNOPROMPT -sDEVICE=pdfwrite -dPDFSETTINGS=/" + (String) gudtOptions.acPDFProfile + " -dCompatibilityLevel=1.5 -sOutputFile=\"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				#endif
			}
			// PNG: PngOptimizer, TruePNG, pngout, optipng, pngwolf, Leanify, advpng, deflopt, defluff, deflopt
			if (PosEx(sExtension, KS_EXTENSION_PNG) > 0)
			{
				bool bIsAPNG;

				bIsAPNG = IsAPNG(sInputFile.c_str());

				if (bIsAPNG)
				{
					//iError = RunPlugin(iCount, "apngopt", (sPluginsDirectory + "apngopt.exe \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "apngopt", (sPluginsDirectory + "apngopt.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}

				//iError = RunPlugin(iCount, "PngOptimizer", (sPluginsDirectory + "PngOptimizer.exe -file:\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "PngOptimizer", (sPluginsDirectory + "PngOptimizer.exe -file:\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				if (!bIsAPNG)
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
						sFlags += "/md remove all ";
					}
					//iError = RunPlugin(iCount, "TruePNG", (sPluginsDirectory + "truepng.exe " + sFlags + "/quiet /y /out \"" + acTmpFile + "\" \"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "TruePNG", (sPluginsDirectory + "truepng.exe " + sFlags + "/quiet /y /out \"%TMPOUTPUTFILE%\" \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}

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
				//iError = RunPlugin(iCount, "PNGOut", (sPluginsDirectory + "pngout.exe /q /y /r /d0 /mincodes0 " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "PNGOut", (sPluginsDirectory + "pngout.exe /q /y /r /d0 /mincodes0 " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 6 / 9, 6);
				sFlags += "-o" + (String) iLevel + " ";
				if (bIsAPNG)
				{
					// For some reason -strip all -protect acTL,fcTL,fdAT is not keeping APNG chunks
					//iError = RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -protect acTL,fcTL,fdAT -quiet " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -protect acTL,fcTL,fdAT -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				else
				{
					if (!gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "-strip all ";
					}
					//iError = RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -quiet " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "OptiPNG", (sPluginsDirectory + "optipng.exe -zw32k -quiet " + sFlags + + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}

				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				if (!bIsAPNG)
				{
					sFlags = "";
					iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
					sFlags += "--zopfli-iterations=" + (String) iLevel + " ";
					//iError = RunPlugin(iCount, "pngwolf", (sPluginsDirectory + "pngwolf.exe " + sFlags + "--in=\"" + sShortFile + "\" --out=\"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "pngwolf", (sPluginsDirectory + "pngwolf.exe " + sFlags + "--in=\"%INPUTFILE%\" --out=\"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

					//iError = RunPlugin(iCount, "pngrewrite", (sPluginsDirectory + "pngrewrite.exe \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
					iError = RunPlugin(iCount, "pngrewrite", (sPluginsDirectory + "pngrewrite.exe \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

					//iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"" + grdFiles->Cells[0][iCount] + "\" \"" + acTmpFile + "\"").c_str(), acPluginsDirectory, acTmpFile);

					sFlags = "";
					iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
					sFlags += "-i " + (String) iLevel + " ";
					//iError = RunPlugin(iCount, "advpng", (sPluginsDirectory + "advpng.exe -z -q -4 " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "advpng", (sPluginsDirectory + "advpng.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

					sFlags = "";
					if (gudtOptions.bPNGCopyMetadata)
					{
						sFlags += "/k ";
					}
					//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
				//iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat " + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				
				if (!bIsAPNG)
				{
					//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				}
			}
			// SWF: Leanfy, flasm, zRecompress
			if (PosEx(sExtension, KS_EXTENSION_SWF) > 0)
			{
				//ToDo: TEST
				//iError = RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -x \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -x \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				if (clsUtil::SizeFile(sInputFile.c_str()) >= (unsigned int) ParseNumberThousand(grdFiles->Cells[1][iCount]))
				{
					CopyFile(StringReplace(grdFiles->Cells[0][iCount], ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), grdFiles->Cells[0][iCount].c_str(), false);
				}
				DeleteFile(StringReplace(grdFiles->Cells[0][iCount], ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));

				//iError = RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -u \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "flasm", (sPluginsDirectory + "flasm.exe -u \"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				if (clsUtil::SizeFile(sInputFile.c_str()) >= (unsigned int) ParseNumberThousand(grdFiles->Cells[1][iCount]))
				{
					CopyFile(StringReplace(grdFiles->Cells[0][iCount], ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).c_str(), grdFiles->Cells[0][iCount].c_str(), false);
				}
				DeleteFile(StringReplace(grdFiles->Cells[0][iCount], ".swf", ".$wf", TReplaceFlags() << rfReplaceAll << rfIgnoreCase));

				//iError = RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tswf-lzma \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "zRecompress", (sPluginsDirectory + "zRecompress.exe -tswf-lzma \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// TAR: Leanify
			if (PosEx(sExtension, KS_EXTENSION_TAR) > 0)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// TIFF: jhead, ImageMagick, jpegoptim, jpegtran, mozjpegtran
			if (PosEx(sExtension, KS_EXTENSION_TIF) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bTIFFCopyMetadata)
				{
					//iError = RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe -purejpg -di -dx -dt -q \"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");		
					iError = RunPlugin(iCount, "jhead", (sPluginsDirectory + "jhead.exe -purejpg -di -dx -dt -q \"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
					sFlags += "-strip ";
				}
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet -compress ZIP " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				if (!gudtOptions.bTIFFCopyMetadata)
				{
					sFlags += "--strip-all ";
				}
				//iError = RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "jpegoptim", (sPluginsDirectory + "jpegoptim.exe -o -q --all-progressive " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

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
				//iError = RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "jpegtran", (sPluginsDirectory + "jpegtran.exe -progressive " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"" + acTmpFile + "\" -progressive " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "mozjpegtran", (sPluginsDirectory + "mozjpegtran.exe -outfile \"%TMPOUTPUTFILE%\" -progressive " + sFlags + "\"%INPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// WEBP: dwebp + cwebp, ImageWorsener
			if (PosEx(sExtension, KS_EXTENSION_WEBP) > 0)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 5 / 9, 5) + 1;
				sFlags += "-m " + (String) iLevel + " ";

				TCHAR acTmpFileWebp[MAX_PATH];
				_tcscpy(acTmpFileWebp, acTmpFile);
				_tcscat(acTmpFileWebp, _T(".png"));

				//ToDo: TEST
				//iError = RunPlugin(iCount, "dwebp", (sPluginsDirectory + "dwebp.exe -mt \"" + sShortFile + "\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "dwebp", (sPluginsDirectory + "dwebp.exe -mt \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "");
				if (iError == 0)
				{
					//iError = RunPlugin(iCount, "cwebp", (sPluginsDirectory + "cwebp.exe -mt -quiet -lossless " + sFlags + "\"" + acTmpFileWebp + "\" -o \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, "");
					iError = RunPlugin(iCount, "cwebp", (sPluginsDirectory + "cwebp.exe -mt -quiet -lossless " + sFlags + "\"" + acTmpFileWebp + "\" -o \"%INPUTFILE%\" -o \"" + acTmpFileWebp + "\"").c_str(), sPluginsDirectory, sInputFile, "");
					if (clsUtil::SizeFile(acTmpFile) < clsUtil::SizeFile(sInputFile.c_str()))
					{
						CopyFile(acTmpFile, grdFiles->Cells[0][iCount].c_str(), false);
					}
				}
				DeleteFile(acTmpFileWebp);

				//iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageWorsener", (sPluginsDirectory + "imagew.exe -noresize -zipcmprlevel 9 \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// ZIP: Leanify, advzip, deflopt, defluff, deflopt
			if (PosEx(sExtension, KS_EXTENSION_ZIP) > 0)
			{
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 8 / 9, 8) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				iError = RunPlugin(iCount, "Leanify", (sPluginsDirectory + "leanify.exe -q " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			
				sFlags = "";
				iLevel = min(gudtOptions.iLevel * 7 / 9, 7) + 1;
				sFlags += "-i " + (String) iLevel + " ";
				//iError = RunPlugin(iCount, "advzip", (sPluginsDirectory + "advzip.exe -z -q -4 " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "advzip", (sPluginsDirectory + "advzip.exe -z -q -4 " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				sFlags = "";
				if (gudtOptions.bZIPCopyMetadata)
				{
					sFlags += "/c ";
				}
				//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");

				//iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat " + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "defluff", (sPluginsDirectory + "defluff.bat \"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
				
				//iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"" + sShortFile + "\"").c_str(), sPluginsDirectory, "");
				iError = RunPlugin(iCount, "DeflOpt", (sPluginsDirectory + "deflopt.exe /a /b /s " + sFlags + "\"%TMPINPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}
			// MISC: ImageMagick
			if (PosEx(sExtension, KS_EXTENSION_MISC) > 0)
			{
				sFlags = "";
				if (!gudtOptions.bMiscCopyMetadata)
				{
					sFlags += "-strip ";
				}
				//iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"" + sShortFile + "\" \"" + acTmpFile + "\"").c_str(), sPluginsDirectory, acTmpFile);
				iError = RunPlugin(iCount, "ImageMagick", (sPluginsDirectory + "ImageMagick.exe -quiet " + sFlags + "\"%INPUTFILE%\" \"%TMPOUTPUTFILE%\"").c_str(), sPluginsDirectory, sInputFile, "");
			}

			if (gudtOptions.bKeepAttributes)
			{
				if (iFileAttributes != INVALID_FILE_ATTRIBUTES)
				{
					SetFileAttributes(sInputFile.c_str(), iFileAttributes);
				}
				clsUtil::SetFileTimestamp(sInputFile.c_str(), &udtFileCreated, &udtFileModified);
			}

			//Make sure the file was indeed processed because asuming we got gains. This is to solve Pending items being counted as 0 bytes
			if (grdFiles->Cells[2][iCount] != "")
			{
				iTotalBytes += (ParseNumberThousand(grdFiles->Cells[1][iCount]));
				iSavedBytes += (ParseNumberThousand(grdFiles->Cells[1][iCount]) - ParseNumberThousand(grdFiles->Cells[2][iCount]));
			}
		}
		//If file was not processed, mark it as skipped
		if (grdFiles->Cells[3][iCount] == "Pending")
		{
			grdFiles->Cells[3][iCount] = "Skipped";
		}
		RefreshStatus(true, iTotalBytes, iSavedBytes);

		//Abort for loop if operation is cancelled
		if (mbCancel)
		{
			break;
		}
	}

	//grdFiles->Enabled = true;
	if (iTotalBytes != 0)
	{
		iPercentBytes = iSavedBytes * 100 / iTotalBytes;
	}
	else
	{
		iPercentBytes = 0;
	}

	stbMain->Panels->Items[0]->Text = FormatNumberThousand(iCount - 1) + " files processed. " + FormatNumberThousand(iSavedBytes) + " bytes saved (" + FormatNumberThousand(iPercentBytes) + "%)";
	stbMain->Hint = stbMain->Panels->Items[0]->Text;
	gbProcess = false;
	RefreshStatus(false);
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
		TStrings *strFiles = dlgAddFiles->Files;
		for (iCount = strFiles->Count; iCount > 0; iCount--)
		{
			AddFiles(strFiles->Strings[iCount - 1].c_str());
		}
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
	int iCol, iCols;


	iSelectedRow1 = grdFiles->Selection.Top;
	iSelectedRow2 = grdFiles->Selection.Bottom;

	iCols = grdFiles->ColCount;
	iRows = grdFiles->RowCount - 1;
	for (iRow = iSelectedRow2; iRow < iRows; iRow++)
	{
		for (iCol = 0; iCol < iCols; iCol++)
		{
			grdFiles->Cells[iCol][iRow] = grdFiles->Cells[iCol][iRow + 1];
		}
	}
	grdFiles->RowCount -= (iSelectedRow2 - iSelectedRow1 + 1);
	RefreshStatus();
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesOptionsClick(TObject *Sender)
{
	frmOptions = new TfrmOptions(Application);
	frmOptions->ShowModal();
	delete frmOptions;
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
	frmAbout->ShowModal();
	delete frmAbout;
}



//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuFilesDonateClick(TObject *Sender)
{
	ShellExecute(NULL, _T("open"), _T("http://nikkhokkho.sourceforge.net/images/FileOptimizerDonate.html"), _T(""), _T(""), SW_SHOWMAXIMIZED);
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
			gudtOptions.iCheckForUpdates = (clsUtil::MsgBox(NULL, ("Do you want " + Application->Name + " to automatically check for updates?").c_str(), _T("Check for updates"), MB_YESNO | MB_ICONQUESTION) == ID_YES);
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
	unsigned int iRow, iRows, iSize;
	String sExtension;
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
				if (grdFiles->Cells[0][iRow] == pacFile)
				{
					return;
				}
			}
			iSize = clsUtil::SizeFile(pacFile);
			//We will only add files with more than 0 bytes
			if (iSize > 0)
			{
				sExtension = " " + GetExtension(pacFile).LowerCase() + " ";
				if (PosEx(sExtension, KS_EXTENSION_ALL) > 0)
				{
					grdFiles->Cells[0][iRows] = pacFile;
					grdFiles->Cells[1][iRows] = FormatNumberThousand(iSize);
					grdFiles->Cells[2][iRows] = "";
					grdFiles->Cells[3][iRows] = "Pending";
					grdFiles->RowCount++;
				}
			}
		}
	}
	RefreshStatus();
}



// ---------------------------------------------------------------------------
int __fastcall TfrmMain::RunPluginOld(int piCurrent, String psStatus, String psProcess, String psDirectory, String psTmpName)
{
	int iError;
	unsigned int iSize, iSizeTmp, iPercent;
	String sShortFile;


	if (gbStop)
	{
		//Close();
		return (0);
	}

	if (psTmpName != "")
	{
		DeleteFile(psTmpName.c_str());
	}
	sShortFile = GetShortName(grdFiles->Cells[0][piCurrent]);

	grdFiles->Cells[3][piCurrent] = "Running " + psStatus + "...";
	iSize = clsUtil::SizeFile(sShortFile.c_str());
	grdFiles->Cells[2][piCurrent] = FormatNumberThousand(iSize);

	iError = RunProcess(psProcess.c_str(), psDirectory.c_str(), NULL, 0, true);
	Log(3, ("Return: " + ((String) iError) + ". Process: " + psProcess).c_str());

	if (psTmpName != "")
	{
		iSizeTmp = clsUtil::SizeFile(psTmpName.c_str());
		if ((iSizeTmp > 0) && (iSizeTmp < iSize))
		{
			iSize = iSizeTmp;
			CopyFile(psTmpName.c_str(), grdFiles->Cells[0][piCurrent].c_str(), false);
		}
		DeleteFile(psTmpName.c_str());
	}

	iPercent = (iSize * 100) / ParseNumberThousand(grdFiles->Cells[1][piCurrent]);
	grdFiles->Cells[2][piCurrent] = FormatNumberThousand(iSize);
	grdFiles->Cells[3][piCurrent] = grdFiles->Cells[3][piCurrent].sprintf(_T("Done (%3d%%)."), iPercent);

	return (iError);
}



// ---------------------------------------------------------------------------
int __fastcall TfrmMain::RunPlugin(int piCurrent, String psStatus, String psCommandLine, String psDirectory, String psInputFile, String psOutputFile)
{
	int iError;
	unsigned int iSize, iSizeNew, iPercent;
	String sInputFile, sOutputFile, sTmpInputFile, sTmpOutputFile, sCommandLine;
	TCHAR acTmp[MAX_PATH];


	if (gbStop)
	{
		//Close();
		return (0);
	}

	_stprintf(acTmp, _T("%s\\%s"), _tgetenv(_T("TEMP")), (Application->Name + "Input" + GetExtension(psInputFile)).c_str());
	sTmpInputFile = acTmp;
	
	_stprintf(acTmp, _T("%s\\%s"), _tgetenv(_T("TEMP")), (Application->Name + "Output" + GetExtension(psInputFile)).c_str());
	sTmpOutputFile = acTmp;
	
	sInputFile = psInputFile;
	sOutputFile = psOutputFile;
	sCommandLine = psCommandLine;

	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());
	
	grdFiles->Cells[3][piCurrent] = "Running " + psStatus + "...";
	iSize = clsUtil::SizeFile(sInputFile.c_str());
	grdFiles->Cells[2][piCurrent] = FormatNumberThousand(iSize);
	
	//Handle copying original file, if there is not Output nor Tmp for commands that only accept 1 file
	if ((PosEx("%OUTPUTFILE%", psCommandLine) == 0) && (PosEx("%TMPOUTPUTFILE%", psCommandLine) == 0))
	{
		CopyFile(sInputFile.c_str(), sTmpInputFile.c_str(), false);
		//sInputFile = sTmpOutputFile;
	}

	sCommandLine = StringReplace(sCommandLine, "%INPUTFILE%", sInputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = StringReplace(sCommandLine, "%OUTPUTFILE%", sOutputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = StringReplace(sCommandLine, "%TMPINPUTFILE%", sTmpInputFile, TReplaceFlags() << rfReplaceAll);
	sCommandLine = StringReplace(sCommandLine, "%TMPOUTPUTFILE%", sTmpOutputFile, TReplaceFlags() << rfReplaceAll);

	iError = RunProcess(sCommandLine.c_str(), psDirectory.c_str(), NULL, 0, true);
	Log(3, ("Return: " + ((String) iError) + ". Process: " + sCommandLine).c_str());

	//We did get a TMP output file, so if smaller, make it overwrite input file
	if (PosEx("%TMPOUTPUTFILE%", psCommandLine) != 0)
	{
		iSizeNew = clsUtil::SizeFile(sTmpOutputFile.c_str());
		if ((iSizeNew > 0) && (iSizeNew < iSize))
		{
			iSize = iSizeNew;
			CopyFile(sTmpOutputFile.c_str(), sInputFile.c_str(), false);
		}
	}
	else if ((PosEx("%OUTPUTFILE%", psCommandLine) == 0) && (PosEx("%TMPOUTPUTFILE%", psCommandLine) == 0))
	{
		iSizeNew = clsUtil::SizeFile(sTmpInputFile.c_str());
		if ((iSizeNew > 0) && (iSizeNew < iSize))
		{
			iSize = iSizeNew;
			CopyFile(sTmpInputFile.c_str(), sInputFile.c_str(), false);
			//sInputFile = sTmpOutputFile;
		}
	}	

	DeleteFile(sTmpInputFile.c_str());
	DeleteFile(sTmpOutputFile.c_str());

	iPercent = (iSize * 100) / ParseNumberThousand(grdFiles->Cells[1][piCurrent]);
	grdFiles->Cells[2][piCurrent] = FormatNumberThousand(iSize);
	grdFiles->Cells[3][piCurrent] = grdFiles->Cells[3][piCurrent].sprintf(_T("Done (%3d%%)."), iPercent);

	return (iError);
}



// ---------------------------------------------------------------------------
void __fastcall TfrmMain::CheckForUpdates(bool pbSilent)
{
	TCHAR acPath[MAX_PATH];
	TCHAR acBuffer[512];


	memset(acBuffer, 0, sizeof(acBuffer));
	if (clsUtil::DownloadFile(KS_APP_UPDATE_URL, acPath, sizeof(acPath)))
	{
		mbstowcs(acBuffer, (char *) acPath, (sizeof(acPath) / sizeof(TCHAR)) - 1);
		GetModuleFileName(NULL, acPath, sizeof(acPath) - 1);
		if (_tcscmp(acBuffer, clsUtil::ExeVersion(acPath)) > 0)
		{
			if (clsUtil::MsgBox(NULL, (Application->Name + " version " + (String) acBuffer + " is available.\r\nDo you want to download it now?").c_str(), _T("Check updates"), MB_YESNO | MB_ICONQUESTION) == ID_YES)
			{
				ShellExecute(NULL, _T("open"), KS_APP_URL, _T(""), _T(""), SW_SHOWNORMAL);
			}
		}
		else if (!pbSilent)
		{
			clsUtil::MsgBox(NULL, ("You already have latest " + Application->Name + " version.").c_str(), _T("Check updates"), MB_OK|MB_ICONINFORMATION);
		}
	}
	else if (!pbSilent)
	{
		clsUtil::MsgBox(NULL, _T("Error checking for updates."), _T("Check updates"), MB_OK | MB_ICONINFORMATION);
	}
}


//---------------------------------------------------------------------------
String __fastcall TfrmMain::GetExtension (String psFilename)
{
	int iSource;
	TCHAR *pacSource;
	String sRes = "";


	pacSource = psFilename.c_str();
	for (iSource = psFilename.Length(); iSource >= 0; iSource--)
	{
		if (pacSource[iSource] == '.')
		{
			sRes = &pacSource[iSource];
			break;
		}
	}
	return (sRes);
}



//---------------------------------------------------------------------------
String __inline TfrmMain::FormatNumberThousand (int piNumber)
{
	String sRes;

	sRes = FormatFloat("###,###,###,###,###", piNumber);
	if (sRes == "")
	{
		sRes = "0";
	}
	return (sRes);
}



//---------------------------------------------------------------------------
int __inline TfrmMain::ParseNumberThousand (String psNumber)
{
	return (StrToIntDef(StringReplace(psNumber, FormatSettings.ThousandSeparator, "", TReplaceFlags() << rfReplaceAll), 0));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long __fastcall TfrmMain::RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait)
{
	unsigned long lExitCode;
	STARTUPINFO udtSI;
	PROCESS_INFORMATION udtPI;
	SECURITY_ATTRIBUTES udtSA;
	HANDLE hRead, hWrite;
	TCHAR acTmp[2048];


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
			WaitForSingleObject(udtPI.hProcess, 100);
			GetExitCodeProcess(udtPI.hProcess, &lExitCode);
			if (gbStop)
			{
				TerminateProcess(udtPI.hProcess, 0);
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
	iSize = clsUtil::SizeFile(pacFile);
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
			delete acBuffer;
		}
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall TfrmMain::IsInnoSetup(const TCHAR *pacFile)
{
	bool bRes;
	unsigned int iSize, iPos;
	unsigned char *acBuffer;

	
	bRes = false;
	iSize = 128 * 1024;
	acBuffer = new unsigned char[iSize];
	if (acBuffer)
	{
		clsUtil::ReadFile(pacFile, acBuffer, &iSize);
		for (iPos = 0; iPos < iSize - 10; iPos++)
		{
			if (memcmp((const void *) &acBuffer[iPos], (const void *) "Inno Setup", 10) == 0)
			{
				bRes = true;
				break;                
			}    
		}
		delete acBuffer;
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
	//Prevent flickering
	LockWindowUpdate(Handle);	

	RefreshStatus();

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


//---------------------------------------------------------------------------
void __fastcall TfrmMain::RefreshStatus(bool pbUpdateStatusBar, unsigned int piTotalBytes, unsigned int piSavedBytes)
{
	unsigned int iPercentBytes;


	//Prevent flickering
	LockWindowUpdate(Handle);	

	if (gbProcess)
	{
		if (piTotalBytes != 0)
		{
			iPercentBytes = piSavedBytes * 100 / piTotalBytes;
		}
		else
		{
			iPercentBytes = 0;
		}
		stbMain->Panels->Items[0]->Text = FormatNumberThousand(grdFiles->Row) + " / " + FormatNumberThousand(grdFiles->RowCount - 1) + " files. " + FormatNumberThousand(piSavedBytes) + " bytes saved (" + FormatNumberThousand(iPercentBytes) + "%)";
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
				grdFiles->ColCount = 4;
				grdFiles->Cells[0][0] = "File";
				grdFiles->Cells[1][0] = "Original size";
				grdFiles->Cells[2][0] = "Optimized size";
				grdFiles->Cells[3][0] = "Status";

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
	LockWindowUpdate(NULL);	
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
	String sText;

	sText = "FileOptimizer is a lossless (no quality loss) file size optimizer that supports";
	sText += StringReplace(StringReplace(KS_EXTENSION_ALL.UpperCase(), ".", ", ", TReplaceFlags() << rfReplaceAll), " ,", ",", TReplaceFlags() << rfReplaceAll);
	sText += ",... file formats among others.";
	clsUtil::MsgBox(NULL, sText.c_str(), _T("Information"), MB_ICONINFORMATION | MB_OK);
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

