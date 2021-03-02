#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_THREADS 5

void* printthread(void* tid)
{
	printf("Hi. My thread ID is: %lu) %lu\n", *(size_t*)tid, pthread_self());
	pthread_exit(tid);
	return tid;
}


int main()
{
	void* retval = NULL;
	int status;
	size_t i =0;
	pthread_t threads[NUM_OF_THREADS];
	for(i =0; i<NUM_OF_THREADS; ++i)
	{
		int j = i;
		status = pthread_create(&threads[i],NULL,printthread, (void*)&j);
		/*pthread_join(pthread_self(), &retval);*/
		if(status)
		{
			/*thread creation fails*/
			continue;
		}
		
	}
	
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], &retval);
	}
	
return 0;
}
