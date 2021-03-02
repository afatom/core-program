#include "arr.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define OK 0
#define INVALID_ARR_SIZE 1
#define NULL_ARR 2
#define PALINDROME 0
#define NOT_PALINDROME 1
#define ASCENDING_NUMBER 0
#define NOT_ASCENDING_NUMBER 1
#define PRIME_NUMBER 0
#define NOT_PRIME_NUMBER 1

int CheckParams (int arr[], int size)
{
  if (NULL==arr)
  {
    return NULL_ARR;
  }
  if (size<1)
  {
    return INVALID_ARR_SIZE;
  }
  return OK;
}

void Swap (int* NumOne, int* NumTwo)
{
  int temp = *NumOne;
  *NumOne = *NumTwo;
  *NumTwo = temp;
}

void PrintArr (int arr[], int size)
{
  for (int i=0; i<size; ++i)
  {
    printf("| %d |",arr[i]);
  }
  printf("\n");
}

int FindMax (int arr[], int size, int* MaxNumber)
{
  int result, i, max;
  /*check inputs*/
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }
  /*find max element*/
  max=arr[0];
  for(i=1; i<size; ++i)
  {
    if(arr[i]>max)
    {
      max=arr[i];
    }
  }
  *MaxNumber=max;
  return OK;
}

int ArrAscendingSort (int arr[], int size)
{
  int result; int counter =0;
  /*check inputs*/
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }
  for (int i=0; i<size-1; ++i)
  {
    for (int j=0; j<size-i-1; ++j)
    {
      if (arr[j]>arr[j+1])
      {
        Swap (&arr[j],&arr[j+1]);
        ++counter;
      }
    }
    /*in this case. the array is sorted*/
    if (counter==0)
    {
      break;
    }
  }
  return OK;
}

int IsPalindromeNumber (int Num)
{
  int RevNum = 0; int InputNum = Num;
  while (InputNum!=0)
  {
    RevNum*=10;
    RevNum+=(InputNum%10);
    InputNum/=10;
  }

  if (RevNum==Num)
  {
    /*palindrome number*/
    return PALINDROME;
  }
  /*not palindrome*/
  return NOT_PALINDROME;
}

int FrequentNumber (int arr[], int size, int* frequent)
{
  int result; int counterOne =1; int counterTwo=1;
  int freqElement;
  /*check inputs*/
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }
  for (int i=0; i<size; ++i)
  {

    for (int j=size-1; j>i; --j)
    {
      if (arr[j]==arr[i])
      {
        ++counterOne;
      }
    }
    if (counterOne==size-1)
    {
      *frequent=arr[0];
      return OK;
    }
    if (counterOne>counterTwo)
    {
      counterTwo=counterOne;
      freqElement = arr[i];
    }
    counterOne=1;
  }
*frequent=freqElement;
return OK;
}

int IsAscendingDigits (int number)
{
  int tempNum = number; 
  int counter=(tempNum%10);
  tempNum/=10;
  while (tempNum != 0)
  {
    if ((tempNum%10)<counter)
    {
      counter=(tempNum%10);
    }
    else
    {
      return NOT_ASCENDING_NUMBER;
    }
    tempNum/=10;
  }
  return ASCENDING_NUMBER;
}

int IsPrimeNumber (int number)
{
  if (number < 0)
  {
    return NOT_PRIME_NUMBER;
  }
  if (number >= 1 && number <=3)
  {
    return PRIME_NUMBER; 
  }
  double sqrtRes = sqrt (number);
  for (int i=2; i<=(int)sqrtRes; ++i)
  {
    if (number%i==0)
    {
      return NOT_PRIME_NUMBER;
    }
  }
  return PRIME_NUMBER;
}

int SortOddsFirst (int *arr, size_t size)
{
  int result;
  /*check inputs*/
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }
  for (int i=0; i<size-1; ++i)
  {
    for (int j=0; j<size-i-1; ++j)
    {
      if (arr[j]%2!=0 && arr[j+1]%2==0)
      {
        Swap (&arr[j],&arr[j+1]);
      }
    }
  }
  return OK;
}

int MedianFounder (int *arr, size_t size, int* median)
{
   int result;
   int countHigh = 0; int countLow=-1; 
   *median=arr[0];
  /*check inputs*/
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }
  /*even array size*/
  if (size%2!=0)
  {
    for (int i=0; i<size; ++i)
    {
      for (int j=0; j<size; ++j)
      {
        if (arr[i]<=arr[j])
        {
          ++countLow;
        }
      }
      if (countLow==((size-1)/2) || countLow==size-1)
      {
        (*median=arr[i]);
        break; 
      }
    }
    return OK; 
  }
  return OK;
}