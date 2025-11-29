@echo off

REM - CALL "$(SolutionDir)scripts\postbuild-win.bat" "$(TargetExt)" "$(BINARY_NAME)" "$(Platform)" "$(COPY_VST2)" "$(TargetPath)" "$(VST2_32_PATH)" "$(VST2_64_PATH)" "$(VST3_32_PATH)" "$(VST3_64_PATH)" "$(AAX_32_PATH)" "$(AAX_64_PATH)" "$(BUILD_DIR)" "$(VST_ICON)" "$(AAX_ICON)" "$(CREATE_BUNDLE_SCRIPT)"

set FORMAT=%~1
set NAME=%~2
set PLATFORM=%~3
set COPY_VST2=%~4
set BUILT_BINARY=%~5
set VST2_32_PATH=%~6
set VST2_64_PATH=%~7 
set VST3_32_PATH=%~8
set VST3_64_PATH=%~9

REM Shift to access parameters 10-15
shift
shift 
shift
shift
shift 
shift
shift
shift
shift

REM AAX variables disabled - not needed
REM set AAX_32_PATH=%~1
REM set AAX_64_PATH=%~2
set BUILD_DIR=%~1
set VST_ICON=%~2
REM set AAX_ICON=%~3
set CREATE_BUNDLE_SCRIPT=%~4

echo POSTBUILD SCRIPT VARIABLES -----------------------------------------------------
echo FORMAT %FORMAT% 
echo NAME %NAME% 
echo PLATFORM %PLATFORM% 
echo COPY_VST2 %COPY_VST2% 
echo BUILT_BINARY %BUILT_BINARY% 
echo VST2_32_PATH %VST2_32_PATH% 
echo VST2_64_PATH %VST2_64_PATH% 
echo VST3_32_PATH %VST3_32_PATH% 
echo VST3_64_PATH %VST3_64_PATH% 
echo BUILD_DIR %BUILD_DIR%
echo VST_ICON %VST_ICON% 
REM echo AAX_ICON %AAX_ICON% 
echo CREATE_BUNDLE_SCRIPT %CREATE_BUNDLE_SCRIPT%
echo END POSTBUILD SCRIPT VARIABLES -----------------------------------------------------

if %PLATFORM% == "Win32" (
  if %FORMAT% == ".exe" (
    copy /y %BUILT_BINARY% %BUILD_DIR%\%NAME%_%PLATFORM%.exe
  )

  if %FORMAT% == ".dll" (
    copy /y %BUILT_BINARY% %BUILD_DIR%\%NAME%_%PLATFORM%.dll
  )
  
  if %FORMAT% == ".dll" (
    if %COPY_VST2% == "1" (
      echo copying 32bit binary to 32bit VST2 Plugins folder ... 
      copy /y %BUILT_BINARY% %VST2_32_PATH%
    ) else (
      echo not copying 32bit VST2 binary
    )
  )
  
  if %FORMAT% == ".vst3" (
    echo copying 32bit binary to VST3 BUNDLE ..
    call "%CREATE_BUNDLE_SCRIPT%" "%BUILD_DIR%\%NAME%.vst3" "%VST_ICON%" %FORMAT%
    copy /y %BUILT_BINARY% "%BUILD_DIR%\%NAME%.vst3\Contents\x86-win"
    if exist "%VST3_32_PATH%" ( 
      echo copying VST3 bundle to 32bit VST3 Plugins folder ...
      call "%CREATE_BUNDLE_SCRIPT%" "%VST3_32_PATH%\%NAME%.vst3" "%VST_ICON%" %FORMAT%
      xcopy /E /H /Y "%BUILD_DIR%\%NAME%.vst3\Contents\*"  "%VST3_32_PATH%\%NAME%.vst3\Contents\"
    )
  )
)

if %PLATFORM% == "x64" (
  if not exist "%ProgramFiles(x86)%" (
    echo "This batch script fails on 32 bit windows... edit accordingly"
  )

  if %FORMAT% == ".exe" (
    copy /y %BUILT_BINARY% "%BUILD_DIR%\%NAME%_%PLATFORM%.exe"
  )

  if %FORMAT% == ".dll" (
    copy /y %BUILT_BINARY% "%BUILD_DIR%\%NAME%_%PLATFORM%.dll"
  )
  
  if %FORMAT% == ".dll" (
    if %COPY_VST2% == "1" (
      echo copying 64bit binary to 64bit VST2 Plugins folder ... 
      copy /y %BUILT_BINARY% "%VST2_64_PATH%"
    ) else (
      echo not copying 64bit VST2 binary
    )
  )
  
  if %FORMAT% == ".vst3" (
    echo copying 64bit binary to VST3 BUNDLE ...
    call "%CREATE_BUNDLE_SCRIPT%" "%BUILD_DIR%\%NAME%.vst3" "%VST_ICON%" %FORMAT%
    copy /y %BUILT_BINARY% "%BUILD_DIR%\%NAME%.vst3\Contents\x86_64-win"
    if exist "%VST3_64_PATH%" (
      echo copying VST3 bundle to 64bit VST3 Plugins folder ...
      call "%CREATE_BUNDLE_SCRIPT%" "%VST3_64_PATH%\%NAME%.vst3" "%VST_ICON%" %FORMAT%
      xcopy /E /H /Y "%BUILD_DIR%\%NAME%.vst3\Contents\*"  "%VST3_64_PATH%\%NAME%.vst3\Contents\"
    )
  )
)