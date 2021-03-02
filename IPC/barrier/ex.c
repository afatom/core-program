#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 4

pthread_barrier_t mybarrier;

void* threadFn(void *id_ptr) {
  int thread_id = *(int*)id_ptr;
  int wait_sec = 1 + rand() % 5;
  printf("thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
  sleep(wait_sec);
  printf("thread %d: I'm ready...\n", thread_id);

  pthread_barrier_wait(&mybarrier);

  printf("thread %d: going!\n", thread_id);
  return NULL;
}


int main() {
  int i;
  pthread_t ids[THREAD_COUNT];
  int short_ids[THREAD_COUNT];

  srand(time(NULL));
  pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT + 1);

  for (i=0; i < THREAD_COUNT; i++) {
    short_ids[i] = i;
    pthread_create(&ids[i], NULL, threadFn, &short_ids[i]);
  }

  printf("main() is ready.\n");

  pthread_barrier_wait(&mybarrier);

  printf("main() is going!\n");

  for (i=0; i < THREAD_COUNT; i++) {
    pthread_join(ids[i], NULL);
  }

  pthread_barrier_destroy(&mybarrier);

  return 0;
}
















UNIT(Barrier_MT_Synchronization_Test)
	int* arr;
	Player* prr;
	Args* pArg;
	Barrier *pBar = NULL;
	pthread_t pthread_1;
	pthread_t pthread_2;
	pthread_t pthread_3;
	pthread_t pthread_4;
	

	 pthread_mutex_init(&fun_mutex, NULL);
           
	 pthread_mutex_init(&res_mutex, NULL);
           
   
    
	
	prr = PlayersArrGen(NUM_OF_THREADS);
	ASSERT_THAT(prr != NULL);
	
	arr = ArrGenerator(ARR_SIZE);
	ASSERT_THAT(arr != NULL);
	
	pArg = (Args*)malloc(sizeof(Args));
	ASSERT_THAT(pArg != NULL);
	
	
    pBar = BarrierCreate(NUM_OF_THREADS);
    ASSERT_THAT(pBar!=NULL);
    
    
    /*pthread_barrier_init(&pArg->barrier,NULL, NUM_OF_THREADS);*/
    
    pthread_barrier_init(&mybarrier,NULL, NUM_OF_THREADS);
    
    
    /******************** thread_1 intialize */
    pArg->m_bar = pBar;
    pArg->m_arr = arr;
    pArg->m_size = 256;
    pArg->m_prr = prr;
    
    
	/*ASSERT_THAT((pthread_create(&pthread_1,NULL,CountArrayElements, pArg))==0);*/
	
	ASSERT_THAT((pthread_create(&pthread_1,NULL,IncrGlobalArray, &globarr[0]))==0);
	
    /*********************************************/
    
    
    /******************** thread_2 intialize */
    pArg->m_bar = pBar;
    pArg->m_arr = arr + 256;
    pArg->m_size = 256;
    pArg->m_prr = prr + 1;
    
    /*
	ASSERT_THAT((pthread_create(&pthread_2,NULL,CountArrayElements, pArg))==0);*/
	ASSERT_THAT((pthread_create(&pthread_2,NULL,IncrGlobalArray, &globarr[1]))==0);

    /*********************************************/
    
     /******************** thread_3 intialize */
    pArg->m_bar = pBar;
    pArg->m_arr = arr + 512;
    pArg->m_size = 256;
    pArg->m_prr = prr + 2;
    
    /*
	ASSERT_THAT((pthread_create(&pthread_3,NULL,CountArrayElements, pArg))==0);*/
	
	ASSERT_THAT((pthread_create(&pthread_3,NULL,IncrGlobalArray, &globarr[2]))==0);
	
    /*********************************************/
    
     /******************** thread_4 intialize */
    pArg->m_bar = pBar;
    pArg->m_arr = arr + 768;
    pArg->m_size = 256;
    pArg->m_prr = prr + 3;
    
    /*
	ASSERT_THAT((pthread_create(&pthread_4,NULL,CountArrayElements, pArg))==0);*/
	
	ASSERT_THAT((pthread_create(&pthread_4,NULL,IncrGlobalArray, &globarr[3]))==0);
    /*********************************************/
    
   
    
    /*wait for the basterds to finish the work*/
    ASSERT_THAT ((pthread_join(pthread_1, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_2, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_3, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_4, NULL))==0);
    
    
    printf("%d%d%d%d\n",globarr[0],globarr[1],globarr[2],globarr[3]);
    
    
    /*print prr array*/
    PrintPrr(prr, NUM_OF_THREADS);
    
	BarrierDestroy(&pBar);
    ASSERT_THAT (pBar == NULL);
    free(prr);
    free(arr);
    free(pArg);

	/*pthread_barrier_destroy(&pArg->barrier);
*/
    pthread_barrier_destroy(&mybarrier);
END_UNIT



/***************************************barrier wait**/

/**********************************************************************/
Barrier_Result BarrierWait(Barrier* _barrier)
{
	if(NULL == _barrier || _barrier->m_magic != BARRIER_IS_VALID)
	{
		return BARRIER_NOT_INITIALIZED;
	}
	
	if((pthread_mutex_lock(&_barrier->m_mutex))!=0)
	{
		return BARRIER_INTERNAL_ERROR;
	}
	
	if(--_barrier->m_latingThreads == 0)
	{
		_barrier->m_latingThreads = _barrier->m_count; /*for future usess*/
		/*wake the basterds*/
		pthread_cond_broadcast(&_barrier->m_cv);
		pthread_mutex_unlock(&_barrier->m_mutex);
	}
	else{
		/*atomically release the mutex pointed to by mp and cause the 
		calling thread to block on the condition variable pointed 
		* to by cv. (For Solaris threads,*/
		pthread_cond_wait(&_barrier->m_cv, &_barrier->m_mutex);
		pthread_mutex_unlock(&_barrier->m_mutex);
	}
	return BARRIER_SUCCESS;
	
}
/**********************************************************************/

	
	if(--_barrier->m_latingThreads == 0)
	{
		_barrier->m_latingThreads = _barrier->m_count; /*for future usess*/
		/*wake the basterds*/
		pthread_mutex_unlock(&_barrier->m_mutex);
		pthread_cond_broadcast(&_barrier->m_cv);
		
	}
	else{
		/*atomically release the mutex pointed to by mp and cause the 
		calling thread to block on the condition variable pointed 
		* to by cv. (For Solaris threads,*/
		pthread_cond_wait(&_barrier->m_cv, &_barrier->m_mutex);
		pthread_mutex_unlock(&_barrier->m_mutex);
	}
	return BARRIER_SUCCESS;
	
}
/*****************************************************/


















