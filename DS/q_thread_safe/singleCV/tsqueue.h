
#ifndef __TSQUEUE_H_
#define __TSQUEUE_H_

#include <stddef.h> 	/*<< size_t*/

typedef struct Queue Queue;

typedef enum QueueResult{
	QUEUE_SUCCESS = 0,
	QUEUE_UNINITIALIZED_ERROR,
	QUEUE_UNDERFLOW,
	QUEUE_ALLOCATION_ERROR,
	QUEUE_INVALID_ITEM,
	QUEUE_OVERFLOW
}QueueResult;

typedef int (*ItemPrint)(void *item, void *context);

typedef void (*_elementDestroy)(void* _item);

/*******************************************************************************
*[Description]:Creating Queue Datat Structure. 
*[Input]:size of the Queue (its also the size of the array in the structure) 
*[output]:Memory allocation to Queue pointer 
*[Errors]:(1) ERR_OK (creation operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED (when Malloc fails)
*******************************************************************************/
Queue* QueueCreate(void);

/*******************************************************************************
*[Description]:Deleting Queue Datat Structure. 
*[Input]:pointer to Queue. 
*[output]:No output (Memory freeing) 
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
void   QueueDestroy(Queue**_queue, void (*_elementDestroy)(void* _item));

/*******************************************************************************
*[Description]:Inserting elements to Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and item to insert. 
*[output]:Err status of insertion
*[Errors]:(1) ERR_OK (insertion operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_OVERFLOW (4) ERR_UNDERFLOW 
*******************************************************************************/
QueueResult QueueInsert(Queue *_queue, void* _item);

/*******************************************************************************
*[Description]:Deleting elements From Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and pointer to Removed item. 
*[output]:Err status of Removing
*[Errors]:(1) ERR_OK (Removing operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW = removing from empty Queue 
*******************************************************************************/
QueueResult	QueueRemove(Queue *_queue, void** _pItem);

/*******************************************************************************
*[Description]:Check if Queue Datat Structure is empty 
*[Input]:pointer to Queue 
*[output]:int (1= empty, 0=not empty  -1=Null)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/
int	IsEmptyQueue(Queue *_queue);

/*******************************************************************************
*[Description]:My Own Function Queue items number. this function was written for
*Test uses.
*[Input]:pointer to Queue and pointer to numofitems for return. 
*[Return]:Num of items in Q
*[Errors]: ERR_OK in success case ERR_NOT_INITIALIZED (when pointer points to NULL)
*and ERR_GENERAL When NULL sent to function
*******************************************************************************/
 size_t QueueItemsNum(Queue *_queue);
 
/*******************************************************************************
*[Description]:for test use only. prints queue elements
*[Input]:pointer to Queue 
*[output]:void (prints to stdout)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/

/*for each maybe*/
void QueueItemsPrint(const Queue *_queue, ItemPrint _fp, void *_context);
#endif /* __TSQUEUE_H_*/




