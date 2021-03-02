#include "recursion.h"
#include <stdio.h>
#include <stdlib.h> /*size_t usage*/


int main()
{
	/*
	size_t feb = MyFebonnaci(10);
	int _arr[4]={10,10,20,0};
	double avg = Avarage(_arr, 4);
	int sum = arrSum(_arr, 4);
	size_t strlen = myRecStrLenClassic("ABCDEF");
	char _s[4]="ABC";
	ReverseCharArr(_s, 3);
	printf("reverse string = %s\n",_s);
	*/
	//PrintTriangle(5);
	//PrintTrianglemod(4,4, '*');
	//MultTable(4, 4);
	//rawmult(5, 2);
	//MultTable(4, 4);
	//size_t feb = MyIterativeFebo(2);
	//printf("feb an = %lu\n", feb);
	//feb = MyFebonnaci(10);
	//printf("feb an = %lu\n", feb);
	HannoiParadox(3, 'A', 'B', 'C');
	findGCD(84, 108);
	//printf("res = %d\n",res);
	//PrintTriangleOp(4,4, '*');
	//PrintTriangleOpposite(5);
	/*
	char lastChar = GetLastChar(_s);
	int isEqual = IsEqualStrings("ABCD", "ABCD");
	char dest[5];
	RecStrCpy(dest, "asdf");
	size_t len = RecStrCpyLen(dest, "REW");
	printf("feb: %lu\navg: %f\nsum: %d\nstrlen: %lu\nlastchar: %c\nIsEqualstrings: %d\nstrcpy: %s\nstrcpylen: %s\nstrcpylen: %lu\n",feb,avg,sum,strlen,lastChar,isEqual,dest,dest,len);*/
	int arr[10]={1,2,3,4,5,6,7,8,9,10};
	int lion = findlion(9, arr,10);
	printf("lion lion = %d\n", lion);

	return 0;
}
