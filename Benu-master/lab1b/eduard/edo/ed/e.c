#include <stdio.h>
#include <postavke.h>
#include <string.h>

void printE(const char *text) 
{
	char p[DULJINA];

	strcpy ( p, text );
	strcat ( p, " --printE" );
	printf("%s\n", p);
	return;
}