#include <stdio.h>
#include <postavke.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

void lab1y() 
{
	float t = time(NULL);
	float s = sin(t);
	printf("lab1y pokrenut u t=%f, sin(t)==%f", t, s);
}