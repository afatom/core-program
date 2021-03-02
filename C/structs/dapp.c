#include "dapp.h"
#include <stdlib.h>
#include <stdio.h>

#define MAGIC_NUM 154628512348

struct DA {
    size_t MagicNumber;
    int* DataArr;
    size_t size;
    size_t NumOfElements;
    size_t IncrBlockSize;
};

DA* CreateDA (size_t size, size_t IncrBlockSize)
{
    /*Impossible work situation*/
    if (size==0 && IncrBlockSize==0)
    {
        return NULL;
    }
    /*Allocating Memory for DA pointer*/
    DA* DAPtr = (DA*) malloc (1*sizeof(DA));
    /*check if malloc success*/
    if (NULL==DAPtr)
    {
        return NULL;
    }
    /*Allocating Memory for data array*/
    DAPtr->DataArr= (int*) malloc (size*sizeof(int));
    /*check if malloc success*/
    if (NULL==DAPtr->DataArr)
    {
        /*free DAPtr allocation*/
        free (DAPtr);
        return NULL;
    }
    DAPtr->size = size;
    DAPtr->NumOfElements = 0;
    DAPtr->IncrBlockSize = IncrBlockSize;
    DAPtr->MagicNumber = MAGIC_NUM;
    return DAPtr;
}

void DestroyDA (DA* DAPtr)
{
    /*check if pointer freed before*/
    if (DAPtr == NULL || DAPtr->MagicNumber == 0)
    {
        return;
    }
    DAPtr->MagicNumber==0;
    free(DAPtr->DataArr);
    DAPtr->DataArr=NULL; /*Avoiding Invalid Memory usage*/
    free(DAPtr);/*DAPtr=NULL; will not change the DAPtr to NULL, Because DAPtr is alocal Variable
                *the change will not preserved after return command*/
    return;
}
int ReallocDataArr (DA* DAPtr)
{
    if (NULL==DAPtr)
    {
        return POINTER_NOT_INITIALIZED;
    }
    /*realloc atempt*/
    int* temp = (int*) realloc (DAPtr->DataArr,(DAPtr->size+DAPtr->IncrBlockSize)*sizeof(int));
    /*check if realloc success*/
    if (NULL==temp)
    {
        return REAALLOCATION_FAILURE;
    }
    DAPtr->DataArr=temp;
    DAPtr->size+=DAPtr->IncrBlockSize;
    return OK;
}
int InsertDA (DA* DAPtr, int data)
{
    if (NULL==DAPtr)
    {
        return POINTER_NOT_INITIALIZED;
    }
    /*Is realloc Needed*/
    if ((DAPtr->size==DAPtr->NumOfElements) && (DAPtr->IncrBlockSize)>0)
    {
        int reallocRes = ReallocDataArr (DAPtr);
        if (reallocRes)
        {
            return REAALLOCATION_FAILURE;

        }
    }
    /*enough space for insert*/
    if ((DAPtr->size > DAPtr->NumOfElements))
    {
        DAPtr->DataArr[DAPtr->NumOfElements]=data;
        ++DAPtr->NumOfElements;
        return OK;
    }
    /*Overflow situation indeed!*/
    return OVERFLOW;
}

int DeleteDA (DA* DAPtr, int* data)
{
    if (NULL==DAPtr)
    {
        return POINTER_NOT_INITIALIZED;
    }
    /*Check if there is at least one element*/
    if (DAPtr->NumOfElements >=1)
    {
        *data=DAPtr->DataArr[DAPtr->NumOfElements-1];
        //DAPtr->NumOfElements-=-1;
        --DAPtr->NumOfElements;
        return OK;
    }
    /*Underflow situation*/
    return UNDERFLOW;
}

void PrintDA (DA* DAPtr)
{
    if (NULL==DAPtr)
    {
        printf("DAPtr Dose Not Exist!\n");
        return;
    }
    printf("*************************\n");
    printf("DATA Array Size: %lu.\n",DAPtr->size);
    printf("DATA Array NOE: %lu.\n",DAPtr->NumOfElements);
    printf("DATA Array Incr: %lu.\n",DAPtr->IncrBlockSize);
    printf("*************************\n");
    if (DAPtr->NumOfElements==0)
    {
        printf("->Empty Data Array.");
    }
    for (int i=0; i<DAPtr->NumOfElements; ++i)
    {
        printf("|%d ",DAPtr->DataArr[i]);
    }
    printf("\n");
    
}