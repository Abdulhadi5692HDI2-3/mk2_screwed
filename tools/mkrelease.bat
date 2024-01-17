@echo off
set arch=%~1
set bldarch=%~2
where curl.exe > curlpath
set /p rcurl=<curlpath
set curl="%rcurl%"
del curlpath
if [%arch%]==[] call :fixvar
rd /s /q %CD%\%arch%
mkdir %CD%\%arch%

mkdir %CD%\%arch%\EFI

mkdir %CD%\%arch%\EFI\BOOT

copy %CD%\%bldarch%\Main\mk2load.efi %CD%\%arch%\EFI\BOOT\boot%bldarch%.efi
copy %CD%\%bldarch%\Release\krnl.exe %CD%\%arch%\krnl.exe

%curl% -Lo oscdimg.exe https://github.com/ntdevlabs/tiny11builder/raw/main/oscdimg.exe
oscdimg.exe -n -d -m %arch% %CD%\MK2.iso
del oscdimg.exe
exit /b %errorlevel%

:fixvar
set arch=amd64
set bldarch=x64
goto :eof