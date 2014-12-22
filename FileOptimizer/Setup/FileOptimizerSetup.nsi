; -------------------------------------------------------------------------------------------------
SetCompressor /SOLID /FINAL lzma 
SetCompressorDictSize 128
Unicode true



; -------------------------------------------------------------------------------------------------
!include "MUI.nsh"
!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"
!include x64.nsh



; -------------------------------------------------------------------------------------------------
!define APP_NAME 	"FileOptimizer"
!define APP_DESCRIPTION	"Lossless file size optimizer"
!define APP_COMPANY	"Javier Gutiérrez Chamorro (Guti)"
!define APP_COPYRIGHT	"© Copyright 2012-2015 by Javier Gutiérrez Chamorro (Guti)"
!define APP_WEB		"http://nikkhokkho.sourceforge.net/static.php?page=FileOptimizer"
!define APP_VERSION 	"7.0.0.0"



; -------------------------------------------------------------------------------------------------
Icon "..\${APP_NAME}.ico"
;UninstallIcon "..\${APP_NAME}.ico"
OutFile "..\${APP_NAME}Setup.exe"
Name "${APP_NAME}"
InstallDir "$PROGRAMFILES\${APP_NAME}"
InstallDirRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "InstallDir"



; -------------------------------------------------------------------------------------------------
Function .onInit
        ${If} ${RunningX64}
        	${EnableX64FSRedirection}
		StrCpy '$INSTDIR' "$PROGRAMFILES64\${APP_NAME}"
        ${EndIf}
FunctionEnd



; -------------------------------------------------------------------------------------------------
Section "Files"
	CreateDirectory "$SMPROGRAMS\FileOptimizer"

	SetOutPath $INSTDIR
	File ..\Win32\Release\*.chm
	CreateDirectory "$SMPROGRAMS\${APP_NAME}";
	${If} ${RunningX64}
		File ..\Win32\Release\*64.exe
		SetOutPath $INSTDIR\Plugins64
		File /r ..\Win32\Release\Plugins64\*.*
		CreateShortCut "$SMPROGRAMS\${APP_NAME}\Launch ${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$QUICKLAUNCH\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
	${Else}
		File ..\Win32\Release\*32.exe
		SetOutPath $INSTDIR\Plugins32
		File /r ..\Win32\Release\Plugins32\*.*
		CreateShortCut "$SMPROGRAMS\${APP_NAME}\Launch ${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME} x86"
		CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME} x86"
		CreateShortCut "$QUICKLAUNCH\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME} x86"
	${EndIf}

	WriteUninstaller "$INSTDIR\Uninstall.exe"

	CreateShortCut "$SMPROGRAMS\${APP_NAME}\Help.lnk" "$INSTDIR\${APP_NAME}.chm" "" "" "" SW_SHOWNORMAL "" "${APP_NAME} Help"
	CreateShortCut "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "" "" SW_SHOWNORMAL "" "Uninstall ${APP_NAME}"
	CreateShortCut "$FAVORITES\${APP_NAME} Home Page.lnk" "${APP_WEB}" "" "" "" "" "" "${APP_NAME} Home Page"

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayName" "${APP_NAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "Publisher" "${APP_COMPANY}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayVersion" "${APP_VERSION}"

	${If} ${RunningX64}
		WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayIcon" "$\"$INSTDIR\${APP_NAME}64.exe$\""
	${Else}
		WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayIcon" "$\"$INSTDIR\${APP_NAME}32.exe$\""
	${EndIf}

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "ProductID" "${APP_NAME} ${APP_VERSION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "RegCompany" "${APP_COMPANY}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "RegOwner" "${APP_COPYRIGHT}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "URLInfoAbout" "${APP_WEB}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "URLUpdateInfo" "${APP_WEB}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "HelpLink" "${APP_WEB}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "Comments" "${APP_DESCRIPTION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "InstallDir" "($INSTDIR)"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "NoModify" "1"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "NoRepair" "1"
 	!include "FileFunc.nsh"
	${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
	IntFmt $0 "0x%08X" $0
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "EstimatedSize" "$0"
SectionEnd



; -------------------------------------------------------------------------------------------------
Section "Uninstall"
	RMDir /r "$INSTDIR"
	RmDir /r "$SMPROGRAMS\${APP_NAME}"
	Delete "$PROFILE\${APP_NAME}.ini"
	Delete "$DESKTOP\${APP_NAME}.lnk"
	Delete "$QUICKLAUNCH\${APP_NAME}.lnk"
	Delete "$FAVORITES\${APP_NAME} Home Page.lnk"
	DeleteRegKey HKCU "Software\${APP_NAME}"	;Not needed because we do not write on the registry.
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"
SectionEnd



; -------------------------------------------------------------------------------------------------
VIProductVersion "${APP_VERSION}"
	VIAddVersionKey "ProductName" "${APP_NAME}"
	VIAddVersionKey "InternalName" "${APP_NAME}.exe"
	VIAddVersionKey "Comments" "Get more info at ${APP_WEB}"
	VIAddVersionKey "CompanyName" "${APP_COMPANY}"
	VIAddVersionKey "LegalTrademarks" "${APP_COPYRIGHT}"
	VIAddVersionKey "LegalCopyright" "${APP_COPYRIGHT}"
	VIAddVersionKey "FileDescription" "${APP_DESCRIPTION}"
	VIAddVersionKey "FileVersion" "${APP_VERSION}"