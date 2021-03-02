#include "queue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "vector.h"


struct Queue
{
    Vector* m_vec;
    size_t  m_capacity;
    size_t  m_head;    /* Index of head in m_vec . */
    size_t  m_tail;    /* Index of tail in m_vec . */
    size_t  m_nItems;
};

/******************************************************************************/
Queue* QueueCreate(size_t _capacity)
{
    Queue *_queuePtr = NULL;
    if (_capacity == 0)
    {
        return NULL;
    }
    
    _queuePtr = (Queue*)malloc(sizeof(Queue));

    if (NULL == _queuePtr)
    {
        return NULL; 
    }
	
	_queuePtr->m_vec = VectorCreate(_capacity,0);
	if(NULL == _queuePtr->m_vec)
	{
		free(_queuePtr);
		return NULL;
	}
	
    _queuePtr->m_capacity = _capacity;
    _queuePtr->m_head = 0;   
    _queuePtr->m_tail = 0;    
    _queuePtr->m_nItems = 0;
    return _queuePtr;
}

/******************************************************************************/
void   QueueDestroy(Queue **_queue)
{
	Vector* _vector = (*_queue)->m_vec;
                    
    if (NULL == *_queue )
    {
        return;
    }

    VectorDestroy(&_vector, NULL);
  
    free(*_queue);
    *_queue = NULL;
    return;
}
/******************************************************************************/
Queue_Status QueueInsert(Queue *_queue, void* _item)
{
    if (NULL == _queue)
    {
        return QUEUE_UNINTIALIZED_ERROR;
    }
    if (_queue->m_nItems == _queue->m_capacity)
    {
        return QUEUE_OVERFLOW;
    }
    /*first insert then ++tail*/
    if ((VectorAppend( _queue->m_vec, _item))!= VECTOR_SUCCESS)
    {
    	return QUEUE_ALLOCATION_ERROR;
    }
    _queue->m_vec[_queue->m_tail] = _item;
    
    _queue->m_tail = ((_queue->m_tail+1) % _queue->m_capacity);
    ++_queue->m_nItems;
    return ERR_OK;
}
/*******************************************************************************
*[Description]:Deleting elements From Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and pointer to Removed item. 
*[output]:Err status of Removing
*[Errors]:(1) ERR_OK (Removing operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW = removing from empty Queue 
*******************************************************************************/
ADTErr	QueueRemove(Queue *_queue, int *_item)
{
    if (NULL == _queue)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (NULL == _item)
    {
        return ERR_GENERAL;
    }
    if (_queue->m_nItems == 0)
    {
        return ERR_UNDERFLOW;
    }
    /*first remove then ++head*/
    *_item =_queue->m_vec[_queue->m_head];
    _queue->m_head = ((_queue->m_head+1) % _queue->m_capacity);
    --_queue->m_nItems;
    return ERR_OK;
}
/*******************************************************************************
*[Description]:My Own Function Queue items number. this function was written for
*Test uses.
*[Input]:pointer to Queue and pointer to numofitems for return. 
*[Return]:Num of items in Q
*[Errors]: ERR_OK in success case ERR_NOT_INITIALIZED (when pointer points to NULL)
*and ERR_GENERAL When NULL sent to function
*******************************************************************************/
ADTErr QueueItemsNum(Queue *_queue, size_t *_numOfiItems)
{
    if (NULL == _queue)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (NULL == _numOfiItems)
    {
        return ERR_GENERAL;
    }
    *_numOfiItems = _queue->m_nItems;
    return ERR_OK;
}
/*******************************************************************************
*[Description]:Check if Queue Datat Structure is empty 
*[Input]:pointer to Queue 
*[output]:int (1= empty, 0=not empty  -1=Null)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/
int	QueueIsEmpty(Queue *_queue)
{
    if (NULL == _queue || _queue->m_nItems == 0)
    {
        return 1;
    }
    return 0; /*Not Empty*/
}

/*******************************************************************************
*[Description]:for test use only. prints queue elements
*[Input]:pointer to Queue 
*[output]:void (prints to stdout)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/
void   QueuePrint(Queue *_queue)
{
    size_t index;
    /*printing from head to tail*/
    if (NULL == _queue)
    {
        printf("Empty Queue.\n");
        return;
    }
    printf("***********************************\n");
    printf("Queue Size: %lu.\n",_queue->m_capacity);
    printf("Queue NOI: %lu.\n",_queue->m_nItems);
    printf("Queue Head Index: %lu.\n",_queue->m_head);
    printf("Queue tail Index: %lu.\n",_queue->m_tail);
    printf("***********************************\n");
    for(index = 0; index < _queue->m_nItems; ++index)
    {
        printf("%d",_queue->m_vec[_queue->m_head + index]);
    }
    printf("\n");
    return;
}
