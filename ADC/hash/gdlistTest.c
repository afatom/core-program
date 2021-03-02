#include "mu_test.h"
#include "gdlist.h"
#include <stdio.h>
#include <stdlib.h>
#include "list_itr.h"
#include "list_functions.h"
#include <string.h>
#include <time.h>
#include <assert.h>
#define NDEBUG

UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT

#define UNIQUE_AGE 77

#define SIZE 50
#define TRUE 1
#define FALSE 0
#define NUM 10
#define ARR_SIZE 15
/******************************************************************************************************/
typedef enum {
    SEARCH_BY_AGE = 10,
    SEARCH_BY_NAME,
    SEARCH_BY_EDU
} PredicateContext;


/**********************************************************************************/
typedef struct Person {
    int age;
    int arr[10];
    int edu;
    char name[16];
}Person;

/**********************************************************************************/
void ElementDestroyer(void* _elem)
{
    if(NULL == (Person*)_elem)
    {
        return;
    }
    free((Person*)_elem);
}
/**********************************************************************************/
int PredicateFunc(void *_element, void *_context)
{
    if (((Person *)_element)->age == UNIQUE_AGE)
    {
        return 1;
    }
    return 0;
}

int YoungerThanMe(void *_element, void *_context)
{
    if (((Person *)_element)->age < UNIQUE_AGE)
    {
        return 1;
    }
    return 0;
}

int PrintMe(void *_element, void *_context)
{
    printf("%d ",(((Person *)_element)->age));

    return 1;
    
}

typedef int (*CompareItems)(void *_a, void *_b);

/** 
 * @brief Action function to check if a < b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a < _b
 */
int IsLess(void *_a, void *_b)
{
    return ( ((Person *)_a)->age <= ((Person *)_b)->age) ? (TRUE):(FALSE) ;
}

int IsLarger(void *_a, void *_b)
{
    return (((Person *)_a)->age < ((Person *)_b)->age) ? (TRUE) : (FALSE);
}

int IsEqual(void *_a, void *_b)
{
    return (((Person *)_a)->age == ((Person *)_b)->age) ? (TRUE) : (FALSE);
}


static int AssertSortedList(ListItr _begin, ListItr _end, CompareItems _islessFp)
{
    if (NULL == _islessFp || NULL == _begin || NULL == _end)
    {
        return FALSE;
    }
    while (ListItrEquals(_begin, _end) == FALSE)
    {
      	if (_islessFp(ListItrGet(_begin), ListItrGet(ListItrNext(_begin))) == FALSE)
        {
            return FALSE;
        }
        _begin = ListItrNext(_begin);
    }
    return TRUE;
}


/******************************************************************************************************/

/******************************************************************************************************/
UNIT(Create_Normal_Test)
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    ListDestroy(&list, NULL);
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
UNIT(Double_Destroy_Test)
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    ListDestroy(&list, NULL);
    /*ListDestroy(&list, NULL);*/
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/

UNIT(Push_Head_Null_Test)
    Person* adham = NULL;
    List* list = NULL;     
    adham = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushHead(list, (void*)adham) == LIST_UNINITIALIZED_ERROR);
    free(adham);
END_UNIT
/******************************************************************************************************/

UNIT(Push_Tail_Null_Test)
    Person* adham = NULL;
    List* list = NULL;     
    adham = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushTail(list, (void*)adham) == LIST_UNINITIALIZED_ERROR);
    free(adham);
END_UNIT

/******************************************************************************************************/

UNIT(List_Count_Zero_Items_Test)
    size_t cnt;
    Person* adham = NULL;
    List* list = NULL;     
    adham = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushTail(list, (void*)adham) == LIST_UNINITIALIZED_ERROR);
    cnt = ListSize(list);
    ASSERT_THAT(cnt == 0);
    free(adham);
END_UNIT

/******************************************************************************************************/
UNIT(Destroy_After_Push_Head_Operation_Test)
    Person* adham = NULL;
    size_t cnt;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    adham = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushHead(list, (void*)adham) == LIST_SUCCESS);
    cnt = ListSize(list);
    ASSERT_THAT(cnt == 1);
    ListDestroy(&list, ElementDestroyer);
    ASSERT_THAT(NULL == list);
END_UNIT

/******************************************************************************************************/
UNIT(Destroy_After_Push_Tail_Operation_Test)
    Person* adham = NULL;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    adham = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushTail(list, (void*)adham) == LIST_SUCCESS);
    ListDestroy(&list, ElementDestroyer);
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
UNIT(Pop_Empty_List_Test)
    Person* deleted = NULL;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);

    ASSERT_THAT(ListPopTail(list, (void*)(&deleted)) == LIST_UNDERFLOW);
    ASSERT_THAT(ListPopHead(list, (void *)(&deleted)) == LIST_UNDERFLOW);

    ListDestroy(&list, NULL);
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
UNIT(Push_Head__And__Tail__Many_Nodes_Test)
    Person** arr;
    size_t i =0, count=0;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    
    arr = (Person**)malloc(5000*sizeof(Person));
    assert(NULL != arr);

    for(i=0; i<2500; ++i)
    {
        arr[i]=(Person*)malloc(1 * sizeof(Person));
        assert(NULL != arr[i]);
        arr[i]->age = rand() % 100;
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
        assert ((count = ListSize(list))==i+1);
    }
    for (i = 2500; i < 5000; ++i)
    {
        arr[i] = (Person *)malloc(1 * sizeof(Person));
        assert(NULL != arr[i]);
        arr[i]->age = rand() % 100;
        ASSERT_THAT(ListPushTail(list, (void *)arr[i]) == LIST_SUCCESS);
        assert((count = ListSize(list)) == i + 1);
    }

    ListDestroy(&list, ElementDestroyer);
    free(arr);
    arr=NULL;
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
/******************************************************************************************************/
UNIT(Pop_Head__And__Tail__Many_Nodes_Test)
    Person** arr;
    Person* deleted = NULL;
    size_t i =0, count=0;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    
    arr = (Person**)malloc(5000*sizeof(Person));
    assert(NULL != arr);

    for(i=0; i<2500; ++i)
    {
        arr[i]=(Person*)malloc(1 * sizeof(Person));
        assert(NULL != arr[i]);
        arr[i]->age = rand() % 100;
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
        assert ((count = ListSize(list))==i+1);
    }
    for (i = 2500; i < 5000; ++i)
    {
        arr[i] = (Person *)malloc(1 * sizeof(Person));
        assert(NULL != arr[i]);
        arr[i]->age = rand() % 100;
        ASSERT_THAT(ListPushTail(list, (void *)arr[i]) == LIST_SUCCESS);
        assert((count = ListSize(list)) == i + 1);
    }

    for (i = 0; i < 2500; ++i)
    {
        ASSERT_THAT(ListPopHead(list, (void *)&deleted) == LIST_SUCCESS);
        free(deleted);
        assert((count = ListSize(list)) == 5000-i-1);
    }

    ListDestroy(&list, ElementDestroyer);
    
    free(arr);
    arr=NULL;
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/



UNIT(Push_Pop_Head_Operations_Test)
    Person* adham = NULL;
    Person* alex = NULL;
    Person* slash = NULL;
    Person *deletedPerson = NULL;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    adham = (Person*)malloc(sizeof(Person));
    alex = (Person*)malloc(sizeof(Person));
    slash = (Person*)malloc(sizeof(Person));
    deletedPerson = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushTail(list, (void*)adham) == LIST_SUCCESS);
    ASSERT_THAT(ListPushHead(list, (void*)alex) == LIST_SUCCESS);
    ASSERT_THAT(ListPushTail(list, (void*)slash) == LIST_SUCCESS);
    
    ASSERT_THAT(ListSize(list) == 3);
    ASSERT_THAT(IsListEmpty(list)==0);

    ASSERT_THAT(ListPopHead(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 2);
    free(deletedPerson);

    ASSERT_THAT(ListPopHead(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 1);
    free(deletedPerson);

    ASSERT_THAT(ListPopHead(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 0);
    free(deletedPerson);

    ListDestroy(&list, ElementDestroyer);
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
UNIT(Push_Pop_Tail_Operations_Test)
    Person* adham = NULL;
    Person* alex = NULL;
    Person* slash = NULL;
    Person *deletedPerson = NULL;
    List* list = NULL;     
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    adham = (Person*)malloc(sizeof(Person));
    alex = (Person*)malloc(sizeof(Person));
    slash = (Person*)malloc(sizeof(Person));
    deletedPerson = (Person*)malloc(sizeof(Person));
    ASSERT_THAT(ListPushTail(list, (void*)adham) == LIST_SUCCESS);
    ASSERT_THAT(ListPushHead(list, (void*)alex) == LIST_SUCCESS);
    ASSERT_THAT(ListPushTail(list, (void*)slash) == LIST_SUCCESS);
    
    ASSERT_THAT(ListSize(list) == 3);
    ASSERT_THAT(IsListEmpty(list)==0);

    ASSERT_THAT(ListPopTail(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 2);


    ASSERT_THAT(ListPopTail(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 1);


    ASSERT_THAT(ListPopTail(list, (void*)(&deletedPerson)) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == 0);

    free(adham);free(slash);free(alex);
    ListDestroy(&list, ElementDestroyer);
    ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/
UNIT(List_Size_Test)
int i;
Person **arr = NULL;
List *list = NULL;
list = ListCreate();
ASSERT_THAT(list != NULL);
arr = (Person **)malloc(SIZE * sizeof(Person*));
for(i= 0; i<SIZE; ++i)
{
    arr[i]=(Person *)malloc(sizeof(Person));
}

for (i = 0; i < SIZE; ++i)
{
    ASSERT_THAT(ListPushHead(list, (void *)(arr[i])) == LIST_SUCCESS);
    ASSERT_THAT(ListSize(list) == i+1);
}

ListDestroy(&list, ElementDestroyer);
free(arr);
ASSERT_THAT(NULL == list);
END_UNIT
/******************************************************************************************************/

/*******************************************/
/*        List Iterators Funcs Test        */
/*******************************************/
UNIT(Iterators__Test)
    ListItr ptr1 = NULL, ptr2 = NULL, ptr3=NULL;
    List *list = NULL;
    Person* adham =NULL;
    Person* alisher = NULL;
    Person* newPerson = NULL;
    void* per = NULL;

    list = ListCreate();

    ASSERT_THAT(list != NULL);
    ptr1 = ListItrBegin(list);
    ptr2 = ListItrEnd(list);

    ASSERT_THAT(ptr1 != NULL);
    ASSERT_THAT(ptr2 != NULL);

    ASSERT_THAT(IsListItrPointsToNull(ptr1) == FALSE);
    ASSERT_THAT(IsListItrPointsToNull(ptr2) == FALSE);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == TRUE);
    adham = malloc(sizeof(Person));
    
    /*Get itr test*/
    adham->age = 12;
    ListPushHead(list,(void*)adham);
    ptr1 = ListItrBegin(list);
    per = ListItrGet(ptr1);
    ASSERT_THAT(((Person*)per)->age == 12);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == FALSE);

    /*Next test*/
    ptr1 = ListItrNext(ptr1);
    ASSERT_THAT(ptr1 == ptr2);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == TRUE);
    

    /*Prev Test*/
    ptr3 = ListItrBegin(list);
    ptr1 = ListItrPrev(ptr1);
    per = ListItrGet(ptr1);
    ASSERT_THAT(((Person*)per)->age == 12);
    ASSERT_THAT(ListItrEquals(ptr1, ptr3) == TRUE);

    /*Set test*/
    alisher = (Person*)malloc(sizeof(Person));
    alisher->age = 122;
    per = ListItrSet(ptr3, (void*)(alisher));
    ASSERT_THAT(((Person*)per)->age == 12);
    free(per);
    per = ListItrGet(ptr3);
    ASSERT_THAT(((Person*)per)->age == 122);

    /*Insert before*/
    newPerson = (Person*)malloc(sizeof(Person));
    newPerson->age=555;
    ptr3 = ListItrInsertBefore(ptr3, (void *)(newPerson));
    ptr1 = ListItrBegin(list);
    ASSERT_THAT(ListItrEquals(ptr1, ptr3) == TRUE);
    per = ListItrGet(ptr3);
    ASSERT_THAT(((Person *)per)->age == 555);
    ASSERT_THAT(ListSize(list) == 2);
    
    ListDestroy(&list, ElementDestroyer);


END_UNIT
/******************************************************************************************************/


UNIT(Iterator__Remove__Test)
    ListItr ptr1 = NULL, ptr2 = NULL;
    List *list = NULL;
    Person* adham =NULL;

    void* per = NULL;
    void* removed = NULL;

    list = ListCreate();

    ASSERT_THAT(list != NULL);
    ptr1 = ListItrBegin(list);
    ptr2 = ListItrEnd(list);

    ASSERT_THAT(ptr1 != NULL);
    ASSERT_THAT(ptr2 != NULL);

    ASSERT_THAT(IsListItrPointsToNull(ptr1) == FALSE);
    ASSERT_THAT(IsListItrPointsToNull(ptr2) == FALSE);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == TRUE);
    adham = malloc(sizeof(Person));
    
    /*Get itr test*/
    adham->age = 12;
    ListPushHead(list,(void*)adham);
    ptr1 = ListItrBegin(list);
    per = ListItrGet(ptr1);
    ASSERT_THAT(((Person*)per)->age == 12);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == FALSE);

    /*Next test*/
    ptr1 = ListItrNext(ptr1);
    ASSERT_THAT(ptr1 == ptr2);
    ASSERT_THAT(ListItrEquals(ptr1, ptr2) == TRUE);
    
    /*Remove test*/
    ptr1 = ListItrBegin(list);
    ASSERT_THAT(ListSize(list) == 1);
    removed = ListItrRemove(ptr1);
    ASSERT_THAT(((Person*)removed)->age == 12);
    ASSERT_THAT(ListSize(list) == 0);
    
    /*check edge case - remove tail attempt*/
    ptr1 = ListItrEnd(list);
    removed = ListItrRemove(ptr1);
    ASSERT_THAT(removed == NULL);
    
    ListDestroy(&list, ElementDestroyer);


END_UNIT
/******************************************************************************************************/
UNIT(List_Itr_Find_First_Function_Test)
    Person** arr;
    void* per = NULL;
    int i =0;
    ListItr _end = NULL, _begin=NULL, founded = NULL;
    List *list = NULL;
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    arr = (Person**)malloc(100 * sizeof(Person*)); 
    for(i=0; i < 50; ++i)
    {
        arr[i]= (Person*)malloc(sizeof(Person));
        arr[i]->age = rand() % 70;
    }

    arr[50]=(Person*)malloc(sizeof(Person));
    arr[50]->age = UNIQUE_AGE;
    arr[50]->edu = UNIQUE_AGE;

    for (i = 51; i < 100; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 70;
    }

    for(i=0; i<100; ++i)
    {
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
    }
    ASSERT_THAT(ListSize(list) == 100);
    _begin = ListItrBegin(list);
    _end = ListItrEnd(list);

    founded = ListItrFindFirst(_begin, _end, PredicateFunc, NULL);
    ASSERT_THAT (founded != NULL);
    per = ListItrGet(founded);
    ASSERT_THAT(((Person *)per)->age == UNIQUE_AGE);
    ASSERT_THAT(((Person *)per)->edu == UNIQUE_AGE);
    ListDestroy(&list, ElementDestroyer);
    free(arr);

END_UNIT

UNIT(ListItrCountIf_Function_Test)
    Person **arr;
    size_t counter=0;
    int i = 0;
    ListItr _end = NULL, _begin = NULL;
    List *list = NULL;
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    arr = (Person **)malloc(100 * sizeof(Person *));
    for (i = 0; i < 50; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 100;
    }

    arr[50] = (Person *)malloc(sizeof(Person));
    arr[50]->age = UNIQUE_AGE;
    arr[50]->edu = UNIQUE_AGE;

    for (i = 51; i < 100; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 100;
    }

    for (i = 0; i < 100; ++i)
    {
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
    }
    ASSERT_THAT(ListSize(list) == 100);
    _begin = ListItrBegin(list);
    _end = ListItrEnd(list);
    /*ListItrForEach(_begin, _end, PrintMe, NULL);*/      /*<< Printing function*/
    _begin = ListItrBegin(list);
    counter = ListItrCountIf( _begin, _end, YoungerThanMe, NULL);
    ASSERT_THAT(counter);
    ListDestroy(&list, ElementDestroyer);
    free(arr);

END_UNIT

UNIT(ListItr_Bubble_Sort_Function_Test)
    Person **arr;
    
    int i = 0;
   
    ListItr _end = NULL, _begin = NULL;
    List *list = NULL;
    list = ListCreate();
    ASSERT_THAT(list != NULL);
    arr = (Person **)malloc(ARR_SIZE * sizeof(Person *));
    for (i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = rand() % 100;
    }

    for (i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
    }
    ASSERT_THAT(ListSize(list) == ARR_SIZE);
    _begin = ListItrBegin(list);
    _end = ListItrEnd(list);
    /*
    puts("before sort\n\n\n");
    ListItrForEach(_begin, _end, PrintMe, NULL);
    puts("***************\n");
    */
    ListItrSort(_begin, _end, IsLess);
    
    _begin = ListItrBegin(list);
    _end = ListItrEnd(list);
    _end = ListItrPrev(_end);
    
    /*puts("After sort\n\n\n");
    ListItrForEach(_begin, _end, PrintMe, NULL);
    */
    ASSERT_THAT(AssertSortedList(_begin, _end, IsLess) == TRUE);
    

    ListDestroy(&list, ElementDestroyer);
    free(arr);

END_UNIT

UNIT(Splice_Fuction_Test)
	
	
	Person **arr;
	Person **prr;
	int i = 0;

	ListItr _end = NULL, _begin = NULL, dest = NULL;
	List *list = NULL;
	List* listdest = NULL;
	
	list = ListCreate();
	listdest = ListCreate();
	
	ASSERT_THAT(list != NULL);
	ASSERT_THAT(listdest != NULL);
	
	arr = (Person **)malloc(ARR_SIZE * sizeof(Person *));
	prr = (Person **)malloc(ARR_SIZE * sizeof(Person *));
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = (Person *)malloc(sizeof(Person));
		arr[i]->age = ARR_SIZE-i;
	}
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		prr[i] = (Person *)malloc(sizeof(Person));
		prr[i]->age = 25;
	}

	for (i = 0; i < ARR_SIZE; ++i)
	{
		ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
	}
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		ASSERT_THAT(ListPushHead(listdest, (void *)prr[i]) == LIST_SUCCESS);
	}
	
	ASSERT_THAT(ListSize(list) == ARR_SIZE);
	
	_begin = ListItrBegin(list);
	_begin = ListItrNext(_begin);
	_end = ListItrEnd(list);
	_end = ListItrPrev(_end);
	dest = ListItrEnd(listdest);
	/*
	puts("before splicing - src list -");
    ListItrForEach(_begin, ListItrEnd(list), PrintMe, NULL);
    puts("\nafter splicing -dest lest -");
    */
    ListItrSplice(dest, _begin, _end);

	/*
    ListItrForEach(ListItrBegin(listdest), ListItrEnd(listdest), PrintMe, NULL);
    puts("\n");
   	*/
    ListDestroy(&list, ElementDestroyer);
   	ListDestroy(&listdest, ElementDestroyer);
    free(arr);
    free(prr);
END_UNIT

UNIT(ListItr_Cut_Fuction_Test)
    Person **arr;
    
    int i = 0;

    ListItr _end = NULL, _begin = NULL;
    List *list = NULL;
    List *listdest = NULL;

    list = ListCreate();
    ASSERT_THAT(list != NULL);

    arr = (Person **)malloc(ARR_SIZE * sizeof(Person *));
    for (i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = ARR_SIZE - i;
    }

    for (i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
    }

    ASSERT_THAT(ListSize(list) == ARR_SIZE);

    _begin = ListItrBegin(list);
    _begin = ListItrNext(_begin);
    _begin = ListItrNext(_begin);
    _end = ListItrEnd(list);
    _end = ListItrPrev(_end);
    _end = ListItrPrev(_end);
/*
    start = _begin;
    last = _end;
    puts("before Cutting");
    ListItrForEach(start, last, PrintMe, NULL);
    puts("\n");*/
    listdest = ListItrCut(_begin, _end);
    ASSERT_THAT(NULL!=listdest);
/*
    puts("New List - after cut -");
    
    _begin = ListItrBegin(listdest);
    _end = ListItrEnd(listdest);
    ListItrForEach(_begin,_end, PrintMe, NULL);
    puts("\n");*/
    ListDestroy(&list, ElementDestroyer);
    ListDestroy(&listdest, ElementDestroyer);
    free(arr);
END_UNIT
/******************************************************************************************************/

UNIT(List_Itr_Unique_Function_Test)
    Person **arr;
    int i = 0;

    ListItr _end = NULL, _begin = NULL;
    List *list = NULL;
    List *listdest = NULL;

    list = ListCreate();
    ASSERT_THAT(list != NULL);

    arr = (Person **)malloc(ARR_SIZE * sizeof(Person *));
    for (i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = (Person *)malloc(sizeof(Person));
        arr[i]->age = (i) % 8;
    }

    arr[0]->age = 1;
    arr[1]->age = 1;
    arr[2]->age = 2;
    arr[3]->age = 2;
    arr[4]->age = 3;
    arr[5]->age = 3;
    arr[6]->age = 4;
    arr[7]->age = 4;
    arr[8]->age = 5;
    arr[9]->age = 5;
    arr[10]->age = 6;
    arr[11]->age = 6;
    arr[12]->age = 7;
    arr[13]->age = 7;
    arr[14]->age = 8;

    for (i = ARR_SIZE-1; i >= 0; --i)
    {
        ASSERT_THAT(ListPushHead(list, (void *)arr[i]) == LIST_SUCCESS);
    }

    ASSERT_THAT(ListSize(list) == ARR_SIZE);

    _begin = ListItrBegin(list);
    _end = ListItrEnd(list);
/*
    start = _begin;
    last = _end;
    
    ListItrForEach(start, last, PrintMe, NULL);
    puts("\nunique Test - Before unique op");
    */
    listdest = ListItrUnique(_begin, _end, IsEqual);
    ASSERT_THAT(NULL!=listdest);
    
    /*dest list itrs*/
    _begin = ListItrBegin(listdest);
    _end = ListItrEnd(listdest);
    /*
    puts("unique Test - After unique op - dest lest -");
    ListItrForEach(_begin,_end, PrintMe, NULL);
    puts("\n");*/
    /*original list*/
    /*ASSERT_THAT( AssertSortedList(start, last, IsLarger) == TRUE);*/
    /* new list*/
    /*ASSERT_THAT(AssertSortedList(_begin, _end, IsLarger) == TRUE);*/

    ListDestroy(&list, ElementDestroyer);
    ListDestroy(&listdest, ElementDestroyer);
    free(arr);
END_UNIT 



/******************************************************************************************************/
/*Main function Macro*/
TEST_SUITE(****** Generic-Double-List-Test ******)
TEST(ssssrand)
TEST(Create_Normal_Test)
TEST(Double_Destroy_Test)
TEST(Destroy_After_Push_Head_Operation_Test)
TEST(Destroy_After_Push_Tail_Operation_Test)
TEST(Push_Head__And__Tail__Many_Nodes_Test)
TEST(Push_Pop_Head_Operations_Test)
TEST(Push_Pop_Tail_Operations_Test)
TEST(Pop_Head__And__Tail__Many_Nodes_Test)
TEST(Pop_Empty_List_Test)
TEST(List_Size_Test)
TEST(Push_Head_Null_Test)
TEST(Push_Tail_Null_Test)
TEST(List_Count_Zero_Items_Test)
TEST(Iterators__Test)
TEST(Iterator__Remove__Test)
TEST(List_Itr_Find_First_Function_Test)
TEST(ListItrCountIf_Function_Test)
TEST(ListItr_Bubble_Sort_Function_Test)
TEST(Splice_Fuction_Test)
TEST(ListItr_Cut_Fuction_Test)
TEST(List_Itr_Unique_Function_Test)
END_SUITE





