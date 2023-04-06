/*! Hello world program */

#include <stdio.h>
#include <api/prog_info.h>
#include <api/malloc.h>
#include <arch/interrupt.h>
#include <arch/processor.h>

int demo()
{
	void *ptrs[15];

    for(int i = 0; i < 15; i++){
        ptrs[i] = malloc(100);
    }

    printf("----------------\n");
    
    for(int i = 0; i < 4; i++){
        free(ptrs[i]);
    }

    printf("----------------\n");
     
    ptrs[0] = malloc(300);

    printf("----------------\n");
    
    for(int i = 5; i < 15; i++){
        free(ptrs[i]);
    }
    
    printf("----------------\n");

#if 0	/* test escape sequence */
	printf("\x1b[20;40H" "Hello World at 40, 20!\n");
#endif

	return 0;
}