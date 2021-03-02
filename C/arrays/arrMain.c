#include "arr.h"
#include <stdio.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void PrintTestRes (int testResult);
/*Is Prime Number Function Tests*/
void Is_Prime_Number_Negative_Input_Test ();
void Is_Prime_Number_Zero_Input_Test ();
void Is_Prime_Number_Prime_Input_Test ();
void Is_Prime_Number_NOt_Prime_Input_Test (); 

int main(int argc, char const *argv[])
{
  int max =0; int size = 10;int freq=0;int res =0;
  int arr [10]={0,1,3,0,6,1,8,9,1,1};
  res = FrequentNumber (arr, size, &freq);
  printf("freq number is = %d\n", freq);
  /*
  int result = FindMax (arr, size, &max);
  printf("max num = %d\n",max);
  result = ArrAscendingSort (arr, size);
  PrintArr(arr,size);
  
  int pal =0;
  pal = IsPalindromeNumber (757);
  printf("pal = %d\n", pal);
  int freq=0; int res =0;
  res = FrequentNumber (arr, size, &freq);
  printf("freq number is = %d\n", freq);
  */
  /*
  int res = IsAscendingDigits (123456989);
  printf("Ascending Return = %d\n",res);

  int nres = IsPrimeNumber (19);
  printf ("Prime Return = %d \n", nres);
  
  int arr [5]={0,0,0,0,0};
  int ares = SortOddsFirst (arr, 5);
  PrintArr(arr,10);
  */
  /*
  int arr [5]={1,2,3,4,5};
  int median =-123456;
  int sres = MedianFounder (arr,5, &median);
  printf ("Array Median = %d.\n", median);
  */
  Is_Prime_Number_Zero_Input_Test ();
  return 0;
}

void PrintTestRes (int testResult)
{
  if (testResult!=0)
  {
    //printf("RED");
    printf(RED "FAIL\n");
    //printf("\033[0m");
    return;
  }
  printf(RESET "PASS\n");
  return;
}

void Is_Prime_Number_Zero_Input_Test ()
{
  int res = IsPrimeNumber (0);
  printf ("Is_Prime_Number_Zero_Input_Test_____");
  PrintTestRes (1);
  return;
}
