.PHONY: all

OS_DISK_IMAGE:=Build/RF32.img
CCFLAGS:=-fno-pic -nostdlib -nolibc -ffreestanding -c -Wall -m32

all: Bootloader Kernel Image

run:
	qemu-system-i386 -fda ${OS_DISK_IMAGE}

debug:
	qemu-system-i386 -fda $(OS_DISK_IMAGE) -s -S --monitor stdio 

Image:
	@echo -e "\nCreating blank disk image ${OS_DISK_IMAGE}"
	@dd if=/dev/zero \
	   of=${OS_DISK_IMAGE} \
	   bs=512 \
	   count=2880 
	@echo -e "\nWriting Bootsector"
	@dd if=Build/Bootloader_Stage1.bin \
	   of=${OS_DISK_IMAGE} \
	   bs=512 
	@dd if=Build/Bootloader_Stage2.bin \
		of=${OS_DISK_IMAGE} \
		bs=512              \
		seek=1
	@dd if=Build/Kernel.bin \
		   of=${OS_DISK_IMAGE} \
		   bs=512 \
		   seek=2

Bootloader: Bootloader_Stage1 Bootloader_Stage2

Bootloader_Stage1: Source/Bootloader/Stage1.asm
	nasm -fbin $< -o Build/Bootloader_Stage1.bin

Bootloader_Stage2: Source/Bootloader/Stage2.asm
	nasm -fbin $< -o Build/Bootloader_Stage2.bin

Kernel: KEntry KMain
	ld -TLinker/Kernel.ld \
		-o Build/Kernel.bin \
		Build/KEntry.o Build/KMain.o

KEntry: Source/Kernel/KEntry.asm
	nasm -felf32 $< -o Build/KEntry.o

KMain: Source/Kernel/Kernel.c
	gcc ${CCFLAGS} $< -o Build/KMain.o
