@echo off
@set _MISSILE_SCRIPT_ENV=1
@set _X86_DIR=%~dp0x86
@set _NMICRO_DIR=%_X86_DIR%\nmicro
@set _TOOLS_DIR=%~dp0
path %_X86_DIR%;%_TOOLS_DIR%;%_NMICRO_DIR%;%PATH%
cd..
title MK2 BUILD ENVIRONMENT - Running in %CD%
set username=%username%
echo Current user is now: %username%