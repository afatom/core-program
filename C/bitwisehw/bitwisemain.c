#include "bitwiseop.h"
#include <stdlib.h>
#include <stdio.h>


int main ()
{
	unsigned char _xNot;
	unsigned char _x = ~0;
	DisplayUCBits(_x);
	InvertBits(_x, &_xNot);
	DisplayUCBits(_xNot);
	unsigned char _xRot;
	_x = 167;
	DisplayUCBits(_x);
	RotatetBits(_x, 3, &_xRot);
	DisplayUCBits(_xRot);
	/*
	unsigned char _answere;
	puts("Set func\n");
	_x=255;
	DisplayUCBits(_x);
	SetBits(_x, 4, 2, 128,&_answere );
	DisplayUCBits(_answere);
	unsigned int _ans;
	DisplayUIBits(4294967295);
	SetBitsByValue(4294967295, 10, 0, 0, &_ans);
	DisplayUIBits(_ans);*/
    return 0;
}
