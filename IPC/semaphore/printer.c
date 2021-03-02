#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>


void Producer(void* _msg);
void Consumer(void* _buffer);

char buf[1024];
sem_t mutex;


int main (int argc, char* argv[])
{
	/*shared memmory Object*/
	const char* shm = "/obj";
   	int shm_open(shm, O_RDWR, mode_t mode);

	char* msg = "Hi, from user, its user msg!";
	
	if(sem_init(&mutex,0,1) != 0)
	{
		printf("Semaphore Init Error::\n");
		perror("Semaphore Init Fails");
  		exit(EXIT_FAILURE);
	}
	
	 
	sem_destroy(&mutex); 

return 0;
}



void Producer(void* _msg)
{
	char* ptr = (char*)_msg;
	/*we need to lock this section while Produser is Wr to buf*/
	sem_wait(&mutex);
	sprintf(buf,"%s",ptr); 		/*<< Critical Section! Wr user msg to buf*/
	sem_post(&mutex);
	pthread_exit(0);
	return;
}

void Consumer(void* _buffer)
{
	char* ptr = (char*)_buffer;
	/*Lock this section while consumer is reading data*/
	sem_wait(&mutex);
	printf("%s\n",ptr);		/*<< Critical section! Read and print user msg to stdout*/
	sem_post(&mutex);
	pthread_exit(0);
	return;
}

