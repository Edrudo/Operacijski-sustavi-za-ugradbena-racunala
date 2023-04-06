rom_a = 0x100000;
instructions_a = 0x200000;
constants_a = 0x300000;
data_a = 0x400000;

ENTRY(arch_startup)

SECTIONS {
	.code rom_a: AT(rom_a)
	{
		kernel_code_addr = .;

		/* instructions */
		*?/boot/startup.asm.o ( .text* )
		*?/boot/premjesti.o ( .text* )
	}
	size_c = SIZEOF(.code);

	.instrukcije instructions_a: AT(rom_a + size_c)
	{

		*( .text* )
	}
	size_i = SIZEOF(.instrukcije);

	.rodata constants_a : AT(rom_a + size_c + size_i)
	{
		kernel_rodata_addr = .;

		/* read only data (constants), initialized global variables */
		*( .rodata* )
	}
	size_con = SIZEOF(.rodata);

	.bss data_a: AT(rom_a + size_c + size_i + size_con)
	{
		*( .bss* COMMON* .data* )

		. = ALIGN (4096);
	}
	size_d = SIZEOF(.bss);

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
