/******************************************
[File Name]:Header File H.W 2 - Stack ADT
**[Course]:Data Structure. Core51
**[H.W]:2
**[Author]:Adham 
*******************************************/
#ifndef _STACK_H_
#define _STACK_H_

#include "vector.h"
#include "ADTDefs.h"
#include <stdlib.h>
 
typedef struct Stack Stack;

/*******************************************************************************
*[Description]:Creating Stack Datat Structure. 
*[Input]:size of the stack and Increment blocksize in case stack is full 
*[output]:Stack Data structure with _size elements 
*[Errors]:(1) ERR_OK (creation operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED (when Malloc fails)
*******************************************************************************/
Stack* StackCreate (size_t _size, size_t _blockSize);

/*******************************************************************************
*[Description]:Deleting Stack Datat Structure. 
*[Input]:pointer to stack. 
*[output]:No output (Memory freeing) 
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
void StackDestroy (Stack* _stack);

/*******************************************************************************
*[Description]:Adding an item at the end of the Stack Datat Structure. 
*[Input]:pointer to stack and an item to be added 
*[output]:Status Error Code 
*[Errors]:(1) ERR_OK (Adding operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED in case we need to 
*allocate more memory. (4) ERR_OVERFLOW in case there is no free space and block
*size is Zero.
*******************************************************************************/
ADTErr StackPush (Stack* _stack, int _item);

/*******************************************************************************
*[Description]:Deleting an item at the end of the Stack Datat Structure. 
*[Input]:pointer to stack and a pointer to deleted item 
*[output]:Status Error Code 
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW wen there is no items to delete
*******************************************************************************/
ADTErr StackPop (Stack* _stack, int* _item);

/*******************************************************************************
*[Description]:Points to the Last Input Item with _item pointer  
*[Input]:pointer to stack and a pointer for pointing to last input 
*[output]:Status Error Code 
*[Errors]:(1) ERR_OK (points operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
ADTErr StackTop (Stack* _stack, int* _item);

/*******************************************************************************
*[Description]:Check if all stack elements are ZERO   
*[Input]:pointer to stack  
*[output]:Int 1= All elements are zero  0=Not all the elements are zero 
*[Errors]:(1) ERR_OK (check operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
int StackIsEmpty (Stack* _stack);


/******************************************************************************/
/*  Unit-Test functions Only                                                  */
/******************************************************************************
*[Description]:Unit-Test function - Printing values variabels for Debug and test 
*only
*[Input]:Stack data structure pointer 
*[output]: printing values of variabels to stdout 
*[Errors]:(1) ERR_NOT_INITIALIZED (when stack pointer points to NULL)
*******************************************************************************/
void StackPrint (Stack* _stack);
/*Unit-Test function Only*/
/*calcs NOI*/
ADTErr StackItemsNum(Stack *_stack, int *_numOfItems);


#endif /*_STACK_H_*/
