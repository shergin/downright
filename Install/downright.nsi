;Include Modern UI

	!include "MUI.nsh"

;General
	;Name and file
	Name "Downright blackrain (g3v8)"
	OutFile "downright.exe"

	;Default installation folder
	InstallDir "$PROGRAMFILES\Shergin lab\Downright blackrain"
  
	;Get installation folder from registry if available
	InstallDirRegKey HKCU "Software\Shergin lab\Downright" ""

;--------------------------------
;Interface Settings

	!define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings

	;Remember the installer language
	!define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
	!define MUI_LANGDLL_REGISTRY_KEY "Software\Shergin lab\Downright\Installer" 
	!define MUI_LANGDLL_REGISTRY_VALUENAME "InstallerLanguage"

;--------------------------------
;Pages

	!insertmacro MUI_PAGE_LICENSE "..\Install\License.txt"
;	!insertmacro MUI_PAGE_COMPONENTS
	!insertmacro MUI_PAGE_DIRECTORY
	!insertmacro MUI_PAGE_INSTFILES
  
	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

	!insertmacro MUI_LANGUAGE "English"
	!insertmacro MUI_LANGUAGE "Russian"


LangString SectionLanguageName ${LANG_RUSSIAN} "Локализованные жесты"
LangString SectionLanguageName ${LANG_ENGLISH} "Localization gesture"

LangString SectionOneName ${LANG_RUSSIAN} "Downright blackrain"
LangString SectionOneName ${LANG_ENGLISH} "Downright blackrain"

LangString SectionTwoName ${LANG_RUSSIAN} "Ярлыки в меню Пуск"
LangString SectionTwoName ${LANG_ENGLISH} "Start Menu shortcuts"

LangString SectionThreeName ${LANG_RUSSIAN} "Запускать вместе с Windows"
LangString SectionThreeName ${LANG_ENGLISH} "Start with Windows"

LangString SectionOneDescription ${LANG_RUSSIAN} "Главный программный компонент"
LangString SectionOneDescription ${LANG_ENGLISH} "Main program module"


;--------------------------------
;Reserve Files
  
	;These files should be inserted before other files in the data block
	;Keep these lines before any File command
	;Only for solid compression (by default, solid compression is enabled for BZIP2 and LZMA)
  
	!insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Sections

Section !$(SectionOneName) SectionOne
	SectionIn RO
	SetOutPath "$INSTDIR"

	File "..\Release\Downright.exe"
	File "..\Release\Mirror.dll"
	File "..\Gestures\russian.downright"

	SetOutPath "$INSTDIR\Languages"
	File "..\Languages\russian.lng"
	File "..\Languages\english.lng"
	
	SetOutPath "$INSTDIR\Help"
	File "..\Help\russian_help.htm"

	;Store installation folder
	WriteRegStr HKCU "Software\Shergin lab\Downright\General" "ProgramDirectory" $INSTDIR
	WriteRegStr HKCU "Software\Shergin lab\Downright\General" "FileName" "$INSTDIR\russian.downright"
	WriteRegStr HKCU "Software\Shergin lab\Downright\General" "Language" "Russian"
	
	;Start with windows
	DeleteRegValue HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Downright"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Downright" "$INSTDIR\downright.exe"
	
	;Create uninstaller
	WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Installer Functions

Function .onInit
	!insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd


SubSection $(SectionLanguageName)
SubSectionEnd
	Section $(SectionTwoName) SectionTwo
		CreateDirectory "$SMPROGRAMS\Downright blackrain"
		CreateShortCut "$SMPROGRAMS\Downright blackrain\Downright blackrain.lnk" "$INSTDIR\Downright.exe" "" "$INSTDIR\Downright.exe" 0
		CreateShortCut "$SMPROGRAMS\Downright blackrain\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
		CreateShortCut "$SMPROGRAMS\Downright blackrain\downright.shergin.com.lnk" "http://downright.shergin.com"
	SectionEnd

Section $(SectionThreeName) SectionThree
	;CreateDirectory "$SMPROGRAMS\Downright blackrain"
	;CreateShortCut "$SMPROGRAMS\Downright blackrain\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
	;CreateShortCut "$SMPROGRAMS\Downright blackrain\Downright blackrain.lnk" "$INSTDIR\Downright.exe" "" "$INSTDIR\Downright.exe" 0
SectionEnd

;--------------------------------
;Descriptions

	;USE A LANGUAGE STRING IF YOU WANT YOUR DESCRIPTIONS TO BE LANGAUGE SPECIFIC

	;Assign descriptions to sections
;	!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
;		!insertmacro MUI_DESCRIPTION_TEXT ${SectionOne} $(SectionOneDescription)
;		!insertmacro MUI_DESCRIPTION_TEXT ${SectionTwo} "Start Menu Shortcuts."
;		!insertmacro MUI_DESCRIPTION_TEXT ${SectionThree} "Start Menu Shortcuts."
;	!insertmacro MUI_FUNCTION_DESCRIPTION_END

 
 


 
 
 
 
 
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"

	Delete "$INSTDIR\Downright.exe"
	Delete "$INSTDIR\Mirror.dll"
	Delete "$INSTDIR\Uninstall.exe"
	RMDir "$INSTDIR"

	Delete "$SMPROGRAMS\Downright blackrain\*.*"
	RMDir "$SMPROGRAMS\Downright blackrain"

	DeleteRegKey /ifempty HKCU "Software\Shergin lab\Downright"

SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

	!insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd