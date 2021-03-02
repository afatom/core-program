#ifndef _ARR_H_
#define _ARR_H_

#include <stdlib.h>

/*******************************************************************************
*[def]: Finding max element in given array.
*[input]: int array with size
*[output]: max element
*[Errors]:0=OK, 1=INVALID_ARR_SIZE, 2=NULL_ARR
*******************************************************************************/
int FindMax (int arr[], int size, int* MaxNumber);

/*******************************************************************************
*[def]:sorting agiven array in ascending order
*[input]:int array with size
*[output]: sorted array
*[Errors]:0=OK, 1=INVALID_ARR_SIZE, 2=NULL_ARR
*******************************************************************************/
int ArrAscendingSort (int arr[], int size);

/*Printing array elements*/
void PrintArr (int arr[], int size);

/*******************************************************************************
*[def]:check if number is palindrome or not
*[input]:int number for test
*[output]: 0= PALINDROME; 1=NOT_PALINDROME;
*[Errors]:NO ERRORS
*******************************************************************************/
int IsPalindromeNumber (int Num);

/*******************************************************************************
*[def]:findin frequent number in the array
*[input]:int array with size
*[output]: frequent number
*[Errors]:0=OK, 1=INVALID_ARR_SIZE, 2=NULL_ARR
*******************************************************************************/
int FrequentNumber (int arr[], int size, int* frequent);

/*******************************************************************************
*[def]:check if digits are in ascending number
*[input]:int number
*[output]:0=yes, -1=no (identical digits=-1)
*[Errors]:No Errors
*******************************************************************************/
int IsAscendingDigits (int number);
/*******************************************************************************
*[def]:check if number is aprime number
*[input]:integer number
*[output]:0=yes -1=no
*[Errors]:no errors
*******************************************************************************/
int IsPrimeNumber (int number);
/*******************************************************************************
*[def]:sort array - odds first - witout changing elements order
*[input]:int array 
*[output]:sorted array - odds first.
*[Errors]:0=OK, 1=INVALID_ARR_SIZE, 2=NULL_ARR
*******************************************************************************/
int SortOddsFirst (int *arr, size_t size);

/*******************************************************************************
*[def]:returning median element
*[input]:int array 
*[output]:median element without changing arr order
*[Errors]:0=OK, 1=INVALID_ARR_SIZE, 2=NULL_ARR
*******************************************************************************/
int MedianFounder (int *arr, size_t size, int* median);

#endif/*_ARR_H_*/
