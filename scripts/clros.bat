@echo off
:: msbuild should be in PATH (we can't look for it)
msbuild MK2.sln /p:Configuration=Main /p:Platform=x64 -t:clean -maxcpucount:4
rd /s /q x64
rd /s /q emulboot
rd /s /q ovmf
goto :eof