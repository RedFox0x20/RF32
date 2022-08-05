/*
 * Interrupts.c
 */
#include <Kernel/System.h>

#define IDT_INTERRUPT_HANDLERS_COUNT 17
#define IDT_SYSCALL_INTERRUPT 16
#define IDT_ENTRY_COUNT 256

/*
 * IDT_Entry_t
 * The IDT is expected to use the following structure to map each interrupt
 * with the kernel defined handler
 */
typedef struct
{
	unsigned short OffsetLow;
	unsigned short Selector;
	unsigned char Reserved;
	unsigned char Attributes;
	unsigned short OffsetHigh;
} __attribute__((packed)) IDT_Entry_t;

/*
 * IDT_Ptr_t
 * The IDT is pointed to by an entry using this structure with the lidt
 * instruction.
 */
typedef struct
{
	unsigned short Limit;
	IDT_Entry_t *Ptr;
} __attribute__((packed)) IDT_Ptr_t;

static IDT_Entry_t IDT[IDT_ENTRY_COUNT];
static const IDT_Ptr_t IDT_Ptr = 
{
	.Limit = (sizeof(IDT_Entry_t) * IDT_ENTRY_COUNT)-1,
	.Ptr = IDT
};

void (*IDT_Handlers[IDT_INTERRUPT_HANDLERS_COUNT-1])(void);

/* Import our IDT methods Interrupts.asm */
extern void
	IDT_Interrupt0(void),
	IDT_Interrupt1(void),
	IDT_Interrupt2(void),
	IDT_Interrupt3(void),
	IDT_Interrupt4(void),
	IDT_Interrupt5(void),
	IDT_Interrupt6(void),
	IDT_Interrupt7(void),
	IDT_Interrupt8(void),
	IDT_Interrupt9(void),
	IDT_Interrupt10(void),
	IDT_Interrupt11(void),
	IDT_Interrupt12(void),
	IDT_Interrupt13(void),
	IDT_Interrupt14(void),
	IDT_Interrupt15(void),
	IDT_SyscallHandlerStub(void),
	IDT_SetIDT(const IDT_Ptr_t* Ptr);

static const void (*IDT_Interrupts[IDT_INTERRUPT_HANDLERS_COUNT-1]) = 
{
	IDT_Interrupt0,
	IDT_Interrupt1,
	IDT_Interrupt2,
	IDT_Interrupt3,
	IDT_Interrupt4,
	IDT_Interrupt5,
	IDT_Interrupt6,
	IDT_Interrupt7,
	IDT_Interrupt8,
	IDT_Interrupt9,
	IDT_Interrupt11,
	IDT_Interrupt12,
	IDT_Interrupt13,
	IDT_Interrupt14,
	IDT_Interrupt15
};

static void IDT_InitPIC(void)
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);
}

static IDT_Entry_t* IDT_SetEntry(unsigned int ID, void (*func)(void))
{
	if (ID < 32) { return 0; }
	
	IDT_Entry_t* Entry = &(IDT[ID]);
	Entry->OffsetLow = (unsigned short int)((unsigned long int)func & 0x0000FFFF);
	Entry->OffsetHigh = 
		(unsigned short int)((unsigned long int)func & 0xFFFF0000) >> 16;
	Entry->Reserved = 0;
	Entry->Attributes = 0x8E;
	Entry->Selector = 0x08;

	return Entry;

}

void IDT_Setup(void)
{
	unsigned int i;
	SYS_CLI();
	IDT_InitPIC();

	for (i = 0; i < IDT_INTERRUPT_HANDLERS_COUNT; i++)
	{
		IDT_Handlers[i] = 0;
	}

	for (i = 0; i < 32; i++)
	{
		IDT[i].OffsetLow = 0;
		IDT[i].OffsetHigh = 0;
		IDT[i].Reserved = 0;
		IDT[i].Selector = 0;
		IDT[i].Attributes = 0;
	}

	for (; i < 48; i++)
	{
		IDT_SetEntry(i, IDT_Interrupts[i-32]);
	}

	for (; i < IDT_ENTRY_COUNT; i++)
	{
		IDT[i].OffsetLow = 0;
		IDT[i].OffsetHigh = 0;
		IDT[i].Reserved = 0;
		IDT[i].Selector = 0;
		IDT[i].Attributes = 0;
	}

	IDT_SetEntry(IDT_SYSCALL_INTERRUPT, IDT_SyscallHandlerStub);

	IDT_SetIDT(&IDT_Ptr);
}

void IDT_SetHandler(unsigned int ID, void (*func)(void))
{
	if (ID < IDT_INTERRUPT_HANDLERS_COUNT-1) 
	{
		IDT_Handlers[ID] = func;
	}
	else if (ID == 0x0080)
	{
		IDT_Handlers[IDT_SYSCALL_INTERRUPT] = func;
	}
}

void IDT_InterruptHandler(unsigned short int ID, Registers32_t Regs)
{
	if (ID < 16)
	{
		void (*func)(void) = IDT_Handlers[ID];
		if (func != NULL)
		{
			func();
		}
	}
	else if (ID == 0x0080)
	{
		void (*func)(Registers32_t) = (void (*)(Registers32_t))
			IDT_Handlers[IDT_SYSCALL_INTERRUPT];

		if (func != NULL)
		{
			func(Regs);
		}
	}
	if (ID >= 8)
	{
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);
}

void IDT_SyscallHandler(Registers32_t Regs)
{
	return;
}
