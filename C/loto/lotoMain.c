#include "loto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAW 6
#define COL 10
int main ()
{
    
    char arr[RAW][COL] ;
	int num;
	int i =0;
	int res;
    
	while (i < 6)
	{
        num = NumbersLottery();
        ArrayFill(&arr[0][1], RAW, COL,num);
        ++i;
	}
    
    /*
    ArrayFill(&arr[0][1], RAW, COL, 1);
    ArrayFill(&arr[0][1], RAW, COL, 21);
    ArrayFill(&arr[0][1], RAW, COL, 13);
    ArrayFill(&arr[0][1], RAW, COL, 6);
    ArrayFill(&arr[0][1], RAW, COL, 33);
    ArrayFill(&arr[0][1], RAW, COL, 40);
    */
    printarr(&arr[0][1], RAW, COL);
    res = printToFile(&arr[0][1], RAW, COL, "test.txt");
    
    return 0;
}
