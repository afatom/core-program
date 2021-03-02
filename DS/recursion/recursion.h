#ifndef _RECURSION_H_
#define _RECURSION_H_

#include <stdlib.h> /*size_t usage*/

/*Function 1*/
/*Function for calculating n'th element in fabonnaci series*/
/******************************************************************************/
size_t MyFebonnaci(size_t _an);


/*Function 2*/
/*Function for calculating elements Average Of agivin array*/
/******************************************************************************/
double Avarage(int *_arr, size_t _n);

/*Function 3*/
/*Function for calculating Sum Of the elements of agivin array*/
/******************************************************************************/
int arrSum(int *arr, size_t len);

/*Function 4*/
/*Function for calculating length of string*/
/******************************************************************************/
size_t myRecStrLen (const char* _str);

/*Function 5*/
/*Function for calculating length of string*/
/******************************************************************************/
size_t myRecStrLenClassic (const char* _str);

/*Function 6*/
/*Function for Reversing char array*/
/******************************************************************************/
void ReverseCharArr(char* _str, size_t _n);

/*Function 7*/
/*Function for printing atriangle*/
/******************************************************************************/
void PrintTriangle(size_t _n);

/*Function 8*/
/*Function for printing opposite triangle*/
/******************************************************************************/
void PrintTriangleOpposite(size_t _n);

/*Function 8*/
/*Function for returning last char in agivin string*/
/******************************************************************************/
char GetLastChar(char* _str);

/*Function 9*/
/*Function for Comparing two Strings - zero will return if the strings is identical*/
/******************************************************************************/
int IsEqualStrings(char *_strLeft, char *_strRight);

/*Function 10*/
/*Function for copying src string into destination string. caller is responsible 
*for Sending a string with enough space*/
/******************************************************************************/
void RecStrCpy(char* _dest, char* _src);

/*Function 11*/
/*Function for copying src string into destination string and returning num of 
*copied chars. caller is responsible for Sending a string with enough space*/
/******************************************************************************/
size_t RecStrCpyLen(char* _dest, char* _src);

//void PrintTriangleOp(size_t _raw, size_t _height, char charToPrint);
void MultTable(size_t _raw, size_t _height);
void PrintTrianglemod(size_t _raw, size_t _height, char charToPrint);
void rawmult(size_t size, size_t multplier);
size_t MyIterativeFebo(size_t _an);
void HannoiParadox(int n, char from, char to, char via);
void findGCD(int num1, int num2);
int findlion(int num, int *arr, size_t size);
#endif /*_RECURSION_H_*/
