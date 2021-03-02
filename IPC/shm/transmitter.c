#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>


void Producer(void* _msg);
void Consumer(void* _buffer);

char buf[1024];
sem_t mutex;

#define SIZE 1024
#define FAILURE -1
#define SUCCESS 0
#define MAX_LINE_SIZE 256


int main (int argc, char* argv[])
{

   	key_t shmkey;
   	const char *pathname = "PRCSHM";
   	int proj_id = 'A'; 
   	int shmid; /*msg q id*/
   	void* shmptr = NULL;
   	
   	shmkey = ftok(pathname, proj_id); /*<< generate aunique queue key*/

	if ((shmid = shmget(shmkey,SIZE,0666|IPC_CREAT)) == -1)
	{
		puts("SHMget Error");
		perror("SHMget Error");
  		exit(EXIT_FAILURE);
	}

	shmptr = shmat(shmid,(void*)0,0); /*check flag*/
	if(shmptr == (char*)(-1))
	{
		puts("SHMat Err");
		perror("SHMat Err");
  		exit(EXIT_FAILURE);
	}

	int ReadAndWriteline(const char* _src, void* _destBuf);
	

	



return 0;
}



int ReadAndWriteline(const char* _src, void* _destBuf)
{
	FILE* fp = NULL;
	fp  = fopen(_src, "a+");
	if(fp == NULL)
	{
		return FAILURE; 
	}
	while(!ferror(fp))
	{
		fgets ((char*)_destBuf, MAX_LINE_SIZE, fp );
	}
	fclose(fp);
	return SUCCESS;
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

