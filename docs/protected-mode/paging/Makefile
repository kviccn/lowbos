objects = boot.o kernel.o

kernel.elf: $(objects)
	ld -m elf_i386 -e entry -Ttext 0x100000 $^ -o $@
	objdump -S -Msuffix $@ > kernel.asm

%.o: %.c
	cc -m32 -c $<

%.o: %.S
	cc -m32 -c $<

run: kernel.elf
	DISPLAY=:0 qemu-system-i386 -kernel kernel.elf -monitor stdio

clean:
	rm -f *.elf *.o *.asm
