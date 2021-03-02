#ifndef _GSORT_H_
#define _GSORT_H_
#include "ADTDefs.h"
#include <stddef.h>

typedef int (*fp)(void *, void *);

typedef struct Person
{
    int age;
    int edu;
    double money;
} Person;


ADTErr GenericBubbleSort(void *_arr, size_t _numOfItems, size_t _sizeOfElement, fp _isLess);

/*******************************************************************************
*[Description]:Generic Shake Sort Algo.
*[Input]:strings array to sort be sorted, smaller first (sorting with strcmp
* function). 
*[Return]:Void - Sorted array of strings
*[Errors]:NONE
*******************************************************************************/
/*
ADTErr GenericShakeSort(void *_arr[], size_t _numOfItems, fp _isLess);
*/
#endif /* _GSORT_H_*/