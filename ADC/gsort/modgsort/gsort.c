#include <stdio.h>
#include <stdlib.h>
#include "ADTDefs.h"
#include "gsort.h"
#include <string.h>


#define FALSE 0
#define TRUE 1

/*typedef int (*fp)(void *, void *);*/

static void modSwap(void *first, void *sec, size_t _sizeOfElement)
{
	void* temp =(void*) malloc(sizeof(_sizeOfElement));
	memcpy(temp, first, _sizeOfElement);
	memcpy(first, sec, _sizeOfElement);
	memcpy(sec, temp, _sizeOfElement);
	free(temp);
}
/******************************************************************************/
/******************************************************************************/
ADTErr GenericBubbleSort(void *_arr, size_t _numOfItems, size_t _sizeOfElement, fp _isLess)
{
	size_t i, j;
	if (_arr == NULL || _numOfItems == 0)
	{
		return ERR_INVALID_DATA_IN;
	}
	/*****************************************/
	for(i =0; i < _numOfItems-1; ++i)
	{
		for(j = 0; j<_numOfItems-i-1; ++j)
		{
			if(!_isLess(((char*)_arr+j*(_sizeOfElement)), ((char*)_arr+(j+1)*(_sizeOfElement))))
			{
				modSwap(((char*)_arr+j*(_sizeOfElement)), ((char*)_arr+(j+1)*(_sizeOfElement)), _sizeOfElement);
			}
		}
	}
	return ERR_OK;
}
/******************************************************************************/
/*
ADTErr GenericShakeSort(void *_arr[], size_t _numOfItems, fp _isLess)
{
	size_t i = 0, j, p;
	if (_arr == NULL || _numOfItems == 0)
	{
		return ERR_INVALID_DATA_IN;
	}
	for (i = 0; i < _numOfItems - 1; ++i)
	{
		for (j = 0; j < _numOfItems - i - 1; ++j)
		{
			if (!_isLess(_arr[j], _arr[j + 1]))
			{
				swap(&_arr[j], &_arr[j + 1]);
			}
		}

		for (p = _numOfItems - i - 1; p > i; --p)
		{
			if ((_isLess(_arr[p], _arr[p-1])))
			{
				
				swap(&_arr[p], &_arr[p - 1]);
				
			}
		}
	}
	return ERR_OK;
}*/