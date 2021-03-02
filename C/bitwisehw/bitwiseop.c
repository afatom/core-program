#include "bitwiseop.h"
#include <stdlib.h>
#include <stdio.h>

#define UC_BUFFER 8 /*unsigned int bit size*/
#define UI_BUFFER 32 /*unsigned int bit size*/


void DisplayUIBits(unsigned int _input)
{
    int i = UI_BUFFER - 1;
    int _arr[UI_BUFFER] = {0};
    while (i >= 0)
    {
        _arr[i] = (_input % 2);
        _input = _input / 2;
        --i;
    }
    printf("*********************************************************************************\n");
    for (int j = 0; j < UI_BUFFER; ++j)
    {
        printf("%d ", _arr[j]);
    }
    printf("\n********************************************************************************\n");
    return ;
}

void DisplayUCBits(unsigned char _input)
{
    int i = UC_BUFFER - 1;
    //int new=_input;
    int _arr[UC_BUFFER] = {0};
    while (i >= 0)
    {
        _arr[i] = (_input % 2);
        _input = _input / 2;
        --i;
    }
    printf("***************\n");
    for (int j = 0; j < (UC_BUFFER); ++j)
    {
        printf("%d ", _arr[j]);
    }
    printf("\n***************\n");
    return;
}


void InvertBits(unsigned char _x, unsigned char *_xNot)
{
    //unsigned char mask = 255;
    unsigned char mask = ~0;
    *_xNot = (_x) ^ (mask); 
    return ;
}

void RotatetBits(unsigned char _x, size_t _n, unsigned char *_xRot)
{
    size_t i = 0;
    unsigned char mask = ~0;
    printf("%d ",mask);
    mask = mask>>1;
        printf("%d ",mask);
    unsigned char one = ~0;
    one>>=(UC_BUFFER-1);
    mask = mask | 1;
            printf("%d ",mask);
    unsigned char res = _x;
    while (i < _n)
    {
        if (res % 2 != 0) /*zoge*/
        {
            /*shift right once*/
            res >>= 1;
            /*turn MSB bit ON*/ /**/
            res = res|(mask);
            ++i;
        }
        else
        {
            /*shift right once*/
            res >>= 1;
            ++i;
        }
    }
    *_xRot = res;
    return ;
}

int SetBits(unsigned char _x, size_t _p, size_t _n, unsigned char _y, unsigned char *_answere)
{
    /*check params*/
    if (_p > UC_BUFFER || _n < 0 || _p < _n)
    {
        return 1; /*invalid inputs*/ 
    }
    unsigned char temp = _x;
    unsigned char mask = 255;
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
    unsigned int mask = 4294967295;
    DisplayUIBits(_w);
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







