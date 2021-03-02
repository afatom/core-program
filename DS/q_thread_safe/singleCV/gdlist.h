#ifndef __GDLIST_H__
#define __GDLIST_H__


/** 
 *  @file gdlist.h
 *  @brief Create a Generic Double Linked List data type
 * 
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap an store pointer to user proveded element.
 * 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 

#include <stddef.h>  /* size_t */


typedef struct List List;

typedef enum List_Result {
	LIST_SUCCESS = 0,
	LIST_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	LIST_NULL_ELEMENT_ERROR,			/**< Null element input */
	LIST_UNDERFLOW						/**< No Nodes to remove */
	
	
} ListResult;

/** 
 * @brief Create a list
 * 
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* ListCreate(void);

/** 
 * @brief Destroy list
 * @details Destroys the list completely 
 *          optionally destroys elements using user provided function
 *
 * @params[in] _pList : A pointer to previously created List returned via ListCreate
 *					   on completion *_pList will be null
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the list
 *             or a null if no such destroy is required
 * 
 * @return void
 */
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));

/** 
 * @brief Add element to head of list
 * @details time complexity: O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item (void* pointer) An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if arrived _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
ListResult ListPushHead(List* _list, void* _item);

/** 
 * @brief Add element to the list's tail
 * @details time complexity O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate 
 * @params _item (void* pointer) An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if arrived _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
ListResult ListPushTail(List* _list, void* _item);

/** @brief Remove element from list's head
 *  @details if successfull, stores a pointer to the removed item in _pItem
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if arrived _item is NULL
 * @retval LIST_UNDERFLOW on memory empty list
 */
ListResult ListPopHead(List* _list, void** _pItem);

/** @brief Remove element from list's tail
 *  @details if successfull, stores a pointer to the removed item in _pItem
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if arrived _item is NULL
 * @retval LIST_UNDERFLOW on memory empty list
 */
ListResult ListPopTail(List* _list, void** _pItem);

/** @brief Get number of elements in the list
 * Average time complexity O(n).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @returns size_t
 * @retval Num of nodes
 */
size_t ListSize(const List* _list);

/** @brief check if list is empty
 * Average time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @returns int
 * @retval 1 if list is empty, 0 if not
 */
int IsListEmpty(const List* _list);

#endif /* __GDLIST_H__ */
