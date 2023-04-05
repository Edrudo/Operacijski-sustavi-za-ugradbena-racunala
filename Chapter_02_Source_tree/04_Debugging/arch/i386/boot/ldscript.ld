/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

SECTIONS {
	.code 0x0 :
	{
		kernel_code_addr = .;

		/* instructions */
		*?/boot/startup.asm.o ( .text* )
		*?/boot/premjesti.o ( .text* )
	}
	.instrukcije 0x200000: AT(0x20000)
	{

		*( .text* )
	}
	size_instrukcije = SIZEOF(.instrukcije);

	.data 0x300000 : AT(0x30000)
	{
		kernel_data_addr = .;

		/* read only data (constants), initialized global variables */
		* ( .rodata* .data* )
	}
	size_data = SIZEOF(.data);

	.bss 0x400000: AT(0x40000)
	{
		*( .bss* COMMON* )

		. = ALIGN (4096);
	}

	.stog 0x700000: AT(0x70000)
	{
		*( .stog )
		. = ALIGN (4096);
		stack_start = .; /* set a symbol to the start of the stack */
		. += 0x200000;   /* allocate 2 MB for the stack */
		stack_end = .;   /* set a symbol to the end of the stack */
	}

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */

#ifndef DEBUG
	/DISCARD/ : { *(*) }
#endif
	kernel_end_addr = .;
}
