#ifndef _HEAP_H_
#define _HEAP_H_
#include "ADTDefs.h"
#include <stddef.h>    /*size_t*/

typedef struct Heap Heap;

/*******************************************************************************
*[Description]:Building Heap Tree DS (Heap Max)  
*[Input]:Main vector structure pointer 
*[Return]:Heap pointer
*[Errors]:Null will be returned in anull vector situation
*******************************************************************************/
Heap* HeapBuild(Vector* _vec);

/*******************************************************************************
*[Description]:Destroying heap DS and returning Vector to main
*[Input]:heap pointer 
*[Return]:vector pointer
*[Errors]:Null will be returned in anull vector pointer or null heap pointer or 
*double free situation.
*******************************************************************************/

Vector* HeapDestroy(Heap* _heap);
/*******************************************************************************
*[Description]:Inserting data to Heap while keeping heap max structure
*[Input]:heap pointer and data to be inserted
*[Return]:Err Status
*[Errors]:ERR_NOT_INITIALIZED int Null heap or Null vector pointer ERR_OVERFLOW
*in vector overflow situation.
*******************************************************************************/

ADTErr HeapInsert(Heap* _heap, int _data);
/*******************************************************************************
*[Description]:Returning Max Element int the heap.
*[Input]:heap pointer and data pointer. 
*[Return]:Err Status
*[Errors]:ERR_NOT_INITIALIZED int Null heap or Null vector pointer, ERR_GENERAL
*in data null pointer or no elements exist case. 
*******************************************************************************/
ADTErr HeapMax(const Heap* _heap, int* _data);

/*******************************************************************************
*[Description]:Returning and extracting Max Element in the heap.
*[Input]:heap pointer and data pointer. 
*[Return]:Err Status
*[Errors]:ERR_NOT_INITIALIZED int Null heap or Null vector pointer, ERR_GENERAL
*in data null pointer or no elements exist case. ERR_UNDERFLOW in underflow 
*situation
*******************************************************************************/
ADTErr HeapExtractMax(Heap* _heap, int* _data);
/*******************************************************************************
*[Description]:Returning Heap items num.
*[Input]:heap pointer. 
*[Return]:Number of items in the heap.
*[Errors]:None. Zero will be returned in NULL heap situation.
*******************************************************************************/
size_t HeapItemsNum(const Heap* _heap);
/*******************************************************************************
*[Description]:Heap printing.
*[Input]:heap pointer. 
*[Return]:Void
*[Errors]:None. 
*******************************************************************************/
void HeapPrint(const Heap* _heap);

#endif /*_HEAP_H_*/
