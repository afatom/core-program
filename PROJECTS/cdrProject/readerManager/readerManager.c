#include "readerManager.h"
#include "watcher.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "channel.h"
#include <pthread.h>
#include "com.h"
#include <unistd.h>
#include <stdio.h>

#define CHAN_BUFF_SIZE 4096
#define FOUND 1
#define NOT_FOUND 0

#define READER_MANAGER_IS_VALID 0xBEEFBEEF
#define READER_MANAGER_IS_UNVALID 0xDEADBEEF





struct ReaderManager{
	size_t m_magicNum;
	Watcher* m_watcher;
	Channel* m_upControlChannel;
	Channel* m_downControlChannel;
	};



typedef struct args {
	Watcher* m_watcher;
	Channel* m_upControlChannel;
	Channel* m_downControlChannel;
	}args;


void* ListenerThreadFunction(void* argsPtr)
{
	CCMD inCommand;
	ControlMsg inMsg;
	
	args* ptr = NULL;
	ptr = (args*)argsPtr;
	
	while((ChannelReceive(ptr->m_upControlChannel, &inMsg, sizeof(ControlMsg)) == CHANNEL_SUCCESS))
	{	
		switch(inMsg.m_command)
		{
			case CCMD_PING:
			puts("CCMD_PING   Received :From: Main");
			assert(ChannelTransmit(ptr->m_downControlChannel, 
		&inMsg, sizeof(ControlMsg)) == CHANNEL_SUCCESS);
			break;
			
			case CCMD_PAUSE:
			assert((WatcherPauseWatching(ptr->m_watcher)) == WATCHER_SUCCESS);
			break;
			
			case CCMD_RESUME:
			assert((WatcherResumeWatching(ptr->m_watcher)) == WATCHER_SUCCESS);
			break;
			
			case CCMD_SHUTDOWN:
			assert((WatcherShutDown(ptr->m_watcher)) == WATCHER_SUCCESS);
			break;
			
			default: break;
		}
		puts("Listener is Listening");
	}
	
	return (void*)0;
}






static size_t SearchInConfigFile(const char* configFile, const char* str);
static int GetStrInConfigFile(const char* configFile, const char* str, char* buffer);


ReaderManager* ReaderManagerCreate(const char* _configFile)
{
	ReaderManager* ptr = NULL;
	Watcher* pwt = NULL;
	char parserAbsolutePath[512];
	char cdrsRelativePath[512];
	char dataChannelName[512];
	char upControlChannelName[64];
	char dnControlChannelName[64];
	int retval =0;
	
	ptr = (ReaderManager*)malloc(sizeof(ReaderManager));
	if(!ptr)
	{
		return NULL;
	}
	
	assert((retval = GetStrInConfigFile(_configFile, "up controll channel name", upControlChannelName)) == FOUND);
	if(!retval)
	{
		free(ptr);
		return NULL;
	}
	
	assert((ptr->m_upControlChannel = ChannelCreate(upControlChannelName, CHAN_BUFF_SIZE, CHANNEL_CREATE))!=NULL);
	if(ptr->m_upControlChannel == NULL)
	{
		free(ptr);
		return NULL;
	}
	
	
	
	assert((retval = GetStrInConfigFile(_configFile, "down controll channel name", dnControlChannelName)) == FOUND);
	if(!retval)
	{
		ChannelDestroy(&(ptr->m_upControlChannel));
		free(ptr);
		return NULL;
	}
	
	assert((ptr->m_downControlChannel = ChannelCreate(dnControlChannelName, CHAN_BUFF_SIZE, CHANNEL_CREATE))!=NULL);
	if(ptr->m_downControlChannel == NULL)
	{
		ChannelDestroy(&(ptr->m_upControlChannel));
		free(ptr);
		return NULL;
	}
	
	
	assert((retval = GetStrInConfigFile(_configFile, "parser path", parserAbsolutePath)) == FOUND);
	if(!retval)
	{
		free(ptr);
		return NULL;
	}
	
	assert((retval = GetStrInConfigFile(_configFile, "cdr channel name", dataChannelName)) == FOUND);
	if(!retval)
	{
		free(ptr);
		return NULL;
	}
	
	assert((retval = GetStrInConfigFile(_configFile, "cdrs relative path", cdrsRelativePath)) == FOUND);
	if(!retval)
	{
		free(ptr);
		return NULL;
	}
	
	pwt =  WatcherCreate(parserAbsolutePath, cdrsRelativePath, dataChannelName);
	if(!pwt)
	{
		free(ptr);
		return NULL;
	}
	
	ptr->m_watcher = pwt;
	ptr->m_magicNum = READER_MANAGER_IS_VALID;
	return ptr;
}

/******************************************************************************************************************/
void ReaderManagerDestroy(ReaderManager** _pReaderManager)
{
	if(!_pReaderManager || !*_pReaderManager || (*_pReaderManager)->m_magicNum != READER_MANAGER_IS_VALID)
	{
		return; 
	}
	
	(*_pReaderManager)->m_magicNum = READER_MANAGER_IS_UNVALID;
	WatcherDestroy(&(*_pReaderManager)->m_watcher);
	free((*_pReaderManager));
	(*_pReaderManager)=NULL;
	return;
}
/******************************************************************************************************************/


ReaderManager_Status ReaderManagerStart(ReaderManager* _readerManager)
{
	Watcher_Status stat;
	args* pthreadArgs = NULL;
	pthread_t listener;
	if(!_readerManager)
	{
		return READERMANAGER_NOT_INTIALIZED_ERROR;
	}
	
	pthreadArgs = (args*)malloc(sizeof(args));
	assert(pthreadArgs!=NULL);
	if(!pthreadArgs)
	{
		return READERMANAGER_ALLOCATION_ERROR;
	}
	
	
	pthreadArgs->m_watcher = _readerManager->m_watcher;
	pthreadArgs->m_upControlChannel = _readerManager->m_upControlChannel;
	pthreadArgs->m_downControlChannel = _readerManager->m_downControlChannel;
	
	assert((stat = WatcherStartWatching(_readerManager->m_watcher)) == WATCHER_SUCCESS);
	
	if(pthread_create(&listener, NULL,ListenerThreadFunction, pthreadArgs))
	{
		return READERMANAGER_THREAD_CREATING_ERROR;
	}
	
	return READERMANAGER_SUCCESS;
}



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
