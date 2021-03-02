#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "ADTDefs.h" /*Error return*/
#include <stdlib.h> /*size_t*/

typedef struct Vector Vector;

/*******************************************************************************
*[Description]:Creates Main Vector Structure By Allocating _initialSize Memory
*Elements.  
*[Input]:Initial allocation size of Memory and size of shunk blockSize when its
*nedded 
*[output]:Pointer to Vector data structure.
*[Errors]:(1) ERR_ALLOCATION_FAILED (when malloc fails) (2) ERR_OK (malloc 
*success  
*******************************************************************************/
Vector*	VectorCreate(size_t _initialSize, size_t _extensionBblockSize);


/*******************************************************************************
*[Description]:Deleting Main Vector Structure By freeing the whole allocated 
*Memory  
*[Input]:Main vector structure pointer 
*[output]:No output for this function
*[Errors]:(1) ERR_NOT_INITIALIZED (when pointer is points to NULL)
*******************************************************************************/
void	VectorDestroy(Vector* _vector);

/*******************************************************************************
*[Description]:Adding new item to Vector to the last array element 
*[Input]:Main vector structure pointer & item value 
*[output]:Inserting this item to the right place in the array
*[Errors]:(1) ERR_OK (Adding operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_REALLOCATION_FAILED (when realloc fails)
*(4) ERR_OVERFLOW (when vector is full and _extensionBblockSize is Zero)
*******************************************************************************/
ADTErr   VectorAdd(Vector *_vector,  int  _item); 	

/*******************************************************************************
*[Description]:Deleting the last inserted item 
*[Input]:Main vector structure pointer & pointer to hold the deleted item 
*[output]:deleting the contenent of array element and hold it 
*[Errors]:(1) ERR_OK (Deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW (when there is no items to 
*delete
*******************************************************************************/
ADTErr   VectorDelete(Vector *_vector,  int* _item); 

/*******************************************************************************
*[Description]:Getting an item value from vector array in the range 1-numOfItems
*[Input]:Main vector structure pointer & position or inddex of this item & 
*pointer for holding item value 
*[output]:integer data type. item. 
*[Errors]:(1) ERR_OK (getting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW (when there is no items to 
*get (4) ERR_WRONG_INDEX (when accessing wrong index)
*******************************************************************************/
ADTErr   VectorGet(Vector *_vector, size_t _index, int *_item);

/*******************************************************************************
*[Description]:Setting or updating an item in agiven index range 1-numOfItems
*[Input]:Main vector structure pointer & index were we setting & item value to 
*be set 
*[output]:ADTErr error Warnings 
*[Errors]:(1) ERR_OK (setting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when Vector pointer points to NULL) (3) ERR_WRONG_INDEX (when accessing wrong 
*index)
*******************************************************************************/
ADTErr   VectorSet(Vector *_vector, size_t _index, int  _item);

/*******************************************************************************
*[Description]:Calculating and returning number of items interd
*[Input]:Main vector structure pointer & pointer to num of items 
*[output]:ADTErr error Warnings and num of items
*[Errors]:(1) ERR_NOT_INITIALIZED (when Vector pointer points to NULL) 
*******************************************************************************/
ADTErr   VectorItemsNum(Vector *_vector, size_t	*_numOfItems);
int IsEmptyVector(Vector *_vector);

/*  Unit-Test functions  */
/*******************************************************************************
*[Description]:Unit-Test function - Printing values variabels for Debug and test 
*only
*[Input]:Main vector structure pointer 
*[output]: printing values of variabels to stdout 
*[Errors]:(1) ERR_NOT_INITIALIZED (when Vector pointer points to NULL)
*******************************************************************************/
void VectorPrint(Vector *_vector);


#endif /* _VECTOR_H_ */
