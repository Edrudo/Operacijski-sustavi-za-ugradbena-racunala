#include <types/basic.h>
void premjesti()
{
	extern size_t size_c;
	extern size_t size_i;
	extern size_t size_d;
	size_t size_code = (size_t) &size_c;
	size_t size_instruction = (size_t) &size_i;
	size_t size_constants = (size_t) &size_d;
	size_t i;

	// code
	char *od = (char *) 0x100000;
	char *kamo = (char *) 0x0;
	for ( i = 0; i< size_d; i++ )
		*kamo++ = *od++;
		
	// instructions
	od = (char *) 0x100000 + size_code;
	kamo = (char *) 0x200000;
	for ( i = 0; i< size_d; i++ )
		*kamo++ = *od++;

	// constants
	od = (char *) 0x100000 + size_code + size_instruction;
	kamo = (char *) 0x300000;
	for ( i = 0; i< size_d; i++ )
		*kamo++ = *od++;
		
	// data
	od = (char *) 0x100000 + size_code + size_instruction + size_constants;
	kamo = (char *) 0x400000;
	for ( i = 0; i< size_d; i++ )
		*kamo++ = *od++;

}