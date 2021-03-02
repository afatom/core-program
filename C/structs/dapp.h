#ifndef _DAPP_H_
#define _DAPP_H_

#include <stdlib.h>

/*Errors Return*/
#define OK 0
#define POINTER_NOT_INITIALIZED 1
#define REAALLOCATION_FAILURE 2
#define OVERFLOW 3
#define UNDERFLOW 4
#define MAGIC_NUM 154628512348

typedef struct DA DA;
/*******************************************************************************
*[def]: Creating daynamic array data dtructure
*[input]: size of the daynamic array and IncrBlockSize chunk
*[output]: Pointer to the above Data structure (Or NULL if allocation fails)
*[Errors]:None [NULL if allocation fails]
*******************************************************************************/
DA* CreateDA (size_t size, size_t IncrBlockSize);

/*******************************************************************************
*[def]: Destroy daynamic array and structure pointer
*[input]: pointer to the structure
*[output]: No output (freeing memory)
*[Errors]:None
*******************************************************************************/
void DestroyDA (DA* DAPtr);

/*******************************************************************************
*[def]: Inserts element to the array (inserting in the last)
*[input]: data to insert, and pointer to data structure  
*[output]:inserting status. 
*[Errors]:(0=ok, 1=poiter not initialized, 2=realloc fail, 3=overflow).
*******************************************************************************/
int InsertDA (DA* DAPtr, int data);

/*******************************************************************************
*[def]:Removing last element and holds its adress.
*[input]:pointer to DA structure, and data pointer  
*[output]:Deleting status
*[Errors]:(0=ok, 1=poiter not initialized, 4=underflow).
*******************************************************************************/
int DeleteDA (DA* DAPtr, int* data);

/*******************************************************************************
*[def]:printing DA array elements
*[input]:DA structure pointer  
*[output]:void - array elements
*[Errors]:NONE
*******************************************************************************/
void PrintDA (DA* DAPtr);


#endif /*_DAPP_H_*/