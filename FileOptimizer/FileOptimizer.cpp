// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"
#include <limits.h>
#include "cppMain.h"
#include "clsUtil.h"


// ---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>


//---------------------------------------------------------------------------
USEFORM("Source\cppAbout.cpp", frmAbout);
USEFORM("Source\cppOptions.cpp", frmOptions);
USEFORM("Source\cppMain.cpp", frmMain);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE phInstance, HINSTANCE phPrevInstance, LPTSTR pacCmdLine, int piShow)
{
	HANDLE hMutex = NULL;


	try
	{
		//Simple command line help
		if (_tcsnccmp(pacCmdLine, _T("/?"), 2) == 0)
		{
			clsUtil::MsgBox(NULL, _T(
				"FileOptimizer command line syntax is:\n"
				"FileOptimizer.exe <Path|File> [/Options]\n\n"
				"<Path|File>: Specifies a path to recursively process or a single file. You can specify as much Files/Paths as you want. Paths with extended characters, or spaces, should be double quoted. Such as *.JPG \"C:\\PROYECTOS\\\" C:\\TEST.PNG\n\n"
				"[/Options]: Optionally you can specify any options, using same syntax as in the INI file, prepending them with a slash. Such as /GIFAllowLossy=true /Level=9 /PDFCustomDPI=150 /ExcludeMask=.bak\n\n"
				"Arguments work like:\n\n"
				"C:\\PROYECTOS\\FileOptimizer\\Win32\\Release\\FileOptimizer64.exe /PNGCopyMetadata=true \"C:\\PROYECTOS\\FileOptimizer\\_Tests\\_ - copia\"\n\n"
				"Where:\n\n"
				"- /PNGCopyMetadata=false: Activate copying PNG metadata.\n"
				"- \"C:\\PROYECTOS\\FileOptimizer\\Win32\\Release\\FileOptimizer64.exe: Is the full path where FileOptimizer executable is.\n"
				"- \"C:\\PROYECTOS\\FileOptimizer\\_Tests\\_ - copia\\\": Is the full path of the folder to recursively process. Be aware enclosing it with double quotes as in the example, which is Windows mandatory if the folder contains spaces, or extended characters.\n\n"
				"Alternatively you can specify only one single file instead of a folder:\n\n"
				"C:\\PROYECTOS\\FileOptimizer\\Win32\\Release\\FileOptimizer64.exe \"C:\\PROYECTOS\\FileOptimizer\\_Tests\\_ - copia\\av-214_.zip\"\n\n"
				"Where:\n\n"
				"- \"C:\\PROYECTOS\\FileOptimizer\\Win32\\Release\\FileOptimizer64.exe: Is the full path where FileOptimizer executable is.\n"
				"- \"C:\\PROYECTOS\\FileOptimizer\\_Tests\\_ - copia\\av-214_.zip\": Is the full path of the file to process."
			), _T("Command-line help"), MB_OK | MB_ICONINFORMATION);
			return(-1);
		}
		
		#if defined( _DEBUG)
			ReportMemoryLeaksOnShutdown = true;
		#endif
		SetProcessWorkingSetSize(GetCurrentProcess(), UINT_MAX, UINT_MAX);	//GS:AGGRESSIVE
		SetMinimumBlockAlignment(mba16Byte);
	
		Application->Initialize();
		Application->Name = "FileOptimizer";
		Application->Title = Application->Name;
		Application->HelpFile = Application->Name + ".chm";
		Application->MainFormOnTaskBar = true;

		if (!TfrmMain::GetOption(_T("Options"), _T("AllowMultipleInstances"), false))
		{
			hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, Application->Name.c_str());
			if (!hMutex)
			{
				hMutex = CreateMutex(NULL, false, Application->Name.c_str());
			}
			else
			{
				if (clsUtil::MsgBox(NULL, ("There is one instance of " + Application->Name + " still running.\r\n\r\nDo you want to open another?").c_str(), _T("Still running"), MB_YESNO | MB_ICONQUESTION) == IDNO)
				{
					return (1);
				}
			}
		}
		Screen->Cursor = crAppStart;
		// Disable file system redirection on Win64 environments
		HMODULE hKernel32 = LoadLibrary(_T("KERNEL32.DLL"));
		if (hKernel32)
		{
			typedef BOOL (WINAPI Wow64DisableWow64FsRedirectionType)(PVOID *);
			Wow64DisableWow64FsRedirectionType *Wow64DisableWow64FsRedirectionProc = (Wow64DisableWow64FsRedirectionType *) GetProcAddress(hKernel32, "Wow64DisableWow64FsRedirection");
			if (Wow64DisableWow64FsRedirectionProc)
			{
				PVOID pOldWin64Redirect;
				Wow64DisableWow64FsRedirectionProc(&pOldWin64Redirect);
			}
			FreeLibrary(hKernel32);
		}

		// Enable drag and drop between non-elevated processes and elevated ones in Vista and later
		HMODULE hUser32 = LoadLibrary(_T("USER32.DLL"));
		if (hUser32)
		{
			typedef BOOL (WINAPI ChangeWindowMessageFilterType)(UINT, DWORD);
			ChangeWindowMessageFilterType *ChangeWindowMessageFilterProc = (ChangeWindowMessageFilterType *) GetProcAddress(hUser32, "ChangeWindowMessageFilter");
			if (ChangeWindowMessageFilterProc)
			{
				ChangeWindowMessageFilterProc(WM_DROPFILES, MSGFLT_ADD);
				ChangeWindowMessageFilterProc(WM_COPYDATA, MSGFLT_ADD);
				ChangeWindowMessageFilterProc(0x0049, MSGFLT_ADD);
			}
			FreeLibrary(hUser32);
		}

		//TStyleManager::TrySetStyle("Windows");
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
		ReleaseMutex(hMutex);
	}
	return (0);
}
