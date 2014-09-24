// --------------------------------------------------------------------------
/*
 3.00. 23/09/2012. FileOptimizer. Added LoadForm, SaveForm, CopyToRecycleBin, SetTaskListProgress
 2.00. 09/08/2012. FileOptimizer. Added clsUtil static class wrapper, optimized SizeFile, mapped to TCHAR and merged clsPreferences common functions
 1.00. 18/08/2011. TBClamAV. Initial version-
 */
// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"
#include <Tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::ReplaceString(const TCHAR *pacString, const TCHAR *pacSearch, const TCHAR *pacReplace)
{
	/*
	 char acRes[1024];

	 AnsiString s = StringReplace(pacString, pacSearch, pacReplace, TReplaceFlags() << rfReplaceAll);
	 strcpy(acRes, s.c_str());
	 return(acRes);
	 */

	TCHAR *tok;
	TCHAR *newstr;
	TCHAR *oldstr;
	newstr = _tcsdup(pacString);
	while ((tok = _tcsstr(newstr, pacSearch)) != NULL)
	{
		oldstr = newstr;
		newstr = new TCHAR[_tcslen(oldstr) - _tcslen(pacSearch) + _tcslen(pacReplace) + 1];
		memcpy(newstr, oldstr, (tok - oldstr) * sizeof(TCHAR));
		memcpy(newstr + (tok - oldstr), pacReplace, _tcslen(pacReplace) * sizeof(TCHAR));
		memcpy(newstr + (tok - oldstr) + _tcslen(pacReplace) * sizeof(TCHAR), tok + _tcslen(pacSearch),
			_tcslen(oldstr) - _tcslen(pacSearch) - (tok - oldstr));
		memset(newstr + _tcslen(oldstr) - _tcslen(pacSearch) + _tcslen(pacReplace), 0, 1);
		delete oldstr;
	}
	return newstr;
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::MsgBox(HWND phWnd, const TCHAR *pacText, const TCHAR *pacTitle, int piType)
{
	int iButton;
	Winapi::Commctrl::TASKDIALOGCONFIG udtFlags;
	HMODULE hDLL;
	typedef int (WINAPI TaskDialogType)(const Winapi::Commctrl::TASKDIALOGCONFIG *pTaskConfig, int *pnButton, int *pnRadioButton, bool *pfVerificationFlagChecked);
	TaskDialogType *TaskDialogProc;


	if ((hDLL = LoadLibrary(_T("COMCTL32.DLL"))) && (TaskDialogProc = (TaskDialogType *) GetProcAddress(hDLL, "TaskDialogIndirect")))
	{
		memset(&udtFlags, 0, sizeof(udtFlags));
		udtFlags.cbSize = sizeof(udtFlags);
		udtFlags.hwndParent = phWnd;
		udtFlags.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_CAN_BE_MINIMIZED;

		if ((piType & MB_ABORTRETRYIGNORE) == MB_ABORTRETRYIGNORE)
		{
			udtFlags.dwCommonButtons = TDCBF_CANCEL_BUTTON | TDCBF_RETRY_BUTTON | TDCBF_CLOSE_BUTTON;
			udtFlags.nDefaultButton = IDRETRY;
			iButton = IDCANCEL;
		}
		else if ((piType & MB_CANCELTRYCONTINUE) == MB_CANCELTRYCONTINUE)
		{
			udtFlags.dwCommonButtons = TDCBF_CANCEL_BUTTON | TDCBF_RETRY_BUTTON | TDCBF_OK_BUTTON;
			udtFlags.nDefaultButton = IDRETRY;
			iButton = IDCANCEL;
		}
		else if ((piType & MB_OKCANCEL) == MB_OKCANCEL)
		{
			udtFlags.dwCommonButtons = TDCBF_OK_BUTTON | TDCBF_CANCEL_BUTTON;
			udtFlags.nDefaultButton = IDOK;
			iButton = IDCANCEL;
		}
		else if ((piType & MB_RETRYCANCEL) == MB_RETRYCANCEL)
		{
			udtFlags.dwCommonButtons = TDCBF_RETRY_BUTTON | TDCBF_CANCEL_BUTTON;
			udtFlags.nDefaultButton = IDRETRY;
			iButton = IDCANCEL;
		}
		else if ((piType & MB_YESNO) == MB_YESNO)
		{
			udtFlags.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
			udtFlags.nDefaultButton = IDYES;
			iButton = IDNO;
		}
		else if ((piType & MB_YESNOCANCEL) == MB_YESNOCANCEL)
		{
			udtFlags.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON;
			udtFlags.nDefaultButton = IDYES;
			iButton = IDCANCEL;
		}
		else
		{
			udtFlags.dwCommonButtons = TDCBF_OK_BUTTON;
			udtFlags.nDefaultButton = IDOK;
			iButton = IDOK;
		}

		if (((piType & MB_ICONEXCLAMATION) == MB_ICONEXCLAMATION) || ((piType & MB_ICONWARNING) == MB_ICONWARNING))
		{
			udtFlags.pszMainIcon = TD_WARNING_ICON;
		}
		else if (((piType & MB_ICONINFORMATION) == MB_ICONINFORMATION) || ((piType & MB_ICONASTERISK) == MB_ICONASTERISK))
		{
			udtFlags.pszMainIcon = TD_INFORMATION_ICON;
		}
		else if (((piType & MB_ICONSTOP) == MB_ICONSTOP) || ((piType & MB_ICONERROR) == MB_ICONERROR) || ((piType & MB_ICONHAND) == MB_ICONHAND))
		{
			udtFlags.pszMainIcon = TD_ERROR_ICON;
		}
		//else if ((piType & MB_ICONQUESTION) == MB_ICONQUESTION)
		else
		{
			udtFlags.pszMainIcon = NULL;
		}

		udtFlags.pszWindowTitle = (TCHAR *) pacTitle;
		if (_tcslen(pacText) < 256)
		{
			udtFlags.pszMainInstruction = (TCHAR *) pacText;
			//(*TaskDialogProc)(phWnd, NULL, acTitle, acText, L"", udtFlags, (wchar_t *) pcIcon, &iButton);
		}
		else
		{
			udtFlags.pszMainInstruction = (TCHAR *) pacTitle;
			udtFlags.pszContent = (TCHAR *) pacText;
			//(*TaskDialogProc)(phWnd, NULL, acTitle, acTitle, acText, udtFlags, (wchar_t *) pcIcon, &iButton);
		}
		(*TaskDialogProc)(&udtFlags, &iButton, NULL, NULL);
		FreeLibrary(hDLL);
		return (iButton);
	}
	else
	{
		return (MessageBox(phWnd, pacText, pacTitle, piType));
	}
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HANDLE __fastcall clsUtil::FindProcess(const TCHAR *pacProcess)
{
	PROCESSENTRY32 udtEntry;
	HANDLE hSnapshot;
	HANDLE hProcess;
	bool bRes;


	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	udtEntry.dwSize = sizeof(PROCESSENTRY32);
	bRes = Process32First(hSnapshot, &udtEntry);
	hProcess = NULL;
	while (bRes)
	{
		if (_tcsicmp(udtEntry.szExeFile, pacProcess) == 0)
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, udtEntry.th32ProcessID);
			break;
		}
		bRes = Process32Next(hSnapshot, &udtEntry);
	}

	CloseHandle(hSnapshot);
	return (hProcess);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long __fastcall clsUtil::RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait)
{
	unsigned long lExitCode;
	STARTUPINFO udtSI;
	PROCESS_INFORMATION udtPI;
	SECURITY_ATTRIBUTES udtSA;
	HANDLE hRead, hWrite;


	Screen->Cursor = crHourGlass;
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

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, true, NULL, NULL, (TCHAR *) pacDirectory, &udtSI,
				&udtPI))
		{
			//_stprintf(acTmp, _T("Cannot launch %s"), pacProcess);
			//MsgBox(NULL, acTmp, _T("Error"), MB_OK | MB_ICONASTERISK);
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

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, false, NULL, NULL, (TCHAR *) pacDirectory,
				&udtSI, &udtPI))
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
			WaitForSingleObject(udtPI.hProcess, INFINITE);
			GetExitCodeProcess(udtPI.hProcess, &lExitCode);
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
bool __fastcall clsUtil::ExistsFile(const TCHAR *pacFile)
{
	int iAttributes;


	iAttributes = GetFileAttributes(pacFile);
	return (iAttributes != -1);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned int __fastcall clsUtil::SizeFile(const TCHAR *pacFile)
{
	unsigned int iSize = 0;
	WIN32_FILE_ATTRIBUTE_DATA udtFileAttribute;


	if (GetFileAttributesEx(pacFile, GetFileExInfoStandard, (void*)&udtFileAttribute))
	{
		iSize = udtFileAttribute.nFileSizeLow;
	}
	return (iSize);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::ReadFile(const TCHAR *pacFile, void *pvData, unsigned int *piSize)
{
	unsigned long lSize;
	HANDLE hFile;
	HANDLE hMapping;
	bool bRes = false;
	void *pacBuffer;


	hFile = CreateFile(pacFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		lSize = GetFileSize(hFile, NULL);
		if (*piSize != 0)
		{
			lSize = *piSize;
		}
		if (lSize > 0)
		{
			// Use file mapped IO
			hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, lSize, NULL);
			if (hMapping != INVALID_HANDLE_VALUE)
			{
				pacBuffer = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, lSize);
				if (pacBuffer != NULL)
				{
					memcpy(pvData, pacBuffer, lSize);
					UnmapViewOfFile(pacBuffer);
				}
				CloseHandle(hMapping);
			}
			// Use regular IO
			else
			{
				::ReadFile(hFile, pvData, (unsigned long) piSize, &lSize, NULL);
			}
		}
		*piSize = lSize;
	}
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::WriteFile(const TCHAR *pacFile, void *pvData, unsigned int piSize)
{
	unsigned long lSize;
	HANDLE hFile;
	HANDLE hMapping;
	bool bRes = false;
	void *pacBuffer;


	hFile = CreateFile(pacFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// Use file mapped IO
		hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, piSize, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
			pacBuffer = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, piSize);
			if (pacBuffer != NULL)
			{
				memcpy(pacBuffer, pvData, piSize);
				UnmapViewOfFile(pacBuffer);
			}
			CloseHandle(hMapping);
		}
		// Use regular IO
		else
		{
			::WriteFile(hFile, pvData, piSize, &lSize, NULL);
		}
	}
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetFileTimestamp(const TCHAR *pacFile, FILETIME *pudtCreated, FILETIME *pudtModified)
{
	HANDLE hFile;
	bool bRes = false;


	hFile = CreateFile(pacFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = GetFileTime(hFile, pudtCreated, pudtModified, NULL);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetFileTimestamp(const TCHAR *pacFile, FILETIME *pudtCreated, FILETIME *pudtModified)
{
	HANDLE hFile;
	bool bRes = false;


	hFile = CreateFile(pacFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = SetFileTime(hFile, pudtCreated, pudtModified, NULL);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DownloadFile(const TCHAR *pacUrl, void *pvData, unsigned int piSize)
{
	bool bRes = false;
	HINTERNET hInternet, hHttp;
	unsigned long lRead;


	GetModuleFileName(NULL, (TCHAR *) pvData, piSize - 1);
	_stprintf((TCHAR *) pvData, _T("%s/%s"), Application->Name.c_str(), ExeVersion((const TCHAR *) pvData));
	if ((hInternet = InternetOpen((const TCHAR *) pvData, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL)) != NULL)
	{
		if ((hHttp = InternetOpenUrl(hInternet, pacUrl, NULL, 0,
					INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_HYPERLINK, NULL)) != NULL)
		{
			memset(pvData, 0, piSize);
			if (InternetReadFile(hHttp, pvData, piSize, &lRead))
			{
				bRes = true;
			}
		}
	}
	InternetCloseHandle(hHttp);
	InternetCloseHandle(hInternet);
	return (bRes);
}



// --------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::ExeVersion(const TCHAR *pacFile)
{
	unsigned int iVersionSize;
	TCHAR *pacVersionData;
	void *a;
	VS_FIXEDFILEINFO udtVersionInfo;
	static TCHAR acRes[2048];


	acRes[0] = NULL;
	iVersionSize = GetFileVersionInfoSize(pacFile, 0);
	pacVersionData = new TCHAR[iVersionSize];
	if (pacVersionData)
	{
		if (GetFileVersionInfo(pacFile, 0, iVersionSize, pacVersionData))
		{
			if (VerQueryValue(pacVersionData, _T("\\"), &a, &iVersionSize))
			{
				memcpy(&udtVersionInfo, a, iVersionSize);
				_stprintf(acRes, _T("%d.%d%d.%d"), HIWORD(udtVersionInfo.dwFileVersionMS), LOWORD(udtVersionInfo.dwFileVersionMS), HIWORD(udtVersionInfo.dwFileVersionLS), LOWORD(udtVersionInfo.dwFileVersionLS));
			}
		}
		delete[] pacVersionData;
	}
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIniPath(void)
{
	TCHAR acTmp[2048];
	static TCHAR acPath[MAX_PATH] = _T("");
	HANDLE hFile;


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		GetModuleFileName(NULL, acTmp, sizeof(acTmp) - 1);
		*_tcsrchr(acTmp, '.') = NULL;
		_tcscat(acTmp, _T(".ini"));
		// Check if we can write to that location
		hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".ini").c_str());
		}
		else
		{
			CloseHandle(hFile);
			_tcscpy(acPath, acTmp);
		}
	}
	return (acPath);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacDefault)
{
	static TCHAR acRes[2048];


	GetPrivateProfileString(pacSection, pacKey, pacDefault, acRes, sizeof(acRes), GetIniPath());
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piDefault)
{
	TCHAR acDefault[2048];
	TCHAR acRes[2048];


	_itot(piDefault, acDefault, 10);
	GetPrivateProfileString(pacSection, pacKey, acDefault, acRes, sizeof(acRes), GetIniPath());
	return (_ttoi(acRes));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdDefault)
{
	TCHAR acDefault[2048];
	TCHAR acRes[2048];


	_stprintf(acDefault, _T("%f"), pdDefault);
	GetPrivateProfileString(pacSection, pacKey, acDefault, acRes, sizeof(acRes), GetIniPath());
	return (_ttof(acRes));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbDefault)
{
	TCHAR acDefault[2048];
	TCHAR acRes[2048];


	if (pbDefault)
	{
		_tcscpy(acDefault, _T("true"));
	}
	else
	{
		_tcscpy(acDefault, _T("false"));
	}
	GetPrivateProfileString(pacSection, pacKey, acDefault, acRes, sizeof(acRes), GetIniPath());
	return (_tcsicmp(acRes, _T("true")) == 0);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacValue)
{
	WritePrivateProfileString(pacSection, pacKey, pacValue, GetIniPath());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbValue)
{
	TCHAR acValue[2048];


	if (pbValue)
	{
		_tcscpy(acValue, _T("true"));
	}
	else
	{
		_tcscpy(acValue, _T("false"));
	}
	WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piValue)
{
	TCHAR acValue[2048];


	_itot(piValue, acValue, 10);
	WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdValue)
{
	TCHAR acValue[2048];


	_stprintf(acValue, _T("%f"), pdValue);
	WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName)
{
	HKEY hKey;
	static TCHAR acRes[2048];


	memset(acRes, 0, sizeof(acRes));
	RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_QUERY_VALUE, &hKey);
	RegSetValueEx(hKey, pacName, NULL, REG_SZ, (BYTE *) acRes, NULL);
	RegCloseKey(hKey);
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, const TCHAR *pacValue)
{
	HKEY hKey;


	RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_SET_VALUE, &hKey);
	RegQueryValueEx(hKey, pacName, NULL, NULL, (BYTE *) pacValue, NULL);
	RegCloseKey(hKey);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetLogPath(void)
{
	TCHAR acTmp[2048];
	static TCHAR acPath[MAX_PATH] = _T("");
	HANDLE hFile;


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		GetModuleFileName(NULL, acTmp, sizeof(acTmp) - 1);
		*_tcsrchr(acTmp, '.') = NULL;
		_tcscat(acTmp, _T(".log"));
		// Check if we can write to that location
		hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".log").c_str());
		}
		else
		{
			CloseHandle(hFile);
			_tcscpy(acPath, acTmp);
		}
	}
	return (acPath);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::LogAdd(const TCHAR *pacFile, int piLine, const TCHAR *pacFunc, int piLevel, const TCHAR *pacValue, int piDesiredLevel)
{
	TCHAR acPath[MAX_PATH];
	FILE *pLog;
	TCHAR acLevel[][32] = { _T("CRITICAL"), _T("ERROR"), _T("WARNING"), _T("INFORMATION"), _T("NONE") };

	if ((piDesiredLevel) > piLevel)
	{
		_tcscpy(acPath, GetLogPath());
		pLog = _tfopen(acPath, _T("at"));
		TDateTime dteDate = dteDate.CurrentDateTime();
		_ftprintf(pLog, _T("[%s %s]	%s	%s	(%d)	%s()	%s\n"), dteDate.DateString().c_str(), dteDate.TimeString().c_str(), acLevel[piLevel], pacFile, piLine, pacFunc, pacValue);
		fclose(pLog);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::LoadForm(TForm *pfrmForm)
{
	int iWindowState;


	pfrmForm->Left = GetIni(pfrmForm->Name.c_str(), _T("Left"), pfrmForm->Left);
	pfrmForm->Top = GetIni(pfrmForm->Name.c_str(), _T("Top"), pfrmForm->Top);
	pfrmForm->Width = GetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
	pfrmForm->Height = GetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	iWindowState = GetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	//We do not want to reopen FileOptimizer in minimized state
	if (iWindowState == wsMinimized)
	{
		iWindowState = wsNormal;
	}
	pfrmForm->WindowState = (TWindowState) iWindowState;
	pfrmForm->DefaultMonitor = (TDefaultMonitor) GetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), pfrmForm->DefaultMonitor);
	return(true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SaveForm(TForm *pfrmForm)
{
	SetIni(pfrmForm->Name.c_str(), _T("Left"), pfrmForm->Left);
	SetIni(pfrmForm->Name.c_str(), _T("Top"), pfrmForm->Top);
	SetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
	SetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	SetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	SetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), (int) pfrmForm->DefaultMonitor);
	return(true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::CopyToRecycleBin(const TCHAR *pacSource)
{
	int iRes;
	SHFILEOPSTRUCT udtFileOp;
	TCHAR acSource[MAX_PATH], acDestination[MAX_PATH];


	// ShFileOperation expect strings ending in double NULL
	memset(acSource, 0, sizeof(acSource));
	_tcscpy(acSource, pacSource);
	_tcscpy(acDestination, acSource);
	_tcscat(acDestination, _T(".tmp"));

	CopyFile(acSource, acDestination, false);

	memset(&udtFileOp, 0, sizeof(udtFileOp));
	udtFileOp.wFunc = FO_DELETE;
	udtFileOp.fFlags = FOF_ALLOWUNDO | FOF_NO_UI;
	udtFileOp.pFrom = acSource;

	iRes = SHFileOperation(&udtFileOp);
	if (iRes == 0)
	{
		DeleteFile(acSource);
		MoveFile(acDestination, acSource);
		DeleteFile(acDestination);
		return(true);
	}
	else
	{
		DeleteFile(acDestination);
		return(false);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SetTaskListProgress(unsigned int piCompleted, unsigned int piTotal)
{
	ITaskbarList3 *pTaskList = NULL;
	HRESULT hRes;
	OSVERSIONINFO udtVersion;


	// In 7 or newer use new TaskDialog
	memset(&udtVersion, 0, sizeof(OSVERSIONINFO));
	udtVersion.dwOSVersionInfoSize = sizeof(udtVersion);
	GetVersionEx(&udtVersion);
	if ((udtVersion.dwMajorVersion > 6) || ((udtVersion.dwMajorVersion == 6) && (udtVersion.dwMinorVersion >= 1)))
	//if (LOBYTE(LOWORD(GetVersion())) >= 6)
	{
		hRes = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **) &pTaskList);
		if (pTaskList)
		{
			if (SUCCEEDED(hRes))
			{
				pTaskList->HrInit();
				if (Application->MainForm)
				{
					pTaskList->SetProgressState(Application->MainForm->Handle, TBPF_NORMAL);
					pTaskList->SetProgressValue(Application->MainForm->Handle, piCompleted, piTotal);
				}
				return(true);
			}
			pTaskList->Release();
		}
	}
	return(false);
}

