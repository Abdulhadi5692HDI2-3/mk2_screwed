@echo off
cd %~dp0
@set _MISSILE_SCRIPT_ENV=1
@set _X86_DIR=%~dp0x86
@set _NMICRO_DIR=%_X86_DIR%\nmicro
@set _TOOLS_DIR=%~dp0
@set _MASM615_DIR=%_X86_DIR%\MASM615
path %_TOOLS_DIR%;%_X86_DIR%;%_NMICRO_DIR%;%_MASM615_DIR%\BIN\;%_X86_DIR%\VS2022_BUILDTOOLS;%PATH%
cd..
if not exist developer\privenv.bat goto :setupenv
call "developer\privenv.bat"
title MK2 BUILD ENVIRONMENT - Running in %CD%
set username=%username%
echo Current user is now: %username%
goto :eof


:setupenv
@(
ECHO @ECHO OFF
ECHO :: Add any environment variables here such as your favourite editor
ECHO :: or virtual machine software
ECHO.
ECHO :: Examples:
ECHO REM SET "EDITOR=C:\Program Files\Notepad++\notepad++.exe"
ECHO REM SET "VM=C:\Program Files\qemu\qemu-system-i386.exe"
ECHO SET "BUILDMACHINE=^%COMPUTERNAME^%"

)>developer\privenv.bat
goto :eof

:eof :: END OF FILE