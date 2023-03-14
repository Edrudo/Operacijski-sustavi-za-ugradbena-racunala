#include <stdio.h>
#include <string.h>
#include <postavke.h>

void printEduard(const char *prefix)
{
	char p[DULJINA];

	strcpy ( p, prefix );
	strcat (p, " --printEduard");
	printf("%s\n", p);
	printEdo(p);
	return;
}