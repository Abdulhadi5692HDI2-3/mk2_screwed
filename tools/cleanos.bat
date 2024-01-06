@echo off
:: msbuild pls be in path
msbuild MK2.sln /p:Platform=x64 /p:Configuration=Debug -t:clean -maxcpucount:1
goto :eof