#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ADTDefs.h"
#include "mu_test.h"
#include <time.h>


#define SIZE 1000

UNIT(Initialize_UNIT_ONLY)
	srand((unsigned int)time(NULL));
END_UNIT

UNIT(QuickSortRecorsion_Normal_Test)
    int *arr = NULL;
    int i;
    ADTErr res;
    arr = (int*)malloc(1000 * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 1000; ++i)
    {
    	arr[i]=1000-i;
    }
    ASSERT_THAT((res = QuickSortRecorsion(arr, 1000)) == ERR_OK);
    for(i = 0; i < 1000; ++i)
    {
    	ASSERT_THAT(arr[i] == i+1);
    }
    free(arr);
END_UNIT

UNIT(Quick_Sort_Recorsion_Random_Test)
    int *arr = NULL;
    int i;
    ADTErr res;
    arr = (int*)malloc(1000 * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 1000; ++i)
    {
    	arr[i]= rand();
    }
    ASSERT_THAT((res = QuickSortRecorsion(arr, 1000)) == ERR_OK);
    /*check sorting in for loop*/
    for(i = 0; i < 999; ++i)
    {
    	ASSERT_THAT(arr[i+1] >= arr[i]);
    }
    free(arr);
END_UNIT

UNIT(QuickSortRecorsion_NULL_Test)
    int *arr = NULL;
    int arrx [5]={0};
    
    ADTErr res;
    ASSERT_THAT(NULL == arr);
    ASSERT_THAT((res = QuickSortRecorsion(arr, 5)) == ERR_NOT_INITIALIZED);
    ASSERT_THAT((res = QuickSortRecorsion(arrx, 0)) == ERR_GENERAL);
    
END_UNIT

UNIT(InsertionSort_Normal_Test)
    int *arr = NULL;
    int i;
    
    arr = (int*)malloc(1000 * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 1000; ++i)
    {
    	arr[i]=1000-i;
    }
    InsertionSort(arr, 1000);
    for(i = 0; i < 1000; ++i)
    {
    	ASSERT_THAT(arr[i] == i+1);
    }
    free(arr);
END_UNIT

UNIT(SelectionSort_Normal_Test)
    Person *arr = NULL;
    int i;
    ADTErr res;
    arr = (Person*)malloc(1000 * sizeof(Person));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 1000; ++i)
    {
    	arr[i].m_age=1000-i;
    }
    ASSERT_THAT((res = SelectionSort(arr, 1000)) == ERR_OK);
    for(i = 0; i < 1000; ++i)
    {
    	ASSERT_THAT(arr[i].m_age == i+1);
    }
    free(arr);
END_UNIT

UNIT(bublePersons_Normal_Test)
    Person *arr = NULL;
    int i;
    
    arr = (Person*)malloc(1000 * sizeof(Person));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 1000; ++i)
    {
    	arr[i].m_age=1000-i;
    }
    bublePersons(arr,1000);
    for(i = 0; i < 1000; ++i)
    {
    	ASSERT_THAT(arr[i].m_age == i+1);
    }
    free(arr);
END_UNIT

UNIT(Merge_Sort_Test)
    int *arr = NULL;
    int i;
    ADTErr res;
    arr = (int*)malloc(10 * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < 10; ++i)
    {
    	arr[i]=10-i;
    }
    ASSERT_THAT((res =MergeSort(arr, 10)) == ERR_OK);
    for(i = 0; i < 10; ++i)
    {
    	ASSERT_THAT(arr[i] == i+1);
    }
    free(arr);
END_UNIT

UNIT(CountingSort_Normal_Test)
    int *arr = NULL;
    int i;
    ADTErr res;
    arr = (int*)malloc(SIZE * sizeof(int));
    ASSERT_THAT(NULL != arr);
    for(i = 0; i < SIZE; ++i)
    {
    	arr[i]=SIZE-i;
    }
    ASSERT_THAT((res = CountingSort(arr, SIZE)) == ERR_OK);
    for(i = 0; i < SIZE; ++i)
    {
    	ASSERT_THAT(arr[i] == i+1);
    }
    free(arr);
END_UNIT

UNIT(Radix_Sort_Normal_Test)
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
    free(arr);
END_UNIT
/************************************************************/
/************************************************************/
TEST_SUITE(Sorting___Algorithims____Tests)
	TEST(Initialize_UNIT_ONLY)
	TEST(QuickSortRecorsion_Normal_Test)
	TEST(QuickSortRecorsion_NULL_Test)
	TEST(InsertionSort_Normal_Test)
	TEST(SelectionSort_Normal_Test)
	TEST(bublePersons_Normal_Test)
	TEST(Quick_Sort_Recorsion_Random_Test)
  	TEST(CountingSort_Normal_Test)
  	TEST(Merge_Sort_Test)
  	TEST(Radix_Sort_Normal_Test)
END_SUITE


