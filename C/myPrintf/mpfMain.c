#include "mpf.h"
#include <string.h> /*string manpulation functions*/
#include <stdio.h>  /*puts func*/
#include <stdarg.h>



int main (int argc, char* argv[])
{
    int numOfChars1, numOfChars2;
    char str[7]="adham";
    char sstr[25] = "C language Programming";

    double f = 100000.212;
    int x = 32;
    numOfChars1 =  MyPrintf("my name is %s and i love the %s and i am %d years old! i need %f ILS\t",str,sstr,x,f);
    numOfChars2 = printf("my name is %s and i love the %s and i am %d years old! i need %f ILS\t", str, sstr, x, f);

    printf("\nnum1  %d  \nnum2  %d\n", numOfChars1, numOfChars2);
    
    return 0;
}