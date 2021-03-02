#include "str.h"
#include <stdio.h>

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void PrintTestRes(int testResult);
void Myatoi_Numbers_Only_Test();
void Myatoi_Negative_Numbers_Test();
void Myatoi_Numbers_With_sign_Plus_Test();
void Myatoi_Letters_First_Test();
void Myatoi_Letters_Last_Test();
void Myatoi_Mixed_String_Test();


int main()
{
    /*
    Myatoi_Numbers_Only_Test();
    Myatoi_Negative_Numbers_Test();
    Myatoi_Numbers_With_sign_Plus_Test();
    Myatoi_Letters_First_Test();
    Myatoi_Letters_Last_Test();
    Myatoi_Mixed_String_Test();
    */
    char str [20]="3123fasd  .125"; int result=0;
    int status = Myatoi (str, &result);
    printf("MyAtoi Result: %d\n", result);

    return 0;

  

}
/*
void PrintTestRes(int testResult)
{
    if (testResult != 0)
    {
        //printf("RED");
        printf(RED "FAIL");
        //printf("\033[0m");
        //printf(RESET);
        return;
    }
    printf(RESET "PASS");
    return;
}

void Myatoi_Numbers_Only_Test()
{
    char arr1[20] = "000";
    char arr2[10] = "01";
    char arr3[5] = "10";
    char arr4[20] = "123456789";
    char arr5[5] = "1000";
    char arr6[7] = "777";
    int testarr[6]={000,01,10,123456789,1000,777};
    int res1 = Myatoi (arr1);
    int res2 = Myatoi (arr2);
    int res3 = Myatoi (arr3);
    int res4 = Myatoi (arr4);
    int res5 = Myatoi (arr5);
    int res6 = Myatoi (arr6);
    int FinalRes=0;
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0]
    - testarr[1] - testarr[2] - testarr[3] - testarr[4] - testarr[5] - testarr[6]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Numbers_Only_Test.\n");
    return;
}

void Myatoi_Negative_Numbers_Test()
{
    char arr1[20] = "-1234";
    char arr2[10] = "-99";
    char arr3[5] = "-777";
    char arr4[20] = "-1234567";
    char arr5[5] = "-850";
    char arr6[7] = "-9";
    int testarr[6] = {-1234, -99, -777, -1234567, -850, -9};
    int res1 = Myatoi(arr1);
    int res2 = Myatoi(arr2);
    int res3 = Myatoi(arr3);
    int res4 = Myatoi(arr4);
    int res5 = Myatoi(arr5);
    int res6 = Myatoi(arr6);
    int FinalRes = 0;
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0] - testarr[1] - testarr[2] - testarr[3] - testarr[4] - testarr[5] - testarr[6]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Negative_Numbers_Test.\n");
    return;
}

void Myatoi_Numbers_With_sign_Plus_Test()
{
    char arr1[20] = "+1234";
    char arr2[10] = "+9";
    char arr3[5] = "+777";
    char arr4[20] = "+1234567";
    char arr5[5] = "+850";
    char arr6[7] = "+1";
    int testarr[6] = {+1234, +9, +777, +1234567, +850, +1};
    int res1 = Myatoi(arr1);
    int res2 = Myatoi(arr2);
    int res3 = Myatoi(arr3);
    int res4 = Myatoi(arr4);
    int res5 = Myatoi(arr5);
    int res6 = Myatoi(arr6);
    int FinalRes = 0;
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0] - testarr[1] - testarr[2] - testarr[3] - testarr[4] - testarr[5] - testarr[6]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Numbers_With_sign_Plus_Test.\n");
    return;
}

void Myatoi_Letters_First_Test()
{
    char arr1[20] = "A++1234";
    char arr2[10] = "ABC++9";
    char arr3[25] = "abwklk777";
    char arr4[20] = "po1234567";
    char arr5[5] = "klk1";
    char arr6[7] = "gfh85";
    int testarr[6] = {0};
    int res1 = Myatoi(arr1);
    int res2 = Myatoi(arr2);
    int res3 = Myatoi(arr3);
    int res4 = Myatoi(arr4);
    int res5 = Myatoi(arr5);
    int res6 = Myatoi(arr6);
    int FinalRes = 0;
    printf("res1, res2,res3,4,5,6,: %d %d %d %d %d %d\n",res1,res2,res3,res4,res5,res6);
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Letters_First_Test.\n");
    return;
}

void Myatoi_Letters_Last_Test()
{
    char arr1[20] = "1234Abc";
    char arr2[10] = "985ABCd";
    char arr3[25] = "10abwklk";
    char arr4[20] = "159poldj";
    char arr5[15] = "6369klk";
    char arr6[17] = "789456gfh";
    int testarr[6] = {1234, 985, 10, 159, 6369, 789456};
    int res1 = Myatoi(arr1);
    int res2 = Myatoi(arr2);
    int res3 = Myatoi(arr3);
    int res4 = Myatoi(arr4);
    int res5 = Myatoi(arr5);
    int res6 = Myatoi(arr6);
    int FinalRes = 0;
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0] - testarr[1] - testarr[2] - testarr[3] - testarr[4] - testarr[5] - testarr[6]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Letters_Last_Test.\n");
    return;
}

void Myatoi_Mixed_String_Test()
{
    char arr1[20] = "-12  34Abc";
    char arr2[10] = "985AB  Cd";
    char arr3[15] = "555.639";
    char arr4[20] = "123ggg";
    char arr5[15] = "696.  5";
    char arr6[17] = "-8 5 8 9 as";
    int testarr[6] = {-12, 985, 555, 123, 696, -8};
    int res1 = Myatoi(arr1);
    int res2 = Myatoi(arr2);
    int res3 = Myatoi(arr3);
    int res4 = Myatoi(arr4);
    int res5 = Myatoi(arr5);
    int res6 = Myatoi(arr6);
    int FinalRes = 0;
    FinalRes += (res1 + res2 + res3 + res4 + res5 + res6 - testarr[0] - testarr[1] - testarr[2] - testarr[3] - testarr[4] - testarr[5] - testarr[6]);
    PrintTestRes(FinalRes);
    printf("________Myatoi_Mixed_String_Test.\n");
    return;
}
*/