#include "bitwise.h"
#include <stdlib.h>
#include <stdio.h>


typedef int (*bitz)(size_t, BitMap*); /*typedef function pointer*/
/*******************************************************************/
int Operate(bitz t,size_t bit, BitMap *ptr)
{
    return t(bit, ptr);
}


int main ()
{
    size_t bit;
    BitMap* ptr = CreateBitMap(16);
    bitz arr[4] = {TurnBitOn, TurnBitOff, IsBitOn,DisplayBits};
	TurnBitOn(15, ptr);
    Operate(arr[0], 0, ptr);
    Operate(arr[3], 0, ptr);
    Operate(arr[0], 1, ptr);
    Operate(arr[0], 2, ptr);
 	Operate(arr[3], 0, ptr);
    Operate(arr[0], 7, ptr);
    Operate(arr[3], 0, ptr);
    Operate(arr[0], 3, ptr);
    Operate(arr[0], 4, ptr);
    Operate(arr[0], 5, ptr);
    Operate(arr[0], 6, ptr);
    Operate(arr[3], 0, ptr);
    /*
    */
   
    
    DestroyBitMap(&ptr);
    return 0;
}
