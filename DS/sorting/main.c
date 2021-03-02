#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ADTDefs.h"
#include "mu_test.h"
#include <time.h>


#define SIZE 3



int main ()
{
	//ADTErr res;
	//int arr[4]={4,3,2,1};
	//MergeSort(arr,4);
	int arr[SIZE]={543,16,1};
	RadixSort(arr, SIZE);
	print(arr, SIZE);
/*
	int *arr = NULL;
    int i;
    ADTErr res;
    arr = (int*)malloc(SIZE * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < SIZE; ++i)
    {
    	arr[i]=SIZE-i;
    }
    ASSERT_THAT((res = RadixSort(arr, SIZE)) == ERR_OK);
    for(i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT(arr[i] == i+1);
    }
    free(arr);*/
return 0;
}
