#include "queue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "ADTDefs.h"

#define MAGIC_NUM 53177365641

struct Queue
{
    int*    m_items;
    size_t  m_size;
    size_t  m_head;    /* Index of head in m_items array. */
    size_t  m_tail;    /* Index of tail in m_items array. */
    size_t  m_nItems;
    size_t  m_magic;
};

/*******************************************************************************
*[Description]:Creating Queue Datat Structure. 
*[Input]:size of the Queue (its also the size of the array in the structure) 
*[output]:Memory allocation to Queue pointer 
*[Errors]:(1) ERR_OK (creation operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED (when Malloc fails)
*******************************************************************************/
Queue* QueueCreate(size_t _size)
{
    Queue *_queuePtr = NULL;
    if (_size == 0)
    {
        return NULL;
    }
    /*malloc for Q struct*/
    _queuePtr = (Queue*)malloc(sizeof(Queue));
    /*check malloc*/
    if (NULL == _queuePtr)
    {
        return NULL; /*malloc failure*/
    }
    /*m_items allocating*/
    _queuePtr->m_items = (int*)malloc(_size * sizeof(int));
    if (NULL == _queuePtr->m_items)
    {
        free(_queuePtr);
        return NULL;
    }
    _queuePtr->m_size = _size;
    _queuePtr->m_head = 0;    /* Index of head in m_items array. */
    _queuePtr->m_tail = 0;    /* Index of tail in m_items array. */
    _queuePtr->m_nItems = 0;
    _queuePtr->m_magic = MAGIC_NUM;
    return _queuePtr;
}

/*******************************************************************************
*[Description]:Deleting Queue Datat Structure. 
*[Input]:pointer to Queue. 
*[output]:No output (Memory freeing) 
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
void   QueueDestroy(Queue *_queue)
{
                        /*free was done before*/
    if (NULL == _queue || _queue->m_magic == 0)
    {
        return;
    }
    _queue->m_magic = 0;
    free(_queue->m_items);
    _queue->m_items = NULL;
    free(_queue);
    return;
}
/*******************************************************************************
*[Description]:Inserting elements to Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and item to insert. 
*[output]:Err status of insertion
*[Errors]:(1) ERR_OK (insertion operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_OVERFLOW (4) ERR_UNDERFLOW 
*******************************************************************************/
ADTErr QueueInsert(Queue *_queue, int  _item)
{
    if (NULL == _queue)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (_queue->m_nItems == _queue->m_size)
    {
        return ERR_OVERFLOW;
    }
    /*first insert then ++tail*/
    _queue->m_items[_queue->m_tail] = _item;
    _queue->m_tail = ((_queue->m_tail+1) % _queue->m_size);
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
    *_item =_queue->m_items[_queue->m_head];
    _queue->m_head = ((_queue->m_head+1) % _queue->m_size);
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
    printf("Queue Size: %lu.\n",_queue->m_size);
    printf("Queue NOI: %lu.\n",_queue->m_nItems);
    printf("Queue Head Index: %lu.\n",_queue->m_head);
    printf("Queue tail Index: %lu.\n",_queue->m_tail);
    printf("***********************************\n");
    for(index = 0; index < _queue->m_nItems; ++index)
    {
        printf("%d",_queue->m_items[_queue->m_head + index]);
    }
    printf("\n");
    return;
}