#ifndef _VECTORSORT_H_
#define _VECTORSORT_H_

#include "ADTDefs.h"
#include "vector.h"
/*******************************************************************************
*[Description]:Sorting vector items array (smaller first) by insertion sort algo
*[Input]:Vector pointer.
*[output]:Sorted vector array (smaller first). 
*[Errors]:in success case ERR_OK will be returned, in NULL vector 
*ERR_NOT_INITIALIZED will be returned.
*******************************************************************************/
ADTErr InsertionSort(Vector* _vec);


#endif /*_VECTORSORT_H_*/
