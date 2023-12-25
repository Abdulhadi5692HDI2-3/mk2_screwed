CFLAGS = -Wall -fpic -ffreestanding -fno-stack-protector -nostdlib -Ibase/inc -Iexternal/
LDFLAGS =  -nostdlib -n -T link.ld
STRIPFLAGS =  -s -K mmio -K fb -K bootboot -K environment -K initstack
INITRD = initrd.tar
7Z = tools/7z.exe

all: mk2krnlos.x86_64.elf

run: mk2krnlos.x86_64.elf
	$(7Z) a -ttar $(INITRD) $<
	cmd /k run.bat $(INITRD)
mk2krnlos.x86_64.elf:
	x86_64-elf-gcc $(CFLAGS) -mno-red-zone -c base/mk2os/mk2krnlos.c -o mk2krnlos.o
	x86_64-elf-gcc $(CFLAGS) -mno-red-zone -c base/mk2os/ioasm.c -o ioasm.o
	x86_64-elf-gcc $(CFLAGS) -mno-red-zone -c base/mk2os/serial.c -o serial.o
	x86_64-elf-gcc $(CFLAGS) -mno-red-zone -c base/mk2os/console.c -o console.o
	x86_64-elf-gcc $(CFLAGS) -mno-red-zone -c external/printf.c -o printf.o
	x86_64-elf-ld $(LDFLAGS) mk2krnlos.o ioasm.o serial.o console.o printf.o -o mk2krnlos.x86_64.elf
	x86_64-elf-strip $(STRIPFLAGS) mk2krnlos.x86_64.elf

clean: clean.windows

clean.windows:
	cmd /k clean.bat