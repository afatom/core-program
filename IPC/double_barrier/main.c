
#define _GNU_SOURCE
#include <stdlib.h>  /*size_t*/
#include <stdio.h>

#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

pthread_barrier_t barrier1;
pthread_barrier_t barrier2;


#define NTS 8
#define BAR_COUNT 4 

void* ThreadFunc(void* _args)
{
	printf("Thread %lu Arrived to Barrier 1\n", (unsigned long)pthread_self());
	pthread_barrier_wait(&barrier1);
	
	printf("Thread %lu Passed Barrier 1 and waiting on Barrier2\n", (unsigned long)pthread_self());
	
	pthread_barrier_wait(&barrier2);
	printf("Thread %lu Passed Barrier2! Good Bye\n", (unsigned long)pthread_self());
	return NULL;
}



int main(void)
{
	int i;
	pthread_t arr[NTS];
	pthread_barrier_init(&barrier1, NULL, BAR_COUNT);
	pthread_barrier_init(&barrier2, NULL, BAR_COUNT);
    
    for(i = 0; i < NTS; ++i)
    {
		pthread_create(&arr[i],NULL, ThreadFunc, NULL);
	}
	

    
	for(i = 0; i < NTS; ++i)
    {
		pthread_join(arr[i], NULL);
	}
	
	
	pthread_barrier_destroy(&barrier1);
	pthread_barrier_destroy(&barrier2);
	

	return 0;
}
