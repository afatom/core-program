#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTDefs.h"

/******************************************************************************/
/*                         Static Functions                                   */
/******************************************************************************/
static void swapints(int* one, int* two);
static size_t partition(int* arr, size_t size);
static void swapPersons(Person *one, Person *two);
static void swap(char* *first, char* *last);
static void swapints(int* one, int* two);
static ADTErr QuickSortRec(int *arr, size_t size);
static void Merge(int* _arr, int* _mergeArr, size_t _size, size_t _secBegin);
static void MergeSortRec(int* _arr, size_t _size, int* _mergeArr);
static int FindMax(int *_arr, size_t _size);
static void BuildSortArr(int* _sourceArr, int* _destArr, int* _countArr, size_t _sourceSize);
static int* CreateCountArr(size_t _size);
static void CountNumsApperance(int* _sourceArr, size_t _sourceSize, int* _countArr);
static void SumCounts(int* _countArr, size_t _countSize);
static void ArrCopy(int* _sourceArr, int* _destArr, size_t _size);
static int CalcNumOfDigits(int _num);
static void ModCountNumsApperance(int* _sourceArr, size_t _sourceSize, int* _countArr, size_t _digit);
static void ModBuildSortArr(int* _sourceArr, int* _destArr, int* _countArr, size_t _sourceSize, size_t _digit);
static void MergeSortIterative(int* _arr, size_t _size, int* _mergeArr);
/******************************************************************************/
/******************************************************************************/
ADTErr MergeSort(int* _arr, size_t _size)
{
  int* _mergeArr = NULL;
  if(NULL == _arr)
  {
    return ERR_NOT_INITIALIZED;
  }
  if(_size == 0)
  {
    return ERR_GENERAL;
  }
  _mergeArr = (int*)malloc((_size) * sizeof(int));
  if(NULL == _mergeArr)
  {
    return ERR_ALLOCATION_FAILED;
  }
  /*sort*/
  MergeSortRec(_arr, _size, _mergeArr);
  free(_mergeArr);
  return ERR_OK;
}
/******************************************************************************/
/******************************************************************************/
ADTErr MergeSortIterativeAlgo(int* _arr, size_t _size)
{
  int* _mergeArr = NULL;
  if(NULL == _arr)
  {
    return ERR_NOT_INITIALIZED;
  }
  if(_size == 0)
  {
    return ERR_GENERAL;
  }
  _mergeArr = (int*)malloc((_size) * sizeof(int));
  if(NULL == _mergeArr)
  {
    return ERR_ALLOCATION_FAILED;
  }
  /*sort*/
  MergeSortIterative(_arr, _size, _mergeArr);
  free(_mergeArr);
  return ERR_OK;
}
/******************************************************************************/
/******************************************************************************/
ADTErr QuickSortRecorsion(int *_arr, size_t _size)
{
  if(NULL == _arr)
  {
    return ERR_NOT_INITIALIZED;
  }
  if(_size == 0)
  {
    return ERR_GENERAL;
  }
  return QuickSortRec(_arr, _size);
}
/******************************************************************************/
/******************************************************************************/
void bublePersons(Person* arr, size_t size)
{
  size_t i, j;
  for(i=0; i<size-1; ++i)
  {
    for(j=0; j<size-i-1; ++j)
    {
      if(arr[j].m_age > arr[j+1].m_age)
      {
        swapPersons(&arr[j], &arr[j+1]);
      }
    }
  }
}
/*****************************************************************************/
/*****************************************************************************/
ADTErr SelectionSort(Person* arr, size_t size)
{
  size_t i,j, minIndex;
  int min;
  if(NULL == arr)
  {
    return ERR_NOT_INITIALIZED;
  }
  if (size == 0)
  {
    return ERR_GENERAL;
  }
  for(i=0; i < size-1; ++i)
  {
    min = arr[i].m_age;
    minIndex = i;
    for(j=i+1; j < size; ++j)
    {
      /*find new min*/
      if(arr[j].m_age < min)
      {
        min = arr[j].m_age;
        minIndex = j;
      }
    }
    /*swap i,j*/
    if(minIndex != i)
    {
      swapPersons(&arr[i], &arr[minIndex]);
    }

  }
  return ERR_OK;
}
/*****************************************************************************/
/*****************************************************************************/
void BubbleSortStringsArr(char** arr, size_t size)
{
  size_t i =0, j;
  int comp; int flag = 0;
  for(i =0; i<size -1; ++i)
  {
    for(j = 0; j<size-i-1;++j)
    {
      comp = strcmp(arr[j],arr[j+1]);
      if(comp > 0)
      {
        /*swap*/
        swap(&arr[j],&arr[j+1]);
        flag = 1;
      }
    }
    if(flag == 0)
    {
      return; /*sorted*/
    }
  }
}
/*****************************************************************************/
/*****************************************************************************/
void ShakeSortStringsArr(char** arr, size_t size)
{
  size_t i =0, j, p;
  int comp; int flag = 0;
  for(i =0; i<size -1; ++i)
  {
    for(j = 0; j<size-i-1;++j)
    {
      comp = strcmp(arr[j],arr[j+1]);
      if(comp > 0)
      {
        /*swap*/
        swap(&arr[j],&arr[j+1]);
        flag = 1;
      }
    }
    if(flag == 0)
    {
      return; /*sorted*/
    }

    for(p= size-i-1; p > i; --p)
    {
      comp = strcmp(arr[p],arr[p-1]);
      if(comp < 0)
      {
        /*swap*/
        swap(&arr[p],&arr[p-1]);
        flag = 1;
      }
    }
    if(flag == 0)
    {
      return; /*sorted*/
    }
    }
}
/*****************************************************************************/
/*****************************************************************************/
void InsertionSort(int *arr, size_t size)
{
  size_t i, j;
  for (i = 0; i < size; ++i)
  {
    for (j = i; j > 0; --j)
    {
      if (arr[j] < arr[j - 1])
      {
        swapints(&arr[j], &arr[j - 1]);
      }
    }
  }
}
/*****************************************************************************/
/*****************************************************************************/
void print(int* arr, size_t size)
{
  size_t i;
  for(i =0; i< size; ++i)
  {
    printf("%d ", arr[i]);
  }
  puts("\n");
}
/*****************************************************************************/
/*****************************************************************************/
void PrintStrings(char** names, size_t size)
{
  int i;
  for(i =0; i< size; ++i)
  {
    printf("%s ", names[i]);
  }
  puts("\n");
}
/*****************************************************************************/
/*****************************************************************************/
/*Static Functions*/
/*****************************************************************************/
static size_t partition(int *arr, size_t size)
{
  size_t pivot = 0, leftIndex, rightIndex;
  leftIndex = 1;
  rightIndex = size - 1;
  if(size == 0)
  {
  	return 0;
  }
  while (rightIndex > leftIndex)
  {
    while (arr[leftIndex] <= arr[pivot] && (leftIndex < size))
    {
      ++leftIndex;
    }
    while (arr[rightIndex] > arr[pivot])
    {
      --rightIndex;
    }
    if (rightIndex > leftIndex)
    {
      swapints(&arr[leftIndex], &arr[rightIndex]);
    }
  }
  if (arr[pivot] > arr[rightIndex])
  {
    swapints(&arr[pivot], &arr[rightIndex]);
  }
  return rightIndex;
}
/*****************************************************************************/
/*****************************************************************************/
static void swapPersons(Person *one, Person *two)
{
  Person tmp = *one;
  *one = *two;
  *two = tmp;
}
/*****************************************************************************/
/*****************************************************************************/
static ADTErr QuickSortRec(int *_arr, size_t _size)
{
  size_t pivot;
  if (_size <= 1)
  {
    return ERR_OK;
  }
  pivot = partition(_arr, _size);
  QuickSortRec(_arr, pivot);
  QuickSortRec(_arr + pivot + 1, _size - pivot - 1);
  return ERR_OK;
}
/*****************************************************************************/
/*****************************************************************************/
static void swap(char **first, char **last)
{
  char *temp = *first;
  *first = *last;
  *last = temp;
}
/*****************************************************************************/
/*****************************************************************************/
static void swapints(int *one, int *two)
{
  int temp = *one;
  *one = *two;
  *two = temp;
}
/*****************************************************************************/
/*****************************************************************************/
static void MergeSortRec(int* _arr, size_t _size, int* _mergeArr)
{
	if(_size == 1)
  	{
    	return; 
  	}
  	/* 0 - size/2*/
  	MergeSortRec(_arr, _size/2, _mergeArr);
  	MergeSortRec(_arr + _size/2, _size - _size/2, _mergeArr);
  	/*merge halfs*/
  	Merge(_arr, _mergeArr, _size, _size/2);
  	/*_arr = _mergeArr;*/
}
/*****************************************************************************/
/*****************************************************************************/
static void Merge(int* _arr, int* _mergeArr, size_t _size, size_t _secBegin)
{
	size_t i, j;
	int rightIndex = (int)_secBegin;
	int leftIndex = 0;
	for(i = 0; i < _size; ++i)
	{
		/*right reach end*/
		if(rightIndex == _size)
		{
			_mergeArr[i] = _arr[leftIndex];
			++leftIndex;	
		}
		/*left reach _secBegin*/
		else if(leftIndex == _secBegin)
		{
			_mergeArr[i] = _arr[rightIndex];
			++rightIndex;
		}
		/*right side bigger than left side*/
		else if(_arr[leftIndex] <= _arr[rightIndex])
		{
			_mergeArr[i]=_arr[leftIndex];
			++leftIndex;
		}
		else
		{
			_mergeArr[i]=_arr[rightIndex];
			++rightIndex;
		}
	}
	print(_mergeArr, _size);
	/*copy merge array to arr array*/
	for(j = 0; j < _size; ++j)
	{
		_arr[j]=_mergeArr[j];
	}
}
/*****************************************************************************/
/*****************************************************************************/
static void MergeSortIterative(int* _arr, size_t _size, int* _mergeArr)
{
	int j, subArray, flag = 1;
	subArray = 2;
	
	while (flag )
	{
		for (j = 0; j < _size; j += subArray)
		{
			if (_size - j >= subArray)
			{
				Merge( _arr + j, _mergeArr, subArray, subArray / 2);
			}
			else if (_size - j > subArray / 2)
			{
				Merge( _arr + j, _mergeArr, _size - j, subArray / 2);
			}
		}
		if (subArray > _size)
		{
			flag = 0;
		}
		subArray *= 2;
	}

}
/*****************************************************************************/
/*****************************************************************************/
ADTErr RadixSort(int* _arr, size_t _size)
{
  int digitsArray[10]={0};
  int maxNum, digitsNum,i, _digit;
  if(NULL == _arr)
  {
    return ERR_NOT_INITIALIZED;
  }
  if(_size == 0)
  {
    return ERR_GENERAL;
  }
  maxNum =FindMax(_arr,_size);
  /*calcs num of digits*/
  digitsNum = CalcNumOfDigits(maxNum);
  _digit =1;
  for(i=0; i< digitsNum; ++i)
  {
    ModifiedCountingSort(_arr, _size, _digit);
    _digit*=10;
  }
  return ERR_OK;
}
/*****************************************************************************/
/*****************************************************************************/
ADTErr CountingSort(int* _arr, size_t _size)
{
	int max;
	int* countArr = NULL;
	int* SortArr = NULL;
	max = FindMax(_arr, _size);
	max+=1;
	if((countArr = CreateCountArr((size_t)max)) == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	/*counter array creation*/
	CountNumsApperance(_arr, _size, countArr);
	SumCounts(countArr, (size_t)(max));
	/*sort array creation*/
	if((SortArr = CreateCountArr(_size)) == NULL)
	{
		free(countArr);
		return ERR_ALLOCATION_FAILED;
	}
	/**/
	BuildSortArr(_arr, SortArr, countArr, _size);
	ArrCopy(SortArr, _arr, _size);
	free(countArr);
	free(SortArr);
	return ERR_OK;
}
/*****************************************************************************/
/*****************************************************************************/
ADTErr ModifiedCountingSort(int* _arr, size_t _size, size_t _digit)
{
	int countArr[10] = {0};
	int* SortArr = NULL;
	/*counter array creation*/
	ModCountNumsApperance(_arr, _size, countArr, _digit);
	SumCounts(countArr, 10);
	/*sort array creation*/
	if((SortArr = CreateCountArr(_size)) == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	/**/
	ModBuildSortArr(_arr, SortArr, countArr, _size, _digit);
	ArrCopy(SortArr, _arr, _size);
	free(SortArr);
	return ERR_OK;
}
/*****************************************************************************/
/*****************************************************************************/
static int FindMax(int *_arr, size_t _size)
{
	int max, i;
	max=_arr[0];
	for(i=0; i<_size; ++i)
	{
		if(_arr[i]>max)
		{
			max = _arr[i];
		}
	}
	return max;		
}
/*****************************************************************************/
/*****************************************************************************/
static int* CreateCountArr(size_t _size)
{
	int* ptr =NULL;
	if(_size == 0)
	{
		return NULL;
	}
	ptr = (int*)calloc(_size, sizeof(int));
	return ptr;
}	
/*****************************************************************************/
/*****************************************************************************/
static void CountNumsApperance(int* _sourceArr, size_t _sourceSize, int* _countArr)
{
	size_t i;
	for(i = 0; i < _sourceSize; ++i)
	{
		++_countArr[_sourceArr[i]];
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static void ModCountNumsApperance(int* _sourceArr, size_t _sourceSize, int* _countArr, size_t _digit)
{
	size_t i;
	for(i = 0; i < _sourceSize; ++i)
	{
		++_countArr[(_sourceArr[i] / _digit) % 10];
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static void SumCounts(int* _countArr, size_t _countSize)
{
	size_t i;
	for(i=1; i<_countSize; ++i)
	{
		_countArr[i]+=_countArr[i-1];
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static void ArrCopy(int* _sourceArr, int* _destArr, size_t _size)
{
	size_t i;
	for(i = 0; i < _size; ++i)
	{
		_destArr[i] = _sourceArr[i];
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static void BuildSortArr(int* _sourceArr, int* _destArr, int* _countArr, size_t _sourceSize)
{
	size_t i;
	int srcNum, countNum;
	for(i = _sourceSize; i > 0; --i)
	{
		srcNum = _sourceArr[i-1];
		countNum = _countArr[srcNum];
		countNum-=1;
		_destArr[countNum] = srcNum; 
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static void ModBuildSortArr(int* _sourceArr, int* _destArr, int* _countArr, size_t _sourceSize, size_t _digit)
{
	size_t i;
	int srcNumDigit, countNum;
	for(i = _sourceSize; i > 0; --i)
	{
		srcNumDigit = ((_sourceArr[i-1])/_digit) % 10;
		countNum = --_countArr[srcNumDigit];
		_destArr[countNum] = _sourceArr[i-1]; 
	}
}	
/*****************************************************************************/
/*****************************************************************************/
static int CalcNumOfDigits(int _num)
{
  int digitsNum = 0;
  while(_num != 0)
  {
    ++digitsNum;
    _num/=10;
  }
  return digitsNum;
}
/*****************************************************************************/
/*****************************************************************************/

