// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"
#include <limits.h>
#include "clsUtil.h"


// ---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>



// ---------------------------------------------------------------------------
USEFORM("Source\cppAbout.cpp", frmAbout)
USEFORM("Source\cppMain.cpp", frmMain)
USEFORM("Source\cppOptions.cpp", frmOptions)
//---------------------------------------------------------------------------
USEFORM("Source\cppAbout.cpp", frmAbout)
USEFORM("Source\cppMain.cpp", frmMain)
USEFORM("Source\cppOptions.cpp", frmOptions)



//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE phInstance, HINSTANCE phPrevInstance, LPTSTR pacCmdLine, int piShow)
{
	HANDLE hMutex = NULL;
	HMODULE hDLL;


	try
	{
		hMutex = CreateMutex(NULL, false, Application->Name.c_str());
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			if (clsUtil::MsgBox(NULL, ("There is one instace of " + Application->Name + " still running.\r\n\r\nDo you want to open another?").c_str(), _T("Still running"), MB_YESNO | MB_ICONQUESTION) == IDNO)
			{
				return (1);
			}
		}

		Screen->Cursor = crAppStart;
		SetProcessWorkingSetSize(GetCurrentProcess(), UINT_MAX, UINT_MAX);	//GS:AGGRESSIVE
		SetMinimumBlockAlignment(mba16Byte);

        // Disable file system redirection on Win64 environments
        hDLL = LoadLibrary(_T("KERNEL32.DLL"));
		if (hLL)
		{
			typedef BOOL (WINAPI Wow64DisableWow64FsRedirectionType)(PVOID *);
			Wow64DisableWow64FsRedirectionType *Wow64DisableWow64FsRedirectionProc = (Wow64DisableWow64FsRedirectionType *) GetProcAddress(hDLL, "Wow64DisableWow64FsRedirection");
			if (Wow64DisableWow64FsRedirectionProc)
			{
				PVOID pOldWin64Redirect;
				Wow64DisableWow64FsRedirectionProc(&pOldWin64Redirect);
			}
			FreeLibrary(hDLL);
		}

		// Enable drag and drop between non-elevated processes and elevated ones in Vista and later
		hDLL = LoadLibrary(_T("USER32.DLL"));
		if (hDLL)
		{
			typedef BOOL (WINAPI ChangeWindowMessageFilterType)(UINT, DWORD);
			ChangeWindowMessageFilterType *ChangeWindowMessageFilterProc = (ChangeWindowMessageFilterType *) GetProcAddress(hDLL, "ChangeWindowMessageFilter");
			if (ChangeWindowMessageFilterProc)
			{
				ChangeWindowMessageFilterProc(WM_DROPFILES, MSGFLT_ADD);
				ChangeWindowMessageFilterProc(WM_COPYDATA, MSGFLT_ADD);
				ChangeWindowMessageFilterProc(0x0049, MSGFLT_ADD);
			}
			FreeLibrary(hDLL);
		}

		Application->Initialize();
		Application->Name = "FileOptimizer";
		Application->Title = Application->Name;
		Application->HelpFile = Application->Name + ".chm";
		Application->MainFormOnTaskBar = true;

		TStyleManager::TrySetStyle("Windows10");
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Screen->Cursor = crDefault;
		Application->Run();
	}
	catch (Exception &excE)
	{
		Application->ShowException(&excE);
	}

	if (hMutex)
	{
		CloseHandle(hMutex);
	}
	return (0);
}
