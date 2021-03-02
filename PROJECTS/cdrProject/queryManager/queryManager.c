#include "channel.h"
#include "queryManager.h"
#include "aggregator.h"
#include <string.h> /*strstr*/
#include <stdlib.h>
#include <stdio.h> /*fopen*/
#include <assert.h>
#include <pthread.h>
#include "com.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>


#define CHAN_SIZE 4096
#define MAX_THREADS_NUM 4


#define NDEBUG

struct QueryManager{
	Aggregator** m_aggregatorsArray;
	Channel* m_uiChannel;
	}; 


typedef struct args {
	Aggregator** m_aggArr;
	DataMsg m_data;
	}args;


/*agg[0] = subagg
 * agg[1] = opagg
 * */

static void NumToString(size_t _num, char* _str)
{
    sprintf(_str, "%lu", _num);
    return;
}


void* ThreadFunction(void* threadArgs)
{
	args* ptr = NULL;
	pid_t pid;
	ptr = (args*)threadArgs;
	char pidChannel[24];
	Channel* downChan;
	DataMsg msg;
	char PID[16];
	Aggregator_Result agg_ret;
	char _pQueryRet[1024];
	
	
	
	pid = ptr->m_data.m_senderPid;
	
    sprintf(PID, "%lu", (size_t)ptr->m_data.m_senderPid);
    
    printf("ui pID %s\n",PID);
	
	
	msg.m_senderPid = getpid();
	msg.m_command = DCMD_PING;
	
	
	downChan = ChannelCreate(PID , CHAN_SIZE, CHANNEL_CREATE);
	
	switch(ptr->m_data.m_command)
	{
		case DCMD_PING:
		
		printf("Received Ping from UI-PID  %lu\n",(size_t)pid);
		ChannelTransmit(downChan, &msg, sizeof(DataMsg));
		break;
		
		case DCMD_SUBQ:
		agg_ret = AggGetSubscriberQuery(ptr->m_aggArr[0], ptr->m_data.m_subImsi, msg.m_retvalQuery);
		msg.m_senderPid = getpid();
		msg.m_command = DCMD_SUBQ;
		msg.m_subImsi =  ptr->m_data.m_subImsi;
		/**assert(agg_ret == AGGREGATOR_SUCCESS);*/
		ChannelTransmit(downChan, &msg, sizeof(DataMsg));
		break;
		
		case DCMD_OPQ:
		
		break;
		
		case DCMD_SUBREP:
		
		break;
		
		
		case DCMD_OPREP:
		
		break;
		default: break;
	}
	
	return (void*)0;
}

/**********************************************************************************************/

QueryManager* QueryManagerCreate(Aggregator** _aggregatorsArray, const char* _uiChannelName)
{
	QueryManager* ptr = NULL;
	if(!_aggregatorsArray || !*_aggregatorsArray)
	{
		return NULL;
	}
	
	ptr = (QueryManager*)malloc(sizeof(QueryManager));
	if(!ptr)
	{
		return NULL;
	}
	
	ptr->m_uiChannel = ChannelCreate(_uiChannelName, CHAN_SIZE, CHANNEL_CREATE);
	if(!ptr->m_uiChannel)
	{
		free(ptr);
		return NULL;
	}
	
	ptr->m_aggregatorsArray = _aggregatorsArray;
	return ptr;
}

/**********************************************************************************************/
void QueryManagerDestroy(QueryManager** _pQueryManager, Aggregator*** _retvalAggregatorsArray)
{
	if(!_pQueryManager || !*_pQueryManager || !_retvalAggregatorsArray )
	{
		return;
	}
	*_retvalAggregatorsArray = (*_pQueryManager)->m_aggregatorsArray;
	ChannelDestroy(&(*_pQueryManager)->m_uiChannel);
	free(*_pQueryManager);
	*_pQueryManager=NULL;
	return;
}
/**********************************************************************************************/
QueryManager_Status QueryManagerStartListening(QueryManager* _queryManager)
{
	pthread_t getter;	
	args* ptr = NULL;
	DataMsg pMsg;
	int retval =0;
	
	if(!_queryManager)
	{
		return QUERYMANAGER_NOT_INITIALIZED;
	}
	
	ptr = (args*)malloc(sizeof(args));
	if(!ptr)
	{
		return QUERYMANAGER_ALLOCATION_ERROR;
	}
	
	ptr->m_aggArr = _queryManager->m_aggregatorsArray;

	while((ChannelReceive(_queryManager->m_uiChannel, &pMsg, sizeof(DataMsg)) == CHANNEL_SUCCESS))
	{		
		ptr->m_data = pMsg;
		
		retval = pthread_create(&getter, NULL, ThreadFunction, ptr);
		if(retval)
		{
			return QUERYMANAGER_THREAD_CREATE_ERROR;
		}
		
		/**ThreadFunction(ptr);**/
		
		if(pthread_join(getter, NULL))
		{
			return QUERYMANAGER_THREAD_JOIN_ERROR;
		}
	}
		
	return QUERYMANAGER_CHANNEL_COMM_UI_ERROR;	
}











