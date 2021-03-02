#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "channel.h"
#include "mu_test.h"
#include <assert.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
/******************************************************************************/


/*char buf[1024];*/
pthread_mutex_t mutex;

int isEmpty = TRUE;

typedef struct Args{
	char* m_fileName;
	Channel* m_channel; 
}Args;



/******************************************************************************/

typedef struct Cdr
{
	char m_imsi[16]; char m_msidn[16]; char m_imei[16];
	char m_obn[64]; char m_mcc[8]; char m_ctype[8];
	char m_cd[8];char m_ctime[16];char m_dur[8];
	char m_dwn[8];char m_up[8];char m_pms[8];char m_pop[8];
}Cdr;


/******************************************************************************/
static FILE* FileInit(const char* _fileName)
{
	FILE* fp = NULL;
	fp = fopen(_fileName,"r");
	if(NULL == fp)
	{
		puts("File Open Err");	
	}
	rewind(fp);
	return fp;
}

/******************************************************************************/
static void ParseAndSend(Channel* _channel, FILE* _fp)
{
	Cdr mcdr;
		
	while (TRUE)
	{
		fscanf(_fp, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
			   mcdr.m_imsi, mcdr.m_msidn, mcdr.m_imei, mcdr.m_obn, mcdr.m_mcc, mcdr.m_ctype, mcdr.m_cd,
			   mcdr.m_ctime, mcdr.m_dur, mcdr.m_dwn, mcdr.m_up, mcdr.m_pms, mcdr.m_pop);
		if (feof(_fp))
		{
			break;
		}
/*		sleep(1);*/
		
		if(!pthread_mutex_lock(&mutex) && isEmpty)
		{
			assert(ChannelTransmit(_channel, &mcdr, sizeof(mcdr)) == CHANNEL_SUCCESS);
			isEmpty = FALSE;
			pthread_mutex_unlock(&mutex);			
		}
	}
	fclose(_fp);
	
}
	
/******************************************************************************/



void* Reader(void* _args)
{
	FILE* fp;
	
	fp = FileInit(((Args*)_args)->m_fileName);


	ParseAndSend(((Args*)_args)->m_channel, fp);
	pthread_exit(0);
	return (void*)(0);
}
/******************************************************************************/
void* Aggregator(void* _args)
{
	int i=0;
	Cdr pMsg;
	
	if(NULL == ((Args*)_args)->m_channel)
	{
		return _args;
	}
	
	while(TRUE)
	{
		/*		sleep(1);*/
		
		if(!pthread_mutex_lock(&mutex) && !isEmpty)
		{
			assert(ChannelReceive(((Args*)_args)->m_channel, &pMsg, sizeof(pMsg)) == CHANNEL_SUCCESS);
			isEmpty = TRUE;
			pthread_mutex_unlock(&mutex);			
		}
		
		/*assert(ChannelReceive(ch, &pMsg, sizeof(pMsg)) == CHANNEL_SUCCESS);*/
		printf("printing line # %d\n",++i);
		fprintf(stdout, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
				pMsg.m_imsi, pMsg.m_msidn, pMsg.m_imei, pMsg.m_obn, pMsg.m_mcc, pMsg.m_ctype, pMsg.m_cd,
				pMsg.m_ctime, pMsg.m_dur, pMsg.m_dwn, pMsg.m_up, pMsg.m_pms, pMsg.m_pop);

	
		
	}
	ChannelDestroy(&((Args*)_args)->m_channel);
	pthread_exit(0);
	return (void*)(0);
}
/******************************************************************************/

int main (int argc, char* argv[])
{
	pthread_t thread1;
	pthread_t thread2;
/*	assert (0 == pthread_mutex_destroy(&mutex));*/
	
/*   	assert(0 == pthread_mutex_init(&mutex,NULL));*/
   	if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        puts("Mutex Creation Failure");
        exit(1);
    }
	/*mutex = PTHREAD_MUTEX_INITIALIZER;*/
	

	Channel* ch;
	ch = ChannelCreate("MyOwnBuffer", 4096, CHANNEL_CREATE);
	if(NULL == ch)
	{
		exit(1);
	}
	
	
	Args* pArgs;
	pArgs = (Args*)malloc(sizeof(Args));
	
	pArgs->m_fileName = "cdr.txt";
	pArgs->m_channel = ch;
	
	
	
	if(pthread_create(&thread1,NULL,Reader,(void*)pArgs) != 0)
	{
		printf("Thread1 Create Error::\n");
		perror("Producer Thread Fails");
  		exit(EXIT_FAILURE);
	}
	
	if(pthread_create(&thread2,NULL,Aggregator,(void*)pArgs) != 0)
	{
		printf("Thread2 Create Error::\n");
		perror("Consumer Thread Fails");
  		exit(EXIT_FAILURE);
	}
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	 
	pthread_mutex_destroy(&mutex);
	ChannelDestroy(&ch);
return 0;
}


