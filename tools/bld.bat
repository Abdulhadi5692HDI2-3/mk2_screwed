@echo off
set BUILDA=1000
:: generate a header
@(
echo #pragma once
echo #include "../external/mk2/MK2.Utils.h"
echo #define BUILDNUM %BUILDA%
echo #define BUILD_DATE_TIME "%DATE% AT %TIME%"
echo #define BUILD_DATE_TIMEW _WIDESTR^("%DATE% AT %TIME%"^)
)>%cd%\incgen\mk2ver.h

:: msbuild should be in PATH (we can't look for it)
echo [BULD START AT %TIME% ON %DATE%]
echo Compiling MK2 Build %BUILDA%
msbuild MK2.sln /p:Configuration=Main /p:Platform=x64 -t:build -maxcpucount:4
echo [BULD END AT %TIME% ON %DATE%]
goto :eof