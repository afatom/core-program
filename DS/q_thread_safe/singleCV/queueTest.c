#include "queue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "mu_test.h"
#include <time.h>
#include <assert.h>
#include <pthread.h>

#define NDEBUG

UNIT(srand_Initialize)
srand((unsigned int)time(NULL));
END_UNIT

#define TRUE 1
#define SIZE 10

typedef struct Person {
    char age;
    char edu;
}Person;


int PrintItem(void *item, void *context)
{
    printf("%d ", ((Person*)item)->age);
    return TRUE;
}

void elementDestroyer(void* _item)
{
    if(NULL != _item)
    free(_item);
    return;
}

typedef struct Args{
	Queue* 	m_q;
	void* 	m_item;
	void**	m_pItem;
	}Args;


void* Queue_Pthread_Insert(void* _args)
{
	QueueResult stat;
	stat = QueueInsert(_args->m_q, _args->m_item);
	return (void*)(stat);
}


void* Queue_Pthread_Remove(void* _args)
{
	QueueResult stat;
	stat = QueueRemove(_args->m_q, _args->m_pItem);
	return (void*)(stat);
}




/*****************************************************************************/
UNIT(Create_And_Destroy_Queue_Test)
    Queue *ptr = NULL;
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);
    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    ASSERT_THAT (ptr == NULL);
END_UNIT
/*****************************************************************************/
UNIT(Insert_Items_To_Queue_Test)
    Person** prr;
    int i;
    Queue *ptr = NULL;
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);

    prr = (Person**)malloc(SIZE * sizeof(Person*));
    assert(NULL != prr);
    for(i = 0;i < SIZE; ++i)
    {
        prr[i]=(Person*)malloc(sizeof(Person));
        prr[i]->age= (char)(i+1);
        ASSERT_THAT(QueueInsert(ptr, prr[i]) == QUEUE_SUCCESS);
    }
/*
    QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    
    free(prr);
    ASSERT_THAT (ptr == NULL);
END_UNIT


/*****************************************************************************/
UNIT(MT_Insert_Items_To_Queue_Test)
    
    pthread_t Inserter_one;
    pthread_t Inserter_two;
    Args* pArgs = NULL;
    Person per1;
    Person per2;
	void* retval=NULL;
    Queue *ptr = NULL;
    
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);

    
    
    per1.age='q';
    per1.edu='d';
    
    per2.age='b';
    per2.edu='x';
    
    pArgs = (Args*)malloc(sizeof(Args));
    ASSERT_THAT(pArgs != NULL);
    
    pArgs->m_q = ptr;
    pArgs->m_item = &per1;
    	
    pthread_create(&Inserter_one, NULL,Queue_Pthread_Insert, pArgs);
    
	pArgs->m_q = ptr;
    pArgs->m_item = &per2;
    
    pthread_create(&Inserter_two, NULL,Queue_Pthread_Insert, pArgs);
    
    ASSERT_THAT((pthread_join(Inserter_one, &retval)) == 0);
    ASSERT_THAT((pthread_join(Inserter_two, &retval)) == 0);
    
     ASSERT_THAT(QueueItemsNum(ptr)== 2);
    
    
    QueueDestroy(&ptr, elementDestroyer);
    free(pArgs);
    ASSERT_THAT (ptr == NULL);
END_UNIT

/*****************************************************************************/
UNIT(Insert_And_Remove_Items_From_Queue_Test)
    Person** prr;
    void* _pItem =NULL;
    int i;
    Queue *ptr = NULL;
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);

    prr = (Person**)malloc(SIZE * sizeof(Person*));
    assert(NULL != prr);
    for(i = 0;i < SIZE; ++i)
    {
        prr[i]=(Person*)malloc(sizeof(Person));
        prr[i]->age= (char)(i+1);
        ASSERT_THAT(QueueInsert(ptr, prr[i]) == QUEUE_SUCCESS);
    }
    ASSERT_THAT(IsEmptyQueue(ptr)!=TRUE);
    ASSERT_THAT(QueueItemsNum(ptr)== SIZE);
    /*
    QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    QueueRemove(ptr, &_pItem);
    /*
    QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    free(_pItem);
    QueueRemove(ptr, &_pItem);
    /*
    QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    free(_pItem);
    /*
    QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    ASSERT_THAT(QueueItemsNum(ptr) == SIZE-2);
    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    free(prr);
    ASSERT_THAT (ptr == NULL);
END_UNIT
/*****************************************************************************/
UNIT(Remove_Items_From_Empty_Queue_Test)
    Person** prr;
    void* _pItem =NULL;
    int i;
    Queue *ptr = NULL;
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);
    ASSERT_THAT(QueueRemove(ptr, &_pItem) == QUEUE_UNDERFLOW);

    prr = (Person**)malloc(SIZE * sizeof(Person*));
    assert(NULL != prr);
    for(i = 0;i < SIZE; ++i)
    {
        prr[i]=(Person*)malloc(sizeof(Person));
        prr[i]->age= (char)(i+1);
        ASSERT_THAT(QueueInsert(ptr, prr[i]) == QUEUE_SUCCESS);
    }
    ASSERT_THAT(IsEmptyQueue(ptr)!=TRUE);
    ASSERT_THAT(QueueItemsNum(ptr)== SIZE);

    for (i = 0; i < SIZE; ++i)
    {
        ASSERT_THAT(QueueRemove(ptr, &_pItem) == QUEUE_SUCCESS);
        free(_pItem);
    }

    ASSERT_THAT(QueueRemove(ptr, &_pItem) == QUEUE_UNDERFLOW);
    ASSERT_THAT(QueueRemove(NULL, &_pItem) == QUEUE_UNINITIALIZED_ERROR);
    ASSERT_THAT(QueueRemove(ptr, NULL) == QUEUE_INVALID_ITEM);

    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    free(prr);
    ASSERT_THAT (ptr == NULL);
END_UNIT
/*****************************************************************************/
UNIT(Insert_Items_To_NULL_Queue_Test)

    int* _pItem =NULL;
    int i;
    Queue *ptr = NULL;
    ASSERT_THAT(ptr==NULL);
    i = 10;
    _pItem = &i;
    ASSERT_THAT(QueueInsert(ptr, _pItem) == QUEUE_UNINITIALIZED_ERROR);

    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    ASSERT_THAT (ptr == NULL);
END_UNIT
/*****************************************************************************/



/*****************************************************************************/
/***************/
/*Main Function*/
/*****************************************************************************/
TEST_SUITE(Generic Queue test)
TEST(srand_Initialize)
TEST(Create_And_Destroy_Queue_Test)
TEST(Insert_Items_To_Queue_Test)
TEST(MT_Insert_Items_To_Queue_Test)
TEST(Insert_And_Remove_Items_From_Queue_Test)
TEST(Remove_Items_From_Empty_Queue_Test)
TEST(Insert_Items_To_NULL_Queue_Test)
END_SUITE
