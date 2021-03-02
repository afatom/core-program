#include <stdlib.h>  		/*size_t*/
#include <stdio.h>			/*printf*/
#include "mu_test.h"
#include <time.h>			/*srand*/
#include <assert.h>
#include "vector.h"
#include <dlfcn.h>


const char* dlibPath = "/home/adham/work/lib/libGDS.so.1.0";
#define NUM 1000
#define NDEBUG
#define _GNU_SOURCE
#define EXIT_FAILURE 1
#define PERSONS_ARR_SIZE 5
#define BLOCK_SIZE 50
#define INITIAL_SIZE 600
#define BUFF 50
#define ARR_HUGE_SIZE 5

#define TRUE 1
#define FALSE 0

UNIT(srand_Initialize)
	srand((unsigned int)time(NULL));
END_UNIT

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

static int iAmStaticGlobalVar = 888;

int iAmGlobalVar = 909;




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
        *(arr+i)= i*i;
    }
    return 1;
}
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/






/****************************************************************************************/
typedef struct Person{
        int age;
        int edu;
        char name[32];
    }Person; 


/****************************************************************************************/
/****************************************************************************************/
int PrintPersonInColor(void *_element, size_t _index, void *_context)
{
    printf("Person-%lu---Age---%d---Edu---%d.\n", _index, ((Person *)_element)->age, ((Person *)_element)->edu);
    return 1;

}
/****************************************************************************************/
/****************************************************************************************/
int PrintPerson(void *_element, size_t _index, void *_context)
{
    puts("Person Details:");
    printf("age %d edu %d name %s\n", ((Person *)_element)->age, ((Person *)_element)->edu, ((Person *)_element)->name);
    printf("Found at index %lu\n", _index);
    return 1;
}

void PrintOnePerson(void *_element, void *_context)
{
    printf("age  %d  edu  %d \n", ((Person *)_element)->age, ((Person *)_element)->edu);
}

static void PersonDestroy(void *_item)
{
    if ((Person *)_item == NULL)
    {
        return;
    }
    free((Person *)_item);
    /*_item = NULL;*/
}

/****************************************************************************************/
/****************************************************************************************/
static void swap(int* arr, int firstindex, int secindex)
{
    int firstval, secval;
    firstval =  arr[firstindex];
    secval =  arr[secindex];
    arr[secindex] = firstval;
    arr[firstindex]= secval;
    return;
}
/****************************************************************************************/
/****************************************************************************************/
static void ShuffleArray(int *_arr, int _size)
{
    int i, newIndex;
    for (i = _size - 1; i >= 0; --i)
    {
        newIndex = rand() % (i + 1);
        swap(_arr, i, newIndex);
    }
}

/****************************************************************************************/
/****************************************************************************************/
/*
static int CheckItemInVectorValidity(Person* _person, Vector* _vec, size_t _index)
{
    void* pval = NULL;
    VectorGet(_vec,_index,&pval);
    if(_person->age != ((Person*)pval)->age || _person != pval )
    {
        return FALSE;
    }
    return TRUE;
}*/
/****************************************************************************************/
/****************************************************************************************/


typedef void (*_elementDestroy)(void* _item);
typedef void (*VectorAction)(void* _element, void* _context);

void DestroyMyElement(void* item)
{
	/*do nothing*/
	return;
}

void DestroyMallocElements(void* item)
{
	free(item);
	return;
}



void PrintVec(void* elem, void* context)
{
	printf("%d\n",*((int*)elem));
	return;
}

/************************************************************ Vector Functions*/	
typedef Vector* (*vecCreate)(size_t , size_t);
typedef VectorResult (*vecAppend)(Vector*, void*);
typedef size_t (*vecSize)(const Vector*);
typedef void (*vecDestroy)(Vector** , _elementDestroy);
typedef VectorResult (*vecGet)(const Vector*, size_t , void**);
typedef VectorResult (*vecSet)(Vector*, size_t, void*);
typedef void (*printforEach)(const Vector*, VectorAction, void*);
typedef VectorResult (*vecRemove)(Vector*, void**);

/*****************************************************************************/
UNIT(Create_And_Destroy_Vector_Test)
	void* libHandle=NULL;
	char* error = NULL;
	Vector* vec = NULL;
	size_t initial = 0, block =0;
	vecCreate fp;
	vecDestroy fdstr;

	libHandle = dlopen(dlibPath,RTLD_LAZY);
	if(!libHandle)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	/*
	#pragma GCC diagnostic push    
	#pragma GCC diagnostic ignored "-Werror=pedantic"    
 	#pragma GCC diagnostic pop    
	*/	
	fp =(vecCreate)(dlsym(libHandle,"VectorCreate"));
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fdstr=(vecDestroy)dlsym(libHandle,"VectorDestroy");
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
	initial = 10;
	block = 15;
	vec = fp(initial, block);
	ASSERT_THAT(vec!=NULL);
	fdstr(&vec,DestroyMyElement);
	ASSERT_THAT(vec==NULL);
	dlclose(libHandle);
END_UNIT
/*****************************************************************************/
UNIT(Append_Get_And_Set_Vector_Test)
	void* libHandle=NULL;
	int* ptr1 = NULL;
	int* ptr2 = NULL;
	void* get = NULL;
	int p1=10;
	int p2=20;
	
	char* error = NULL;
	Vector* vec = NULL;
	size_t initial = 0, block =0;
		
	
	/*void (*fnDestroy)(Vector**, void (*_elementDestroy)(void* _item));*/ 	
	vecCreate fp;
	vecAppend fap;
	vecSize fsz;
	vecDestroy fdstr;
	vecGet fgt;
	libHandle = dlopen(dlibPath,RTLD_LAZY);
	if(!libHandle)
	{
	
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
	/*
	#pragma GCC diagnostic push    
	#pragma GCC diagnostic ignored "-Werror=pedantic"    
 	#pragma GCC diagnostic pop    
*/	
	fp =(vecCreate)(dlsym(libHandle,"VectorCreate"));
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
 	fap=(vecAppend)(dlsym(libHandle,"VectorAppend"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
 	fsz=(vecSize)(dlsym(libHandle,"VectorSize"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fdstr=(vecDestroy)dlsym(libHandle,"VectorDestroy");
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fgt=(vecGet)(dlsym(libHandle,"VectorGet"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	

	
	initial = 10;
	block = 15;
	vec = fp(initial, block);
	
	assert(vec != NULL);
	ptr1 = &p1;
	ptr2 = &p2;
	
	fap(vec,(void*)ptr1);
	fap(vec,(void*)ptr2);
	
	ASSERT_THAT(fsz(vec)==2);
	
	fgt(vec,1,&get);
	ASSERT_THAT(*((int*)get)==(*ptr1));
	fgt(vec,2,&get);
	ASSERT_THAT(*((int*)get)==(*ptr2));
	fdstr(&vec,DestroyMyElement);
	ASSERT_THAT(vec==NULL);
	dlclose(libHandle);
	
END_UNIT
/*****************************************************************************/
/****************************************************************************************/
UNIT(Vector__Append__Many__Test)
int i;
Vector *vec = NULL;

Person **arr = NULL;
Person *getPerson = NULL;
int shufled[ARR_HUGE_SIZE];
void* libHandle=NULL;



char* error = NULL;
	

/*void (*fnDestroy)(Vector**, void (*_elementDestroy)(void* _item));*/ 	
vecCreate fp;
vecAppend fap;
vecSize fsz;
vecDestroy fdstr;
vecGet fgt;
/**************************************/
libHandle = dlopen(dlibPath,RTLD_LAZY);
if(!libHandle)
{

	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}

/*
#pragma GCC diagnostic push    
#pragma GCC diagnostic ignored "-Werror=pedantic"    
#pragma GCC diagnostic pop    
*/	
fp =(vecCreate)(dlsym(libHandle,"VectorCreate"));
if((error = dlerror()) != NULL)
{
	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}

 	fap=(vecAppend)(dlsym(libHandle,"VectorAppend"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
	 	fsz=(vecSize)(dlsym(libHandle,"VectorSize"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fdstr=(vecDestroy)dlsym(libHandle,"VectorDestroy");
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fgt=(vecGet)(dlsym(libHandle,"VectorGet"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
arr = (Person **)malloc(ARR_HUGE_SIZE * sizeof(Person *));
ASSERT_THAT(arr != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    arr[i] = (Person *)malloc(1 * sizeof(Person));
    shufled[i] = i;
}

ShuffleArray(shufled, ARR_HUGE_SIZE);

getPerson = (Person *)malloc(1 * sizeof(Person));


vec = fp(INITIAL_SIZE, BLOCK_SIZE);
	

ASSERT_THAT(vec != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((fap(vec, (void *)(arr[shufled[i]]))) == VECTOR_SUCCESS);
}

for (i = 1; i <= ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((fgt(vec, (size_t)i, (void *)(&getPerson))) == VECTOR_SUCCESS);
    ASSERT_THAT(getPerson == arr[shufled[i - 1]]);
}

ASSERT_THAT(fsz(vec)==ARR_HUGE_SIZE);
fdstr(&vec, PersonDestroy);

free(arr);
ASSERT_THAT(NULL == vec);
END_UNIT

/*****************************************************************************/

UNIT(Vector_Get_Set__Items__Test)

int i;
Vector *vec = NULL;
VectorResult res;
Person **arr = NULL;
Person *getPerson = NULL;
void* libHandle=NULL;

char* error = NULL;
int shufled[ARR_HUGE_SIZE];
/**************************************/
vecCreate fp;
vecAppend fap;
vecSize fsz;
vecDestroy fdstr;
vecGet fgt;
vecSet fst;
/**************************************/
libHandle = dlopen(dlibPath,RTLD_LAZY);
if(!libHandle)
{

	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}

/*
#pragma GCC diagnostic push    
#pragma GCC diagnostic ignored "-Werror=pedantic"    
#pragma GCC diagnostic pop    
*/	
fp =(vecCreate)(dlsym(libHandle,"VectorCreate"));
if((error = dlerror()) != NULL)
{
	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}

 	fap=(vecAppend)(dlsym(libHandle,"VectorAppend"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fsz=(vecSize)(dlsym(libHandle,"VectorSize"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fdstr=(vecDestroy)dlsym(libHandle,"VectorDestroy");
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fgt=(vecGet)(dlsym(libHandle,"VectorGet"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
	fst=(vecSet)(dlsym(libHandle,"VectorSet"));
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
arr = (Person **)malloc(ARR_HUGE_SIZE * sizeof(Person *));
ASSERT_THAT(arr != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    arr[i] = (Person *)malloc(1 * sizeof(Person));
    arr[i]->age = rand() % 80 ;
    arr[i]->edu = rand() % 20;
    shufled[i] = i;
}

ShuffleArray(shufled, ARR_HUGE_SIZE);

getPerson = (Person *)malloc(1 * sizeof(Person));


vec = fp(INITIAL_SIZE, BLOCK_SIZE);

ASSERT_THAT(vec != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((fap(vec, (void *)(arr[shufled[i]]))) == VECTOR_SUCCESS);
    ASSERT_THAT(fsz(vec)==i+1);
}

for (i = 1; i <= ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((res = fgt(vec, (size_t)i, (void *)(&getPerson))) == VECTOR_SUCCESS);
    ASSERT_THAT(getPerson == arr[shufled[i - 1]]);
    ASSERT_THAT((res = fst(vec, (size_t)i, (void *)(getPerson))) == VECTOR_SUCCESS);
}
/*VectorForEach(vec, PrintPersonInColor, NULL);*/
fdstr(&vec, PersonDestroy);

free(arr);
ASSERT_THAT(NULL == vec);
END_UNIT





/******************************************************************************/
/*funcs calls for readelf ex.*/
/*****************************/

UNIT(___READ_ELFFILE_TEST___)

int i;
Vector *vec = NULL;
VectorResult res;
Person **arr = NULL;
Person *getPerson = NULL;
void* libHandle=NULL;
static int iAmStaticLocalVar = 105;
int arrx[10]={1,2,3,4,5,6,7,8,9,10};
char mchar = 'a';
char* str="OMG";

int* alloc=NULL;
char* error = NULL;
int shufled[ARR_HUGE_SIZE];
/**************************************/
vecCreate fp;
vecAppend fap;
vecSize fsz;
vecDestroy fdstr;
vecGet fgt;
vecSet fst;
/**************************************/
libHandle = dlopen(dlibPath,RTLD_LAZY);
if(!libHandle)
{

	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}


alloc = (int*)malloc(BUFF * sizeof(int));
assert(NULL != alloc);

ThisIsExternFunction(arrx, BUFF);

ThisIsStaticFunction(arrx, BUFF);
ASSERT_THAT(*str=='O');
ASSERT_THAT(mchar=='a');

--iAmStaticGlobalVar;
++iAmGlobalVar;
free(alloc);
++iAmStaticLocalVar;
ASSERT_THAT(iAmStaticLocalVar==106);
/*
#pragma GCC diagnostic push    
#pragma GCC diagnostic ignored "-Werror=pedantic"    
#pragma GCC diagnostic pop    
*/	
fp =(vecCreate)(dlsym(libHandle,"VectorCreate"));
if((error = dlerror()) != NULL)
{
	fprintf(stderr, "%s\n", dlerror());
	exit(EXIT_FAILURE);
}

 	fap=(vecAppend)(dlsym(libHandle,"VectorAppend"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fsz=(vecSize)(dlsym(libHandle,"VectorSize"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fdstr=(vecDestroy)dlsym(libHandle,"VectorDestroy");
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
 	fgt=(vecGet)(dlsym(libHandle,"VectorGet"));
	
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
	fst=(vecSet)(dlsym(libHandle,"VectorSet"));
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
   		exit(EXIT_FAILURE);
	}
	
arr = (Person **)malloc(ARR_HUGE_SIZE * sizeof(Person *));
ASSERT_THAT(arr != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    arr[i] = (Person *)malloc(1 * sizeof(Person));
    arr[i]->age = rand() % 80 ;
    arr[i]->edu = rand() % 20;
    shufled[i] = i;
}

ShuffleArray(shufled, ARR_HUGE_SIZE);

getPerson = (Person *)malloc(1 * sizeof(Person));


vec = fp(INITIAL_SIZE, BLOCK_SIZE);

ASSERT_THAT(vec != NULL);

for (i = 0; i < ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((fap(vec, (void *)(arr[shufled[i]]))) == VECTOR_SUCCESS);
    ASSERT_THAT(fsz(vec)==i+1);
}

for (i = 1; i <= ARR_HUGE_SIZE; ++i)
{
    ASSERT_THAT((res = fgt(vec, (size_t)i, (void *)(&getPerson))) == VECTOR_SUCCESS);
    ASSERT_THAT(getPerson == arr[shufled[i - 1]]);
    ASSERT_THAT((res = fst(vec, (size_t)i, (void *)(getPerson))) == VECTOR_SUCCESS);
}
/*VectorForEach(vec, PrintPersonInColor, NULL);*/
fdstr(&vec, PersonDestroy);

free(arr);
ASSERT_THAT(NULL == vec);
END_UNIT





/***************/
/*Main Function*/
/*****************************************************************************/
TEST_SUITE(Test My Dynamic Lib)
TEST(srand_Initialize)
TEST(Create_And_Destroy_Vector_Test)
TEST(Append_Get_And_Set_Vector_Test)
TEST(Vector__Append__Many__Test)
TEST(Vector_Get_Set__Items__Test)
TEST(___READ_ELFFILE_TEST___)
END_SUITE
