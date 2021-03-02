#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

	void SwapChars (char* first, char* second)
	{
		char temp=*first;
		*first=*second;
		*second=temp;
		return;
	}

void RevStr(char *str)
{
    size_t len =strlen(str);
    if (len<=1)
    if (str==NULL || len<=1)
    {
        return;
    }
    char* first=&str[0];
    char* last=&str[len-1];
    while ((last-first)>=1)
    {
        SwapChars (first,last);
        ++first;
        --last;
    }
    return;
}
/*str to int*/
int Myatoi (const char* str, int* result)
{
    size_t len = strlen (str);
    int i=0; int res=0; int j=0;
    while (str[i]!='\0'&& !(res=isdigit(str[i])))
    {
        ++i;
        ++j;
    }
    if (j>=2 && (str[j-1]=='+'||str[j-1]=='-'||str[j-1]==' ') && (str[j-2]!=' ') )
    {
        return 0;
    }
    if (j==len)
    {
        return 0;
    }

    int result=0; char ch;
    int sign =1;
    if (str[j-1]=='-')
    {
        sign=-1;
    }
    while (str[j] != '\0' && (res = isdigit(str[j])))
    {
        ch=str[j];
        result*=10;
        result += ch -'0';
        ++j;        
    }
    return sign*result;
}
int RevNum(int num)
{
    int temp = num;
    int result = 0;
    while (temp != 0)
    {
        result *= 10;
        result += (temp % 10);
        temp /= 10;
    }
    return result;
}

int GetBase(int Number, int Base)
{
    int sign =1;
    int Result;
    int Multiplier;
    if (Base < 2 || Base > 10)
    {
        return 0;
    }
    if (Number<0 && Base==10)
    {
        Number=Number*(-1);
        sign=-1;
    }
    if (Number < 0 && Base != 10)
    {
        Number = Number * (-1);
    }
    Result = Number % Base;
    Multiplier = 10;
    while ((Number /= Base) > 0)
    {
        Result = (Number % Base) * Multiplier + Result;
        Multiplier *= 10;
    }

    return sign*Result;
}

char *Myitoa(int val, char *str, int base)
{
    int result = 0,res=0,temp=0,i=0;
    /*check inputs*/
    if (val == 0 || base<2 ||base>10)
    {
        str[0] = 0+'0';
        str[1] = '\0';
        
        return str;
    }
    if (base == 10 && val<0)
    {
        str[i]= 0+'-';
        ++i;
    }
    /**/
    temp = GetBase(val, base);
    //res = RevNum(temp);
    res = temp;
    
    if (val<0 && base==10)
    {
        res=res*(-1);
    }
    
    while (res != 0)
    {
        result = (res % 10);
        str[i] = result+'0';
        ++i;
        res /= 10;
    }
    if (val<0 && base==10)
    {
        RevStr(str+1);
    }
    else {
        RevStr(str);
    }
    str[++i] = '\0';
    return str;
}
