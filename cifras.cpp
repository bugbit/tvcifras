#include <stdio.h>
#include "cifras.h"

const char *Cifras::numerosTV[]=
{
	"1","2","3","4","5","6","7","8","9","10","25","50","75","100",NULL
};

int Cifras::grupos[][6]=
{
	{ 1,2,3,4,5,6 },
	{ 7,8,9,1,2,3 },
	{ 4,5,6,7,8,9 },
	{ 10,10,25,50,75,100 }
};
