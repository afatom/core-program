#include <stdio.h>
#include <stddef.h>
#include "ADTDefs.h"
#include "gsort.h"
#include <string.h>


#define FALSE 0
#define TRUE 1

/*typedef int (*fp)(void *, void *);*/

static void modSwap(void **first, void **sec, size_t _sizeOfElement)
{
	memcpy(*sec, *first, _sizeOfElement);
}


/******************************************************************************/
static void swap(void **first, void **sec)
{
	void* ptr = *first;
	*first = *sec;
	*sec = ptr;
}
/******************************************************************************/
ADTErr GenericBubbleSort(void *_arr[], size_t _numOfItems, fp _isLess)
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
			if(!_isLess(_arr[j], _arr[j+1]))
			{
				swap(&_arr[j], &_arr[j+1]);
			}
		}
	}
	return ERR_OK;
}
/******************************************************************************/
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
				/*swap*/
				swap(&_arr[p], &_arr[p - 1]);
				
			}
		}
	}
	return ERR_OK;
}