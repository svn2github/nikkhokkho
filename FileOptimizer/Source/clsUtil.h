// ---------------------------------------------------------------------------
#pragma once

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#if !defined(_max)
	#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#if !defined(_min)
	#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#if defined(_DEBUG)
	//For some reason BCC64 gaves an error with __FUNC__
	#if defined(_WIN64)
		#define Log(piLevel, pacValue) (clsUtil::LogAdd(_T(__FILE__), __LINE__, _T(""), piLevel, pacValue, 5))
	#else
		#define Log(piLevel, pacValue) (clsUtil::LogAdd(_T(__FILE__), __LINE__, _T(__FUNC__), piLevel, pacValue, 5))
	#endif
#else
	#if defined(_WIN64)
		#define Log(piLevel, pacValue) (clsUtil::LogAdd(_T(__FILE__), __LINE__, _T(""), piLevel, pacValue, gudtOptions.iLogLevel))
	#else
		#define Log(piLevel, pacValue) (clsUtil::LogAdd(_T(__FILE__), __LINE__, _T(__FUNC__), piLevel, pacValue, gudtOptions.iLogLevel))
	#endif
#endif


// ---------------------------------------------------------------------------
class clsUtil
{
	public:
		static const TCHAR * __fastcall ReplaceString(const TCHAR *pacString, const TCHAR *pacSearch, const TCHAR *pacReplace);
		static void * __fastcall MemMem (const void *buf, size_t buf_len, const void *byte_sequence, size_t byte_sequence_len);
		static int __fastcall MsgBox(HWND phWnd, const TCHAR *pacText, const TCHAR *pacTitle, int piType);
		static HANDLE __fastcall FindProcess(const TCHAR *pacProcess);
		static unsigned long __fastcall RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait);
		static bool __fastcall ExistsFile(const TCHAR *pacFile);
		static unsigned long long __fastcall SizeFile(const TCHAR *pacFile);
		static bool __fastcall ReadFile(const TCHAR *pacFile, void *pvData, unsigned int *piSize);
		static bool __fastcall WriteFile(const TCHAR *pacFile, const void *pvData, unsigned int piSize);
		static bool __fastcall GetFileTimestamp(const TCHAR *pacFile, FILETIME *pudtCreated = NULL, FILETIME *pudtAccessed  = NULL, FILETIME *pudtModified  = NULL);
		static bool __fastcall SetFileTimestamp(const TCHAR *pacFile, const FILETIME *pudtCreated = NULL, const FILETIME *pudtAccessed = NULL, const FILETIME *pudtModified = NULL);
		static bool __fastcall DirectoryCreate(String psDirectory);
		static bool __fastcall DownloadFile(const TCHAR *pacUrl, void *pvData, unsigned int piSize);
		static bool __fastcall CopyFile(const TCHAR *pacSource, const TCHAR *pacDestination);
		static const TCHAR * __fastcall ExeVersion(const TCHAR *pacFile);
		static int __fastcall GetFileVersionField(const TCHAR *fn, const TCHAR *info, TCHAR *ret, int len);
		static const TCHAR * __fastcall GetIniPath(void);
		static const TCHAR * __fastcall GetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacDefault);
		static int __fastcall GetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piDefault = 0);
		static long long __fastcall GetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plDefault = 0);
		static double __fastcall GetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdDefault = 0);
		static bool __fastcall GetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbDefault = false );
		static void __fastcall SetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacValue = _T(""));
		static void __fastcall SetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbValue);
		static void __fastcall SetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piValue);
		static void __fastcall SetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plValue);
		static void __fastcall SetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdValue);
		static unsigned int __fastcall Serialize (void *pacBuffer, unsigned int piSize);
		static unsigned int __fastcall Unserialize (void *pacBuffer, unsigned int piSize);
		static int __fastcall Random (int piMin, int piMax);
		static const TCHAR * __fastcall GetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName);
		static void __fastcall SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, const TCHAR *pacValue);
		static const TCHAR * __fastcall GetLogPath(void);
		static void __fastcall LogAdd(const TCHAR *pacFile, int piLine, const TCHAR *pacFunc, int piLevel, const TCHAR *pacValue, int piDesiredLevel);
		static bool __fastcall LoadForm(TForm *pfrmForm);
		static bool __fastcall SaveForm(TForm *pfrmForm);
		static bool __fastcall CopyToRecycleBin(const TCHAR *pacSource);
		static bool __fastcall SetTaskListProgress(unsigned int piCompleted, unsigned int piTotal);
		static unsigned int __fastcall GetWindowsVersion(void);
};

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
