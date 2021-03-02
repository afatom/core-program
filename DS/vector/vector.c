#include "vector.h"
#include <stdio.h> /*printf*/
#include <stdlib.h>

#define MAGIC_NUM 5317733001
#define INCREASE_MEMORY 1
#define REDUCE_MEMORY -1

struct Vector
{
	int*    m_items;			/*Data Array of items */
	size_t  m_originalSize;   /*original allocated memory for items)*/
	size_t  m_size;           /*recent/actual allocated memory for items) */
	size_t  m_nItems;     	  /* recent/actual number of items */
	size_t  m_blockSize;	  /* the chunk size to be allocated when no memory*/
    size_t  m_magicNumber;   /*Double free*/
};

/*******************************************************************************
*[Description]:Creates Main Vector Structure By Allocating _initialSize Memory
*Elements.  
*[Input]:Initial allocation size of Memory and size of shunk blockSize when its
*nedded 
*[output]:Pointer to Vector data structure.
*[Errors]:(1) ERR_ALLOCATION_FAILED (when malloc fails) (2) ERR_OK (malloc 
*success  
*******************************************************************************/
Vector*	VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
    Vector* vecPtr;
    /*check inputs*/
    if (_initialSize == 0 && _extensionBblockSize == 0)
    {
        return NULL;
    }
    /*check malloc*/
    vecPtr = (Vector*) malloc (sizeof(Vector));
    
    if (NULL == vecPtr)
    {
        return NULL;
    }
    /*allocating mem for mitems arr*/
    vecPtr->m_items = (int*) malloc (_initialSize*sizeof(int));
    
    if (NULL == vecPtr->m_items)
    {
        free (vecPtr);
        return NULL;
    }
    /*Vector structure members itializing */
    vecPtr->m_originalSize = _initialSize;
    vecPtr->m_size = _initialSize;
    vecPtr->m_nItems = 0;
    vecPtr->m_blockSize = _extensionBblockSize;
    vecPtr->m_magicNumber = MAGIC_NUM;

    return vecPtr;
}
/*******************************************************************************
*[Description]:Deleting Main Vector Structure By freeing the whole allocated 
*Memory  
*[Input]:Main vector structure pointer 
*[output]:No output for this function
*[Errors]:(1) ERR_NOT_INITIALIZED (when pointer is points to NULL)
*******************************************************************************/
void	VectorDestroy(Vector* _vector)
{
    /*check params*/
    if (NULL == _vector || _vector->m_magicNumber == MAGIC_NUM)
    {
        return;
    }
    /*Avoid double free situation*/
    _vector->m_magicNumber = 0;
    free(_vector->m_items);
    free(_vector);
    return;
}

/*  Unit-Test functions  */
/*******************************************************************************
*[Description]:Unit-Test function - Printing values variabels for Debug and test 
*only
*[Input]:Main vector structure pointer 
*[output]: printing values of variabels to stdout 
*[Errors]:(1) ERR_NOT_INITIALIZED (when Vector pointer points to NULL)
*******************************************************************************/
void VectorPrint(Vector *_vector)
{
    size_t j;
    if (NULL == _vector)
    {
        printf("Vector Does Not Exist !\n");
        return;
    }
    if (_vector->m_nItems == 0)
    {
        printf("Empty Vector ! There Is No Elements To Print.\n");
        return;
    }
    printf("**************************\n");
    printf("\nVector originalsize: %lu\n", _vector->m_originalSize);
    printf("Vector Items Number: %lu\n", _vector->m_nItems);
    printf("Vector m_size: %lu\n", _vector->m_size);
    printf("Vector chunk: %lu\n", _vector->m_blockSize);
    printf("**************************\n");
    for (j = 0; j < _vector->m_nItems; ++j)
    {
        printf("[ %d ]", _vector->m_items[j]);
    }
    printf("\n");
    return;
}

/*******************************************************************************
*[Description]:Adding new item to Vector to the last array element 
*[Input]:Main vector structure pointer & item value 
*[output]:Inserting this item to the right place in the array
*[Errors]:(1) ERR_OK (Adding operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_REALLOCATION_FAILED (when realloc fails)
*(4) ERR_OVERFLOW (when vector is full and _extensionBblockSize is Zero)
*******************************************************************************/
static int IsOverFlow(Vector *_vector)
{
    if (_vector->m_nItems == _vector->m_size && _vector->m_blockSize == 0)
    {
        return 1; /*over flow*/
    }
    return 0;
}

static int IsReallocNeeded(Vector *_vector)
{
    if ((_vector->m_nItems == _vector->m_size) && (_vector->m_blockSize != 0))
    {
        return 1; /*realloc needed*/
    }
    return 0;
}

static ADTErr ReallocMitemsArray(Vector *_vector, int _operation)
{
    int *temp = NULL;
	size_t newSize = 0;
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }
	
	if (_operation == 1) /*increasing mem*/
	{
		newSize = _vector->m_size + _vector->m_blockSize;			
	}
	
	else
	{
		newSize = _vector->m_size - _vector->m_blockSize;	
	}
	
    temp = (int*)realloc((_vector->m_items), (newSize) * sizeof(int));
    if (NULL == temp)
    {
        return ERR_REALLOCATION_FAILED;
    }
    _vector->m_items = temp;
    _vector->m_size = newSize;
    return ERR_OK;
}

ADTErr   VectorAdd(Vector *_vector,  int  _item)
{
    int result = 0;
    ADTErr addResult;
    
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }
    
    if ((result = IsOverFlow(_vector)))
    {
        return ERR_OVERFLOW;
    }
    
    if ((result = IsReallocNeeded(_vector)))
    {
        addResult = ReallocMitemsArray(_vector, INCREASE_MEMORY);
        if (addResult != ERR_OK)
        {
            return addResult;
        }
    }

    _vector->m_items[_vector->m_nItems] = _item;
    ++_vector->m_nItems;
    return ERR_OK;
}

/*******************************************************************************
*[Description]:Deleting the last inserted item 
*[Input]:Main vector structure pointer & pointer to hold the deleted item 
*[output]:deleting the contenent of array element and hold it 
*[Errors]:(1) ERR_OK (Deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW (when there is no items to 
*delete
*******************************************************************************/
static int IsUnderFlow(Vector *_vector)
{
    if (_vector->m_nItems == 0)
    {
        return 1; /*under flow*/
    }
    return 0;
}
static int IsReduceNeeded(Vector *_vector)
{
    if ((_vector->m_nItems == (_vector->m_size - 2 * _vector->m_blockSize)) && (_vector->m_size > _vector->m_originalSize))
    {
        return 1; /*reduce is needed*/
    }
    return 0;
}
ADTErr VectorDelete(Vector *_vector, int *_item)
{
    int result = 0;
    ADTErr deleteResult;
    /*check params*/
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (NULL == _item)
    {
        return ERR_GENERAL;
    }
    /*check underflow*/
    if ((result = (IsUnderFlow(_vector))))
    {
        return ERR_UNDERFLOW;
    }
    /*delete*/
    *_item=_vector->m_items[_vector->m_nItems-1];
    --_vector->m_nItems;
    /*check if realloc needed*/
    if ((result = IsReduceNeeded(_vector)))
    {
        /*reduce array: call realloc function*/
        deleteResult = ReallocMitemsArray(_vector, REDUCE_MEMORY);
        if (deleteResult != ERR_OK)
        {
            return deleteResult;
        }
    }
    return ERR_OK;
}
/*******************************************************************************
*[Description]:Getting an item value from vector array in the range 1-numOfItems
*[Input]:Main vector structure pointer & position or inddex of this item & 
*pointer for holding item value 
*[output]:integer data type. item. 
*[Errors]:(1) ERR_OK (getting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW (when there is no items to 
*get (4) ERR_WRONG_INDEX (when accessing wrong index)
*******************************************************************************/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
    /*check params*/
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (NULL == _item)
    {
        return ERR_GENERAL;
    }
    if (_index >= _vector->m_nItems)
    {
        return ERR_WRONG_INDEX;
    }
    *_item = _vector->m_items[_index];
    return ERR_OK;
}

/*******************************************************************************
*[Description]:Setting or updating an item in agiven index range 1-numOfItems
*[Input]:Main vector structure pointer & index were we setting & item value to 
*be set 
*[output]:ADTErr error Warnings 
*[Errors]:(1) ERR_OK (setting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when Vector pointer points to NULL) (3) ERR_WRONG_INDEX (when accessing wrong 
*index)
*******************************************************************************/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
    /*check params*/
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (_index >= _vector->m_nItems)
    {
        return ERR_WRONG_INDEX;
    }
    _vector->m_items[_index] = _item;
    return ERR_OK;
}

/*******************************************************************************
*[Description]:Calculating and returning number of items interd
*[Input]:Main vector structure pointer & pointer to num of items 
*[output]:ADTErr error Warnings and num of items
*[Errors]:(1) ERR_NOT_INITIALIZED (when Vector pointer points to NULL) 
*******************************************************************************/
ADTErr VectorItemsNum(Vector *_vector, size_t *_numOfItems)
{
    /*check params*/
    if (NULL == _vector)
    {
        return ERR_NOT_INITIALIZED;
    }

    *_numOfItems = _vector->m_nItems;
    return ERR_OK;
}
