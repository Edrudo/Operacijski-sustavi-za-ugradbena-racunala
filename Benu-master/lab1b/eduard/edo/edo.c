#include <stdio.h>
#include <postavke.h>
#include <string.h>

void printEdo(const char *text)
{
	char p[DULJINA];

	strcpy ( p, text );
	strcat ( p, " --printEdo" );
	printf("%s\n", p);
	// printf("ovo je var varijabla %d"" \n", VAR1);
	printEd(p);
	printE(p);
	return;
}