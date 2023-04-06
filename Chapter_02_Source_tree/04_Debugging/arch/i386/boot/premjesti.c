#include <types/basic.h>
#include <stdio.h>
void premjesti()
{
	extern size_t size_c;
	extern size_t size_i;
	extern size_t size_con;
	extern size_t size_d;
	extern size_t rom_a;
	extern size_t instructions_a;
	extern size_t constants_a;
	extern size_t data_a;


	size_t size_code = (size_t) &size_c;
	size_t size_instruction = (size_t) &size_i;
	size_t size_constants = (size_t) &size_con;
	size_t size_data = (size_t) &size_d;
	size_t rom = (size_t) &rom_a;
	size_t instructions = (size_t) &instructions_a;
	size_t constants = (size_t) &constants_a;
	size_t data = (size_t) &data_a;
	size_t i;

	printf("Ovdje sam");
	// instructions
	char *od = (char *) (0x100000 + size_code);
	char *kamo = (char *)(0x200000);
	for ( i = 0; i< size_instruction; i++ )
		*kamo++ = *od++;

	// constants
	od = (char *) (0x100000 + size_code + size_instruction);
	kamo = (char *) (0x300000);
	for ( i = 0; i< size_constants; i++ )
		*kamo++ = *od++;
		
	// data
	od = (char *) (0x100000 + size_code + size_instruction + size_constants);
	kamo = (char *) (0x400000);
	for ( i = 0; i< size_data; i++ )
		*kamo++ = *od++;

}