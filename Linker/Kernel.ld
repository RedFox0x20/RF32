OUTPUT_FORMAT("binary")
OUTPUT_ARCH(i386)

SECTIONS
{
	. = 0x2700;
	.text : 
	{
		Build/KEntry.o(*.text)
	}
	.data :
	{
		Build/KEntry.o(*.data)
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
