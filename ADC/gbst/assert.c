//#define NDEBUG 
#include <stdio.h>
#include <assert.h>



int main ()
{
    int i=10, j=20;
    assert(i<j);
    assert(j<i);
    printf("i %d j %d\n",i,j);
    return 0;
}