// memory.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#define porta 0x28ff44
int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	int * iptr;
	byte * p = (byte *)porta;
	i = 6;
	iptr = &i;
	printf("%i, %x, %x\n", *iptr, iptr, &i);
	//*p = 255;
	printf("%x, %i\n",p,*p);
	
	return 0;
}

