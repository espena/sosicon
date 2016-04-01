Name "sosicon"
Icon deploy\sosicon_installer.ico
OutFile "sosicon_v1.0_gui_setup_x86.exe"
InstallDir $PROGRAMFILES32\sosicon
RequestExecutionLevel admin
LicenseData deploy\license.txt

Page license
Page directory
Page instfiles

Section ""

  SetOutPath $INSTDIR

  	File deploy\sosicon.exe
	File deploy\Qt5Widgets.dll
	File deploy\Qt5Svg.dll
	File deploy\Qt5Gui.dll
	File deploy\Qt5Core.dll
	File deploy\opengl32sw.dll
	File deploy\D3Dcompiler_47.dll
	File deploy\libEGL.dll
	File deploy\libGLESV2.dll
	File deploy\msvcp120.dll
	File deploy\msvcr120.dll
	File deploy\vccorlib120.dll
	File deploy\sosicon_icon.ico

  SetOutPath $INSTDIR\platforms

  	File deploy\platforms\qwindows.dll

  CreateDirectory "$SMPROGRAMS\sosicon"
  CreateShortCut "$SMPROGRAMS\sosicon\SOSI File Converter.lnk" "$INSTDIR\sosicon.exe" "" "$INSTDIR\\sosicon_icon.ico" 0 SW_SHOWNORMAL ALT|CONTROL|SHIFT|F5 "sosicon.espenandersen.no"
  
SectionEnd