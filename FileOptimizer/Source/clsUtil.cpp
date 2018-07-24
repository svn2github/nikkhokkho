// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 3.50. 15/12/2018. FileOptimizer. Added DeleteFile, GetShortName. Do most operations internally using them
 3.47. 22/11/2017. FileOptimizer. Added EscapeIniValue, UnescapeIniValue, EscapeIniKey, UnescapeIniKey.
 3.46. 21/11/2017. FileOptimizer. Added GetRegistryPath.
 3.45. 17/11/2017. FileOptimizer. Added DeleteRegistry, DeleteIni.
 3.44. 15/11/2017. FileOptimizer. Added SetRegistry for ints.
 3.43. 23/06/2017. FileOptimizer. Backported crc32 from Lamark.
 3.42. 12/01/2017. FileOptimizer. Allow writting comments in .INI files
 3.41. 08/08/2016. FileOptimizer. Added ShutdownWindows
 3.40. 27/12/2015. FileOptimizer. Added GetWindowsVersion since GetVersion on Windows 8.1 or later do not work unless application is manifested
 3.30. 05/05/2015. FileOptimizer. Added 64 bit version of GetIni/SetIni. Added MemMem, CopyFile
 3.25. 05/04/2015. FileOptimizer. Added Random
 3.20. 14/03/2015. FileOptimizer. Added Serialize and Unserialize
 3.10. 20/01/2015. FileOptimizer. Minor tweaks and fixes
 3.00. 23/09/2012. FileOptimizer. Added LoadForm, SaveForm, CopyToRecycleBin, SetTaskListProgress
 2.00. 09/08/2012. FileOptimizer. Added clsUtil static class wrapper, optimized SizeFile, mapped to TCHAR and merged clsPreferences common functions
 1.00. 18/08/2011. TBClamAV. Initial version
 */
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "clsUtil.h"



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const void * __fastcall clsUtil::MemMem (const void *buf, size_t buf_len, const void *byte_sequence, size_t byte_sequence_len)
{
	unsigned char *bf = (unsigned char *) buf;
	unsigned char *bs = (unsigned char *) byte_sequence;
	unsigned char *p  = bf;

	while (byte_sequence_len <= (buf_len - (p - bf)))
	{
		unsigned int b = *bs & 0xFF;
		if ((p = (unsigned char *) memchr(p, b, buf_len - (p - bf))) != NULL)
		{
			if ((memcmp(p, byte_sequence, byte_sequence_len)) == 0)
			{
				return (p);
			}
			else
			{
				p++;
			}
		}
		else
		{
			break;
		}
	}
	return (NULL);
}


static unsigned int miTaskDialogTimeout = 0;
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT CALLBACK clsUtil::TaskDialogCallbackProc(HWND phWnd, UINT uNotification, WPARAM wParam, LPARAM lParam, LONG_PTR dwRefData)
{
	HRESULT hResult = S_OK;


	if (uNotification == TDN_CREATED)
	{
		SendMessage(phWnd, TDM_SET_PROGRESS_BAR_RANGE, 0, MAKELONG(0, miTaskDialogTimeout));
	}
	else if (uNotification == TDN_TIMER)
	{
		SendMessage(phWnd, TDM_SET_PROGRESS_BAR_POS, wParam, 0);
		if (wParam > miTaskDialogTimeout)
		{
			PostMessage(phWnd, WM_CLOSE, 0, 0);
            hResult = S_FALSE;
		}
	}
	return (hResult);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::MsgBox(HWND phWnd, const TCHAR *pacText, const TCHAR *pacTitle, unsigned int piType, unsigned int piTimeout)
{
	int iButton = 0;
	Winapi::Commctrl::TASKDIALOGCONFIG udtFlags = {};


	//ToDo: Cache loaded functions from DLL
	HMODULE hComCtl32 = LoadLibrary(_T("COMCTL32.DLL"));
	if (hComCtl32)
	{
		typedef int (WINAPI TaskDialogType)(const Winapi::Commctrl::TASKDIALOGCONFIG *pTaskConfig, int *pnButton, int *pnRadioButton, bool *pfVerificationFlagChecked);
		TaskDialogType *TaskDialogIndirect = (TaskDialogType *) GetProcAddress(hComCtl32, "TaskDialogIndirect");
		if (TaskDialogIndirect)
		{
			udtFlags.cbSize = sizeof(udtFlags);
			udtFlags.hwndParent = phWnd;
			udtFlags.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_CAN_BE_MINIMIZED | TDF_SIZE_TO_CONTENT;
			if (piTimeout != 0)
			{
				udtFlags.dwFlags |= TDF_CALLBACK_TIMER | TDF_SHOW_PROGRESS_BAR;
				udtFlags.pfCallback = (Winapi::Commctrl::PFTASKDIALOGCALLBACK) clsUtil::TaskDialogCallbackProc;
				miTaskDialogTimeout = piTimeout;
			}

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
			}
			else
			{
				udtFlags.pszMainInstruction = (TCHAR *) pacTitle;
				udtFlags.pszContent = (TCHAR *) pacText;
			}
			(*TaskDialogIndirect)(&udtFlags, &iButton, NULL, NULL);
		}
		FreeLibrary(hComCtl32);
	}

	//Fallback when library not loaded or TaskDialogIndirect not exists
	if (iButton == NULL)
	{
		if (piTimeout == 0)
		{
			iButton = MessageBox(phWnd, pacText, pacTitle, piType);
		}
		else
		{
			HMODULE hUser32 = LoadLibrary(_T("USER32.DLL"));
			if (hUser32)
			{
				typedef int (__stdcall *MSGBOXWAPI)(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
				MSGBOXWAPI MessageBoxTimeout = (MSGBOXWAPI) GetProcAddress(hUser32, "MessageBoxTimeoutW");
				if (MessageBoxTimeout)
				{
					iButton = (*MessageBoxTimeout)(phWnd, pacText, pacTitle, (unsigned int) piType, 0, (unsigned long) piTimeout);
				}
                FreeLibrary(hUser32);
			}
		}
	}
	return (iButton);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HANDLE __fastcall clsUtil::FindProcess(const TCHAR *pacProcess)
{
	PROCESSENTRY32 udtEntry;


	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	udtEntry.dwSize = sizeof(PROCESSENTRY32);
	bool bRes = Process32First(hSnapshot, &udtEntry);
	HANDLE hProcess = NULL;
	while (bRes)
	{
		if (_tcsicmp(GetShortName((String) udtEntry.szExeFile).c_str(), GetShortName((String) pacProcess).c_str()) == 0)
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
	PROCESS_INFORMATION udtPI = {};
	SECURITY_ATTRIBUTES udtSA = {};
	HANDLE hRead = NULL, hWrite = NULL;


	Screen->Cursor = crHourGlass;
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

		if (!CreateProcess(NULL, GetShortName((String) pacProcess).c_str(), &udtSA, &udtSA, false, NULL, NULL, GetShortName((String) pacDirectory).c_str(), &udtSI, &udtPI))
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

		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESHOWWINDOW;
		udtSI.wShowWindow = SW_HIDE;

		if (!CreateProcess(NULL, GetShortName((String) pacProcess).c_str(), &udtSA, &udtSA, false, NULL, NULL, GetShortName((String) pacDirectory).c_str(), &udtSI, &udtPI))
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
	unsigned int iAttributes = GetFileAttributes(GetShortName((String) pacFile).c_str());
	return (iAttributes != INVALID_FILE_ATTRIBUTES);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long long __fastcall clsUtil::SizeFile(const TCHAR *pacFile)
{
	unsigned long long lSize = 0;
	WIN32_FILE_ATTRIBUTE_DATA udtFileAttribute;


	if (GetFileAttributesEx(GetShortName((String) pacFile).c_str(), GetFileExInfoStandard, (void*) &udtFileAttribute))
	{
		lSize = ((unsigned long long) udtFileAttribute.nFileSizeHigh << 32) + udtFileAttribute.nFileSizeLow;
	}
	return (lSize);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::ReadFile(const TCHAR *pacFile, void *pvData, unsigned int *piSize, unsigned int piOffset)
{
	unsigned int iSize;
	bool bRes = false;


	HANDLE hMapping = NULL;
	HANDLE hFile = CreateFile(GetShortName((String) pacFile).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		if (*piSize == 0)
		{
			iSize = GetFileSize(hFile, NULL);
		}
		else
		{
			iSize = *piSize;
		}
		if (iSize > 0)
		{
			// Use file mapped IO
			hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, iSize, NULL);
			if (hMapping != INVALID_HANDLE_VALUE)
			{
				void *pacBuffer = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, iSize);
				if ((piOffset == 0) && (pacBuffer != NULL))
				{
					memcpy(pvData, pacBuffer, iSize);
					bRes = UnmapViewOfFile(pacBuffer);
				}
				// Use regular IO
				else
				{
					//Cleanup
					if (pacBuffer != NULL)
					{
						UnmapViewOfFile(pacBuffer);
					}
					if (piOffset != 0)
					{
						SetFilePointer(hFile, (long) piOffset, NULL, FILE_BEGIN);
					}
					bRes = ::ReadFile(hFile, pvData, *piSize, (unsigned long *) &iSize, NULL);
				}
			}
		}
		*piSize = iSize;
	}
	CloseHandle(hMapping);
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::WriteFile(const TCHAR *pacFile, const void *pvData, unsigned int piSize, unsigned int piOffset)
{
	bool bRes = false;


	HANDLE hMapping = NULL;
	HANDLE hFile = CreateFile(GetShortName((String) pacFile).c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// Use file mapped IO
		hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, piSize, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
			void *pacBuffer = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, piSize);
			if ((piOffset == 0) && (pacBuffer != NULL))
			{
				memcpy(pacBuffer, pvData, piSize);
				bRes = UnmapViewOfFile(pacBuffer);
			}
			//CloseHandle(hMapping);
			// Use regular IO
			else
			{
				if (piOffset != 0)
				{
					SetFilePointer(hFile, (long) piOffset, NULL, FILE_BEGIN);
				}
				unsigned int iSize;
				bRes = ::WriteFile(hFile, pvData, piSize, (unsigned long *) &iSize, NULL);
			}
		}
	}
	CloseHandle(hMapping);
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetFileTimestamp(const TCHAR *pacFile, FILETIME *pudtCreated, FILETIME *pudtAccessed, FILETIME *pudtModified)
{
	bool bRes = false;


	HANDLE hFile = CreateFile(GetShortName((String) pacFile).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = GetFileTime(hFile, pudtCreated, pudtAccessed, pudtModified);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetFileTimestamp(const TCHAR *pacFile, const FILETIME *pudtCreated, const FILETIME *pudtAccessed, const FILETIME *pudtModified)
{
	bool bRes = false;


	HANDLE hFile = CreateFile(GetShortName((String) pacFile).c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = SetFileTime(hFile, pudtCreated, pudtAccessed, pudtModified);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DirectoryCreate(String psDirectory)
{
	bool bRes = false;
	TCHAR *acDirectory;

	if (!EndsStr("\\", psDirectory))
	{
		psDirectory += "\\";
	}
	acDirectory = psDirectory.c_str();
	unsigned int iDirectoryLen = (unsigned int) _tcslen(acDirectory);

	for (unsigned int iCount = 0; iCount < iDirectoryLen; iCount++)
	{
		//If found a backslash we try to create that component (it should end with backslash
		if (acDirectory[iCount] == '\\')
		{
			acDirectory[iCount] = NULL;
			bRes = (CreateDirectory(GetShortName((String) acDirectory).c_str(), NULL) != 0);
			acDirectory[iCount] = '\\';
		}
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DownloadFile(const TCHAR *pacUrl, void *pvData, unsigned int piSize)
{
	bool bRes = false;


	if (GetModuleFileName(NULL, (TCHAR *) pvData, piSize - 1) != 0)
	{
		_stprintf((TCHAR *) pvData, _T("%s/%s"), Application->Name.c_str(), ExeVersion((const TCHAR *) pvData));
	}
	HINTERNET hInternet = InternetOpen((const TCHAR *) pvData, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternet != NULL)
	{
		HINTERNET hHttp = InternetOpenUrl(hInternet, pacUrl, NULL, 0, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_HYPERLINK, NULL);
		if (hHttp != NULL)
		{
			memset(pvData, 0, piSize);
			unsigned long lRead;
			if (InternetReadFile(hHttp, pvData, piSize, &lRead))
			{
				bRes = true;
			}
		}
		InternetCloseHandle(hHttp);
	}
	InternetCloseHandle(hInternet);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DownloadFilePost(const TCHAR *pacServer, const TCHAR *pacPage, const char *pacParameters, void *pvData, unsigned int piSize, bool pbHttps)
{
	bool bRes = false;
	

    //ToDo: Use UrlGetPart https://msdn.microsoft.com/en-us/library/windows/desktop/bb773781(v=vs.85).aspx
	if (GetModuleFileName(NULL, (TCHAR *) pvData, piSize - 1) != 0)
	{
		_stprintf((TCHAR *) pvData, _T("%s/%s"), Application->Name.c_str(), ExeVersion((const TCHAR *) pvData));
	}
	HINTERNET hInternet = InternetOpen((const TCHAR *) pvData, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternet)
	{
		
		unsigned int iFlags = INTERNET_DEFAULT_HTTP_PORT;
		if (pbHttps)
		{
			iFlags = INTERNET_DEFAULT_HTTPS_PORT;
		}
		HINTERNET hConnect = InternetConnect(hInternet, pacServer, iFlags, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
		if (hConnect)
		{
			iFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_UI;
			if (pbHttps)
			{
				iFlags |= INTERNET_FLAG_SECURE;
			}
			HINTERNET hRequest = HttpOpenRequest(hConnect, _T("POST"), pacPage, HTTP_VERSION, _T(""), NULL, iFlags, 0);
			if (hRequest)
			{
				if (pbHttps)
				{
					unsigned int iCertificate = 0;
					InternetSetOption(hRequest, INTERNET_OPTION_SECURITY_SELECT_CLIENT_CERT, &iCertificate, sizeof(iCertificate));
				}
				
				TCHAR acHeaders[] = _T("Content-Type: application/x-www-form-urlencoded");
				if (HttpSendRequest(hRequest, acHeaders, _tcslen(acHeaders), (void *) pacParameters, strlen((char *) pacParameters)))
				{
					memset(pvData, 0, piSize);
					unsigned long lRead;
					if (InternetReadFile(hRequest, pvData, piSize, &lRead))
					{
						bRes = (lRead > 0);
					}
				}
			}
			InternetCloseHandle(hRequest);
		}
		InternetCloseHandle(hConnect);
	}
	InternetCloseHandle(hInternet);
	return (bRes);
}




// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::CopyFile(const TCHAR *pacSource, const TCHAR *pacDestination)
{
	bool bRes;
	int i;

	DeleteFile(pacDestination);

	//Try copying file with faster no buffering only available in Windows XP
	bRes = (CopyFileEx(GetShortName((String) pacSource).c_str(), GetShortName((String) pacDestination).c_str(), NULL, NULL, false, COPY_FILE_ALLOW_DECRYPTED_DESTINATION|COPY_FILE_NO_BUFFERING) != 0);
	if (!bRes)
	{
		//Try copying file with buffering
		bRes = ::CopyFile(GetShortName((String) pacSource).c_str(), GetShortName((String) pacDestination).c_str(), false);
	}
	return (bRes);
}




// --------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::ExeVersion(const TCHAR *pacFile)
{
	//GetProductVersion((String) pacFile, iMajor, iMinor, iRevision);

	unsigned int iVersionSize;
	TCHAR *pacVersionData;
	void *a;
	VS_FIXEDFILEINFO udtVersionInfo;
	static TCHAR acRes[2048];

	memset(acRes, 0, sizeof(acRes));	
	iVersionSize = GetFileVersionInfoSize(pacFile, 0);
	pacVersionData = new TCHAR[iVersionSize];
	if (pacVersionData)
	{
		if (GetFileVersionInfo(GetShortName((String) pacFile).c_str(), 0, iVersionSize, pacVersionData))
		{
			if (VerQueryValue(pacVersionData, _T("\\"), &a, &iVersionSize))
			{
				memcpy(&udtVersionInfo, a, iVersionSize);
				_stprintf(acRes, _T("%d.%01d%01d.%d"), HIWORD(udtVersionInfo.dwFileVersionMS), LOWORD(udtVersionInfo.dwFileVersionMS), HIWORD(udtVersionInfo.dwFileVersionLS), LOWORD(udtVersionInfo.dwFileVersionLS));
			}
		}
		delete[] pacVersionData;
	}
	return (acRes);
}



//---------------------------------------------------------------------------
int __fastcall clsUtil::GetFileVersionField(const TCHAR *fn, const TCHAR *info, TCHAR *ret, int len)
{
	DWORD hVersion;
	DWORD vis = GetFileVersionInfoSize(fn, &hVersion);


	if (vis == 0)
	{
		return (0);
	}
	void *vData;
	vData = (void *) new TCHAR[(UINT) vis];

	if (!GetFileVersionInfo(fn, hVersion, vis, vData))
	{
		delete[] (TCHAR *) vData;
		return (0);
	}
	TCHAR vn[100];
	_tcscpy(vn, _T("\\VarFileInfo\\Translation"));

	LPVOID transblock;
	UINT vsize;

	BOOL res = VerQueryValue(vData, vn, &transblock, &vsize);
	if (!res)
	{
		delete[] (TCHAR *) vData;
		return (0);
	}
	// Swap the words so wsprintf will print the lang-charset in the correct format.
	*(DWORD *) transblock = MAKELONG(HIWORD(*(DWORD *) transblock), LOWORD(*(DWORD *) transblock));
	_stprintf(vn, _T("\\StringFileInfo\\%08lx\\%s"),*(DWORD *) transblock, info);
	TCHAR *ver;
	res = VerQueryValue(vData, vn, (LPVOID*) &ver, &vsize);
	if (!res)
	{
		delete[] (TCHAR *) vData;
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
	delete[] (TCHAR *) vData;
	return(vlen);
}




// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIniPath(bool pbAllUsers)
{
	static TCHAR acPath[PATH_MAX] = _T("");
	static TCHAR acPathAllUsers[PATH_MAX] = _T("");


	// Check if we already have it cached
	if ((acPath[0] == NULL) && (acPathAllUsers[0] == NULL))
	{
		TCHAR acTmp[2048];
		
		if (GetModuleFileName(NULL, acTmp, (sizeof(acTmp) / sizeof(TCHAR)) - 1) != 0)
		{
			*_tcsrchr(acTmp, '.') = NULL;
		}
		_tcscat(acTmp, _T(".ini"));

		// Check if we can write to that location
		HANDLE hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".ini").c_str());
			_tcsncpy(acPathAllUsers, acTmp, (sizeof(acPathAllUsers) / sizeof(TCHAR)) - 1);
		}
		else
		{
			CloseHandle(hFile);
			_stprintf(acPath, acTmp);
			_tcsncpy(acPathAllUsers, acPath, (sizeof(acPathAllUsers) / sizeof(TCHAR)) - 1);
		}
		_tcscpy(acPath, GetShortName((String) acPath).c_str());
		_tcscpy(acPathAllUsers, GetShortName((String) acPathAllUsers).c_str());
	}
	if (pbAllUsers)
	{
		return (acPathAllUsers);
	}
	else
	{
		return (acPath);
	}
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacDefault)
{
	static TCHAR acRes[2048];
	TCHAR *pcSemicolon;
	

	memset(acRes, 0, sizeof(acRes));
	UnescapeIniKey((TCHAR *) pacKey);
	GetPrivateProfileString(pacSection, pacKey, pacDefault, acRes, (sizeof(acRes) / sizeof(TCHAR)) - 1, GetIniPath(true));
	if (acRes[0] == NULL)
	{
		GetPrivateProfileString(pacSection, pacKey, pacDefault, acRes, (sizeof(acRes) / sizeof(TCHAR)) - 1, GetIniPath(false));
	}
	UnescapeIniValue(acRes);
	
	//Remove comments
	pcSemicolon = _tcsrchr(acRes, ';');
	if (pcSemicolon)
	{
    	*pcSemicolon = NULL;
	}
	//Remove tabs
	pcSemicolon = _tcschr(acRes, '\t');
	if (pcSemicolon)
	{
    	*pcSemicolon = NULL;
	}

	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piDefault)
{
	TCHAR acDefault[2048];


	_itot(piDefault, acDefault, 10);
	return (_ttoi(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plDefault)
{
	TCHAR acDefault[2048];


	_i64tot(plDefault, acDefault, 10);
	return (_ttoi64(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdDefault)
{
	TCHAR acDefault[2048];


	_stprintf(acDefault, _T("%f"), pdDefault);
	return (_ttof(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbDefault)
{
	TCHAR acDefault[2048];
	TCHAR acValue[2048];


	if (pbDefault)
	{
		_tcscpy(acDefault, _T("true"));
	}
	else
	{
		_tcscpy(acDefault, _T("false"));
	}

	_tcsncpy(acValue, GetIni(pacSection, pacKey, acDefault), (sizeof(acValue) / sizeof(TCHAR)) - 1);
	return ((_tcsicmp(acValue, _T("true")) == 0) || (_tcsicmp(acValue, _T("yes")) == 0) || (_tcsicmp(acValue, _T("on")) == 0) || (_tcscmp(acValue, _T("1")) == 0));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacValue, const TCHAR *pacComment)
{
	bool bRes;
	
	//Escape INI key and value
	EscapeIniKey((TCHAR *) pacKey);
	EscapeIniValue((TCHAR *) pacValue);
	
	//No comment
	if (pacComment[0] == NULL)
	{
		//Try to save for all users
		bRes = WritePrivateProfileString(pacSection, pacKey, pacValue, GetIniPath(true));
		if (!bRes)
		{
			//Save it for current user
			bRes = WritePrivateProfileString(pacSection, pacKey, pacValue, GetIniPath(false));
		}
	}
	else
	{
		TCHAR acValue[2048];

		_tcsncpy(acValue, pacValue, (sizeof(acValue) / sizeof(TCHAR)) - 1);
		_tcscat(acValue, _T("\t\t; "));
		_tcscat(acValue, pacComment);
		//Try to save for all users
		bRes = WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath(true));
		if (!bRes)
		{
			//Save it for current user
			bRes = WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath(false));
		}
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbValue, const TCHAR *pacComment)
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
	return (SetIni(pacSection, pacKey, acValue, pacComment));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_itot(piValue, acValue, 10);
	return (SetIni(pacSection, pacKey, acValue, pacComment));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_i64tot(plValue, acValue, 10);
	return (SetIni(pacSection, pacKey, acValue, pacComment));
}





// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_stprintf(acValue, _T("%f"), pdValue);
	return (SetIni(pacSection, pacKey, acValue, pacComment));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DeleteIni(const TCHAR *pacSection, const TCHAR *pacKey)
{
	return (WritePrivateProfileString(pacSection, pacKey, NULL, GetIniPath()));
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetRegistryPath(void)
{
	static TCHAR acPath[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		_tcscpy(acPath, _T("Software\\"));
		_tcscat(acPath, Application->Name.c_str());
	}
	return (acPath);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName)
{
	HKEY hKey;
	static TCHAR acRes[2048];


	memset(acRes, 0, sizeof(acRes));
	if (RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{
		unsigned int iSize = sizeof(acRes);
		RegQueryValueEx(hKey, pacName, NULL, NULL, (BYTE *) acRes, (LPDWORD) &iSize);
		RegCloseKey(hKey);
    }
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, const TCHAR *pacValue)
{
	bool bRes = false;
	HKEY hKey;


	if (RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
	{
		if (pacValue)
		{
			bRes = (RegSetValueEx(hKey, pacName, NULL, REG_SZ, (BYTE *) pacValue, _tcslen(pacValue) + 1) == ERROR_SUCCESS);
		}
		else
		{
			bRes = (RegDeleteValue(hKey, pacName) == ERROR_SUCCESS);
        }
		RegCloseKey(hKey);
	}
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, unsigned int piValue)
{
	bool bRes = false;
	HKEY hKey;


	if (RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
	{
		bRes = (RegSetValueEx(hKey, pacName, NULL, REG_DWORD, (BYTE *) &piValue, sizeof(piValue)) == ERROR_SUCCESS);
		RegCloseKey(hKey);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, unsigned long long plValue)
{
	bool bRes = false;
	HKEY hKey;


	if (RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
	{
		bRes = (RegSetValueEx(hKey, pacName, NULL, REG_QWORD, (BYTE *) &plValue, sizeof(plValue)) == ERROR_SUCCESS);
		RegCloseKey(hKey);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DeleteRegistry(HKEY phKey, const TCHAR *pacSubkey)
{
	bool bRes;
	
	
	//bRes = (RegDeleteTree(phKey, pacSubkey) == ERROR_SUCCESS);
	bRes = (RegDeleteKey(phKey, pacSubkey) == ERROR_SUCCESS);

	return (bRes);
}


// ---------------------------------------------------------------------------
unsigned int __fastcall clsUtil::Serialize (void *pacBuffer, unsigned int piSize)
{
	for (int iBuffer = (int) piSize - 1; iBuffer >= 0; iBuffer--)
	{
		unsigned char iByte = ((unsigned char *) pacBuffer)[iBuffer];
		((unsigned char *) pacBuffer)[iBuffer << 1] = (iByte & 15) + '0';
		((unsigned char *) pacBuffer)[(iBuffer << 1) + 1] = (iByte >> 4) + '0';
	}
	return (piSize << 1);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned int __fastcall clsUtil::Unserialize (void *pacBuffer, unsigned int piSize)
{
	for (unsigned int iBuffer = 0; iBuffer < piSize; iBuffer+=2)
	{
		unsigned char iNibbleL = ((unsigned char *) pacBuffer)[iBuffer] - '0';
		unsigned char iNibbleH = ((unsigned char *) pacBuffer)[iBuffer + 1] - '0';

		//Do a simple integrity check
		if ((iNibbleL > 15) || (iNibbleH > 15))
		{
			return (0);
		}
		else
		{
			((unsigned char *) pacBuffer)[iBuffer >> 1] = (unsigned char) (iNibbleL + (iNibbleH << 4));
		}
	}
	return (piSize >> 1);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::EscapeIniValue (TCHAR *pacBuffer)
{
	String sBuffer = pacBuffer;
	sBuffer = ReplaceStr(sBuffer, "=", "%3D");
	_tcscpy(pacBuffer, sBuffer.c_str());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::UnescapeIniValue (TCHAR *pacBuffer)
{
	String sBuffer = pacBuffer;
	sBuffer = ReplaceStr(sBuffer, "%3D", "=");
	_tcscpy(pacBuffer, sBuffer.c_str());
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::EscapeIniKey (TCHAR *pacBuffer)
{
	//Same rules as for values
	EscapeIniValue(pacBuffer);
	
	String sBuffer = pacBuffer;
	sBuffer = ReplaceStr(sBuffer, " ", "%20");
	sBuffer = ReplaceStr(sBuffer, "\t", "%20");
	_tcscpy(pacBuffer, sBuffer.c_str());
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::UnescapeIniKey (TCHAR *pacBuffer)
{
	String sBuffer = pacBuffer;
	
	//Same rules as for values
	UnescapeIniValue(pacBuffer);
	
	sBuffer = ReplaceStr(sBuffer, "%20", " ");
	_tcscpy(pacBuffer, sBuffer.c_str());
}




// --------------------------------------------------------------------------------------------------
unsigned int __fastcall clsUtil::Crc32 (const void *pacBuffer, unsigned int piLen, unsigned int piOldCrc)
{
	unsigned int iCont;
	unsigned int iCrc;
	const unsigned int aiTable[] =
	{
		0x000000000, 0x077073096, 0x0EE0E612C, 0x0990951BA, 0x0076DC419, 0x0706AF48F, 0x0E963A535, 0x09E6495A3, 0x00EDB8832, 0x079DCB8A4,
		0x0E0D5E91E, 0x097D2D988, 0x009B64C2B, 0x07EB17CBD, 0x0E7B82D07, 0x090BF1D91, 0x01DB71064, 0x06AB020F2, 0x0F3B97148, 0x084BE41DE,
		0x01ADAD47D, 0x06DDDE4EB, 0x0F4D4B551, 0x083D385C7, 0x0136C9856, 0x0646BA8C0, 0x0FD62F97A, 0x08A65C9EC, 0x014015C4F, 0x063066CD9,
		0x0FA0F3D63, 0x08D080DF5, 0x03B6E20C8, 0x04C69105E, 0x0D56041E4, 0x0A2677172, 0x03C03E4D1, 0x04B04D447, 0x0D20D85FD, 0x0A50AB56B,
		0x035B5A8FA, 0x042B2986C, 0x0DBBBC9D6, 0x0ACBCF940, 0x032D86CE3, 0x045DF5C75, 0x0DCD60DCF, 0x0ABD13D59, 0x026D930AC, 0x051DE003A,
		0x0C8D75180, 0x0BFD06116, 0x021B4F4B5, 0x056B3C423, 0x0CFBA9599, 0x0B8BDA50F, 0x02802B89E, 0x05F058808, 0x0C60CD9B2, 0x0B10BE924,
		0x02F6F7C87, 0x058684C11, 0x0C1611DAB, 0x0B6662D3D, 0x076DC4190, 0x001DB7106, 0x098D220BC, 0x0EFD5102A, 0x071B18589, 0x006B6B51F,
		0x09FBFE4A5, 0x0E8B8D433, 0x07807C9A2, 0x00F00F934, 0x09609A88E, 0x0E10E9818, 0x07F6A0DBB, 0x0086D3D2D, 0x091646C97, 0x0E6635C01,
		0x06B6B51F4, 0x01C6C6162, 0x0856530D8, 0x0F262004E, 0x06C0695ED, 0x01B01A57B, 0x08208F4C1, 0x0F50FC457, 0x065B0D9C6, 0x012B7E950,
		0x08BBEB8EA, 0x0FCB9887C, 0x062DD1DDF, 0x015DA2D49, 0x08CD37CF3, 0x0FBD44C65, 0x04DB26158, 0x03AB551CE, 0x0A3BC0074, 0x0D4BB30E2,
		0x04ADFA541, 0x03DD895D7, 0x0A4D1C46D, 0x0D3D6F4FB, 0x04369E96A, 0x0346ED9FC, 0x0AD678846, 0x0DA60B8D0, 0x044042D73, 0x033031DE5,
		0x0AA0A4C5F, 0x0DD0D7CC9, 0x05005713C, 0x0270241AA, 0x0BE0B1010, 0x0C90C2086, 0x05768B525, 0x0206F85B3, 0x0B966D409, 0x0CE61E49F,
		0x05EDEF90E, 0x029D9C998, 0x0B0D09822, 0x0C7D7A8B4, 0x059B33D17, 0x02EB40D81, 0x0B7BD5C3B, 0x0C0BA6CAD, 0x0EDB88320, 0x09ABFB3B6,
		0x003B6E20C, 0x074B1D29A, 0x0EAD54739, 0x09DD277AF, 0x004DB2615, 0x073DC1683, 0x0E3630B12, 0x094643B84, 0x00D6D6A3E, 0x07A6A5AA8,
		0x0E40ECF0B, 0x09309FF9D, 0x00A00AE27, 0x07D079EB1, 0x0F00F9344, 0x08708A3D2, 0x01E01F268, 0x06906C2FE, 0x0F762575D, 0x0806567CB,
		0x0196C3671, 0x06E6B06E7, 0x0FED41B76, 0x089D32BE0, 0x010DA7A5A, 0x067DD4ACC, 0x0F9B9DF6F, 0x08EBEEFF9, 0x017B7BE43, 0x060B08ED5,
		0x0D6D6A3E8, 0x0A1D1937E, 0x038D8C2C4, 0x04FDFF252, 0x0D1BB67F1, 0x0A6BC5767, 0x03FB506DD, 0x048B2364B, 0x0D80D2BDA, 0x0AF0A1B4C,
		0x036034AF6, 0x041047A60, 0x0DF60EFC3, 0x0A867DF55, 0x0316E8EEF, 0x04669BE79, 0x0CB61B38C, 0x0BC66831A, 0x0256FD2A0, 0x05268E236,
		0x0CC0C7795, 0x0BB0B4703, 0x0220216B9, 0x05505262F, 0x0C5BA3BBE, 0x0B2BD0B28, 0x02BB45A92, 0x05CB36A04, 0x0C2D7FFA7, 0x0B5D0CF31,
		0x02CD99E8B, 0x05BDEAE1D, 0x09B64C2B0, 0x0EC63F226, 0x0756AA39C, 0x0026D930A, 0x09C0906A9, 0x0EB0E363F, 0x072076785, 0x005005713,
		0x095BF4A82, 0x0E2B87A14, 0x07BB12BAE, 0x00CB61B38, 0x092D28E9B, 0x0E5D5BE0D, 0x07CDCEFB7, 0x00BDBDF21, 0x086D3D2D4, 0x0F1D4E242,
		0x068DDB3F8, 0x01FDA836E, 0x081BE16CD, 0x0F6B9265B, 0x06FB077E1, 0x018B74777, 0x088085AE6, 0x0FF0F6A70, 0x066063BCA, 0x011010B5C,
		0x08F659EFF, 0x0F862AE69, 0x0616BFFD3, 0x0166CCF45, 0x0A00AE278, 0x0D70DD2EE, 0x04E048354, 0x03903B3C2, 0x0A7672661, 0x0D06016F7,
		0x04969474D, 0x03E6E77DB, 0x0AED16A4A, 0x0D9D65ADC, 0x040DF0B66, 0x037D83BF0, 0x0A9BCAE53, 0x0DEBB9EC5, 0x047B2CF7F, 0x030B5FFE9,
		0x0BDBDF21C, 0x0CABAC28A, 0x053B39330, 0x024B4A3A6, 0x0BAD03605, 0x0CDD70693, 0x054DE5729, 0x023D967BF, 0x0B3667A2E, 0x0C4614AB8,
		0x05D681B02, 0x02A6F2B94, 0x0B40BBE37, 0x0C30C8EA1, 0x05A05DF1B, 0x02D02EF8D
	};

	iCrc = piOldCrc;
	for (iCont = 0; iCont < piLen; iCont++)
	{
		unsigned char cByte = (unsigned char) iCrc ^ ((unsigned char *) pacBuffer)[iCont];
		iCrc = (iCrc >> 8) ^ aiTable[cByte];
	}
	return (iCrc ^ 0xFFFFFFFF);
}





// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::Random(int piMin, int piMax)
{
	static unsigned int iSeed = (unsigned int) (GetTickCount() * GetCurrentProcessId());

	
	iSeed = (214013 * iSeed + 2531011);
	return ((int) iSeed  % (piMax - piMin) + piMin);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetLogPath(void)
{
	static TCHAR acPath[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		TCHAR acTmp[2048];
		
		if (GetModuleFileName(NULL, acTmp, (sizeof(acTmp) / sizeof(TCHAR)) - 1) != 0)
		{
			*_tcsrchr(acTmp, '.') = NULL;
		}
		_tcscat(acTmp, _T(".log"));
		// Check if we can write to that location
		HANDLE hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".log").c_str());
		}
		else
		{
			CloseHandle(hFile);
			_tcsncpy(acPath, acTmp, (sizeof(acPath) / sizeof(TCHAR)) - 1);
		}
		_tcscpy(acPath, GetShortName((String) acPath).c_str());
	}
	return (acPath);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::LogAdd(const TCHAR *pacFile, int piLine, const TCHAR *pacFunc, int piLevel, const TCHAR *pacValue, int piDesiredLevel)
{
	if ((piDesiredLevel) > piLevel)
	{
		TCHAR acPath[PATH_MAX];
		TCHAR acLevel[][32] = { _T("CRITICAL"), _T("ERROR"), _T("WARNING"), _T("INFORMATION"), _T("NONE") };
		
		_tcsncpy(acPath, GetLogPath(), (sizeof(acPath) / sizeof(TCHAR)) - 1);
		FILE *pLog = _tfopen(acPath, _T("at"));
		TDateTime dteDate = dteDate.CurrentDateTime();
		_ftprintf(pLog, _T("[%s %s]	%s	%s	(%d)	%s()	%s\n"), dteDate.DateString().c_str(), dteDate.TimeString().c_str(), acLevel[piLevel], pacFile, piLine, pacFunc, pacValue);
		fclose(pLog);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::LoadForm(TForm *pfrmForm)
{
	int iWindowState;


	pfrmForm->Left = GetIni(pfrmForm->Name.c_str(), _T("Left"), (Screen->Width - pfrmForm->Width) >> 1);
	pfrmForm->Top = GetIni(pfrmForm->Name.c_str(), _T("Top"), (Screen->Height - pfrmForm->Height) >> 1);
	pfrmForm->Width = GetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
	pfrmForm->Height = GetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	iWindowState = GetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	//We do not want to reopen FileOptimizer in minimized state
	if (iWindowState == (int) wsMinimized)
	{
		iWindowState = (int) wsNormal;
	}
	pfrmForm->WindowState = (TWindowState) iWindowState;
	pfrmForm->DefaultMonitor = (TDefaultMonitor) GetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), pfrmForm->DefaultMonitor);
	pfrmForm->MakeFullyVisible(NULL);
	return (true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SaveForm(TForm *pfrmForm)
{
	if ((pfrmForm->WindowState != wsMaximized) && (pfrmForm->WindowState != wsMinimized))
	{
		SetIni(pfrmForm->Name.c_str(), _T("Left"), pfrmForm->Left);
		SetIni(pfrmForm->Name.c_str(), _T("Top"), pfrmForm->Top);
		SetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
		SetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	}
	SetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	SetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), (int) pfrmForm->DefaultMonitor);
	return (true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::CopyToRecycleBin(const TCHAR *pacSource)
{
	int iRes;
	SHFILEOPSTRUCT udtFileOp = {};
	TCHAR acSource[PATH_MAX] = {};
	TCHAR acDestination[PATH_MAX] = {};


	Application->ProcessMessages();
	// ShFileOperation expect strings ending in double NULL
	_tcsncpy(acSource, pacSource, (sizeof(acSource) / sizeof(TCHAR)) - 1);

	_tcsncpy(acDestination, acSource, (sizeof(acDestination) / sizeof(TCHAR)) - 5);
	_tcscat(acDestination, _T(".tmp"));

	CopyFile(acSource, acDestination);

	udtFileOp.wFunc = FO_DELETE;
	udtFileOp.fFlags = FOF_ALLOWUNDO | FOF_NO_UI;
	udtFileOp.pFrom = acSource;

	iRes = SHFileOperation(&udtFileOp);
	if (iRes == 0)
	{
		DeleteFile(acSource);
		MoveFile(acDestination, acSource);
		DeleteFile(acDestination);
		return (true);
	}
	else
	{
		DeleteFile(acDestination);
		return (false);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SetTaskListProgress(unsigned int piCompleted, unsigned int piTotal)
{
	ITaskbarList3 *pTaskList = NULL;


	// In 7 or newer use new TaskDialog
	if (GetWindowsVersion() >= 601)
	{
		HRESULT hRes = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **) &pTaskList);
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
				return (true);
			}
			pTaskList->Release();
		}
	}
	return (false);
}


// ---------------------------------------------------------------------------
unsigned int __fastcall clsUtil::GetWindowsVersion(void)
{
	static unsigned int iWindowsVersion = NULL;
	

	//Get true Windows version, even for non manifested applications under Windows 8.1 or later
	if (iWindowsVersion == NULL)
	{
		HMODULE hNtDll = LoadLibrary(_T("NTDLL.DLL"));
		if (hNtDll)
		{
			typedef NTSTATUS (WINAPI RtlGetVersionType)(RTL_OSVERSIONINFOW *pudtRtlVersionInfo);
			RtlGetVersionType *RtlGetVersionProc = (RtlGetVersionType *) GetProcAddress(hNtDll, "RtlGetVersion");
			if (RtlGetVersionProc)
			{
				RTL_OSVERSIONINFOW udtRtlVersionInfo;
				RtlGetVersionProc(&udtRtlVersionInfo);
				iWindowsVersion = (udtRtlVersionInfo.dwMajorVersion * 100) + udtRtlVersionInfo.dwMinorVersion;
			}
			FreeLibrary(hNtDll);
		}
		//Fallback when library not loaded or RtlGetVersion not exists
		if (iWindowsVersion == NULL)
		{
			iWindowsVersion = GetVersion();
			iWindowsVersion = (LOBYTE(LOWORD(iWindowsVersion))) * 100 + (HIBYTE(LOWORD(iWindowsVersion)));
		}
	}
	//500: Windows 2000; 501: Windows XP; 502: Windows XP x64/Windows 2003; 600: Windows Vista/2008; 601: Windows 7/Windows 2008 R2; 602: Windows 8/Windows 2012; 603: Windows 8.1; 1000: Windows 10
	return (iWindowsVersion);
}


// ---------------------------------------------------------------------------
bool __fastcall clsUtil::IsWindows64(void)
{
	static unsigned int iWindowsArchitecture = NULL;


	if (iWindowsArchitecture == NULL)
	{
		#if defined(_WIN64)
			iWindowsArchitecture = PROCESSOR_ARCHITECTURE_AMD64;
		#else
			SYSTEM_INFO udtSystemInfo;
			GetNativeSystemInfo(&udtSystemInfo);
			iWindowsArchitecture = udtSystemInfo.wProcessorArchitecture;
		#endif
	}
	return (iWindowsArchitecture == PROCESSOR_ARCHITECTURE_AMD64);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::ShutdownWindows(unsigned int piMode)
{
	bool bRes = false;
	HANDLE hToken; 
	TOKEN_PRIVILEGES udtTokenPrivileges; 


	//Get a token for this process
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		//Get the LUID for the shutdown privilege.
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &udtTokenPrivileges.Privileges[0].Luid); 
		udtTokenPrivileges.PrivilegeCount = 1;  //One privilege to set    
		udtTokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

		// Get the shutdown privilege for this process. 
		AdjustTokenPrivileges(hToken, false, &udtTokenPrivileges, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
		if (GetLastError() == ERROR_SUCCESS) 
		{
			//Shut down the system and force all applications to close.
			unsigned int iFlags;

			//Poweroff
			if (piMode == 1)
			{
				iFlags = EWX_POWEROFF;
			}
			//Reboot
			else if (piMode == 2)
			{
				iFlags = EWX_REBOOT | EWX_FORCE;
			}
			//Logout
			else if (piMode == 3)
			{
				iFlags = EWX_LOGOFF | EWX_FORCE;
			}
			//Shutdown
			else //0
			{
				iFlags = EWX_SHUTDOWN | EWX_HYBRID_SHUTDOWN | EWX_FORCE;
			}
			if (ExitWindowsEx(iFlags, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED))
			{
				bRes = true;
			}
		}
	}
	return (bRes);
}



// ---------------------------------------------------------------------------
String __fastcall clsUtil::GetShortName(String psLongName)
{

/*
	String sRes;


	sRes = ExtractShortPathName(psLongName);
	if (sRes.Length() <= 0)
	{
		sRes = psLongName;
	}
	return(sRes);

*/
	unsigned int iRes;
	TCHAR acShortName[PATH_MAX] = {};


	iRes = GetShortPathName(psLongName.c_str(), acShortName, (sizeof(acShortName) / sizeof(TCHAR)) - 1);
	if ((iRes == 0) || (iRes >= (sizeof(acShortName) / sizeof(TCHAR)) - 1))
	{
		_tcscpy(acShortName, psLongName.c_str());
	}
	return ((String) acShortName);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::DeleteFile(const TCHAR *pacFile)
{
	return (::DeleteFile(GetShortName((String) pacFile).c_str()));
}




// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
