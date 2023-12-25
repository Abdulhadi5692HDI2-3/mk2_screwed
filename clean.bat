if exist *.o del *.o
if exist *.elf del *.elf
if exist *.txt del *.txt
if exist *.fd del *.fd
if exist *.tar del *.tar
if exist dist rmdir /s /q dist
exit /b 0
exit