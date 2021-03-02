#define _GNU_SOURCE

#include "barrier.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "mu_test.h"
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>



Barrier *pBar = NULL;

int globarr[4]={0};
sem_t sem;

pthread_barrier_t mybarrier;
static pthread_mutex_t fun_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t res_mutex;


#define NUM_OF_THREADS 4
#define ARR_SIZE 1024

UNIT(srand_Initialize)
srand((unsigned int)time(NULL));
END_UNIT


typedef struct Player{
	pthread_t m_id;
	size_t m_countResult;
	}Player;

typedef struct Args {
	Barrier* m_bar;
	int* m_arr;
	int m_size;
	Player* m_prr;
	size_t m_prrSize;
	pthread_barrier_t barrier;
	}Args;


int* ArrGenerator(size_t _size)
{
	int* arr;
	size_t i;
	arr = (int*)malloc(_size * sizeof(int));
	for(i = 0; i < _size; ++i)
	{
		arr[(int)i] = rand() % 11;
		
	}
	return arr;
}


Player* PlayersArrGen(size_t size)
{
	return (Player*)calloc(size, sizeof(Player));
}


void PrintPrr(Player* _prr, size_t _size)
{
	size_t i;
	for(i = 0; i < _size; ++i)
	{
		printf("thread_%lu.id %lu  count res %lu\n",i,(unsigned long)(_prr->m_id),(_prr->m_countResult));
	}
	return; 
}

void* CountArrayElements(void* _args)
{
	int arrCount = 0;
	int i = 0;
	pthread_mutex_lock(&fun_mutex);
	
	for(i = 0; i < ((Args*)_args)->m_size; ++i )
	{
		arrCount += ((Args*)_args)->m_arr[i];
	}
	pthread_mutex_unlock(&fun_mutex);
	/*
	assert((BarrierWait(((Args*)_args)->m_bar)) == BARRIER_SUCCESS);
	pthread_barrier_wait(&((Args*)_args)->barrier);*/
	
	/*pthread_barrier_wait(&mybarrier);*/
	
	pthread_mutex_lock(&res_mutex);
	((Args*)_args)->m_prr->m_id = pthread_self();
	
	((Args*)_args)->m_prr->m_countResult = (size_t)arrCount;
	pthread_mutex_unlock(&res_mutex);
	
	return (void*)(0);
}


typedef struct MArgs{
	int* m_arr;
	
	int m_val;
	}MArgs;


void* IncrGlobalArray(void* _args)
{
	
	pthread_mutex_lock(&res_mutex);
	
		
	
	*(((MArgs*)_args)->m_arr) = ((MArgs*)_args)->m_val;
	pthread_mutex_unlock(&res_mutex);


	/**BarrierWait(pBar);*/

	return (void*)(0);
}


UNIT(Double_Barrier_MT_Synchronization_Test)
	pthread_t pthread_1;
	pthread_t pthread_2;
	pthread_t pthread_3;
	pthread_t pthread_4;
	
	MArgs* pMargs;

	int trr[4]={1,2,3,4};
	
	pMargs = (MArgs*)malloc(sizeof(MArgs));
	pMargs->m_arr = trr;
	pMargs->m_val = 256;
	
	/*pthread_mutex_init(&fun_mutex, NULL);*/
	if (pthread_mutex_init(&res_mutex, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
	
	
    pBar = BarrierCreate(NUM_OF_THREADS);
    ASSERT_THAT(pBar!=NULL);
    
	ASSERT_THAT((pthread_create(&pthread_1,NULL,IncrGlobalArray, pMargs))==0);
	pMargs->m_arr =&trr[1];
	ASSERT_THAT((pthread_create(&pthread_2,NULL,IncrGlobalArray, pMargs))==0);
	pMargs->m_arr =&trr[2];
	ASSERT_THAT((pthread_create(&pthread_3,NULL,IncrGlobalArray, pMargs))==0);
	pMargs->m_arr =&trr[3];
	ASSERT_THAT((pthread_create(&pthread_4,NULL,IncrGlobalArray, pMargs))==0);
  
  
  
    /*wait for the basterds to finish the work*/
    ASSERT_THAT ((pthread_join(pthread_1, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_2, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_3, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_4, NULL))==0);
	pthread_mutex_destroy(&res_mutex);
    
    /*printf("%d %d %d %d\n",trr[0],trr[1],trr[2],trr[3]);*/
    /*
    ASSERT_THAT(globarr[0]==256);
    
    ASSERT_THAT(globarr[1]==256);
    
    ASSERT_THAT(globarr[2]==256);
    
    ASSERT_THAT(globarr[3]==256);*/
    
	BarrierDestroy(&pBar);

    ASSERT_THAT (pBar == NULL);
    free(pMargs);

END_UNIT

/*****************************************************************************/
TEST_SUITE(Generic-Barrier-test)
TEST(srand_Initialize)
TEST(Barrier_Create_And_Destroy_Test)
TEST(Barrier_MT_Synchronization_Test)
END_SUITE
