#include <stdlib.h> /*size_t*/
#include <stdio.h> /*VectorPrint function*/
#include "ADTDefs.h"

#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct Queue Queue;

/*******************************************************************************
*[Description]:Creating Queue Datat Structure. 
*[Input]:size of the Queue (its also the size of the array in the structure) 
*[output]:Memory allocation to Queue pointer 
*[Errors]:(1) ERR_OK (creation operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_ALLOCATION_FAILED (when Malloc fails)
*******************************************************************************/
Queue* QueueCreate(size_t _size);

/*******************************************************************************
*[Description]:Deleting Queue Datat Structure. 
*[Input]:pointer to Queue. 
*[output]:No output (Memory freeing) 
*[Errors]:(1) ERR_OK (deleting operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) 
*******************************************************************************/
void   QueueDestroy(Queue *_queue);

/*******************************************************************************
*[Description]:Inserting elements to Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and item to insert. 
*[output]:Err status of insertion
*[Errors]:(1) ERR_OK (insertion operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_OVERFLOW (4) ERR_UNDERFLOW 
*******************************************************************************/
ADTErr QueueInsert(Queue *_queue, int  _item);

/*******************************************************************************
*[Description]:Deleting elements From Queue Datat Structure (FIFO Logic) 
*[Input]:pointer to Queue and pointer to Removed item. 
*[output]:Err status of Removing
*[Errors]:(1) ERR_OK (Removing operation seccess) (2) ERR_NOT_INITIALIZED 
*(when pointer points to NULL) (3) ERR_UNDERFLOW = removing from empty Queue 
*******************************************************************************/
ADTErr	QueueRemove(Queue *_queue, int *_item);

/*******************************************************************************
*[Description]:Check if Queue Datat Structure is empty 
*[Input]:pointer to Queue 
*[output]:int (1= empty, 0=not empty  -1=Null)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/
int	QueueIsEmpty(Queue *_queue);

/*******************************************************************************
*[Description]:My Own Function Queue items number. this function was written for
*Test uses.
*[Input]:pointer to Queue and pointer to numofitems for return. 
*[Return]:Num of items in Q
*[Errors]: ERR_OK in success case ERR_NOT_INITIALIZED (when pointer points to NULL)
*and ERR_GENERAL When NULL sent to function
*******************************************************************************/
ADTErr QueueItemsNum(Queue *_queue, size_t *_numOfiItems);
/*******************************************************************************
*[Description]:for test use only. prints queue elements
*[Input]:pointer to Queue 
*[output]:void (prints to stdout)
*[Errors]:NULL queue pointer or null int array 
*******************************************************************************/
void   QueuePrint(Queue *_queue);


#endif /* _QUEUE_H_ */




