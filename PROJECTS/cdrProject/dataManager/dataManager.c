#include "aggregator.h"
#include "distributor.h"
#include "dataManager.h"
#include "receiver.h"
#include "queryManager.h"
#include <string.h> /*strstr*/
#include <stdlib.h>
#include <stdio.h> /*fopen*/
#include <assert.h>
#include <pthread.h>


#define SUCCESS 1
#define FAIL 0
#define FOUND 1
#define NOT_FOUND 0

#define AGG_NUM 2


#define MAX_CHAN_NAME 1024


struct DataManager{
	QueryManager* m_qm;
	Receiver* m_rec;
	};
	
	
	typedef struct threadArgs{
			QueryManager* m_qm;
			Receiver* m_rec;
		}threadArgs;
	
/***************************************************************************/
static size_t SearchInConfigFile(const char* configFile, const char* str);
static int GetStrInConfigFile(const char* configFile, const char* str, char* buffer);
static DataManager_Status RecStatToDMStat(Receiver_Status stat); 
/***************************************************************************/
DataManager* DataManagerCreate(const char* _configFile)
{
	char* reportPath="/home/adhamfaris/work/PROJECTS/cdrProject/backup/bu.txt";
	Aggregator** aggArray;
	Aggregator** aggArrayCopy;
	DataManager* pdm = NULL;
	Distributor* dist = NULL;
	Receiver* rec = NULL;
	QueryManager* pqm = NULL;
	
	char channelName[MAX_CHAN_NAME];
	char uiQMchannel[MAX_CHAN_NAME];
	
	assert((GetStrInConfigFile(_configFile, "cdr channel name", channelName))==FOUND); 
	assert((GetStrInConfigFile(_configFile, "ui-queryManager channel", uiQMchannel))==FOUND); 
	
	pdm = (DataManager*)malloc(sizeof(DataManager));
	if(!pdm)
	{
		return NULL;
	}
	
	aggArray = (Aggregator**)malloc(2 * sizeof(Aggregator*));
	if(!aggArray || !*aggArray)
	{
		free(pdm);
		return NULL;
	}
	
	
	aggArrayCopy = (Aggregator**)malloc(2 * sizeof(Aggregator*));
	if(!aggArrayCopy || !*aggArrayCopy)
	{
		free(aggArray);
		free(pdm);
		return NULL;
	}
	
	aggArray[0] = AggregatorNewCreate(SearchInConfigFile(_configFile, "initial sub num"),SearchInConfigFile(_configFile, "growtg sub num") );
	assert(aggArray[0] != NULL);
	if(!aggArray[0])
	{
		free(aggArray);
		free(pdm);
		return NULL;
	}
	
	aggArray[1] = AggregatorNewCreate(SearchInConfigFile(_configFile, "initial op num"), SearchInConfigFile(_configFile, "growth op num"));
	assert(aggArray[1] != NULL);
	if(!aggArray[1])
	{
		AggregatorDestroy(&aggArray[0], reportPath, reportPath);
		free(aggArray);
		free(pdm);
		return NULL;
	}
	
	
	aggArrayCopy[0] = aggArray[0];
	aggArrayCopy[1] = aggArray[1];
	
	assert(aggArray[0]!=NULL);
	assert(aggArray[1]!=NULL);
	assert(aggArrayCopy[0]!=NULL);
	assert(aggArrayCopy[1]!=NULL);
	
	dist = DistributorCreate(aggArray, AGG_NUM);
	assert(dist!=NULL);
	rec = ReceiverCreate(channelName, SearchInConfigFile(_configFile, "threads num"), dist);
	pqm = QueryManagerCreate(aggArrayCopy,uiQMchannel);
	assert(pqm!=NULL);
	if(!pqm)
	{
		 /*Destroy all*/ /*<----------------------------------------------------------------------------------------------------------------------------------TODO*/
	}
	pdm->m_qm = pqm;
	pdm->m_rec = rec;
	return pdm;

}

 /************************************************************************************/
void DataManagerDestroy(DataManager** _dataManager)
{
	size_t j=0;
	char reportPath[256]="/home/adhamfaris/work/PROJECTS/cdrProject/backup/bu.txt";
	Aggregator_Result res;
	Distributor* dist = NULL;
	Aggregator** aggArr;
	Aggregator** aggQMArr;
	if(!_dataManager || !*_dataManager)
	{
		return;
	}
	
	/*aggArr = (Aggregator**)malloc(2*sizeof(Aggregator*));*/
	
	
	dist = ReceiverDestroy(&(*_dataManager)->m_rec);
	DistributorDestroy(&dist,&aggArr);
	for(j = 0; j < AGG_NUM; ++j)
	{
		assert(aggArr[j]!=NULL);
		
		res = AggregatorDestroy(&(aggArr[j]), reportPath, reportPath);
		assert(res == AGGREGATOR_SUCCESS);
	}
	
	QueryManagerDestroy(&(*_dataManager)->m_qm, &aggQMArr);
	
	free(*_dataManager);
	*_dataManager = NULL;
	return;
}
 /************************************************************************************/
void* QueryManagerThreadFunction(void* arg)
{
	threadArgs* ptr = NULL;
	ptr = (threadArgs*)arg;
	
	QueryManagerStartListening(ptr->m_qm);
	return (void*)0;
} 
 
 
void* ReceiverThreadFunction(void* arg)
{
	threadArgs* ptr = NULL;
	ptr = (threadArgs*)arg;
	Receiver_Status recstat;
	
	assert((recstat = ReceiverStart(ptr->m_rec))==RECEIVER_SUCCESS);
	return (void*)0;
} 

 
 
DataManager_Status DataManagerRun(DataManager* _dataManager)
{
	pthread_t qMThread;
	pthread_t recThread;
	threadArgs* ptr = NULL;
	
	Receiver_Status recstat;
	if(!_dataManager)
	{
		return DATAMANAGER_NOT_INITIALIZED;
	}
	
	
	ptr = (threadArgs*)malloc(sizeof(threadArgs));
	
	ptr->m_rec = _dataManager->m_rec;
	ptr->m_qm = _dataManager->m_qm;
	/*
	QueryManagerStartListening(_dataManager->m_qm);
	assert((recstat = ReceiverStart(_dataManager->m_rec))==RECEIVER_SUCCESS);
	*/
	
	
    assert((pthread_create(&qMThread, NULL,QueryManagerThreadFunction, ptr))==0);
  assert((pthread_create(&recThread, NULL,ReceiverThreadFunction, ptr))==0);                    
 
  
	assert((pthread_join(qMThread, NULL))==0);
	
	  assert((pthread_join(recThread, NULL))==0);
	
	
	/**
	 * There is aproblem here
	 * when line 157 is invoked the main thread of this program is in wait for task 157 for return
	 * and program will never reach line 158
	 * it seems like i need to create two threads ffor invoking these two tasks
	 * 
	 * **/
	
	return RecStatToDMStat(recstat);

}


/***********************************************************************
 * Static Funcs Implementaion
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * ********************************************************************/
 /************************************************************************************/
static size_t SearchInConfigFile(const char* configFile, const char* str)
{
	/** char str[64] = "initial sub num"; example **/
	FILE *fp;
	char temp[512];
	char* pos;
	char* npos;
	size_t res=0;

	if((fp = fopen(configFile, "r")) == NULL) {
		return(0);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			
			npos=strchr(temp, '\n'); /** remove /n from the string*/
			*npos = '\0';
		
			pos = temp;
			pos = pos + 1 + strlen(str);
			sscanf(pos,"%lu",&res);
			break;
		}
	}

	if(fp) 
	{
		fclose(fp);
	}
   	return(res);
}

/************************************************************************************/
static int GetStrInConfigFile(const char* configFile, const char* str, char* buffer)
{
	/** char str[64] = "initial sub num"; example **/
	FILE *fp;
	char temp[512];
	char* pos;
	char* npos;
	int retval = 0;

	if((fp = fopen(configFile, "r")) == NULL) {
		return(0);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			
			npos=strchr(temp, '\n'); /** remove /n from the string*/
			*npos = '\0';
		
			pos = temp;
			pos = pos + 1 + strlen(str);
			sscanf(pos,"%s",buffer);
			retval =1;
			break;
		}
	}

	if(fp) 
	{
		fclose(fp);
	}
   	return(retval);
}
/************************************************************************************/

static DataManager_Status RecStatToDMStat(Receiver_Status stat)
{
	DataManager_Status dmstat;
	switch(stat)
	{
		case RECEIVER_SUCCESS:
		dmstat = DATAMANAGER_SUCCESS;
		break;
		
		case RECEIVER_NOT_INITIALIZED_ERROR:
		dmstat = DATAMANAGER_NOT_INITIALIZED;
		break;
		
		case RECEIVER_ALLOCATION_ERROR:
		dmstat =  DATAMANAGER_ALLOCATION_FAILURE;
		break;
		
		case RECEIVER_CHANNEL_RECEIVING_DATA_ERROR:
		dmstat =  DATAMANAGER_COMM_ERROR_ON_DATA_CHANNEL;
		break;
		
		case RECEIVER_THREAD_JOIN_ERROR:
		dmstat =  DATAMANAGER_RECEIVER_MT_ERROR;
		break;
		
		default: break;
	}
	return dmstat;
}











