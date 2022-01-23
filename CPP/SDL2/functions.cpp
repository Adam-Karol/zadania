#include "functions.h"
#include <stdlib.h>

int random(int a, int b)
{
	return ( rand() % (b-a)) + a;
}