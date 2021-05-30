OBJS = \
	console.o\
	main.o\
	picirq.o\
	trapasm.o\
	trap.o\
	vectors.o\
	vm.o\

CFLAGS = -m32 -g -c -fno-pic -ffreestanding
ASFLAGS = -m32

all: lowbos.iso

kernel.elf: entry.o $(OBJS)
	ld -m elf_i386 -Ttext 0x100000 $^ -o $@
	objdump -SD -Msuffix $@ > kernel.asm

lowbos.iso: kernel.elf mkiso.sh
	sh mkiso.sh $< $@

vectors.S: vectors
	./vectors > vectors.S

vectors: ../../../tools/vectors.c
	cc $< -o $@

run:	kernel.elf
	DISPLAY=:0 qemu-system-i386 -kernel $< -monitor stdio

run-iso: lowbos.iso
	DISPLAY=:0 qemu-system-i386 -boot d -cdrom $< -monitor stdio

clean:
	rm -rf iso *.iso *.elf *.o *.asm vectors vectors.S
