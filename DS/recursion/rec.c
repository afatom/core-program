#include "recursion.h"
#include <stdio.h>
#include <stdlib.h> /*size_t usage*/

/*Function 1*/
/******************************************************************************/
/*Function for calculating n'th element in fabonnaci series*/
size_t MyFebonnaci(size_t _an)
{
	if (_an == 0)
	{
		return 0;
	}
	if (_an == 1)
	{
		return 1;
	}
	return (MyFebonnaci(_an-1)+MyFebonnaci(_an-2));
}

size_t MyIterativeFebo(size_t _an)
{
	size_t sum = 0; size_t prevsum=0; 
	size_t prevprevsum =0;
	if (_an <= 1)
	{
		sum += _an;
		return sum;
	}
	prevsum = 1; prevprevsum = 0;
	for (int i = 2; i < _an; ++i)
	{	
		prevsum+=prevprevsum;
		sum += prevsum; 
		prevsum = sum;  
	}
	
	/*
	for (int i = _an-2; i < _an-1; ++i)
	{
		sum += sum;  
	}
	*/
	return sum;	
}
/******************************************************************************/

/*Function 2*/
/******************************************************************************/
/*Function for calculating elements Average Of agivin array*/
double Avarage(int *_arr, size_t _n)
{
	double avg1;
	if (_n==1)
	{
		return _arr[0];
	}
	avg1 = Avarage(_arr,_n-1);
	return (avg1*(_n-1) + _arr[_n-1])/(_n);
}
/******************************************************************************/

/*Function 3*/
/******************************************************************************/
/*Function for calculating Sum Of the elements of agivin array*/
int arrSum(int *arr, size_t len)
{
	if(len == 1)
	{
		return arr[0];
	}
	return (arrSum(arr,len-1)+arr[len-1]);
}
/******************************************************************************/

/*Function 4*/
/******************************************************************************/
/*Function for calculating length of string*/
size_t myRecStrLen (const char* _str)
{
	/*solution for the smallest string*/
	if (*_str == '\0')
	{
		return 0;
	}
	/*solution for (n-1) +  link for nth solution*/
	return 	myRecStrLen(_str+1) + 1;
}
/******************************************************************************/

/*Function 5*/
/******************************************************************************/
/*Function for calculating length of string*/
size_t myRecStrLenClassic (const char* _str)
{
	return ((*_str == '\0'))?(0):(myRecStrLen(_str+1) + 1);
}
/******************************************************************************/

/*Function 6*/
/******************************************************************************/
/*Function for Reversing char array*/
void ReverseCharArr(char* _str, size_t _n)
{
	char temp;
	if (_n <=1)
	{
		return;
	}


	temp = *_str;
	*_str= _str[_n-1];
	_str[_n-1] = temp;
	(ReverseCharArr(++_str,(_n-1-1)));
	return;
}
/*******************************************************************/

/*Function 7*/
/******************************************************************************/
/*Function for printing atriangle*/

/*Internal Function - for drawing chars*/
static void PrintChar(char charToPrint, int size)
{
	int j;
  for (j = size; j > 0; --j)
  {
    printf("%c", charToPrint);
  }
  return;
}

static void Printt(char charToPrint, int size)
{
	if (size == 0)
	{
		return;
	}
   	printf("%c", charToPrint);
	Printt(charToPrint, size -1);  	
}
/*
void PrintTriangle(size_t _n)
{
	if (_n == 0)
	{
		return;
	}

    PrintChar('*',_n);
    printf("\n");

	PrintTriangle(_n-1);
	return;
}
*/

/*
void PrintTriangle(size_t _n)
{
	if (_n == 0)
	{
		return;
	}
	
	Printt('@', _n);
	printf("\n");
	PrintTriangle(_n-1);
}
*/
void PrintTrianglemod(size_t _raw, size_t _height, char charToPrint)
{
	if (_raw == 0 || _height == 0)
	{
		return;
	}
   	printf("%c", charToPrint);
	PrintTrianglemod(_raw-1, _height, charToPrint);
	if(_raw == 1)
	{
		printf("\n");
		PrintTrianglemod(_height-1, _height-1, charToPrint);
	}
}














/******************************************************************************/

/*Function 7*/
/******************************************************************************/
/*Function for printing opposite triangle*/
void PrintTriangleOpposite(size_t _n)
{

	if (_n == 0)
	{
		return;
	}

	PrintTriangleOpposite(_n-1);
    PrintChar('*',_n);
    printf("\n");

	return;

}

/*Function 8*/
/******************************************************************************/
/*Function for returning last char in agivin string*/
char GetLastChar(char* _str)
{
	if (*_str == '\0')
	{
		return '\0';
	}
	if(*(_str+1)=='\0')
	{
		return (*_str);
	}
	return GetLastChar(_str+1);

}
/******************************************************************************/

/*Function 9*/
/******************************************************************************/
/*Function for Comparing two Strings - zero will return if the strings is identical*/
int IsEqualStrings(char *_strLeft, char *_strRight)
{
	if((*_strLeft - *_strRight) > 0)
	{
		return 1;
	}
	if ((*_strLeft - *_strRight) < 0)
	{
		return -1;
	}
	if ((*_strLeft - *_strRight) == 0 && ((*_strLeft == '\0' && *_strRight == '\0')))
	{
		return 0;
	}

	return IsEqualStrings(_strLeft + 1, _strRight + 1);
}
/******************************************************************************/

/*Function 10*/
/******************************************************************************/
/*Function for copying src string into destination string. caller is responsible
*for Sending a string with enough space*/
void RecStrCpy(char* _dest, char* _src)
{
	if (*_src == '\0')
	{
		*_dest = '\0';
		return;
	}
	*_dest = *_src;
	RecStrCpy((_dest+1), (_src+1));
	return;
}
/******************************************************************************/
/*func 10 upgrading*/
/*no need for return in void func*/
/* if condition approving*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*
void RecStrCpy(char* _dest, char* _src)
{
	*_dest = *_src;
	if (*_src == '\0')
	{
		return;
	}
	RecStrCpy((_dest+1), (_src+1));
}
*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

/*Function 11*/
/******************************************************************************/
/*Function for copying src string into destination string and returning num of
*copied chars. caller is responsible for Sending a string with enough space*/
size_t RecStrCpyLen(char* _dest, char* _src)
{
	size_t counter = 0;

	if (*_src == '\0')
	{
		*_dest = '\0';
		return 1;
	}
	*_dest = *_src;

	counter = RecStrCpyLen((_dest+1), (_src+1))+1;
	return counter;
}
/******************************************************************************/
void HannoiParadox(int n, char from, char to, char via)
{
	if (n==0)
	{
		return;
	}
	if (n==1)
	{
		printf("Move Ring num %d from %c to %c\n",n,from,to);
		return;
	}

	HannoiParadox(n-1,from,via,to);
	//HannoiParadox(n-(n-1),from,to,via);
	printf("Move ring num %d from %c to %c\n", n, from,to);
	HannoiParadox(n-1,via,to,from);
}

void findGCD(int num1, int num2)
{
	int result1=0,result2=0;
	if (num1==num2)
	{
		printf("GCD = %d\n",num1);
		return;
	}
	/*num2 > num1 must*/
	if (num1>num2)
	{
		num1-=num2;
		return (findGCD(num1,num2));
	}
	if(num2 > num1)
	{
		num2-=num1;
		return (findGCD(num1,num2));
	}
}


int findlion(int num, int *arr, size_t size)
{
	size_t new =0;
	if (size == 0)
	{
		return -1;
	}
	
	if((*(arr+size/2))>num)
	{
		new = size/2;
		if (*(arr+new)==num) return new;
		return findlion(num,arr,new);
	}
	if (*(arr+size/2)<num)
	{
		new = size/2;
		arr = arr +size/2;
		if (*(arr+new)==num) return new;
		return findlion(num,arr+size/2,new);
	}
	
}







