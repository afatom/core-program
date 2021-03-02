#include "channel.h"
#include <time.h> /*srand*/
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
#include <stdlib.h>    
#include <stdio.h>

#include <string.h>
  

/*<< mutext init vars*/
pthread_mutex_t mutex;
int isEmpty = TRUE;


char* buffer=NULL;






/*#define NDEBUG*/
#define KEY_DEFINE 121
#define MTYPE 1
#define VALID_CHANNEL 		0xBEEFBEEF
#define DESTROYED_CHANNEL 	0xDEADBEEF
#define TRUE 1
#define FALSE 0
#define MAX_PATH_LENGTH 4096
#define PROJ_ID 128 /*max 8 bits*/

typedef struct MsgHeader
{
	long m_type; 
}MsgHeader;

static MsgHeader* MsgGenerator(const void* _pMsg, size_t _msgSize, int _isTransmit);

typedef struct Args{
	Channel* 	m_channel;
	void* 	 	m_originalMsg;
	MsgHeader* 	 m_tempMsg;
	size_t  m_msgSize; 
}Args;

static void* SndMsg(void* _args);
static void* RcvMsg(void* _args);
/**********************************************************************/
Channel* ChannelCreate(const char* _channelName, size_t _bufferSize,CHANNEL_FLAGS _flags)
{
	char* buf;
	pthread_t thread1;
	pthread_t thread2;
	/*	assert (0 == pthread_mutex_destroy(&mutex));*/
	
	/*   	assert(0 == pthread_mutex_init(&mutex,NULL));*/
		
	buf = (char*)malloc(_bufferSize * sizeof(char));
   	if(NULL == buf)
   	{
   		return NULL;
   	}
	
   	if (pthread_mutex_init(&mutex, NULL) != 0)
    {
    	free(buf);
       	return NULL;
    }
	/*mutex = PTHREAD_MUTEX_INITIALIZER;*/
	
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
	
	
	buffer = buf;
	return (Channel*)buffer;
}
/**********************************************************************/


void ChannelDestroy(Channel** _channel)
{

	if(NULL == (char**)_channel || NULL == *((char**)_channel) )
	{
		return;
	}

	free(*((char**)_channel));
	*(char**)_channel=NULL;
	return;
}
/******************************************************************************/
ChannelStatus ChannelTransmit(Channel* _channel, const void* _pMsg, size_t _msgSize)
{
	MsgHeader* pNMsg=NULL;
	Args args;
	if(NULL == (char*)_channel )
	{
		return CHANNEL_UN_INITIALIZED;
	}
	
	if(NULL == _pMsg)
	{
		return CHANNEL_INVALID_FUNCTION_PARAMETER;
	}

	
	pNMsg =MsgGenerator(_pMsg, _msgSize, TRUE);
	assert(pNMsg != NULL);
		
	args.m_channel = _channel;
	args.m_originalMsg = (void*)_pMsg;
	args.m_tempMsg = pNMsg;
	args.m_msgSize = _msgSize;
	
	/* b critical section*/
	if ((SndMsg((void*)&args)) != (void*)(0))
	{
		return CHANNEL_TRANSMITTING_ERROR;
		/*destroy mutex and exit*/
	}
	/* e critical section*/
	free(pNMsg);
	
	return CHANNEL_SUCCESS;
}

/******************************************************************************/

static void* SndMsg(void* _args)
{
	if(!pthread_mutex_lock(&mutex) && isEmpty)
	{
		memcpy(_args.m_tempMsg + 1, _args.m_originalMsg, _args.m_msgSize);
		memcpy(args.m_channel, _args.m_tempMsg + 1, _args.m_msgSize);
		isEmpty = FALSE;
		pthread_mutex_unlock(&mutex);
		return (void*)(0);		
	}
	return (void*)(1);/*mutex error occured*/
}
/******************************************************************************/

static void* RcvMsg(void* _args)
{	
	if(!pthread_mutex_lock(&mutex) && isEmpty)
	{
		memcpy(_args.m_tempMsg + 1, (void*)args.m_channel, _args.m_msgSize);
		memcpy(args.m_originalMsg, _args.m_tempMsg + 1, _args.m_msgSize);
		isEmpty = FALSE;
		pthread_mutex_unlock(&mutex);
		return (void*)(0);		
	}
	return (void*)(1);/*mutex error occured*/
}		


/******************************************************************************/


ChannelStatus ChannelReceive(Channel* _channel, void* _pMsg, size_t _msgSize)
{
	MsgHeader* pNMsg=NULL;
	Args args;
	if(NULL == (char*)_channel )
	{
		return CHANNEL_UN_INITIALIZED;
	}
	
	if(NULL == _pMsg)
	{
		return CHANNEL_INVALID_FUNCTION_PARAMETER;
	}
	
	pNMsg = MsgGenerator(_pMsg, _msgSize, FALSE);
	assert(pNMsg != NULL);
	
	args.m_channel = _channel;
	args.m_originalMsg = (void*)_pMsg;
	args.m_tempMsg = pNMsg;
	args.m_msgSize = _msgSize;
	
	
	/* b critical section*/
	if ((RcvMsg((void*)&args)) != (void*)(0))
	{
		return CHANNEL_RECEIVING_ERROR;
		/*destroy mutex and exit*/
	}
	/* e critical section*/
	

	
	free(pNMsg);

	return CHANNEL_SUCCESS;
	
}


/**********************************************************************/

/**********************************************************************/
static MsgHeader* MsgGenerator(const void* _pMsg, size_t _msgSize, int _isTransmit)
{
	/*msg size 0 is valid - PING betwen Tx/Rx*/
	MsgHeader* ptr = NULL;
	ptr = (MsgHeader*)malloc(sizeof(MsgHeader)+_msgSize);
	if(ptr && _isTransmit)
	{
		ptr->m_type = MTYPE;
		memcpy(ptr+1,_pMsg,_msgSize);
	}
	return ptr;
	
}


/**********************************************************************/





