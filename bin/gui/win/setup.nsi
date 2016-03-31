Name "sosicon"
Icon deploy\sosicon_setup.ico
OutFile "sosicon_v1.0_gui_setup.exe"
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
	File deploy\libwinpthread-1.dll
	File deploy\libstdc++-6.dll
	File deploy\libGLESV2.dll
	File deploy\libgcc_s_dw2-1.dll
	File deploy\libEGL.dll
	File deploy\sosicon_shortcut.ico

  SetOutPath $INSTDIR\platforms

  	File deploy\platforms\qwindows.dll

  CreateDirectory "$SMPROGRAMS\sosicon"
  CreateShortCut "$SMPROGRAMS\sosicon\sosicon.lnk" "$INSTDIR\sosicon.exe" "" "$INSTDIR\sosicon_shortcut.ico" 2 SW_SHOWNORMAL ALT|CONTROL|SHIFT|F5 "SOSI File Converter"
  
SectionEnd