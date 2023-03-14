#include <stdio.h>
#include <postavke.h>
#include <string.h>

void printEd(const char *text) 
{
	char p[DULJINA];

	strcpy ( p, text );
	strcat ( p, " --printEd" );
	printf("%s\n", p);
	return;
}