#include "arrays.h"
#include <stdio.h>

int CheckParams (int arr[], int size)
{
  if (NULL==arr)
  {
    return ARRAY_NOT_INITIALIZED;
  }
  if (size<1)
  {
    return INVALID_ARRAY_SIZE;
  }
  return OK;
}
/*[def] = finding max element in given array*/
int FindMax (int arr[], int size)
{
  int result;
  if ((result=CheckParams(arr,size))!=OK)
  {
    return result;
  }

}
