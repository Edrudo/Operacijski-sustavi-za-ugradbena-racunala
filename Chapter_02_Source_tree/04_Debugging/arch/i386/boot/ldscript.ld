/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

SECTIONS {
	.code LOAD_ADDR :
	{
		kernel_code_addr = .;

		/* instructions */
		*?/boot/startup.asm.o ( .text* )

		*( .text* )
	}
	.data :
	{
		kernel_data_addr = .;

		/* read only data (constants), initialized global variables */
		* ( .rodata* .data* )
	}
	size_data = SIZEOF(.data);
	.bss :
	{
		*( .bss* COMMON* )

		. = ALIGN (4096);
	}

	.arch 0x100000:
	{
        *?/arch?* ( .text* )
	}
	
	.kernel 0x200000:
	{
        *?/kernel?* ( .text* )
	}
	
	.lib 0x300000:
	{
        *?/lib?* ( .text* )
	}
	
	.api 0x400000:
	{
        *?/api?* ( .text* )
	}
	
	.programs 0x500000:
	{
        *?/programs?* ( .text* )
	}

	.stog 0x600000:
	{
        *( .stog )
        . = ALIGN (4096);
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