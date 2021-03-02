#include "receiver.h"
#include "cdr.h"
#include "channel.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "aggregator.h"
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define INIT_SUB_CAPACITY 1024
#define GROWTH_SUB_CAPACITY 2048
#define CHANNEL_SIZE 4096
#define DEBUG


#define THREADS_DEF_NUM 4


#define FAIL -1
#define SUCCESS 0
#define CHANNEL_CLOSE 1

struct Receiver{
	Channel* m_channel;
	Distributor* m_dist;
	pthread_t* m_threadsArr;
	size_t m_threadsNum;
};

typedef struct args {
	Channel* m_channel;
	Distributor* m_dist;
	}args;


void* Thread_1_Function(void* _args)
{
	Cdr* pMsg;
	size_t i;
	args* ptr = (args*)_args;
	pMsg = CDR_Create_Empty_Cdr();
	
	while((ChannelReceive(ptr->m_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		#ifdef DEBUG
		puts("Thread_1 Rx cdr\n");
		CdrPrint(pMsg);
		#endif
		
		if (DistributorInsert(ptr->m_dist, pMsg) != DISTRIBUTOR_SUCCESS)
		{
			return (void*)FAIL;
		}
	}
	return (void*)CHANNEL_CLOSE;
}

void* Thread_2_Function(void* _args)
{
	Cdr* pMsg;
	size_t i;
	args* ptr = (args*)_args;
	pMsg = CDR_Create_Empty_Cdr();
	
	while((ChannelReceive(ptr->m_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		#ifdef DEBUG
		puts("Thread_2 Rx cdr\n");
		CdrPrint(pMsg);
		#endif
		
		if (DistributorInsert(ptr->m_dist, pMsg) != DISTRIBUTOR_SUCCESS)
		{
			return (void*)FAIL;
		}
	}
	return (void*)CHANNEL_CLOSE;
}

void* Thread_3_Function(void* _args)
{
	Cdr* pMsg;
	size_t i;
	args* ptr = (args*)_args;
	pMsg = CDR_Create_Empty_Cdr();
	
	while((ChannelReceive(ptr->m_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		#ifdef DEBUG
		puts("Thread_3 Rx cdr\n");
		CdrPrint(pMsg);
		#endif
		
		if (DistributorInsert(ptr->m_dist, pMsg) != DISTRIBUTOR_SUCCESS)
		{
			return (void*)FAIL;
		}
	}
	return (void*)CHANNEL_CLOSE;
}

void* Thread_4_Function(void* _args)
{
	Cdr* pMsg;
	size_t i;
	args* ptr = (args*)_args;
	pMsg = CDR_Create_Empty_Cdr();
	
	while((ChannelReceive(ptr->m_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		#ifdef DEBUG
		puts("Thread_4 Rx cdr\n");
		CdrPrint(pMsg);
		#endif
		
		if (DistributorInsert(ptr->m_dist, pMsg) != DISTRIBUTOR_SUCCESS)
		{
			return (void*)FAIL;
		}
	}
	return (void*)CHANNEL_CLOSE;
}
/**
static int isDestroyMsg(Cdr _msg);**/


/**********************************************************************************************/

Receiver* ReceiverCreate(const char* _channelName, const size_t _threadsNum, Distributor* _distributor)
{
	Receiver* rec = NULL;
	if(!_threadsNum || !_distributor)
	{
		return NULL;
	}
	
	rec = (Receiver*)calloc(1,sizeof(Receiver));
	if(!rec)
	{
		return NULL;
	}
	
	rec->m_threadsArr = (pthread_t*)malloc(THREADS_DEF_NUM * sizeof(pthread_t));	
	if(!rec->m_threadsArr)
	{
		free(rec);
		return NULL;
	}

	rec->m_channel = ChannelCreate(_channelName, CHANNEL_SIZE,CHANNEL_CREATE);
	if(!rec->m_channel)
	{
		free(rec->m_threadsArr);
		free(rec);
		return NULL;
	}
	
	rec->m_threadsNum = THREADS_DEF_NUM;
	rec->m_dist = _distributor;
	return rec;
}
/**********************************************************************************************/

Distributor* ReceiverDestroy(Receiver** _receiver)
{
	Distributor* dist = NULL;
	
	if(!_receiver || !*_receiver)
	{
		return NULL;
	}

	dist = ((*_receiver)->m_dist);
	ChannelDestroy(&((*_receiver)->m_channel));
	free((*_receiver)->m_threadsArr);
	free((*_receiver));
	(*_receiver) = NULL;
	return dist;
}


/**********************************************************************************************/

Receiver_Status ReceiverStart(Receiver* _receiver)
{
	Cdr* pMsg;
	size_t i=0;
	args* ptr = NULL;
	
	pMsg = CDR_Create_Empty_Cdr();
	
	i = _receiver->m_threadsNum;
	if(!_receiver)
	{
		return RECEIVER_NOT_INITIALIZED_ERROR;
	}
	
	ptr = (args*)malloc(sizeof(args));
	assert(ptr != NULL);
	
	ptr->m_channel = _receiver->m_channel;
	ptr->m_dist = _receiver->m_dist;
	
	if(pthread_create(&_receiver->m_threadsArr[0], NULL,Thread_1_Function, ptr)){
		return RECEIVER_CHANNEL_RECEIVING_DATA_ERROR;
	}
	
	if(pthread_create(&_receiver->m_threadsArr[1], NULL,Thread_2_Function, ptr)){
		return RECEIVER_CHANNEL_RECEIVING_DATA_ERROR;
	}
	
	if(pthread_create(&_receiver->m_threadsArr[2], NULL,Thread_3_Function, ptr)){
		return RECEIVER_CHANNEL_RECEIVING_DATA_ERROR;
	}
	
	if(pthread_create(&_receiver->m_threadsArr[3], NULL,Thread_4_Function, ptr)){
		return RECEIVER_CHANNEL_RECEIVING_DATA_ERROR;
	}
	
	for(i = 0; i < THREADS_DEF_NUM; ++i)
	{
	   if(pthread_join(_receiver->m_threadsArr[i], NULL))
	   {
		   return RECEIVER_THREAD_JOIN_ERROR;
	   }
	}
	
	
	ChannelDestroy(&_receiver->m_channel);
	return RECEIVER_SUCCESS;
}
/**********************************************************************************************/





