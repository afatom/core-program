#include "dastr.h"
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
    return;
}