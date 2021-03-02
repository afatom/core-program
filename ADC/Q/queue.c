#include "queue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "gdlist.h"
#include "list_itr.h"
#include "list_functions.h"
#include <assert.h>

struct Queue
{
    List*    m_list;
};


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
    return _queuePtr;
}
/******************************************************************************/
void   QueueDestroy(Queue**_queue, void (*_elementDestroy)(void* _item))
{
	if(NULL == _queue)
	{
		return;
	}
	ListDestroy(&(*_queue)->m_list, _elementDestroy);
	free(*_queue);
	*_queue=NULL;
}
/******************************************************************************/

/******************************************************************************/
QueueResult QueueInsert(Queue *_queue, void* _item)
{
	ListResult status;
	
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _item)
	{
		return QUEUE_INVALID_ITEM;
	}
	
	if( (status = ListPushTail(_queue->m_list, _item)) != LIST_SUCCESS)
	{
		if(status == LIST_UNINITIALIZED_ERROR)
		{
			return QUEUE_UNINITIALIZED_ERROR;
		}
		
		return QUEUE_ALLOCATION_ERROR;
	}
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
	
	if( (status = ListPopHead(_queue->m_list, _pItem)) != LIST_SUCCESS)
	{
		return QUEUE_UNDERFLOW;
	}
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