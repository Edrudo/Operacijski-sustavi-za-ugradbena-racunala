ENTRY(arch_startup)

SECTIONS {
	.code 0x100000: AT(0x100000)
	{
		kernel_code_addr = .;

		/* instructions */
		*?/boot/startup.asm.o ( .text* )
		*?/boot/premjesti.o ( .text* )
	}
	size_c = SIZEOF(.code);

	.instrukcije 0x200000: AT(0x100000 + size_c)
	{

		*( .text* )
	}
	size_i = SIZEOF(.instrukcije);

	.data 0x300000 : AT(0x100000 + size_c + size_i)
	{
		kernel_data_addr = .;

		/* read only data (constants), initialized global variables */
		* ( .rodata* )
	}
	size_d = SIZEOF(.data);

	.bss 0x400000: AT(0x100000 + size_c + size_i + size_d)
	{
		*( .bss* COMMON* );

		. = ALIGN (4096);
	}
	size_b = SIZEOF(.bss);

	.stog 0x800000: AT(0x800000)
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
