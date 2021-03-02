#include <stdlib.h>
#include "stack.h"
#include "vector.h"
#include "ADTDefs.h"
#include <stdio.h>

#define MAGIC_STACK_NUM 5317733852

struct Stack
{
    Vector *m_vector;
    size_t m_magic; /*double free uses*/
};
/*******************************************************************************
*[Description]:Creating Stack Datat Structure.
*[Input]:size of the stack and Increment blocksize in case stack is full
*[output]:Stack Data structure with _size elements
*[Errors]:(1) ERR_OK (creation operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED (when Malloc fails)
*******************************************************************************/
Stack* StackCreate (size_t _size, size_t _blockSize)
{
    Stack *stackPtr = NULL;
    /*check inputs*/
    if (_size==0 && _blockSize==0)
    {
        return NULL;
    }
    stackPtr = (Stack*)malloc(sizeof(Stack));
    if (NULL == stackPtr)
    {
        return NULL;
    }
    stackPtr->m_vector = VectorCreate(_size, _blockSize);
    /*check if vector create succeded*/
    if (NULL == stackPtr->m_vector)
    {
        free(stackPtr);
        return NULL;
    }
    stackPtr->m_magic = MAGIC_STACK_NUM;
    return stackPtr;
}

/*******************************************************************************
*[Description]:Deleting Stack Datat Structure.
*[Input]:pointer to stack.
*[output]:No output (Memory freeing)
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL)
*******************************************************************************/
void StackDestroy (Stack* _stack)
{
    if (NULL == _stack)
    {
        return;
    }
    if(_stack->m_magic == 0)
    {
        return;
    }
    _stack->m_magic = 0;
    free(_stack->m_vector);
    _stack->m_vector = NULL;
    free(_stack);
    return;
}

/*******************************************************************************
*[Description]:Adding an item at the end of the Stack Datat Structure.
*[Input]:pointer to stack and an item to be added
*[output]:Status Error Code
*[Errors]:(1) ERR_OK (Adding operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED in case we need to
*allocate more memory. (4) ERR_OVERFLOW in case there is no free space and block
*size is Zero.
*******************************************************************************/
ADTErr StackPush(Stack *_stack, int _item)
{
    ADTErr addItemResult;
    if (NULL == _stack)
    {
        return ERR_STACK_NOT_INITIALIZED;
    }
    /*calling vector function add*/
    addItemResult = VectorAdd(_stack->m_vector, _item);
    return addItemResult;
}

/*******************************************************************************
*[Description]:Deleting an item at the end of the Stack Datat Structure.
*[Input]:pointer to stack and a pointer to deleted item
*[output]:Status Error Code
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL) (3) ERR_UNDERFLOW wen there is no items to delete
*******************************************************************************/
ADTErr StackPop(Stack *_stack, int *_item)
{
    ADTErr rmItemResult;
    if (NULL == _stack)
    {
        return ERR_STACK_NOT_INITIALIZED;
    }
    if (NULL == _item)
    {
        return ERR_STACK_GENERAL;
    }
    rmItemResult = VectorDelete(_stack->m_vector, _item);
    return rmItemResult;
}

/*******************************************************************************
*[Description]:Points to the Last Input Item with _item pointer
*[Input]:pointer to stack and a pointer for pointing to last input
*[output]:Status Error Code
*[Errors]:(1) ERR_OK (points operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL)
*******************************************************************************/
ADTErr StackTop(Stack *_stack, int *_item)
{
    ADTErr status;
    size_t _numOfItems = 0;
    if (NULL == _stack)
    {
        return ERR_STACK_NOT_INITIALIZED;
    }
    if (NULL == _item)
    {
        return ERR_STACK_GENERAL;
    }
    status = VectorItemsNum(_stack->m_vector, &_numOfItems);
    if (status != ERR_OK)
    {
        return status;
    }
    if (_numOfItems == 0)
    {
    	return ERR_EMPTY_STACK;
    }
    status = VectorGet(_stack->m_vector, (size_t)_numOfItems-1, _item);
    return status;
}

/*******************************************************************************
*[Description]:Check if all stack elements are ZERO
*[Input]:pointer to stack
*[output]:Int 1= All elements are zero  0=Not all the elements are zero
*[Errors]:(1) ERR_OK (check operation seccess) (2) ERR_NOT_INITIALIZED
*(when pointer points to NULL)
*******************************************************************************/
int StackIsEmpty(Stack *_stack)
{
    ADTErr errStatus;
    size_t _numOfItems = 0;
    if (NULL == _stack)
    {
        return 1;
    }
    errStatus = VectorItemsNum(_stack->m_vector, &_numOfItems);
    return (errStatus != ERR_OK || _numOfItems == 0);
}
/*  Unit-Test functions  */
/*******************************************************************************
*[Description]:Unit-Test function - Printing values variabels for Debug and test
*only
*[Input]:Stack data structure pointer
*[output]: printing values of variabels to stdout
*[Errors]:(1) ERR_NOT_INITIALIZED (when stack pointer points to NULL)
*******************************************************************************/
void StackPrint(Stack *_stack)
{
    if (NULL == _stack)
    {
        printf("ERR_STACK_NOT_INITIALIZED\n");
        return;
    }
    VectorPrint(_stack->m_vector);
    return;
}
/******************************/
/*  Unit-Test function Only  */
/****************************/
/*******************************************************************************
*[Description]:Unit-Test function - calculates Num Of Items
*[Input]:Stack data structure pointer and pointer to var
*[output]: Num of items
*[Errors]:(1) ERR_NOT_INITIALIZED (when stack pointer points to NULL)
*******************************************************************************/
ADTErr StackItemsNum(Stack *_stack, int *_numOfItems)
{
    size_t noi;
    ADTErr vecFunctionResult;
    if (NULL == _stack)
    {
        return ERR_STACK_NOT_INITIALIZED;
    }
    if(NULL == _numOfItems)
    {
        return ERR_STACK_GENERAL;
    }
    vecFunctionResult = VectorItemsNum(_stack->m_vector, &noi);
    if (vecFunctionResult != ERR_OK)
    {
        return vecFunctionResult;
    }
    *_numOfItems = (int)noi;
    return ERR_OK;
}
