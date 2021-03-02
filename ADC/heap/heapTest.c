#include "vector.h"
#include <mcheck.h>

#include "heap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include <time.h>

#define NDEBUG

UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT



#define TRUE 1
#define FALSE 0
#define NUM 10
#define INITIAL_SIZE 50
#define BLOCK_SIZE 50

#define ARR_HUGE_SIZE 30

#define SIZE 300
#define VEC_INITIAL_SIZE 300
#define VEC_BLOCK_SIZE 100
/***********************************************************************************/

typedef struct Person {
    int age;
    int edu;
    char name[32];
}Person;


typedef struct VecItem{
	size_t m_index;
	void* m_item;
}VecItem;




/***********************************************************************************/
/* bold - not bold */
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[21m"
/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define GRAY "\x1b[90m"



typedef int (*CompareFunction)(const void *_left, const void *_right);


/***********************************************************************************/

typedef enum {
    NORMALL = 1,
    REDD,
    BLUEE,
    GREENN
} COLOR;
/***********************************************************************************/
/***********************************************************************************/

/****************************************************************************************/
int PrintPersonInColor(void *_element, size_t _index, void *_context)
{
    printf(" %d \n",((Person *)_element)->age);
    return 1;
}
/****************************************************************************************/
/****************************************************************************************/

void PrintPerson(void *_element, void *_context)
{
    printf("%d ", ((Person *)_element)->age);
    return;
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

static void AssertHeapMaxProperty(Vector* vec, size_t heapsize)
{
    size_t i;
    
    Person* getPerson1 = NULL;
    Person *getPerson2 = NULL;
    Person *getPerson3 = NULL;
/*
    getPerson1 = malloc(sizeof(*getPerson1));
    getPerson2 = malloc(sizeof(*getPerson2));
    getPerson3 = malloc(sizeof(*getPerson3));*/

    for (i = 1; i <= (heapsize / 2) - 1; ++i)
    {

        VectorGet(vec, i, (void *)(&getPerson1));
        VectorGet(vec, 2*i, (void *)(&getPerson2));
        VectorGet(vec, 2*i+1, (void *)(&getPerson3));
        assert(getPerson1->age >= getPerson2->age && getPerson1->age >= getPerson3->age);
    }

    if(i*2+1 == heapsize) 
    {
        VectorGet(vec, i, (void *)(&getPerson1));
        VectorGet(vec, 2*i, (void *)(&getPerson2));
        VectorGet(vec, 2*i+1, (void *)(&getPerson3));
        assert(getPerson1->age >= getPerson2->age && getPerson1->age >= getPerson3->age);
    }
    else
    {

        VectorGet(vec, i, (void *)(&getPerson1));
        VectorGet(vec, 2 * i, (void *)(&getPerson2));
        assert(getPerson1->age >= getPerson2->age);
    }
    return;
}

/* AssertSortedVector Function*/
/******************************************************************************/
static int AssertSortedVector(Vector* _vec, CompareFunction _fp)
{
	size_t i=0,vecSize=0;
	VecItem left, right;
	assert(_vec != NULL);
	assert(NULL != _fp);
	vecSize = VectorSize(_vec);
	
	for(i = 1; i <= vecSize-1; ++i)
	{
		VectorGet(_vec,i+1, &right.m_item);
		VectorGet(_vec,i, &left.m_item);
		if(_fp(right.m_item , left.m_item) == TRUE)
		{
			return FALSE; /*un sorrted vector */
		}
	}
	return TRUE;	
}
/******************************************************************************/

/* Assert Max Element Function*/
/******************************************************************************/
static int AssertMaxElementInVector(Vector* _vec, CompareFunction _fp)
{
	size_t i=0,vecSize=0;
	VecItem max, temp;
	assert(_vec != NULL);
	assert(NULL != _fp);
	vecSize = VectorSize(_vec);
	VectorGet(_vec,1, &max.m_item);
	for(i = 1; i <= vecSize; ++i)
	{
		VectorGet(_vec,i, &temp.m_item);
		if(_fp(max.m_item , temp.m_item) == TRUE)
		{
			return FALSE; /*not the max one*/
		}
	}
	return TRUE;	
}
/******************************************************************************/




/*
static int HeapPrint(const void *_element, void *_context)
{
    puts("Person Details:");
    printf("Person age --%d-- edu --%d-- \n", ((Person *)_element)->age, ((Person *)_element)->edu);
    return 1;
}*/
/***********************************************************************************/
int Comparator(const void *_left, const void *_right)
{
    return (((Person*)_left)->age < ((Person*)_right)->age) ? (TRUE):(FALSE);
}
/***********************************************************************************/
/*
static void swap(int *arr, int firstindex, int secindex)
{
    int firstval, secval;
    firstval = arr[firstindex];
    secval = arr[secindex];
    arr[secindex] = firstval;
    arr[firstindex] = secval;
    return;
}*/
/***********************************************************************************/
/*
static void ShuffleArray(int *_arr, int _size)
{
    int i, newIndex;
    for (i = _size - 1; i >= 0; --i)
    {
        newIndex = rand() % (i + 1);
        swap(_arr, i, newIndex);
    }
}
*/
/******************************************************************************/
/******************************************************************************/
UNIT(Heap_Create_And_Destroy_Test)

    Vector* vec = NULL;
    Heap* heap = NULL;

	vec = VectorCreate(INITIAL_SIZE, BLOCK_SIZE);
    heap = HeapBuild(vec, Comparator);
    ASSERT_THAT(NULL != heap);
    vec = HeapDestroy(&heap);
    VectorDestroy(&vec, NULL);	
    ASSERT_THAT(NULL == heap);
    ASSERT_THAT(vec==NULL);
    mtrace();
END_UNIT
/******************************************************************************/
/******************************************************************************/
UNIT(HEAP__BUILD__Null_Inputs__Test)
    Vector* vec = NULL;
    Heap* heap = NULL;
	
    heap = HeapBuild(NULL, Comparator);
    ASSERT_THAT(NULL == heap);
    
    vec = VectorCreate(10,10);
    heap = HeapBuild(vec, NULL);
    ASSERT_THAT(NULL == heap);
    
    
    VectorDestroy(&vec, NULL);	
    ASSERT_THAT(NULL == heap);
    ASSERT_THAT(vec==NULL);
END_UNIT
/******************************************************************************/
/******************************************************************************/
UNIT(HEAP__BUILD__ZeroAndOne__Vec__Size__Test)
    Vector* vec = NULL;
    Heap* heap = NULL;
	int x = 10;
	int* ptr = &x;
    heap = HeapBuild(NULL, Comparator);
    ASSERT_THAT(NULL == heap);
    
    vec = VectorCreate(0,10);
    heap = HeapBuild(vec, Comparator);
    ASSERT_THAT(NULL != heap);
    
    vec = HeapDestroy(&heap);
	VectorAppend(vec,ptr);
	heap = HeapBuild(vec, Comparator);
    ASSERT_THAT(NULL != heap);
    
    vec = HeapDestroy(&heap);    
    VectorDestroy(&vec, NULL);	
    ASSERT_THAT(NULL == heap);
    ASSERT_THAT(vec==NULL);
END_UNIT
/******************************************************************************/
/******************************************************************************/
UNIT(HEAP__BUILD__Test)
Heap* heap=NULL;
size_t i =0;
Person**arr;
Vector* vector =NULL;
vector = VectorCreate(50,50);
arr = (Person**)malloc(10 * sizeof(Person*));
for(i=0; i < 10; ++i)
{
    arr[i]=(Person*)malloc(sizeof(Person));
    arr[i]->age = rand() % 50 ;
    VectorAppend(vector,arr[i]);
}
ASSERT_THAT(10 == VectorSize(vector));

heap = HeapBuild(vector, Comparator);
AssertHeapMaxProperty(vector,10);



assert(HeapSize(heap)==10);
vector = HeapDestroy(&heap);
VectorDestroy(&vector,PersonDestroy);
free(arr);
ASSERT_THAT(NULL==vector);
ASSERT_THAT(NULL==heap);
END_UNIT
/******************************************************/
/******************************************************************************/
/******************************************************************************/
UNIT(HEAP__BUILD__Many_Elements__Test)
Heap* heap=NULL;
size_t i =0;
Person**arr;
Vector* vector =NULL;
vector = VectorCreate(1500,1500);
arr = (Person**)malloc(2000 * sizeof(Person*));
for(i=0; i < 2000; ++i)
{
    arr[i]=(Person*)malloc(sizeof(Person));
    arr[i]->age = rand() % 120 ;
    VectorAppend(vector,arr[i]);
}
ASSERT_THAT(2000 == VectorSize(vector));

heap = HeapBuild(vector, Comparator);
AssertHeapMaxProperty(vector,2000);

assert(HeapSize(heap)==2000);
vector = HeapDestroy(&heap);
VectorDestroy(&vector,PersonDestroy);
free(arr);
ASSERT_THAT(NULL==vector);
ASSERT_THAT(NULL==heap);
END_UNIT

/******************************************************************************/
UNIT(HEAP__Extract__MAX__Test)
    Heap *heap = NULL;
    size_t i = 0;
    Person **arr;
    void* max = NULL;
    void* nmax = NULL;

    Vector *vector = NULL;
    vector = VectorCreate(50, 50);
    arr = (Person **)malloc(10 * sizeof(Person *));
    for (i = 0; i < 10; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 50;
        VectorAppend(vector, arr[i]);
    }
    ASSERT_THAT(10 == VectorSize(vector));

    heap = HeapBuild(vector, Comparator);




    assert(HeapSize(heap) == 10);
    
    VectorGet(vector,1,&nmax);
    max =  HeapExtract(heap);
    assert(max==nmax);


    assert(HeapSize(heap) == 9);

    VectorGet(vector, 1, &nmax);
    max = HeapExtract(heap);
    assert(max == nmax);
   

    assert(HeapSize(heap) == 8);

    vector = HeapDestroy(&heap);
    VectorDestroy(&vector, PersonDestroy);
    free(arr);
    ASSERT_THAT(NULL == vector);
    ASSERT_THAT(NULL == heap);
END_UNIT
/*****************************************************************************/



/******************************************************************************/
UNIT(HEAP__Extract_MANY_MAX__Test)
    Heap *heap = NULL;
    size_t i = 0;
    Person **arr;
    void* max = NULL;
    void* nmax = NULL;

    Vector *vector = NULL;
    vector = VectorCreate(5000, 500);
    arr = (Person **)malloc(5000 * sizeof(Person *));
    for (i = 0; i < 5000; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 1000;
        VectorAppend(vector, arr[i]);
    }
    ASSERT_THAT(5000 == VectorSize(vector));

    heap = HeapBuild(vector, Comparator);

    assert(HeapSize(heap) == 5000);
    for(i=0; i<5000; ++i)
    {
		assert(HeapSize(heap) == 5000 - i);
		VectorGet(vector,1,&nmax);
		max =  HeapExtract(heap);
		assert(max==nmax);
		/*make sure its maximum person*/
		AssertMaxElementInVector(vector, Comparator);    
    }


    vector = HeapDestroy(&heap);
    VectorDestroy(&vector, PersonDestroy);
    free(arr);
    ASSERT_THAT(NULL == vector);
    ASSERT_THAT(NULL == heap);
END_UNIT
/*****************************************************************************/








/*****************************************************************************/
UNIT(HEAP__Insert__And__Peek__Test)
Heap *heap = NULL;
size_t i = 0;
Person **arr;

Person* first = NULL;
Person* sec = NULL;
Person *third = NULL;
const void* peek =NULL;

Vector *vector = NULL;

first =(Person*) malloc(sizeof(Person));
sec = malloc(sizeof(Person));
third = malloc(sizeof(Person));

first->age = 100;
sec->age = 48;
third->age=0;

vector = VectorCreate(50, 50);
arr = (Person **)malloc(10 * sizeof(Person *));
for (i = 0; i < 10; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
    arr[i]->age = rand() % 50;
    VectorAppend(vector, arr[i]);
}
ASSERT_THAT(10 == VectorSize(vector));
/*PrintForEach(vector, PrintPerson, NULL);*/
heap = HeapBuild(vector, Comparator);
AssertHeapMaxProperty(vector, HeapSize(heap));
/*PrintForEach(vector, PrintPerson, NULL);*/
assert(HeapSize(heap) == 10);


HeapInsert(heap, (void *)first);
peek = HeapPeek(heap);
assert( ((Person*)peek)->age == 100);
AssertHeapMaxProperty(vector, HeapSize(heap));
/*PrintForEach(vector, PrintPerson, NULL);
*/
HeapInsert(heap, (void *)sec);
peek = HeapPeek(heap);
assert(((Person *)peek)->age == 100);
AssertHeapMaxProperty(vector, HeapSize(heap));

HeapInsert(heap, (void *)third);
peek = HeapPeek(heap);
assert(((Person *)peek)->age == 100);
AssertHeapMaxProperty(vector, HeapSize(heap));

assert(HeapSize(heap) == 13);

vector = HeapDestroy(&heap);
VectorDestroy(&vector, PersonDestroy);
free(arr);
ASSERT_THAT(NULL == vector);
ASSERT_THAT(NULL == heap);


END_UNIT

/******************************************************************************/

/*****************************************************************************/
UNIT(HEAP__Insert__Many__Test)
Heap *heap = NULL;
size_t i = 0;
Person **arr;
Vector *vector = NULL;

vector = VectorCreate(5000, 550);

arr = (Person **)malloc(5000 * sizeof(Person *));
for (i = 0; i < 5000; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
}


for (i = 0; i <= 4000; ++i)
{
    arr[i]->age = rand() % 200;
    VectorAppend(vector, arr[i]);
}

ASSERT_THAT(4001 == VectorSize(vector));
/*PrintForEach(vector, PrintPerson, NULL);*/
heap = HeapBuild(vector, Comparator);
AssertHeapMaxProperty(vector, HeapSize(heap));
/*PrintForEach(vector, PrintPerson, NULL);*/
assert(HeapSize(heap) == 4001);


for (i = 4001; i < 5000; ++i)
{
    arr[i]->age = rand() % 400;
	HeapInsert(heap, (void *)arr[i]);
	AssertHeapMaxProperty(vector, HeapSize(heap));
}


assert(HeapSize(heap) == 5000);

assert(VectorSize(vector)==5000);

vector = HeapDestroy(&heap);
VectorDestroy(&vector, PersonDestroy);
/*VectorDestroy(&vector, NULL);

for(i =0; i < 5000; ++i)
{
	free(arr[i]);
}
*/
ASSERT_THAT(NULL == vector);
ASSERT_THAT(NULL == heap);
free(arr);

END_UNIT
/*************************************************/
UNIT(Heap_Sort_Algo_Test)


size_t i = 0;
Person **arr;

Vector *vector = NULL;


vector = VectorCreate(50, 50);
arr = (Person **)malloc(20 * sizeof(Person *));
for (i = 0; i < 20; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
    arr[i]->age = rand() % 70;
    VectorAppend(vector, arr[i]);
}
ASSERT_THAT(20 == VectorSize(vector));
/*
puts("before sorting\n");
PrintForEach(vector, PrintPerson, NULL);
*/

HeapSort(vector, Comparator);

ASSERT_THAT (AssertSortedVector(vector, Comparator) == TRUE);
/*
puts("after sorting\n");
PrintForEach(vector, PrintPerson, NULL);*/


VectorDestroy(&vector, PersonDestroy);
free(arr);
ASSERT_THAT(NULL == vector);


END_UNIT
/******************************************************************************/
UNIT(Heap_Sort_Huge_Vector_Test)


size_t i = 0;
Person **arr;

Vector *vector = NULL;


vector = VectorCreate(2000, 500);
arr = (Person **)malloc(2000 * sizeof(Person *));
for (i = 0; i < 2000; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
    arr[i]->age = rand() % 120;
    VectorAppend(vector, arr[i]);
}
ASSERT_THAT(2000 == VectorSize(vector));
/*
puts("before sorting\n");
PrintForEach(vector, PrintPerson, NULL);
*/

HeapSort(vector, Comparator);

ASSERT_THAT (AssertSortedVector(vector, Comparator) == TRUE);
/*
puts("after sorting\n");
PrintForEach(vector, PrintPerson, NULL);*/


VectorDestroy(&vector, PersonDestroy);
free(arr);
ASSERT_THAT(NULL == vector);


END_UNIT
/***********************************************************************************/
/*****************************************************************************/

TEST_SUITE(Generic Heap Test)

    TEST(ssssrand)
    TEST(Heap_Create_And_Destroy_Test)
    TEST(HEAP__BUILD__Null_Inputs__Test)
    TEST(HEAP__BUILD__ZeroAndOne__Vec__Size__Test)
    TEST(HEAP__BUILD__Test)
    TEST(HEAP__BUILD__Many_Elements__Test)
    TEST(HEAP__Extract__MAX__Test)
    TEST(HEAP__Extract_MANY_MAX__Test)
    TEST(HEAP__Insert__And__Peek__Test)
    TEST(HEAP__Insert__Many__Test)
    TEST(Heap_Sort_Algo_Test)
    TEST(Heap_Sort_Huge_Vector_Test)
END_SUITE
/***********************************************************************************/
