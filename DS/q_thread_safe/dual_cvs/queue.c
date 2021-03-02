#include "tsqueue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "gdlist.h"
#include "list_itr.h"
#include "list_functions.h"
#include <assert.h>


#include <string.h>
#include <pthread.h>



#define CHANNEL_MESSAGE_ID 5
#define TRUE 1
#define FALSE 0




#define _DUAL_CV_



#define FAIL 0
#define SUCCESS 1
#define CHANNEL_IS_VALID 0xBEEFBEEF
#define CHANNEL_IS_DESTROYED 0x0xDEADBEEF

#define QUEUE_IS_EMPTY 0
#define QUEUE_IS_FULL 1
#define QUEUE_IS_NOT_FULL 4
#define QUEUE_SIZE 2048




struct Queue{
    List*    		m_list;
    size_t 			m_items;
    int 			m_isEmpty;
    
	pthread_cond_t 	m_readersCv;
	#ifdef _DUAL_CV_
	pthread_cond_t 	m_aggregatorsCv;
	#endif
	pthread_mutex_t m_mutex;	
};

static void CvAndMutexDestroy(Queue* _queue);
static int QueueInit(Queue* _queue);


static int QueueInit(Queue* _queue)
{
	#ifdef _DUAL_CV_
	if (pthread_cond_init(&_queue->m_aggregatorsCv, NULL) != 0)
	{
		return FAIL;
	}
	#endif
	
	if (pthread_mutex_init(&_queue->m_mutex, NULL) != 0 || pthread_cond_init(&_queue->m_readersCv, NULL)!= 0 )
	{
		
		CvAndMutexDestroy(_queue);
		return FAIL;
	}
	_queue->m_isEmpty = QUEUE_IS_EMPTY;
	_queue->m_items = QUEUE_IS_EMPTY;
	
	return SUCCESS;
}



static void CvAndMutexDestroy(Queue* _queue)
{
	#ifdef _DUAL_CV_
	pthread_cond_destroy(&_queue->m_aggregatorsCv);
	#endif
	pthread_cond_destroy(&_queue->m_readersCv);
	pthread_mutex_destroy(&_queue->m_mutex);
	return;
}



/*******************************************************************************/
Queue* QueueCreate(void)
{
    Queue *_queuePtr = NULL;
    /*malloc for Q struct*/
    _queuePtr = (Queue*)malloc(sizeof(Queue));
    /*check malloc*/
    if (NULL == _queuePtr)
    {
        return NULL; /*malloc failure*/
    }
	
	_queuePtr->m_list = ListCreate();
	if(_queuePtr->m_list == NULL)
	{
		free(_queuePtr);
	}
	
	if ((QueueInit(_queuePtr)) != SUCCESS)
	{
		
		free(_queuePtr);
		return NULL;
	}
	
    return _queuePtr;
}

void   QueueDestroy(Queue**_queue, void (*_elementDestroy)(void* _item))
/******************************************************************************/
{
	if(NULL == _queue || *_queue==NULL)
	{
		return;
	}
	ListDestroy(&(*_queue)->m_list, _elementDestroy);
	CvAndMutexDestroy(*_queue);
	free(*_queue);
	*_queue=NULL;
}
/******************************************************************************/

/******************************************************************************/

QueueResult QueueInsert(Queue *_queue, void *_item)
{
	ListResult status;

	if (NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}

	if (NULL == _item)
	{
		return QUEUE_INVALID_ITEM;
	}

	if (_queue->m_items == QUEUE_SIZE)
	{
		return QUEUE_OVERFLOW;
	}

	pthread_mutex_lock(&(_queue->m_mutex));

	while (_queue->m_items == QUEUE_SIZE)
	{
		pthread_cond_wait(&_queue->m_readersCv, &_queue->m_mutex);
	}

	if ((status = ListPushTail(_queue->m_list, _item)) != LIST_SUCCESS)
	{
		if (status == LIST_UNINITIALIZED_ERROR)
		{
			return QUEUE_UNINITIALIZED_ERROR;
		}

		return QUEUE_ALLOCATION_ERROR;
	}
	++_queue->m_items;

	#ifdef _DUAL_CV_
	pthread_cond_signal(&_queue->m_aggregatorsCv);
	#else
	pthread_cond_broadcast(&_queue->m_readersCv);
	#endif
	
	pthread_mutex_unlock(&(_queue->m_mutex));

	return QUEUE_SUCCESS;
}



/******************************************************************************/

QueueResult	QueueRemove(Queue *_queue, void** _pItem)
{
	ListResult status;
	
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _pItem)
	{
		return QUEUE_INVALID_ITEM;
	}
	
	if(_queue->m_items == QUEUE_IS_EMPTY)
	{
		return QUEUE_UNDERFLOW;
	}
	
	if(_queue->m_items == 0)
	{
		return QUEUE_UNDERFLOW;
	}
	
	pthread_mutex_lock(&(_queue->m_mutex));
	
	while(_queue->m_items == 0)
	{
		#ifdef _DUAL_CV_
		pthread_cond_wait(&_queue->m_aggregatorsCv, &_queue->m_mutex);
		#else
		pthread_cond_wait(&_queue->m_readersCv, &_queue->m_mutex);
		#endif
	}
	
	
	if( (status = ListPopHead(_queue->m_list, _pItem)) != LIST_SUCCESS)
	{
		return QUEUE_UNDERFLOW;
	}
	--_queue->m_items;
	
	#ifdef _DUAL_CV_
	pthread_cond_signal(&_queue->m_readersCv);
	#else
	pthread_cond_broadcast(&_queue->m_readersCv);
	#endif

	pthread_mutex_unlock(&(_queue->m_mutex));
	
	return QUEUE_SUCCESS;
	
}

/******************************************************************************/

int	IsEmptyQueue(Queue *_queue)
{
	return IsListEmpty(_queue->m_list);
}

/******************************************************************************/
size_t QueueItemsNum(Queue *_queue)
{
	return ListSize(_queue->m_list);
}

/******************************************************************************/
void QueueItemsPrint(const Queue *_queue, ItemPrint _fp, void* _context)
{
	ListItr _end = ListItrEnd(_queue->m_list);
	ListItr _begin = ListItrBegin(_queue->m_list);
	 
	if(_queue == NULL || _fp == NULL)
	{
		return;
	}
	ListItrForEach(_begin, _end, _fp, _context);
	return;
}
/******************************************************************************/
