OBJS = \
	console.o\
	main.o\
	trapasm.o\
	trap.o\
	vectors.o\
	vm.o\

CFLAGS = -m32 -g -c -fno-pic -ffreestanding
ASFLAGS = -m32

all: kernel.img

bootblock: bootasm.S bootmain.c sign
	cc -m32 -g -c bootasm.S
	cc -m32 -g -fno-builtin -fno-pic -fno-stack-protector -nostdinc -Os -c bootmain.c
	ld -N -e start -Ttext 0x7c00 -m elf_i386 -o bootblock.o bootasm.o bootmain.o
	objdump -S bootblock.o > bootblock.asm
	objcopy -S -O binary -j .text bootblock.o bootblock
	./sign $@

kernel: $(OBJS) entry.o
	ld -m elf_i386 -Ttext 0x100000 entry.o $(OBJS) -o kernel
	objdump -SD $@ >$@.asm

kernel.img: bootblock kernel
	dd if=/dev/zero of=kernel.img count=10000
	dd if=bootblock of=kernel.img conv=notrunc
	dd if=kernel of=kernel.img seek=1 conv=notrunc

vectors.S: vectors
	./vectors > vectors.S

sign: ../../../tools/sign.c
	cc $< -o $@

vectors: ../../../tools/vectors.c
	cc $< -o $@

qemu-kernel:	kernel
	DISPLAY=:0 qemu-system-i386 -kernel kernel -monitor stdio

qemu: kernel.img
	DISPLAY=:0 qemu-system-i386 -drive file=$<,format=raw -monitor stdio

clean:
	rm -rf *.img *.o *.asm bootblock kernel sign vectors vectors.S
