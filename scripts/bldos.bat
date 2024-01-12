@echo off
:: msbuild should be in PATH (we can't look for it)
msbuild MK2.sln /p:Configuration=Main /p:Platform=x64 -t:build -maxcpucount:4
goto :eof