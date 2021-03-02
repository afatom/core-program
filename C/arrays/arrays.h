#ifndef _ARRAYS_H_
#define _ARRAYS_H_
/*Errors*/
#define OK 0
#define INVALID_ARRAY_SIZE 2
#define ARRAY_NOT_INITIALIZED 1
#define PALINDROME 3
#define NOT_PALINDROME 4

/*[def] = finding max element in given array
*[Inputs] = int array and size of the array
*[output] = Max element in the rray
*[Errors] = invalid size (negative size), Un itialized array*/
int FindMax (int arr[], int size);

/*[def] = sorting agiven array in ascending order
*[Inputs] = int array and size of the array
*[output] = Sorted array (ascending order)
*[Errors] = invalid size (negative size), Un itialized array*/
int AscendingSortArray (int arr[], int size);

/*[def] = finding the first frequent element in given array without array changing
*[Inputs] = int array and size of the array
*[output] = frequent element (int)
*[Errors] = invalid size (negative size), Un itialized array*/
int FrequentArrayElement (int arr[], int size);

/*[def] = check if agiven number is palindrome
*[Inputs] = integer number
*[output] =
*[Errors] = invalid size (negative size), Un itialized array*/
int ISPalindromeNumber (int num);



#endif /*_ARRAYS_H_*/
