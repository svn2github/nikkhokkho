; -------------------------------------------------------------------------------------------------
SetCompressor /SOLID /FINAL lzma
SetCompressorDictSize 220
Unicode true


; -------------------------------------------------------------------------------------------------
!define APP_NAME 	"FileOptimizer"
!define APP_DESCRIPTION	"Lossless file size optimizer"
!define APP_COMPANY	"Javier Gutiérrez Chamorro (Guti)"
!define APP_COPYRIGHT	"© Copyright 2012-2018 by Javier Gutiérrez Chamorro (Guti)"
!define APP_WEB		"http://nikkhokkho.sourceforge.net/static.php?page=FileOptimizer"
!define APP_VERSION 	"13.2.0.0"


; -------------------------------------------------------------------------------------------------
!include "MUI.nsh"
!define MUI_ABORTWARNING
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English" ; The first language is the default language
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "SpanishInternational"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Korean"
!insertmacro MUI_LANGUAGE "Italian"
!insertmacro MUI_LANGUAGE "Dutch"
!insertmacro MUI_LANGUAGE "Danish"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Norwegian"
!insertmacro MUI_LANGUAGE "NorwegianNynorsk"
!insertmacro MUI_LANGUAGE "Finnish"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "PortugueseBR"
!insertmacro MUI_LANGUAGE "Polish"
!insertmacro MUI_LANGUAGE "Ukrainian"
!insertmacro MUI_LANGUAGE "Czech"
!insertmacro MUI_LANGUAGE "Slovak"
!insertmacro MUI_LANGUAGE "Croatian"
!insertmacro MUI_LANGUAGE "Bulgarian"
!insertmacro MUI_LANGUAGE "Hungarian"
!insertmacro MUI_LANGUAGE "Thai"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Latvian"
!insertmacro MUI_LANGUAGE "Macedonian"
!insertmacro MUI_LANGUAGE "Estonian"
!insertmacro MUI_LANGUAGE "Turkish"
!insertmacro MUI_LANGUAGE "Lithuanian"
!insertmacro MUI_LANGUAGE "Slovenian"
!insertmacro MUI_LANGUAGE "Serbian"
!insertmacro MUI_LANGUAGE "SerbianLatin"
!insertmacro MUI_LANGUAGE "Arabic"
!insertmacro MUI_LANGUAGE "Farsi"
!insertmacro MUI_LANGUAGE "Hebrew"
!insertmacro MUI_LANGUAGE "Indonesian"
!insertmacro MUI_LANGUAGE "Mongolian"
!insertmacro MUI_LANGUAGE "Luxembourgish"
!insertmacro MUI_LANGUAGE "Albanian"
!insertmacro MUI_LANGUAGE "Breton"
!insertmacro MUI_LANGUAGE "Belarusian"
!insertmacro MUI_LANGUAGE "Icelandic"
!insertmacro MUI_LANGUAGE "Malay"
!insertmacro MUI_LANGUAGE "Bosnian"
!insertmacro MUI_LANGUAGE "Kurdish"
!insertmacro MUI_LANGUAGE "Irish"
!insertmacro MUI_LANGUAGE "Uzbek"
!insertmacro MUI_LANGUAGE "Galician"
!insertmacro MUI_LANGUAGE "Afrikaans"
!insertmacro MUI_LANGUAGE "Catalan"
!insertmacro MUI_LANGUAGE "Esperanto"
!insertmacro MUI_LANGUAGE "Asturian"
!insertmacro MUI_LANGUAGE "Basque"
!insertmacro MUI_LANGUAGE "Pashto"
!insertmacro MUI_LANGUAGE "ScotsGaelic"
!insertmacro MUI_LANGUAGE "Georgian"
!insertmacro MUI_LANGUAGE "Vietnamese"
!insertmacro MUI_LANGUAGE "Welsh"
!insertmacro MUI_LANGUAGE "Armenian"
!insertmacro MUI_LANGUAGE "Corsican"
!insertmacro MUI_LANGUAGE "Tatar"

!include x64.nsh
!include "FileFunc.nsh"


; -------------------------------------------------------------------------------------------------
Icon "..\${APP_NAME}.ico"
;UninstallIcon "..\${APP_NAME}.ico"
OutFile "..\${APP_NAME}Setup.exe"
Name "${APP_NAME}"
InstallDir "$PROGRAMFILES\${APP_NAME}"
InstallDirRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "InstallDir"




; -------------------------------------------------------------------------------------------------
Function .onInit
	${GetParameters} $R0
	${GetOptionsS} $R0 "/AllUsers" $0
	IfErrors +2 0
		SetShellVarContext all
	ClearErrors

        ${If} ${RunningX64}
        	${EnableX64FSRedirection}
		StrCpy '$INSTDIR' "$PROGRAMFILES64\${APP_NAME}"
        ${EndIf}
FunctionEnd



; -------------------------------------------------------------------------------------------------
Section "Files"
	CreateDirectory "$SMPROGRAMS\${APP_NAME}"

	SetOutPath $INSTDIR
	File ..\Win32\Release\*.chm
	File ..\Win32\Release\*.po

	CreateDirectory "$SMPROGRAMS\${APP_NAME}";
	${If} ${RunningX64}
		File ..\Win32\Release\*64.exe
		SetOutPath $INSTDIR\Plugins64
		File /r ..\Win32\Release\Plugins64\*.*
		SetOutPath $INSTDIR
		CreateShortCut "$SMPROGRAMS\${APP_NAME}\Launch ${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$QUICKLAUNCH\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$SENDTO\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}64.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
	${Else}
		File ..\Win32\Release\*32.exe
		SetOutPath $INSTDIR\Plugins32
		File /r ..\Win32\Release\Plugins32\*.*
		SetOutPath $INSTDIR
		CreateShortCut "$SMPROGRAMS\${APP_NAME}\Launch ${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$QUICKLAUNCH\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
		CreateShortCut "$SENDTO\${APP_NAME}.lnk" "$INSTDIR\${APP_NAME}32.exe" "" "" "" SW_SHOWNORMAL "" "${APP_NAME}"
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
	RmDir /r "$INSTDIR"
	RmDir /r "$SMPROGRAMS\${APP_NAME}"
	Delete "$PROFILE\${APP_NAME}.ini"
	Delete "$PROFILE\${APP_NAME}32.ini"
	Delete "$PROFILE\${APP_NAME}64.ini"
	Delete "$PROFILE\${APP_NAME}.log"
	Delete "$PROFILE\${APP_NAME}32.log"
	Delete "$PROFILE\${APP_NAME}64.log"
	Delete "$DESKTOP\${APP_NAME}.lnk"
	Delete "$QUICKLAUNCH\${APP_NAME}.lnk"
	Delete "$SENDTO\${APP_NAME}.lnk"
	Delete "$FAVORITES\${APP_NAME} Home Page.lnk"
	DeleteRegKey HKCU "Software\${APP_NAME}"
	DeleteRegKey HKLM "Software\${APP_NAME}"
	DeleteRegKey HKCU "Software\Microsoft\Internet Explorer\Main\FeatureControl\FEATURE_BROWSER_EMULATION\${APP_NAME}32.exe"
	DeleteRegKey HKCU "Software\Microsoft\Internet Explorer\Main\FeatureControl\FEATURE_BROWSER_EMULATION\${APP_NAME}64.exe"
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