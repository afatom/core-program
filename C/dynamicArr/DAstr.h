#ifndef _DASTR_H_
#define _DASTR_H_

#include <stdlib.h>

/*******************************************************************************
*[def]: Creating daynamic array with size elements
*[input]: size of the daynamic array
*[output]: Pointer to the above array (Or NULL if allocation fails)
*[Errors]:None
*******************************************************************************/
int* CreateDA (size_t size);

/*******************************************************************************
*[def]: Destroy daynamic array
*[input]: pointer to the daynamic array
*[output]: No output (freeing memory)
*[Errors]:None
*******************************************************************************/
void DestroyDA (int* DAptr);

/*******************************************************************************
*[def]: Inserts element to the array (inserting in the last)
*[input]: data to insert, adress of the DAarray, IncrBlock  
*[output]:inserting status. 
*[Errors]:(0=ok, 1=poiter not initialized, 2=realloc fail, 3=overflow).
*******************************************************************************/
int InsertDA (int** DAptr,int data, size_t *NumOfElements, size_t* size, size_t IncrBlockSize);

/*******************************************************************************
*[def]:Removing last element and holds its adress.
*[input]:pointer to DA array, NOE, and pointer for holding removed adress   
*[output]:Deleting status
*[Errors]:(0=ok, 1=poiter not initialized, 4=underflow).
*******************************************************************************/
int DeleteDA (int* DAptr, int* Data, size_t* NumOfElements);

/*******************************************************************************
*[def]:printing DA array elements
*[input]:DAptr, NOE, SIZE   
*[output]:void
*[Errors]:NONE
*******************************************************************************/
void PrintDA (int* DAptr, int* NumOfElements, size_t* size);


#endif/*_DASTR_H_*/