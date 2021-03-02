#ifndef _DLIST_H_
#define _DLIST_H_

#include "ADTDefs.h"
#include <stddef.h>  /*size_t*/

typedef struct List List;

/*******************************************************************************
*[Description]:Creating List and pointer to list with malloc 
*[Input]:VOID
*[output]:Pointer to lisr and memory allocation for instructs
*[Errors]:
*******************************************************************************/
List*     ListCreate(void);

/*******************************************************************************
*[Description]:Deleting whole ADS, first by erasing all nodes and then free for 
*List pointer.
*[Input]:pointer to List for accessing all nodes.
*[output]:Void. erasing data.
*[Errors]:
*******************************************************************************/
void      ListDestroy(List* _list);

/*******************************************************************************
*[Description]:Enserting Nodes from Head Side (Top)
*[Input]:pointer to List and data (Node to insert)
*[output]:ADTErr Code 
*[Errors]:Overflow, NULL
*******************************************************************************/
ADTErr    ListPushHead(List* _list, int _data);

/*******************************************************************************
*[Description]:Enserting Nodes from Tail Side (bottom)
*[Input]:pointer to List and data (Node to insert)
*[output]:ADTErr Code 
*[Errors]:Overflow, NULL
*******************************************************************************/
ADTErr    ListPushTail(List* _list, int _data);

/*******************************************************************************
*[Description]:Removing Nodes from Head Side (bottom)
*[Input]:pointer to List and Adress of data (Node to delete)
*[output]:ADTErr Code 
*[Errors]:Underflow, NULL
*******************************************************************************/
ADTErr    ListPopHead(List* _list, int* _data);

/*******************************************************************************
*[Description]:Removing Nodes from Tail Side (bottom)
*[Input]:pointer to List and Adress of data (Node to delete)
*[output]:ADTErr Code 
*[Errors]:Underflow, NULL
*******************************************************************************/
ADTErr    ListPopTail(List* _list, int* _data);

/*******************************************************************************
*[Description]:Counting Nodes Number or Items 
*[Input]:pointer to List 
*[output]:Num of items/Nodes in the list 
*[Errors]:
*******************************************************************************/
size_t    ListCountItems(const List* _list);

/*******************************************************************************
*[Description]:Check if the list is empty 
*[Input]:pointer to List
*[output]:int (0=empty, 1=Not empty)
*[Errors]:
*******************************************************************************/
int       ListIsEmpty(const List* _list);

/* ListPrint is only for debug */
/*******************************************************************************
*[Description]:List data and elements printing 
*[Input]:pointer to List 
*[output]:VOID - prints to stdout 
*[Errors]:
*******************************************************************************/
void      ListPrint(const List* _list);


#endif /*_DOUBLELL_H_*/
