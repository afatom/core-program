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
	pthread_t thread1;
	pthread_t thread2;
	
	char* msg = 
	"Hi, from user, its user msg!/nhellow world again!/n... Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do:  once or twice she had... peeped into the book her sister was reading, but it had no ...pictures or conversations in it, `and what is the use of a book,...thought Alice `without pictures or conversation?... So she was considering in her own mind (as well as she could,...for the hot day made her feel very sleepy and stupid), whether...the pleasure of making a daisy-chain would be worth the troubl...of getting up and picking the daisies, when suddenly a Whit...Rabbit with pink eyes ran close by her";
	
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
	
	if(pthread_create(&thread2,NULL,(void*)&Consumer,(void*)buf) != 0)
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

