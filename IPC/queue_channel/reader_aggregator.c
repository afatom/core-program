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
#define NDEBUG
/******************************************************************************/

#define MAX_LINE_LENGTH 256

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


static void SkipFirstLine(FILE* _fp);

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
	SkipFirstLine(_fp);
	
	while (TRUE)
	{
		fscanf(_fp, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
			   mcdr.m_imsi, mcdr.m_msidn, mcdr.m_imei, mcdr.m_obn, mcdr.m_mcc, mcdr.m_ctype, mcdr.m_cd,
			   mcdr.m_ctime, mcdr.m_dur, mcdr.m_dwn, mcdr.m_up, mcdr.m_pms, mcdr.m_pop);
		if (feof(_fp))
		{
			break;
		}
		sleep(1);

			assert(ChannelTransmit(_channel, &mcdr, sizeof(mcdr)) == CHANNEL_SUCCESS);		
	}
	fclose(_fp);
	
}
	
/******************************************************************************/



void* Reader(void* _args)
{
	FILE* fp;
	fp = FileInit(((Args*)_args)->m_fileName);
	ParseAndSend(((Args*)_args)->m_channel, fp);
	
	return (void*)(0);
}
/******************************************************************************/

static void SkipFirstLine(FILE* _fp)
{
	char buffer[MAX_LINE_LENGTH];
	fgets(buffer,MAX_LINE_LENGTH,_fp);
	return;
}
/**********************************************************************/
static int CheckAggParams(void* _args)
{
	if(NULL == ((Args*)_args)->m_channel)
	{
		return 1;
	}
	return 0;
}

static Cdr ReceiveMsg(void* _args)
{
	
	Cdr pMsg;
	
	assert(ChannelReceive(((Args*)_args)->m_channel, &pMsg, sizeof(pMsg)) == CHANNEL_SUCCESS);
	return pMsg;
}


static void PrintMsg(Cdr pMsg)
{
	int i =0;
	printf("printing line # %d\n",++i);
	fprintf(stdout, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
	pMsg.m_imsi, pMsg.m_msidn, pMsg.m_imei, pMsg.m_obn, pMsg.m_mcc, pMsg.m_ctype, pMsg.m_cd,
	pMsg.m_ctime, pMsg.m_dur, pMsg.m_dwn, pMsg.m_up, pMsg.m_pms, pMsg.m_pop);
	
	return ;
}

static int IsDestroyMsg(Cdr pMsg)
{
	int stat1 = 1, stat2 = 1, stat3 = 1;
	char buf1[16]="444444444";
	char buf2[16]="444444444";
	char buf3[16]="444444444";
	stat1 = strcmp(buf1,pMsg.m_imsi);
	
	stat2 = strcmp(buf2,pMsg.m_msidn);
	stat3 = strcmp(buf3,pMsg.m_imei);
	printf("stat1,2,3 %d %d %d\n",stat1,stat2,stat3);
	
	if(!stat1 && !stat2 && !stat3)
	{
		return TRUE;
	}
	return FALSE;
	
}

/**********************************************************************/
void* Aggregator(void* _args)
{
	int stat =0;
	Cdr pMsg;
	
	stat = CheckAggParams(_args);
	if(stat == 1) /** fail*/
	{
		return (void*)(1);
	}
	
	while(TRUE)
	{
		sleep(1);
		pMsg = ReceiveMsg(_args);
		if(IsDestroyMsg(pMsg) == TRUE)
		{
			puts("Received Channel Destroy Command! Closing Port & Destroying Channel");
			break;
		}
		PrintMsg(pMsg);
	}
	ChannelDestroy(&((Args*)_args)->m_channel);

	return (void*)(0);
}
/******************************************************************************/

int main (int argc, char* argv[])
{
	pthread_t thread1;
	pthread_t thread2;


	Channel* ch;
	ch = ChannelCreate("MyOwnBuffer",sizeof(Cdr) ,1024, CHANNEL_CREATE);
	#ifdef NDEBUG
	printf("%lu\n",sizeof(Cdr));
	#endif
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
/*	Aggregator((void*)pArgs);*/
/*	Reader((void*)pArgs);*/
	if(pthread_create(&thread2,NULL,Aggregator,(void*)pArgs) != 0)
	{
		printf("Thread2 Create Error::\n");
		perror("Consumer Thread Fails");
  		exit(EXIT_FAILURE);
	}
	
	assert((pthread_join(thread1,NULL)) == 0) ;
	assert((pthread_join(thread2,NULL)) == 0) ;

	

	ChannelDestroy(&ch);
return 0;
}


