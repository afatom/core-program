#include "DAstr.h"
#include <stdlib.h>
#include <stdio.h>



int* CreateDA (size_t size)
{
    int* DAptr = (int*)malloc (size*sizeof(int));
    return DAptr;
}

void DestroyDA (int* DAptr)
{
    if (NULL==DAptr)
    {
        return;
    }
    free (DAptr);
    DAptr=NULL; /*avoid Double free */
    return;
}

int ReallocDA (int** DAptr, size_t *size, size_t IncrBlockSize)
{
    
    int* tempDA=NULL;
    tempDA=(int*)realloc(*DAptr, (*size+IncrBlockSize)*sizeof(int));
    
    if (NULL==tempDA)
    {
        return REAALLOCATION_FAILURE;
    }
    *DAptr=tempDA;
    *size=*size+IncrBlockSize;
    return OK;
}

int InsertDA(int **DAptr, int data, size_t *NumOfElements, size_t *size, size_t IncrBlockSize)
{
    /*check input pointers*/
    if (NULL==*DAptr || NULL==NumOfElements || NULL==size)
    {
        return POINTER_NOT_INITIALIZED;
    }
    /*there is aspace in the array*/
    if (*NumOfElements<*size)
    {
        (*DAptr)[*NumOfElements]=data;
        ++(*NumOfElements);
        return OK;
    }
    /*there is no space and incrBlock =0  -overflow situation-*/
    if (*size==*NumOfElements && IncrBlockSize==0)
    {
        return OVERFLOW;
    }
    /*there is no space and incrBlock >0  -Realloc situation-*/
    if (*size == *NumOfElements && IncrBlockSize > 0)
    {
        /* This i one way to work with [this code do the work]
        int* temp =NULL;
        temp = (int *)realloc (*DAptr, (*size + IncrBlockSize) * sizeof(int));
        if (NULL == temp)
        {
            return REAALLOCATION_FAILURE;
        }
        *DAptr=temp;
        *size=*size+IncrBlockSize;
        */
        int reallocRes; 
        if ((reallocRes = ReallocDA (DAptr, size, IncrBlockSize))!=OK)
        {
            return reallocRes;
        }
        (*DAptr)[*NumOfElements] = data;
        ++(*NumOfElements);
        return OK;
    }
}

int DeleteDA(int *DAptr, int *data, size_t *NumOfElements)
{
    if (NULL==DAptr || NULL==NumOfElements)
    {
        return POINTER_NOT_INITIALIZED;
    }
    /*underflow situation*/
    if (*NumOfElements<1)
    {
        return UNDERFLOW;
    }
    *data = DAptr[*NumOfElements-1];
    --(*NumOfElements);
    return OK;
}

void PrintDA(int* DAptr, size_t* NumOfElements, size_t *size)
{
    if (NULL==DAptr || NULL==NumOfElements || NULL==size)
    {
        printf("Error! one of the pointers is NULL !\n");
        return;
    }
    printf("***************************\n");
    printf ("DA size: %lu.\n",*size);
    printf("DA NOE: %lu.\n", *NumOfElements);
    printf("----------------------------\n");
    for (int i=0; i<*NumOfElements; ++i)
    {
        printf("|%d ", *((DAptr + i)));
        
    }
    printf("\n");
    return;
}
