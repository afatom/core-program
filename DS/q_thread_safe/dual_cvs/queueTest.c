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
#define SIZE 2048 /*be aware that size is limited by this q implementation*/

typedef struct Person {
    int age;
    int edu;
}Person;


int PrintItem(void *item, void *context)
{
    printf("%d ", ((Person*)item)->age);
    return TRUE;
}

void elementDestroyer(void* _item)
{
    if(NULL != _item)
    {	
		free(_item);
    }
    return;
}

typedef struct Args{
	Queue* 	m_q;
	void** *m_pItemsArray;
	void**  m_itemsArray;
	size_t 	m_numOfItems;
	size_t  m_numOfpItems;
	}Args;


void* Queue_Pthread_Insert(void* _args)
{
	QueueResult stat;
	size_t i =0;
	
	while(i < ((Args*)_args)->m_numOfItems)
	{
		if((stat = QueueInsert(((Args*)_args)->m_q, ((Args*)_args)->m_itemsArray[i])) != QUEUE_SUCCESS)
		{
			return (void*)(stat);
		}
		
		++i;
	}
	
	return (void*)(QUEUE_SUCCESS);
}



void* Queue_Pthread_Remove(void* _args)
{
	QueueResult stat;
	size_t i = 0;
	while(i < ((Args*)_args)->m_numOfpItems)
	{
		if((stat = QueueRemove(((Args*)_args)->m_q, ((Args*)_args)->m_pItemsArray[i])) != QUEUE_SUCCESS)
		{
			return (void*)(stat);
		}
		
		++i;
	}
	
	return (void*)(stat);
}



/*
void* Queue_Pthread_Remove(void* _args)
{
	QueueResult stat;
	stat = QueueRemove(((Args*)_args)->m_q, ((Args*)_args)->m_pItem);
	return (void*)(stat);
}*/




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

static void PersonsGenerator(Person** prr, size_t size)
{
	size_t i =0;
	for(i = 0;i < size; ++i)
    {
		 prr[i] = (Person*)malloc(SIZE * sizeof(Person));
		 assert(NULL != prr[i]);
		 prr[i]->age= rand()%120;
		 prr[i]->edu= rand()%20;
	}
	return;
}
/*****************************************************************************/

UNIT(Insert_Items_To_Queue_Test)
    Person* prr[SIZE];
    int i;
    Queue *ptr = NULL;
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);


	PersonsGenerator(prr, SIZE);

    
    for(i = 0;i < SIZE; ++i)
    {
        
        ASSERT_THAT(QueueInsert(ptr, prr[i]) == QUEUE_SUCCESS);
    }

    /*QueueItemsPrint(ptr, PrintItem, NULL);
    puts("\n");*/
    QueueDestroy(&ptr, elementDestroyer);
    QueueDestroy(NULL, elementDestroyer);
    
    ASSERT_THAT (ptr == NULL);
END_UNIT


/*****************************************************************************/
#define NSIZE 2048
UNIT(MT_Insert_Items_To_Queue_Test)
    
    pthread_t Inserter_one;
    /*pthread_t Inserter_two;*/
    Args* pArgs = NULL;
	Person* prr[SIZE];
	void* retval=NULL;
    Queue *ptr = NULL;

    
    ptr = QueueCreate();
    ASSERT_THAT(ptr!=NULL);

    PersonsGenerator(prr, NSIZE);
    
    pArgs = (Args*)malloc(sizeof(Args));
    ASSERT_THAT(pArgs != NULL);
    
    pArgs->m_q = ptr;
    pArgs->m_itemsArray = (void**)prr;
    pArgs->m_numOfItems = NSIZE;
    	
    pthread_create(&Inserter_one, NULL,Queue_Pthread_Insert, pArgs);
    
    /*pthread_create(&Inserter_two, NULL,Queue_Pthread_Insert, pArgs);
    		ASSERT_THAT((pthread_join(Inserter_two, &retval)) == 0);*/

    ASSERT_THAT((pthread_join(Inserter_one, &retval)) == 0);
    
	ASSERT_THAT(QueueItemsNum(ptr)== SIZE);
    
    
    QueueDestroy(&ptr, elementDestroyer);
    free(pArgs);
    ASSERT_THAT (ptr == NULL);
END_UNIT
/*****************************************************************************/

/*****************************************************************************/
TEST_SUITE(Generic Queue test)
	TEST(srand_Initialize)
	TEST(Create_And_Destroy_Queue_Test)
	TEST(Insert_Items_To_Queue_Test)

	TEST(MT_Insert_Items_To_Queue_Test)
	/*TEST(Insert_And_Remove_Items_From_Queue_Test)
	TEST(Remove_Items_From_Empty_Queue_Test)
	TEST(Insert_Items_To_NULL_Queue_Test)*/
END_SUITE
