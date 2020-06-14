all: kernel.img

bootblock: bootasm.S bootmain.c sign
	cc -m32 -g -c bootasm.S
	cc -m32 -g -fno-builtin -fno-pic -fno-stack-protector -nostdinc -Os -c bootmain.c
	ld -N -e start -Ttext=0x7c00 -m elf_i386 -o bootblock.o bootasm.o bootmain.o
	objdump -S bootblock.o > bootblock.asm
	objcopy -S -O binary -j .text bootblock.o bootblock
	./sign $@

kernel: kernel.c
	cc -g -c -m32 -fno-pic -ffreestanding kernel.c -o kernel.o
	ld -m elf_i386 -e kernel_main -Ttext=0x100000 kernel.o -o kernel
	objdump -SD $@ >$@.asm

kernel.img: bootblock kernel
	dd if=/dev/zero of=kernel.img count=10000
	dd if=bootblock of=kernel.img conv=notrunc
	dd if=kernel of=kernel.img seek=1 conv=notrunc

sign: ../../tools/sign.c
	cc $< -o $@

qemu-kernel:	kernel
	DISPLAY=:0 qemu-system-i386 -kernel kernel -monitor stdio

qemu: kernel.img
	DISPLAY=:0 qemu-system-i386 -drive file=$<,format=raw -monitor stdio

clean:
	rm -rf *.img *.o *.asm bootblock kernel sign
