#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bits.h"




int main (int argc, char* argv[])
{
    char bufferout[256];
    char res = 0;
    char num = -105;
    BinaryToHex(111111111, bufferout);
    printf("%s\n", bufferout);
    res = AbsCalculator(num);
    printf("abs num is: %d\n", res);
    return 0;
} 
