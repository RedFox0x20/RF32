OUTPUT_FORMAT("binary")
OUTPUT_ARCH(i386)

SECTIONS
{
	. = 0x2700;
	.text : 
	{
		Build/Kernel/KEntry.asm.o(*.text)
	}
	.data :
	{
		Build/Kernel/KEntry.asm.o(*.data)
	}
	.text :
	{
		*(*.text)
	}
	.data :
	{
		*(*.data)
	}
}
