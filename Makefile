.PHONY: all

OS_DISK_IMAGE:=Build/RF32.img

all: Bootloader Image

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
	@dd if=SampleData.txt   \
		of=${OS_DISK_IMAGE} \
		bs=512              \
		seek=1

Bootloader: Bootloader_Stage1

Bootloader_Stage1: Source/Bootloader/Stage1.asm
	nasm -fbin $< -o Build/Bootloader_Stage1.bin

