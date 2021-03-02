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

#define DEBUG


struct Receiver{
	Channel* m_channel;
	Aggregator** m_aggArr;
	size_t m_aggregatorsNum;
	pthread_t* m_threadsArr;
	size_t m_threadsNum;
};




void* ThreadReceiveChannelFunction(void* _args);
/**
static int isDestroyMsg(Cdr _msg);**/

static void DestroyAggUpToNow(size_t _num,Aggregator** _arr);
static size_t GetThreadsNum(const char* _configFile);
static size_t GetChannelSize(const char* _configFile);
static char* GetChannelName(const char* _configFile, char* _chName);

static void DestroyAggUpToNow(size_t _num,Aggregator** _arr);
static size_t GetThreadsNum(const char* _configFile);
static size_t GetChannelSize(const char* _configFile);
static char* GetChannelName(const char* _configFile, char* _chName);

/**********************************************************************************************/
Receiver* ReceiverCreate(const char* _configFile, size_t _aggregatorsNum)
{
	Receiver* rec = NULL;
	size_t threadsNum=0,i=0;
	char chName[64];
	threadsNum = GetThreadsNum(_configFile);
	if(!threadsNum || !_aggregatorsNum)
	{

		return NULL;	
	}
	
	rec = (Receiver*)calloc(1,sizeof(Receiver));
	if(!rec)
	{
		return NULL;
	}

	if(!(rec->m_aggArr = (Aggregator**)calloc(_aggregatorsNum ,sizeof(Aggregator*))))
	{
		free(rec);
		return NULL;
	}

	for(i=0;i<_aggregatorsNum;++i)
	{
		if(!(rec->m_aggArr[i] = AggregatorNewCreate(INIT_SUB_CAPACITY, GROWTH_SUB_CAPACITY)))
		{
			DestroyAggUpToNow(i, rec->m_aggArr);
			free(rec->m_aggArr);
			free(rec);
		}
	}

GetChannelName(_configFile, chName);

	rec->m_threadsArr = (pthread_t*)malloc(threadsNum * sizeof(pthread_t));
	printf("%s",chName);
	sleep(3);
	rec->m_channel = ChannelCreate(chName, GetChannelSize(_configFile),CHANNEL_CREATE);
	rec->m_aggregatorsNum = _aggregatorsNum;
	rec->m_threadsNum = threadsNum;
	return rec;
}
/**********************************************************************************************/









void ReceiverDestroy(Receiver** _receiver)
{
	size_t i =0;
	if(!_receiver || !*_receiver)
	{
		return;
	}
	
	for(i = 0; i < (*_receiver)->m_aggregatorsNum; ++i)
	{
		AggregatorDestroy(&(*_receiver)->m_aggArr[i],"bu.txt" ,"bu.txt");
	}
	
	free((*_receiver)->m_threadsArr);
	free((*_receiver));
	(*_receiver) = NULL;
	return;
	
}
/**********************************************************************************************/

Receiver_Status ReceiverStart(Receiver* _receiver)
{
	Cdr* pMsg;
	size_t i;
 
	pMsg = CDR_Create_Empty_Cdr();
	
	i = _receiver->m_aggregatorsNum;
	if(!_receiver)
	{
		return RECEIVER_NOT_INITIALIZED_ERROR;
	}
	
	while((ChannelReceive(_receiver->m_channel, pMsg, CdrGetSize()) == CHANNEL_SUCCESS))
	{
		#ifdef DEBUG
		puts("Receiver-> Rx message Before Sending to aggs::");
		CdrPrint(pMsg);
		#endif
		while(i)
		{
			AggregatorInsertCdr(_receiver->m_aggArr[i], pMsg);
			--i;
		}
		i=_receiver->m_aggregatorsNum;
	}
	ChannelDestroy(&_receiver->m_channel);
	return RECEIVER_SUCCESS;
}



/**********************************************************************************************/
static size_t GetThreadsNum(const char* _configFile)
{
	FILE* fp;
	int ret =0;
	char buff[]="threads";
	char scan1[64];
	char scan2[64];
	
	
	fp = fopen(_configFile,"r");
	
	if(!fp)
	{
		
		return (size_t)ret;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);


		if(!strcmp(scan1,buff))
		{

			fscanf(fp,"%s ",scan2);

			fscanf(fp,"%d",&ret);

			
			break;
			
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return (size_t)ret;
}
/**********************************************************************************************/
static size_t GetChannelSize(const char* _configFile)
{
	FILE* fp;
	int ret =0;
	char channel[]="channel";
	char size[]="bufferSize";
	char scan1[64];
	char scan2[64];
	
	fp = fopen(_configFile,"r");
	if(!fp)
	{
		return 0;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);
		if(!strcmp(scan1,channel))
		{

			fscanf(fp,"%s ",scan2);
			if(!strcmp(scan2,size))
			{
				fscanf(fp,"%d",&ret);
				break;
			}
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return (size_t)ret;
}
/**********************************************************************************************/
static char* GetChannelName(const char* _configFile, char* _chName)
{
	FILE* fp;
	char* ret;
	char channel[]="channel";
	char name[]="name";
	char scan1[64];
	char scan2[64];
	
	ret = _chName;
	
	fp = fopen(_configFile,"r");
	if(!fp)
	{
		return 0;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);
		if(!strcmp(scan1,channel))
		{

			fscanf(fp,"%s ",scan2);
			if(!strcmp(scan2,name))
			{
				fscanf(fp,"%s",_chName);
				break;
			}
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return ret;
}
/**********************************************************************************************/
static void DestroyAggUpToNow(size_t _num,Aggregator** _arr)
{
	size_t i =0;
	for(i =0; i < _num; ++i)
	{
		AggregatorDestroy(&_arr[i], "bu.txt", "bu.txt");
	}
}
/**********************************************************************************************/
























/**********************************************************************************************/
static size_t GetThreadsNum(const char* _configFile)
{
	FILE* fp;
	int ret =0;
	char buff[]="threads";
	char scan1[64];
	char scan2[64];
	
	
	fp = fopen(_configFile,"r");
	
	if(!fp)
	{
		
		return (size_t)ret;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);


		if(!strcmp(scan1,buff))
		{

			fscanf(fp,"%s ",scan2);

			fscanf(fp,"%d",&ret);

			
			break;
			
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return (size_t)ret;
}
/**********************************************************************************************/
static size_t GetChannelSize(const char* _configFile)
{
	FILE* fp;
	int ret =0;
	char channel[]="channel";
	char size[]="bufferSize";
	char scan1[64];
	char scan2[64];
	
	fp = fopen(_configFile,"r");
	if(!fp)
	{
		return 0;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);
		if(!strcmp(scan1,channel))
		{

			fscanf(fp,"%s ",scan2);
			if(!strcmp(scan2,size))
			{
				fscanf(fp,"%d",&ret);
				break;
			}
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return (size_t)ret;
}
/**********************************************************************************************/
static char* GetChannelName(const char* _configFile, char* _chName)
{
	FILE* fp;
	char* ret;
	char channel[]="channel";
	char name[]="name";
	char scan1[64];
	char scan2[64];
	
	ret = _chName;
	
	fp = fopen(_configFile,"r");
	if(!fp)
	{
		return 0;
	}
	
	while(1)
	{
		fscanf(fp,"%s ",scan1);
		if(!strcmp(scan1,channel))
		{

			fscanf(fp,"%s ",scan2);
			if(!strcmp(scan2,name))
			{
				fscanf(fp,"%s",_chName);
				break;
			}
		}
		
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return ret;
}
/**********************************************************************************************/
static void DestroyAggUpToNow(size_t _num,Aggregator** _arr)
{
	size_t i =0;
	for(i =0; i < _num; ++i)
	{
		AggregatorDestroy(&_arr[i], "bu.txt", "bu.txt");
	}
}
/**********************************************************************************************/





