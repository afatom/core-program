#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MINUS_SIGN -1
#define PLUS_SIGN 1
#define NOT_A_SIGN 3
#define DIGIT 0

/****************************************************/
/*string to integer function block*/
/****************************************************/
int CheckParam (const char* str)
{
    if (NULL==str)
    {
        return 1; /*fail*/
    }
    return 0;
}
int SkipBlinks (const char* str)
{
    int i = 0;
    while (str[i]==' ')
    {
        ++i;
    }
    return i;
}
int CheckSign (const char* str)
{
    int blinks = SkipBlinks (str);int isdig;
    if (str[blinks]=='-')
    {
        return MINUS_SIGN;
    }
    if (str[blinks]=='+')
    {
        return PLUS_SIGN;
    }
    if ((isdig=isdigit(str[blinks])))
    {
        return DIGIT; /*digit char*/
    } 
    return NOT_A_SIGN; /*invalid char*/
}
int ConvertDigits (const char* str)
{
    int j=SkipBlinks(str); int isdig; int result=0;
    int sign = CheckSign (str);
    if (sign==MINUS_SIGN || sign==PLUS_SIGN)
    {
        ++j;
    }
    while (str[j] != '\0' && (isdig = isdigit(str[j])))
    {
        result*=10;
        result += str[j] -'0';
        ++j;        
    }
    if (sign==DIGIT)
    {
        return result;
    }
    else 
    {
        return sign*result;
    }
}
int Myatoi (const char* str, int* result)
{
    int check;
    if ((check=CheckParam (str)) || (NULL==result))
    {
        return 1; /*function failure. invalid inputs*/
    }
    int pos = SkipBlinks (str);
    int sign = CheckSign (str);
    if (sign==NOT_A_SIGN) /*Not asign char*/
    {
        return 1;
    }
    *result = ConvertDigits (str);
    return 0;
}
/******************************************************/
//char *Myitoa(int val, char *str, int base)
int CheckParams (const char* str, int base)
{
    if (NULL==str || base>10 || base<2)
    {
        return 1;
    }
    return 0;
}

int CheckNumSign (int val)
{
    if (val>=0)
    {
        return PLUS_SIGN;
    }
    return MINUS_SIGN;
}

int ConvertToBase (int val, int base)
{
    
}
