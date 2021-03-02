#define _GNU_SOURCE
#include "FluidBarrier.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include "mu_test.h"
#include <time.h>

#define NTS 5
#define BAR_COUNT 4 
#define _threadsNumAtFirstBarrier 5
#define _threadsNumAtSecBarrier 5


typedef struct Args{
	Barrier* m_barrier;
	}Args;

void* ThreadFunc(void* _args)
{
	printf("Thread %lu Arrived to Barrier 1\n", (unsigned long)pthread_self());
	BarrierWait(((Args*)_args)->m_barrier);
	
	printf("Thread %lu Passed Barrier 1 and waiting on Barrier2\n", (unsigned long)pthread_self());
	
	printf("Thread %lu Passed Barrier2! Good Bye\n", (unsigned long)pthread_self());
	return NULL;
}











UNIT(srand_Initialize)
srand((unsigned int)time(NULL));
END_UNIT

/*****************************************************************************/
UNIT(Fluid_Barrier_Create_And_Destroy_Test)
	Barrier* bar;
	bar = BarrierCreate(10, 3);
	ASSERT_THAT(bar!=NULL);
	BarrierDestroy(&bar);
	ASSERT_THAT(bar==NULL);
END_UNIT
/*****************************************************************************/
/*****************************************************************************/
UNIT(Fluid_Barrier_MT_Wait_Test)
	Barrier* bar;
	int i;
	pthread_t arr[NTS];
	Args* arg;
	
    bar = BarrierCreate(_threadsNumAtFirstBarrier, _threadsNumAtSecBarrier);
	ASSERT_THAT(bar!=NULL);

	arg=(Args*)malloc(sizeof(Args));
    arg->m_barrier = bar;
    
    for(i = 0; i < NTS; ++i)
    {
		pthread_create(&arr[i],NULL, ThreadFunc, arg);
	}
	

    
	for(i = 0; i < NTS; ++i)
    {
		pthread_join(arr[i], NULL);
	}
	
	BarrierDestroy(&bar);
	free(arg);
	ASSERT_THAT(bar==NULL);
END_UNIT
/*****************************************************************************/

TEST_SUITE(Generic-Barrier-test)
	TEST(srand_Initialize)
	TEST(Fluid_Barrier_Create_And_Destroy_Test)
	TEST(Fluid_Barrier_MT_Wait_Test)

END_SUITE
