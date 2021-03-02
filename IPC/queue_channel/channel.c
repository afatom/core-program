
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "channel.h"
#include <semaphore.h>

#define CHANNEL_MESSAGE_ID 5
#define TRUE 1
#define FALSE 0






#define FAIL 0
#define SUCCESS 1
#define CHANNEL_IS_VALID 0xBEEFBEEF
#define CHANNEL_IS_DESTROYED 0x0xDEADBEEF


struct Channel {
	char* 				m_buffer;
	char* 				m_head;
	char* 				m_tail;
	size_t 				m_msgSize;
	size_t 				m_msgsNum;
	pthread_mutex_t 	m_readerLocker; 		/*lock critical section while sending/writing to Q*/
	pthread_mutex_t 	m_aggregatorLocker;	/*lock critical section while receiving/reading from Q*/ 
	sem_t 				m_isEmpty;						
	sem_t 				m_isFull;	
};

/******************************************************************************/
static int ChannelInit(Channel* _chan, size_t _msgSize, size_t _msgsNum, char* _MemBuffer);
static int SemAndMutexInit(Channel* _channel, size_t _msgsNum);
static void SemAndMutexDestroy(Channel* _channel);
/******************************************************************************/
static int ChannelInit(Channel* _chan, size_t _msgSize, size_t _msgsNum, char* _MemBuffer)
{
	if((SemAndMutexInit(_chan,_msgsNum))==FAIL)
	{
		return FAIL;
	}
	_chan->m_buffer= _MemBuffer;
	_chan->m_head = _MemBuffer;
	_chan->m_tail = _MemBuffer;
	_chan->m_msgSize = _msgSize;
	_chan->m_msgsNum = _msgsNum;
   	_chan->m_tail = _chan->m_tail + (_chan->m_msgSize);
   	_chan->m_head = _chan->m_head + (_chan->m_msgSize);
	return SUCCESS;
}
/******************************************************************************/



static int SemAndMutexInit(Channel* _channel, size_t _msgsNum)
{
	if (pthread_mutex_init(&_channel->m_readerLocker, NULL) != 0 || pthread_mutex_init(&_channel->m_aggregatorLocker, NULL) != 0 || 
	sem_init(&_channel->m_isEmpty, 0, 0) != 0 || 
	sem_init(&_channel->m_isFull, 0,(unsigned int)_msgsNum)!=0)
    {
    	SemAndMutexDestroy(_channel);
        return FAIL;
    }
    return SUCCESS;
}
/******************************************************************************/

static void SemAndMutexDestroy(Channel* _channel)
{
	pthread_mutex_destroy(&_channel->m_readerLocker);
	pthread_mutex_destroy(&_channel->m_aggregatorLocker);
	sem_destroy(&_channel->m_isEmpty);
	sem_destroy(&_channel->m_isFull);
	return;
}
/******************************************************************************/

Channel* ChannelCreate(const char* _channelName,size_t _msgSize ,size_t _msgsNum,CHANNEL_FLAGS _flags)
{
	Channel* chan;
	char* buf;
	
	
	buf = (char*)malloc((_msgsNum+1) * _msgSize * sizeof(char));
   	if(NULL == buf)
   	{
   		return NULL;
   	}
   	
   	chan = (Channel*)malloc(sizeof(Channel));
   	if(NULL == chan)
   	{	
   		free(buf);
   		return NULL;
   	}
   	
   	if ((ChannelInit(chan, _msgSize, _msgsNum, buf)) !=SUCCESS)
   	{
   		free(buf);
   		free(chan);
   		return NULL;
   	}
   	
	

   	return chan;
}	
/******************************************************************************/
   	

void ChannelDestroy(Channel** _channel)
{
	if(NULL == _channel || NULL == *_channel) 
	{
		return;
	}
	SemAndMutexDestroy(*_channel);
	free((*_channel));
	(*_channel) = NULL;	
	return;
}
/******************************************************************************/
ChannelStatus ChannelTransmit(Channel* _channel, const void* _pMsg, size_t _msgSize)
{
	sem_wait(&(_channel->m_isFull));
	
	/** crucial check*/
	if((pthread_mutex_lock(&(_channel->m_readerLocker)))!= 0)
	{
		return CHANNEL_TRANSMITTING_ERROR;
	}
	
	memcpy(_channel->m_tail, _pMsg, _channel->m_msgSize);	
	
	_channel->m_tail += ( (sizeof(char))*(_channel->m_msgSize)) % (sizeof(char))*(_channel->m_msgsNum);
	
	
	pthread_mutex_unlock(&(_channel->m_readerLocker));
	sem_post(&(_channel->m_isEmpty));

	return CHANNEL_SUCCESS;
	
}
/******************************************************************************/


ChannelStatus ChannelReceive(Channel* _channel, void* _pMsg, size_t _msgSize)
{

	sem_wait(&(_channel->m_isEmpty));
	/** crucial check*/
	if((pthread_mutex_lock(&(_channel->m_aggregatorLocker))) != 0)
	{
		return CHANNEL_RECEIVING_ERROR;
	}
	
	memcpy(_pMsg, _channel->m_head , _channel->m_msgSize);
	
	_channel->m_head += ((sizeof(char))*(_channel->m_msgSize)) % (sizeof(char))*(_channel->m_msgsNum);
	/*_channel->m_numOfElements --;*/
	
	
	pthread_mutex_unlock(&(_channel->m_aggregatorLocker));
	sem_post(&(_channel->m_isFull));

	return CHANNEL_SUCCESS;
}

/******************************************************************************/











