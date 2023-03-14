#include <stdio.h>
#include <postavke.h>
#include <string.h>

void printEdo(const char *text)
{
	char p[DULJINA];

	strcpy ( p, text );
	strcat ( p, "/edo" );
	printf("%s --printEdo\n", p);
	// printf("ovo je var varijabla %d"" \n", VAR1);
	printEd(p);
	printE(p);
	return;
}