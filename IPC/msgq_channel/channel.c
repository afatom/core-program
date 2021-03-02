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

/**********************************************************************/
struct Channel {
	size_t m_magic;
	int m_msgQueueId; 
};
/**********************************************************************/


static int ConvertChannelFlags(CHANNEL_FLAGS _flags);
static MsgHeader* MsgGenerator(const void* _pMsg, size_t _msgSize, int _isTransmit);

/**********************************************************************/
Channel* ChannelCreate(const char* _channelName, size_t _bufferSize,CHANNEL_FLAGS _flags)
{
	
	key_t qkey;
   	Channel* ch = NULL;
   	char userPath[MAX_PATH_LENGTH];
   	int msqid;
   	FILE* fp = NULL; 
   	
  
   	ch = (Channel*)malloc(sizeof(Channel));
   	if(NULL == ch)
   	{
   		return NULL;
   	}
   	
   	/*snprintf(userPath,MAX_PATH_LENGTH,"%s%s%s","/tmp/",_channelName,"msgq");*/
   	strcpy(userPath,"/tmp/");
   	strncat(userPath, _channelName, MAX_PATH_LENGTH);
   	strcat(userPath,"msgq");
   	
   	fp = fopen(userPath,"w+");
   	assert(fp != NULL);
   	if ((qkey = ftok(userPath, PROJ_ID)) == -1)
   	{
		perror("ftok generating key err");
		exit(1);
	}
	 
	
	#ifdef NDEBUG
	printf("ftok Key %lx\n", (size_t)qkey);
	#endif
	
	if ((msqid = msgget(qkey, 0666|ConvertChannelFlags(_flags))) == -1)
	{
		perror("Channel Create Error");
		free(ch);
  		return NULL;
	}
	
	ch->m_msgQueueId = msqid;
	ch->m_magic = VALID_CHANNEL;
	return ch;
}
/**********************************************************************/


void ChannelDestroy(Channel** _channel)
{

	if(NULL == _channel || NULL == *_channel || (*_channel)->m_magic != VALID_CHANNEL)
	{
		return;
	}
	
	(*_channel)->m_magic = DESTROYED_CHANNEL;
	msgctl((*_channel)->m_msgQueueId,IPC_RMID,NULL);
	free(*_channel);
	*_channel=NULL;
	return;
}
/**********************************************************************/
ChannelStatus ChannelTransmit(Channel* _channel, const void* _pMsg, size_t _msgSize)
{
	MsgHeader* pNMsg=NULL;
	if(NULL == _channel || _channel->m_magic != VALID_CHANNEL)
	{
		return CHANNEL_UN_INITIALIZED;
	}
	
	if(NULL == _pMsg)
	{
		return CHANNEL_INVALID_FUNCTION_PARAMETER;
	}
	
	pNMsg =MsgGenerator(_pMsg, _msgSize, TRUE);
	assert(pNMsg != NULL);
	
	if ((msgsnd(_channel->m_msgQueueId, pNMsg, _msgSize,  0))!=0) /** flag was zero**/
	{
		perror("Channel Send Error");
  		return CHANNEL_TRANSMITTING_ERROR;
	}
	
	free(pNMsg);
	
	return CHANNEL_SUCCESS;
}



ChannelStatus ChannelReceive(Channel* _channel, void* _pMsg, size_t _msgSize)
{
	MsgHeader* pNMsg=NULL;
	if(NULL == _channel || _channel->m_magic != VALID_CHANNEL)
	{
		return CHANNEL_UN_INITIALIZED;
	}
	
	if(NULL == _pMsg)
	{
		return CHANNEL_INVALID_FUNCTION_PARAMETER;
	}
	
	pNMsg = MsgGenerator(_pMsg, _msgSize, FALSE);
	assert(pNMsg != NULL);
	
	msgrcv(_channel->m_msgQueueId, (void*)pNMsg, _msgSize,MTYPE, 0);
	
	memcpy(_pMsg, pNMsg+1, _msgSize);
	
	free(pNMsg);

	return CHANNEL_SUCCESS;
	
}


/**********************************************************************/
static int ConvertChannelFlags(CHANNEL_FLAGS _flags)
{
	switch (_flags)
	{
		case(CHANNEL_CREATE):
		/**printf("IPC CREAT VAL %d\n",(int)IPC_CREAT);**/
		return IPC_CREAT;  
		break;
		
		case(CHANNEL_OPEN):
		return IPC_CREAT;
		break;
		
		case(CHANNEL_EXCL):
		return IPC_CREAT|IPC_EXCL;
		break;
		
		default: break;
	}
	return 0;
}
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





