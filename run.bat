@echo off
set INITRD=%~1
if exist %INITRD% set INITRD=%cd%\%~1
curl -Lo OVMF_X64.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd
mkdir dist
cd dist
curl -Lo BOOTX64.EFI https://gitlab.com/bztsrc/bootboot/raw/master/dist/bootboot.efi
mkdir EFI
cd EFI
mkdir BOOT
cd ..
copy BOOTX64.EFI EFI\BOOT\
mkdir BOOTBOOT
cd BOOTBOOT
copy %INITRD% initrd
cd ..
cd ..
qemu-system-x86_64.exe -M q35 -m 2G -net none -monitor none -parallel none -bios OVMF_X64.fd -hda fat:rw:dist