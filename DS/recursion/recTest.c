#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursion.h"
#include "mu_test.h"

/******************************************************************************/
                                                          /*AVG Function Tests*/
UNIT(AVG_Zero_Elements_Arr_Test)
	double avg;
	int _arr[4]={0,0,0,0}; 
	avg = Avarage(_arr, 4); 
	ASSERT_THAT(avg == 0);
END_UNIT

UNIT(AVG_One_Element_Arr_Test)
	double avg;
	int _arr[1]={10}; 
	avg = Avarage(_arr, 1); 
	ASSERT_THAT(avg == 10);
END_UNIT
UNIT(AVG_Positive_Elements_Arr_Test)
	double avg;
	int _arr[4]={10,10,20,40}; 
	avg = Avarage(_arr, 4); 
	ASSERT_THAT(avg == 20);
END_UNIT

UNIT(AVG_Negative_Arr_Test)
	double avg;
	int _arr[11]={-10,-10,-20,-5,-15}; 
	avg = Avarage(_arr, 5); 
	ASSERT_THAT(avg == -12); 
END_UNIT

UNIT(AVG_Mixed_Arr_Test)
	double avg;
	int _arr[10]={10,10,-20,-5,15,20,50,-10,-2,120}; 
	avg = Avarage(_arr, 10); 
	ASSERT_THAT(avg == 18.8);
END_UNIT
/******************************************************************************/
                                                       /*Strlen Function Tests*/

UNIT(RecStrlen_OneChar_Str_Test)
    size_t strlen;
    char str[2]="A";
    strlen = myRecStrLenClassic(str);
	ASSERT_THAT(strlen == 1);
END_UNIT

UNIT(RecStrlen_Long_Str_Test)
    size_t strlen;
    char str[34]="ADham Fares Is Learning Software!";
    strlen = myRecStrLenClassic(str);
	ASSERT_THAT(strlen == 33);
END_UNIT

/******************************************************************************/
                                           /*Reverse Char array Function Tests*/

UNIT(ReverseCharArr_OneChar_Str_Test)
    char sstr[2]="A";
	ReverseCharArr(sstr,1);
	ASSERT_THAT(*sstr == 'A');
END_UNIT

UNIT(ReverseCharArr_Long_Str_Test)
    char str[9]="ABCDEFGH";
    char rstr[9]="HGFEDCBA";
	ReverseCharArr(str,8);
	ASSERT_THAT(strcmp(str,rstr) == 0);
END_UNIT

/******************************************************************************/
                                                  /*GetLastChar Function Tests*/

UNIT(GetLastChar_OneChar_Str_Test)
    char str[2]= "A";
	char last;
	last = GetLastChar(str);
	ASSERT_THAT(last == 'A');
END_UNIT
UNIT(GetLastChar_Long_Str_Test)
    char str[]= "ABCDFGRTE";
	char last;
	last = GetLastChar(str);
	ASSERT_THAT(last == 'E');
END_UNIT

/******************************************************************************/
                                               /*IsEqualStrings Function Tests*/
UNIT(IsEqualStrings_OneChar_Str_Test)
    int eq;
    eq = IsEqualStrings("a","a");
	ASSERT_THAT(eq == 0);
END_UNIT

UNIT(IsEqualStrings_Long_Str_Test)
    int eq;
    eq = IsEqualStrings("ABCDEFG","ABCDEFG");
	ASSERT_THAT(eq == 0);
END_UNIT

UNIT(IsEqualStrings_Different_Str_Test)
    int eq;
    eq = IsEqualStrings("ABCDEFG","ABC345DEFG");
	ASSERT_THAT(eq != 0);
END_UNIT
/******************************************************************************/
                                                    /*RecStrCpy Function Tests*/

UNIT(RecStrCpy_OneChar_Str_Test)
	char dest[5];
	RecStrCpy(dest, "A");
	ASSERT_THAT(*dest == 'A');
END_UNIT
UNIT(RecStrCpy_Long_Str_Test)
	char dest[5];
	RecStrCpy(dest, "ABCD");
	ASSERT_THAT(strcmp(dest,"ABCD") == 0);
END_UNIT

/******************************************************************************/
                                                 /*RecStrCpyLen Function Tests*/

UNIT(RecStrCpyLen_OneChar_Str_Test)
	char dest[5];
	size_t len;
	len = RecStrCpyLen(dest, "A");
	ASSERT_THAT(*dest == 'A');
	ASSERT_THAT(len == 2);
END_UNIT
UNIT(RecStrCpyLen_Long_Str_Test)
	char dest[25];
	size_t len;
	len = RecStrCpyLen(dest, "ASD DFG GHJ k");
	ASSERT_THAT(strcmp(dest,"ASD DFG GHJ k") == 0);
	ASSERT_THAT(len == 14);
END_UNIT

/******************************************************************************/

/*Main function Macro*/
TEST_SUITE(Recursion test)
	TEST(AVG_Zero_Elements_Arr_Test)
	TEST(AVG_One_Element_Arr_Test)
	TEST(AVG_Positive_Elements_Arr_Test)
	TEST(AVG_Negative_Arr_Test)
	TEST(AVG_Mixed_Arr_Test)
	TEST(RecStrlen_OneChar_Str_Test)
	TEST(RecStrlen_Long_Str_Test)
	TEST(RecStrCpyLen_OneChar_Str_Test)
	TEST(RecStrCpyLen_Long_Str_Test)
	TEST(IsEqualStrings_OneChar_Str_Test)
	TEST(IsEqualStrings_Long_Str_Test)
	TEST(IsEqualStrings_Different_Str_Test)
	TEST(RecStrCpy_OneChar_Str_Test)
	TEST(RecStrCpy_Long_Str_Test)
	TEST(GetLastChar_OneChar_Str_Test)
	TEST(GetLastChar_Long_Str_Test)
	TEST(ReverseCharArr_OneChar_Str_Test)
	TEST(ReverseCharArr_Long_Str_Test)
END_SUITE
