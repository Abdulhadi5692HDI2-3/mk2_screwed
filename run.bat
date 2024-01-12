@echo off
:: check if curl and qemu are installed
where curl.exe > curlpath
where qemu-system-x86_64.exe > qemupath
set /p RCURL=<curlpath
set /p RQEMU=<qemupath
if [%RCURL%]==[] echo No curl.exe binary found! && exit /b 1
set CURL="%RCURL%"
set QEMU="%RQEMU%"
if [%QEMU%]==[""] echo No qemu-system-x86_64.exe binary found! && exit /b 1
del curlpath
del qemupath

:: Project should already be built
if not exist x64 echo ERROR: Project should already be built && exit /b 1

:: We need OVMF firmware for qemu first
mkdir ovmf
cd ovmf
:: Windows 10 has a good enough curl
%CURL% -Lo X64OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

:: Exit the ovmf dir
cd ..

:: Make directory (which will be emulated as a FAT disk by qemu)
mkdir emulos
mkdir emulos\EFI
mkdir emulos\EFI\BOOT

:: Copy bootloader
copy x64\Main\mk2load.efi emulos\EFI\BOOT\BOOTX64.EFI

:: Run the OS
%QEMU% -net none -monitor none -parallel none -L . -pflash ovmf\X64OVMF.fd -hda fat:rw:emulos