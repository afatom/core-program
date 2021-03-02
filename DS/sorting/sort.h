#ifndef _SORT_H_
#define _SORT_H_

#include <stddef.h> /*size_t*/
#include "ADTDefs.h"

struct Person {
    char    m_name[32];
    int     m_age;
};

typedef struct Person Person;

/*******************************************************************************
*[Description]:Quick Sort Recorsion Sort function.
*[Input]:integer array 
*[Return]:sorted array (smaller first). ERR_OK will returned in success case.
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr QuickSortRecorsion(int *_arr, size_t _size);

/*******************************************************************************
*[Description]:Bubble Sort Persons Array.
*[Input]:Person array to sort by age. 
*[Return]:Void-Sorted array by age (younger first)
*[Errors]:NONE
*******************************************************************************/
void bublePersons(Person *arr, size_t size);

/*******************************************************************************
*[Description]:Selection Sort Persons Array.
*[Input]:Person array to sort by age in selection Sort Algoritm.  
*[Return]:Sorted array by age (younger first)
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr SelectionSort(Person *arr, size_t size);

/*******************************************************************************
*[Description]:Merge Sort Integers Array.
*[Input]:Int array to be sorted by merge Sort Algoritm (smaller elements first).  
*[Return]:Sorted array. 
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr MergeSort(int* _arr, size_t _size);
/*******************************************************************************
*[Description]:Radix Sort Integers Array.
*[Input]:Int array to be sorted by Radix Sort Algoritm (smaller elements first).  
*[Return]:Sorted array. 
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr RadixSort(int* _arr, size_t _size);
/*******************************************************************************
*[Description]:Counting Sort Integers Array.
*[Input]:Int array to be sorted by Counting Sort Algoritm (smaller elements first).  
*[Return]:Sorted array. 
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr CountingSort(int* _arr, size_t _size);
/*******************************************************************************
*[Description]:Modified Counting Sort Integers Array with respect to digit value
*[Input]:Int array to be sorted by Counting Sort Algoritm (smaller 
*elements first).  
*[Return]:Sorted array. 
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr ModifiedCountingSort(int* _arr, size_t _size, size_t _digit);
/*******************************************************************************
*[Description]:Merge Sort Integers Array (Iterative Algo)
*[Input]:Int array to be sorted by merge Sort Algoritm (smaller elements first).  
*[Return]:Sorted array. 
*[Errors]:ERR_NOT_INITIALIZED will returned in null array and ERR_GENERAL in 
*array with size = 0 case.
*******************************************************************************/
ADTErr MergeSortIterativeAlgo(int* _arr, size_t _size);
/*******************************************************************************
*[Description]:Bubble Sort Strings Array.
*[Input]:strings array to sort be sorted, smaller first (sorting with strcmp
* function). 
*[Return]:Void-Sorted array of strings
*[Errors]:NONE
*******************************************************************************/
void BubbleSortStringsArr(char** arr, size_t size);

/*******************************************************************************
*[Description]:Shake Sort Strings Array.
*[Input]:strings array to sort be sorted, smaller first (sorting with strcmp
* function). 
*[Return]:Void - Sorted array of strings
*[Errors]:NONE
*******************************************************************************/
void ShakeSortStringsArr(char** arr, size_t size);

/*******************************************************************************
*[Description]:Insertion Sort integer Array.
*[Input]:Int array to be sorted, smaller elements first 
*[Return]:Void - Sorted array of ints
*[Errors]:NONE
*******************************************************************************/
void InsertionSort(int* arr, size_t size);

/******************************************************************************/
/*                       Printing Functions                                   */
/*                                                                            */
/******************************************************************************/
/*Printing integer array elements*/
void print(int* arr, size_t size);

/*Printing strings array elements*/
void PrintStrings(char** names, size_t size);

#endif /*_SORT_H_*/
