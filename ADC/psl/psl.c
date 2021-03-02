#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define NDEBUG
#define BUFF 2048



static int iAmStaticGlobalVar = 888;

int iAmGlobalVar = 909;

const char* ROPtr="HIIIIIIIIIIII read only!";
int uinitglobalvar1;
int uinitglobalvar2;

static int ThisIsStaticFunction(int *arr, int size)
{
    if(arr)
    {
        printf("its Nice to be modified !\n");
    }
    puts("Bad Value Param!");
    return 1;
}



int ThisIsExternFunction(int* arr, int size)
{
    int i=0;
    if(!arr || !size)
    {
        return 0;
    }

    for(i=0; i < size; ++i)
    {
        arr[i]= i;
    }
    return 1;
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



int main (int argc, char* argv[])
{
	int i;


	static int iAmStaticLocalVar = 105;
	int arrx[10]={1,2,3,4,5,6,7,8,9,10};
	char mchar = 'a';
	char* str="OMG";
	int sds;
	int y;
	int xx;
	char sdf;
	char sppr[10]="asdfg";
	
	int* alloc=NULL;

	fprintf(stdout,"hi");
	

	alloc = (int*)malloc(BUFF * sizeof(int));
	assert(NULL != alloc);

	ThisIsExternFunction(alloc, BUFF);

	ThisIsStaticFunction(alloc, BUFF);

	
	
	--iAmStaticGlobalVar;
	++iAmGlobalVar;
	free(alloc);
	++iAmStaticLocalVar;


    return 0;
}
