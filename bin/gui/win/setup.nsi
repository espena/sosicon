Name "sosicon"
Icon deploy\sosicon.ico
OutFile "sosicon_v1.0_gui_setup.exe"
InstallDir $PROGRAMFILES\sosicon
RequestExecutionLevel admin

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

  SetOutPath $INSTDIR\platforms

  	File deploy\platforms\qwindows.dll
  
SectionEnd