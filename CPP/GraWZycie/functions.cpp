#include "functions.h"
#include <stdlib.h>

// Definicje (implementacje) funkcji.

int random(int a, int b)
{
	return ( rand() % (b-a)) + a;
}