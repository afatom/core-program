#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bits.h"


#define UC_BUFFER 8
#define UI_BUFFER 32

#define NIBLE 4


static void RevStr(char *str);
void SwapChars(char *first, char *second)
{
    char temp = *first;
    *first = *second;
    *second = temp;
    return;
}


char* BinaryToHex(unsigned int binaryin, char* bufferout)
{
    unsigned int mask = 0;
    unsigned int temp;
    double res=0;
    int i=0,j=0;
    char hexKeys[17]="0123456789ABCDEF";
    mask = ~mask;
    mask = mask >> 31; /*00...0000 0001*/
    temp = binaryin;
    while(binaryin !=0)
    {
        while(i<4)
        {
            temp = temp & mask;
            res+=pow(2,(double)(temp));
            binaryin = binaryin >>2;
            temp = binaryin; 
            ++i;
        }
        bufferout[j]= hexKeys[(int)res];
        ++j;
        i=0;
    }
    bufferout[j]='\0';
    /*reverse string*/
    RevStr(&bufferout[0]);
    return &bufferout[0];
}

static void RevStr(char *str)
{
    char* first = NULL;
    char* last = NULL;

    size_t len = strlen(str);
    if (len <= 1)
        if (str == NULL || len <= 1)
        {
            return;
        }
    
    first = &str[0];
    last = &str[len - 1];
    while ((last - first) >= 1)
    {
        SwapChars(first, last);
        ++first;
        --last;
    }
    return;
}

char AbsCalculator(char _num)
{
    unsigned char mask = 0;
    char funnum = _num;
    char carry;
    unsigned char one = 0;
    one = ~one;
    mask = ~mask;
    mask = mask << 7; /*we get 128 = 1000 0000*/
    
    if ((funnum & mask) == 0)
    {
        return _num;
    }
    funnum = ~funnum;
    funnum += 1;
    return funnum;
/*

    one = one >> 7;

    while (funnum != 0) *//*<< addition operation*/
    /*
    {
        carry = one & funnum;
        one = one ^ funnum;
        funnum = carry << 1;
    }
    return funnum;*/
}

int SetBits(unsigned char _x, size_t _p, size_t _n, unsigned char _y, unsigned char *_answere)
{
    /*check params*/
    if (_p > UC_BUFFER || _n < 0 || _p < _n)
    {
        return 1; /*invalid inputs*/ 
    }
    unsigned char temp = _x;
    unsigned char mask = ~0;
    mask <<= UC_BUFFER - (_p - _n);
    mask >>= (UC_BUFFER - _p);
    mask=~mask;
    temp = temp & mask;
    _y <<= UC_BUFFER - (_p - _n);
    _y >>= (UC_BUFFER - _p);
    temp = temp | _y;
    *_answere = temp;
    return 0;
}


int SetBitsByValue(unsigned int _w, size_t _i, size_t _j, size_t value, unsigned int *_answere)
{
    /*check params*/
    if (_i > 31 || _j < 0 || _j > _i || value > 1)
    {
        return 1; /*invalid inputs*/
    }
    unsigned int mask = ~0;
    /*DisplayUIBits(_w);*/
    unsigned int temp = _w;
    if (value == 1)
	{
		mask<<=(UI_BUFFER-1 -_i + _j);
		mask>>=(UI_BUFFER- _i-1);
		temp = temp | mask;
        *_answere = temp;
        return 0;
    }
	/*value = 0*/
    mask <<= (UI_BUFFER - 1 - _i + _j);
    mask >>= (UI_BUFFER - _i - 1);
    mask=~mask;
    temp = temp & mask;
    *_answere = temp;
    return 0;
}



void DecToHex(int _inputNum)
{
	int i;
	char temp;
	int mask = 0XF<<shiftsize;
	const size_t shiftsize = sizeof(int) * __CHAR_BIT__ - NIBLE;
	const char* hexaRange="0123456789ABCDEF";
	const char* lead = "0x";
	
	printf("%s", lead);
	do
	{
		printf("%c",hexaRange[(_num & mask) >> shiftsize];
		
	}
	
}

















