@echo off
set TOOLSDIR=tools
set DD=%TOOLSDIR%\dd.exe
set BOOTDIR=base\boot
where nasm.exe > wherenasm
if %errorlevel%==1 echo error while finding nasm! && exit
where qemu-system-i386.exe > whereqemui386
if %errorlevel%==1 echo error while finding qemu! && exit
set /p NASMEXE=<wherenasm
set /p QEMUEXE=<whereqemui386
set NASM="%NASMEXE%"
set QEMU="%QEMUEXE%"
del wherenasm
del whereqemui386
%NASM% %BOOTDIR%\bootloader.asm -f bin -o boot.bin
%DD% if=boot.bin of=mk2.img bs=512 count=1
%QEMU% -fda mk2.img
goto :eof