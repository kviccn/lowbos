boot.elf: boot.o
	ld -m elf_i386 -e entry -Ttext 0x100000 boot.o -o boot.elf
	objdump -S $@ > boot.asm

boot.o: boot.S
	cc -m32 -c boot.S

run: boot.elf
	DISPLAY=:0 qemu-system-i386 -kernel boot.elf -monitor stdio

clean:
	rm -f *.elf *.o *.asm
