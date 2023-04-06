/*! Hello world program */

#include <stdio.h>
#include <api/prog_info.h>
#include <api/malloc.h>
#include <arch/interrupt.h>
#include <arch/processor.h>

int demo()
{
	void *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;

	ptr1 = malloc(10);
	free(ptr1);
	printf("\n\n\n\n\n");

	ptr1 = malloc(1800000);
	printf("adresa od ptr1 je %d\n", ptr1);
	ptr2 = malloc(1800000);
	printf("adresa od ptr2 je %d\n", ptr2);
	ptr3 = malloc(1800000);
	printf("adresa od ptr3 je %d\n", ptr3);
	ptr4 = malloc(1800000);
	printf("adresa od ptr4 je %d\n", ptr4);

	// try to allocate more memory than you have
	ptr5 = malloc(300000);
	if(ptr5){
		printf("adresa od ptr5 je %d\n", ptr5);	
		free(ptr5);
	} else {
		printf("nema dovoljno memorije za ptr5\n");
	}
	if(ptr2){
		free(ptr2);
	}
	if (ptr3)
	{
		free(ptr3);
	}
	// try to allocate more memory than you have
	ptr5 = malloc(3000000);
	if(ptr5){
		printf("adresa od ptr5 je %d\n", ptr5);	
	} else {
		printf("nema dovoljno memorije za ptr5\n");
	}




#if 0	/* test escape sequence */
	printf("\x1b[20;40H" "Hello World at 40, 20!\n");
#endif

	return 0;
}