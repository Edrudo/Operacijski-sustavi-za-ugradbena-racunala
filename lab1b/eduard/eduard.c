#include <stdio.h>
#include <string.h>
#include <postavke.h>

void printEduard(const char *prefix)
{
	char p[DULJINA];

	strcpy ( p, prefix );
	strcat (p, "/eduard");
	printf("%s --printEduard\n", p);
	printEdo(p);
	return;
}