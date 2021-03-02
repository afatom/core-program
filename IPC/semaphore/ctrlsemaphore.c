#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <pthread.h>


typedef int Discrete;
#define PAUSE_ON 	1
#define PAUSE_OFF 	0

void Producer(void* _msg);
void Consumer(void* _buffer);
void Controll(void* _isPause);

char buf[1024];
sem_t mutex;


int main (int argc, char* argv[])
{
	pthread_t thread1;
	pthread_t thread2;
	
	char* msg = 
	"Hi, from user, its user msg! Hellow iam producer";
	
	if(sem_init(&mutex,0,1) != 0)
	{
		printf("Semaphore Init Error::\n");
		perror("Semaphore Init Fails");
  		exit(EXIT_FAILURE);
	}
	
	if(pthread_create(&thread1,NULL,(void*)&Producer,(void*)msg) != 0)
	{
		printf("Thread1 Create Error::\n");
		perror("Producer Thread Fails");
  		exit(EXIT_FAILURE);
	}
	
	if(pthread_create(&thread2,NULL,(void*)&Controll,(void*)&argv[1]) != 0)
	{
		printf("Thread2 Create Error::\n");
		perror("Consumer Thread Fails");
  		exit(EXIT_FAILURE);
	}
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	 
	sem_destroy(&mutex); 

return 0;
}



void Producer(void* _msg)
{
	char* ptr = (char*)_msg;
	/*we need to lock this section while Produser is Wr to buf*/
	while (sem_wait(&mutex))
	{
		sprintf(buf,"%s",ptr); 		/*<< Critical Section! Wr user msg to buf*/
		printf("Producer/Printer Section, TID:%d.\n%s\n",(int)pthread_self(),buf);	
		sem_post(&mutex);
	}
	pthread_exit(0);
	return;
}


void Controll(void* _isPause)
{
	sem_wait(&mutex);
	if(atoi((char*)_isPause) == PAUSE_ON)
	{
		sem_post(&mutex);	
	}
	sem_post(&mutex);
	pthread_exit(0);
	return;
		
}




