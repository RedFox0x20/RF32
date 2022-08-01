.PHONY: all

# CONFIG
CC:=gcc
CCFLAGS:=-fno-pic -nostdlib -nolibc -ffreestanding -c -Wall -m32 -ISource

ASM:=nasm

LD:=ld

# BUILD PATHS
OS_DISK_IMAGE:=Build/RF32.img
BOOTLOADER_SOURCE:=$(wildcard Source/Bootloader/*.asm)
BOOTLOADER_OBJECTS:=$(addsuffix .bin, \
						$(patsubst Source%, Build%, $(BOOTLOADER_SOURCE)))
KERNEL_SOURCE:=$(wildcard Source/Kernel/*.asm) $(wildcard Source/Kernel/*.c)
KERNEL_OBJECTS:=$(addsuffix .o, $(patsubst Source%, Build%, $(KERNEL_SOURCE)))
KERNEL_LINKED:=Build/Kernel.bin
KERNEL_LINKER_SCRIPT:=Linker/Kernel.ld

# DEFAULT
all: Dirs Bootloader Kernel Image

# RUNNERS
run: all run_nobuild

run_nobuild:
	qemu-system-i386 -fda ${OS_DISK_IMAGE}

debug: all debug_nobuild

debug_nobuild:
	qemu-system-i386 -fda $(OS_DISK_IMAGE) -s -S --monitor stdio 

# Build/
clean:
	@rm -rf Build

Dirs:
	@mkdir -p Build Build/Bootloader Build/Kernel

# IMAGE BUILDER
Image:
	@echo -e "\nCreating blank disk image ${OS_DISK_IMAGE}"
	@dd if=/dev/zero \
		of=${OS_DISK_IMAGE} \
		bs=512 \
		count=2880 
	@echo -e "\nWriting Bootsector"
	@dd if=Build/Bootloader/Stage1.asm.bin \
	   of=${OS_DISK_IMAGE} \
	   bs=512 
	@dd if=Build/Bootloader/Stage2.asm.bin \
		of=${OS_DISK_IMAGE} \
		bs=512              \
		seek=1
	@dd if=Build/Kernel.bin \
		of=${OS_DISK_IMAGE} \
		bs=512 \
		seek=2

# BOOTLOADER
Bootloader: $(BOOTLOADER_OBJECTS) 

Build/Bootloader/%.asm.bin: Source/Bootloader/%.asm
	${ASM} -fbin $< -o $@

# KERNEL
Kernel: $(KERNEL_OBJECTS) 
	${LD} -T${KERNEL_LINKER_SCRIPT} \
		-o ${KERNEL_LINKED} ${KERNEL_OBJECTS}

Build/Kernel/%.c.o: Source/Kernel/%.c
	${CC} ${CCFLAGS} $< -o $@

Build/Kernel/%.asm.o: Source/Kernel/%.asm
	${ASM} -felf32 $< -o $@
