#include "gdlist.h"
#include <stdlib.h>     /*Malloc*/
#include <stdio.h>
#include <assert.h>
#include "list_itr.h"
#include "list_functions.h"

#define NDEBUG

#define LIST_VALID 		0xBEEFBEEF
#define LIST_DESTROYED 	0xDEADBEEF
#define TRUE 			1
#define FALSE 			0
#define EMPTY 			1
#define NOT_EMPTY 		0

/*#define IS_LIST_ITRS_EQUAL(itr1, itr2)   ((itr1) == (itr2) ? (TRUE) : (FALSE))   
     */                                   
/*#define IS_PARAMS_NULL(itr1,itr2,itr3)  ((((itr1)==(NULL))||((itr2)==(NULL)||((itr3)==(NULL))))?(NULL):(FALSE))
*/



/******************************************************************************/
typedef struct Node{
    void*           m_element;
    struct Node*    m_next;
    struct Node*    m_prev;
}Node;

/******************************************************************************/
struct List {
    size_t 	m_magicNumber;
    Node   	m_head;
    Node   	m_tail;
};
/*
struct ListItr {
	Node* m_current;
};*/

/*const ListItr ELItr = {NULL};*/    /*<< Emply list iterator*/

/**************************/
/*   Static Funcs List    */
/**************************/
/******************************************************************************/

static ListResult CreateNode(Node **newNode);
static void PushNode(Node *newNode, void** _element);
static void PopNode(Node **_nodePointer);

/******************************************************************************/

List*     ListCreate(void)
{
    List* list = NULL;
    list = (List*)malloc(sizeof(List));
    /*malloc failure*/
    if(NULL == list)
    {
        return NULL;
    }
    /*Linking head with tail*/
    list->m_head.m_next = &(list->m_tail);
    
    list->m_head.m_prev = &list->m_head;
    list->m_tail.m_next = &list->m_tail;
    /*
    list->m_head.m_prev = NULL;
    list->m_tail.m_next = NULL;
	*/
    list->m_tail.m_prev = &(list->m_head);
    /*initialize magics*/
    list->m_magicNumber = LIST_VALID;
    return list;
}

/******************************************************************************/
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
    Node *runPointer = NULL;
    Node *temp = NULL;

    if (NULL == _pList || NULL == *_pList || (*_pList)->m_magicNumber != LIST_VALID)
    {
        return;
    }
    
    (*_pList)->m_magicNumber = LIST_DESTROYED;
    
    temp = (*_pList)->m_head.m_next;
    runPointer = temp->m_next;
    
    if(NULL != _elementDestroy)
    {
    	while(temp != &(*_pList)->m_tail)
    	{
            /*freeing elements/data*/
    		_elementDestroy(temp);
    		temp = runPointer;
    		runPointer = runPointer->m_next;
    	}
    }
    /*while loop for freeing alocated nodes*/
    while(temp != &(*_pList)->m_tail)
	{
    		free(temp);
    		temp = runPointer;
    		runPointer = runPointer->m_next;
	}    
    /*freeing list*/
    free(*_pList);
    *_pList=NULL;
    return;
}
/******************************************************************************/
ListResult ListPushHead(List* _list, void* _item)
{

    Node *newNode = NULL;
    ListResult createResult;
    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    if(NULL == _item)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    /*Create New NODE*/
    if ((createResult = CreateNode(&newNode)) != LIST_SUCCESS)
    {
      return createResult;
    }

    newNode->m_prev = &(_list->m_head);
    /*Node** ptr = &newNode;*/
    PushNode(newNode, &_item);
    return LIST_SUCCESS;
}
/*****************************************************************************/
ListResult ListPushTail(List* _list, void* _item)
{
    Node *newNode = NULL;
    ListResult createResult;
    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    if(NULL == _item)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    /*Create New NODE*/
    if ((createResult = CreateNode(&newNode)) != LIST_SUCCESS)
    {
      return createResult;
    }



    newNode->m_prev = (_list->m_tail.m_prev);

    PushNode(newNode, &_item);
    return LIST_SUCCESS;
}
/*****************************************************************************/
ListResult ListPopHead(List* _list, void** _pItem)
{
    Node *ptr = NULL;

    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    /*Main send me invalid pointer. i cant dereference NULL Adress*/
    if(NULL == _pItem)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    /*Check if list is empty*/
    if (IsListEmpty(_list))
    {
      return LIST_UNDERFLOW;
    }


    ptr = _list->m_head.m_next;
    *_pItem = _list->m_head.m_next->m_element;
    PopNode(&ptr);   
    /*first derefernce main pointer*/
    return LIST_SUCCESS;
}
/*****************************************************************************/

ListResult ListPopTail(List* _list, void** _pItem)
{
    Node *ptr = NULL;

    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return LIST_UNINITIALIZED_ERROR;
    }

    /*Main send me invalid pointer. i cant dereference NULL Adress*/
    if(NULL == _pItem)
    {
        return LIST_NULL_ELEMENT_ERROR;
    }

    /*Check if list is empty*/
    if (IsListEmpty(_list))
    {
      return LIST_UNDERFLOW;
    }

    ptr = _list->m_tail.m_prev;
    *_pItem = _list->m_head.m_next->m_element;
    PopNode(&ptr);   
    /*first derefernce main pointer*/
    return LIST_SUCCESS;
}
/*****************************************************************************/

int IsListEmpty(const List* _list)
{
    if (NULL == _list || _list->m_magicNumber != LIST_VALID || _list->m_head.m_next == &(_list->m_tail))
    {
        return EMPTY;
    }
    
    return NOT_EMPTY;
}
/*****************************************************************************/

size_t ListSize(const List* _list)
{
    size_t counter = 0;
    Node *Nptr = NULL;
    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return 0;
    }
    /*for loop on NOdes*/
    Nptr = _list->m_head.m_next;
    for (; Nptr != &(_list->m_tail); Nptr = Nptr->m_next, ++counter);
    return counter;
}
/*****************************************************************************/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*****************/
/* Itrs Code     */
/*****************/
/******************************************************************************/

/** 
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItrBegin(const List* _list)
{
    if (NULL == _list || _list->m_magicNumber != LIST_VALID)
    {
        return NULL; 
    }

    return (ListItr)(_list->m_head.m_next);
}

int IsListItrPointsToNull(ListItr _itr)
{
	if(_itr == NULL)
	{
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************/

/** 
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItrEnd(const List* _list) /*points to tail struct always*/
{
    if (NULL == _list || _list->m_magicNumber != LIST_VALID )
    {
        return NULL;
    }
    return (ListItr)(_list->m_tail.m_next);
}
/******************************************************************************/

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return ((_a == _b) ? (TRUE) : (FALSE));
}
/******************************************************************************/

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItrNext(ListItr _itr)
{
    if (NULL == _itr )
    {
        return NULL;
    }
    return (ListItr)(((Node *)_itr)->m_next);
}
/******************************************************************************/

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItrPrev(ListItr _itr)
{
    if (NULL == _itr)
    {
        return NULL;
    }
    return (ListItr)(((Node *)_itr)->m_prev);
}
/******************************************************************************/

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
void* ListItrGet(ListItr _itr)
{
    if (NULL == _itr || _itr == (ListItr)(((Node *)_itr)->m_next))
    {
        return NULL;
    }

    return (void*)(((Node *)_itr)->m_element);
}
/******************************************************************************/

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
void* ListItrSet(ListItr _itr, void* _element)
{
    void* temp = NULL;
    if (NULL == _itr || _itr == (ListItr)(((Node *)_itr)->m_next) || NULL == _element)
    {
        return NULL;
    }
    temp = ListItrGet(_itr);
    ((Node *)(_itr))->m_element = _element;

    return temp;
}
/******************************************************************************/

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItrInsertBefore(ListItr _itr, void *_element)
{
    ListResult createResult;
    Node *newNode = NULL;
    if (NULL == _itr || _itr == (ListItr)(((Node *)_itr)->m_prev) || NULL == _element)
    {
        return NULL;
    }

    /*Create New NODE*/
    if((createResult = CreateNode(&newNode)) != LIST_SUCCESS)
    {
        return NULL;
    }
    newNode->m_prev = (((Node *)_itr)->m_prev);
    PushNode(newNode, &_element);

    return (ListItr)(((Node *)_itr)->m_prev);
}
/******************************************************************************/

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */

void *ListItrRemove(ListItr _itr)
{
    void* data = NULL;
    Node* x = NULL;
    /*if itr points to head or to tail, return null*/ 
    if (NULL == _itr || _itr == (ListItr)(((Node *)_itr)->m_next) || _itr == (ListItr)(((Node *)_itr)->m_prev))
    {
        return NULL;
    }
    data = ListItrGet(_itr);
    x = (Node *)_itr;
    PopNode (&x);
    return data;
}

/******************************************************************************/

/********************/
/* STATIC FUNCTIONS */
/********************/

/*****************************************************************************/
static void PushNode(Node *newNode, void** _element)
{
    /*repetable lines no matter wich side (Tail or head)*/
    newNode->m_element = *_element;
    newNode->m_next = newNode->m_prev->m_next;
    newNode->m_next->m_prev->m_next = newNode;
    newNode->m_next->m_prev = newNode;
}
/******************************************************************************/
static ListResult CreateNode(Node **newNode)
{
  *newNode = (Node*)malloc(sizeof(Node));
  if (NULL == *newNode)
  {
      return LIST_ALLOCATION_ERROR;
  }
  return LIST_SUCCESS;
}
/******************************************************************************/
static void PopNode(Node **_nodePointer)
{
    (*_nodePointer)->m_next->m_prev = (*_nodePointer)->m_prev;
    (*_nodePointer)->m_prev->m_next = (*_nodePointer)->m_next;
    (*_nodePointer)->m_next = NULL;
    (*_nodePointer)->m_prev = NULL;
    free(*_nodePointer);
    *_nodePointer = NULL;
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*****************                Iterators Functions                                                                   */

/*************************************************************************************************************************/
/*************************************************************************************************************************/

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void *_context)
{
    if (NULL == _predicate || NULL == _begin || NULL == _end)
    {
        return NULL;
    }
    while (ListItrEquals(_begin, _end) == FALSE)
    {
        if (_predicate(ListItrGet(_begin), _context) == TRUE)
        {
            return _begin;
        }
        _begin = ListItrNext(_begin);
    }
    return _begin;
}
/*************************************************************************************************************************/
size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void *_context)
{
    size_t counter = 0;
    if (NULL == _predicate || NULL == _begin || NULL == _end)
    {
        return 0;
    }
    while (ListItrEquals(_begin, _end) == FALSE)
    {
        if (_predicate(ListItrGet(_begin), _context) == TRUE)
        {
            ++counter;
        }
        _begin = ListItrNext(_begin);
    }
    return counter;
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void *_context)
{
    if (NULL == _action || NULL == _begin || NULL == _end)
    {
        return NULL;
    }
    while (ListItrEquals(_begin, _end) == FALSE)
    {
        if (_action(ListItrGet(_begin), _context) == FALSE)
        {
            return _begin;
        }
        _begin = ListItrNext(_begin);
    }
    return _begin;
}
/*************************************************************************************************************************/
/*
ListItr ModListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action1, ListActionFunction _action2, void* _context)
{
	ListItr begin = _begin;
    if (NULL == _action || NULL == _begin || NULL == _end)
    {
        return NULL;
    }
    while (ListItrEquals(_begin, _end) == FALSE)
    {
        if (_action1(ListItrGet(_begin), _context) == FALSE)
        {
            return _begin;
        }
        _begin = ListItrNext(_begin);
    }
    
    while (ListItrEquals(begin, _end) == FALSE)
    {
        if (_action2(ListItrGet(begin), _context) == FALSE)
        {
            return begin;
        }
        begin = ListItrNext(begin);
    }
    return begin;
}
*/



static void SwapItrs(ListItr _begin, ListItr _end)
{
    /*
    void *_beginElement = NULL;
    void* _endElement = NULL;
    _beginElement = ListItrGet(_begin);
    _endElement = ListItrSet(_end, _beginElement);
    ListItrSet(_begin, _endElement);*/

    void *_beginElement = NULL;
    void *_endElement = NULL;
    _beginElement = ListItrGet(_begin);
    _endElement = ListItrGet(_end);

    ListItrSet(_end, _beginElement);
    ListItrSet(_begin, _endElement);
    
    return;
}

    /** 
 * @brief Sorts a sublist in place using the bubble sort algorithm
 * Complexity O(n*n)
 *
 * @params _begin : Iterator to sublist start
 * @params _end : Iterator to sublist end
 * @params _less : less compare function
 * 
 */
 
static void BubbleItUp(ListItr _begin, ListItr _end, LessFunction _less)
{

    while (ListItrEquals(_begin, _end) != TRUE)
    {

        if (_less(ListItrGet(_begin), ListItrGet(ListItrNext(_begin))) == FALSE)
        {
            SwapItrs(_begin, ListItrNext(_begin));
        }
        _begin = ListItrNext(_begin);
    }
} 
 
 
 
void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    ListItr head = NULL, tail=NULL;
	
    if (NULL == _less || NULL == _begin || NULL == _end)
    {
        return;
    }

    tail = ListItrPrev(_end);
    head = ListItrPrev(_begin);

    while (ListItrEquals(_begin, tail) == FALSE)
    {
 		BubbleItUp(_begin, tail, _less);
     	_begin = ListItrNext(head);
		tail = ListItrPrev(tail); 
        /*_newEnd = ListItrPrev(_newEnd);*/
    }
    return;
}





/** 
 * @brief Splice all element from [_begin.._end) into _dst
 * @details remove all elements from the half open range [_begin.._end)
 * and insert them before _dest
 * O(?)
 *
 * @warning The function assumes that : 
 *  _begin and _end are in the correct order and on the same list
 *  _dest is not between them
 * Otherwise behavior is undefined
 * all three iterators can belong to same list
 */
ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr end = NULL, dest = NULL, endPrev = NULL, destPrev = NULL; 
	if(NULL == _dest || NULL == _begin || NULL == _end)
	{
		return NULL;
	}
	
	end = _end;
	dest = _dest;
	
	endPrev = ListItrPrev(end);
	destPrev = ListItrPrev(dest);
	
	/*link sorce list*/
	((Node*)_end)->m_prev = ((Node*)_begin)->m_prev;
	((Node*)_begin)->m_prev->m_next = (Node*)_end;
	((Node*)_begin)->m_prev=NULL;
	((Node*)endPrev)->m_next = NULL;
	
	/*copy to dest list*/
	((Node*)endPrev)->m_next = ((Node*)_dest);
	((Node*)_dest)->m_prev = ((Node*)endPrev);
	
	((Node*)destPrev)->m_next = (Node*)_begin;
	((Node*)_begin)->m_prev = ((Node*)destPrev); 
	
	
	
	return _begin;
	
}

/** 
 * @brief Removes a sublist [_begin.._end) from a list and creates a new list
 * with all removed items.
 * O(?)
 *
 */
List *ListItrCut(ListItr _begin, ListItr _end)
{
    List* newList = NULL;
    ListItr tailItr = NULL;
    if ( NULL == _begin || NULL == _end)
    {
        return NULL;
    }
    newList = ListCreate( );
    if(NULL == newList)
    {
        return NULL;
    }
    tailItr =  ListItrEnd(newList);
    tailItr = ListItrSplice(tailItr, _begin, _end);
    assert(NULL != tailItr);
    return newList;
}

/** 
 * @brief Removes all duplicate elements from a sorted sublist [_begin.._end) 
 * and rertun a new list with all removed items.
 * O(?)
 * post condition: [_begin.._end) contains only unique elements
 */
List *ListItrUnique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
    List* newList = NULL;
    ListItr prev = NULL;
    ListItr newListEnd = NULL;
    void* element = NULL;

    if (NULL == _equals || NULL == _begin || NULL == _end)
    {
        return NULL;
    }
    newList = ListCreate();
    if(NULL == newList)
    {
        return NULL;
    }

    _begin = ListItrNext(_begin);
    newListEnd = ListItrEnd(newList);
    while (ListItrEquals(_begin, _end) == FALSE)
    {
        /**/
        prev = _begin;     /*<<ListItrPrev will change begin. so we need to preserve it*/
        prev = ListItrPrev(prev);
        if (_equals(ListItrGet(_begin), ListItrGet(prev)) == TRUE)
        {
            /*remove prev node*/
            element = ListItrRemove(prev);
            ListItrInsertBefore(newListEnd, element);
        }
        _begin = ListItrNext(_begin);
    }

    /*check if newList is empty. if yes Destroy it and return NULL*/
    if (IsListEmpty(newList) == EMPTY)
    {
        ListDestroy(&newList,NULL);
        assert(NULL == newList);
        return NULL;
    }
    
    return newList;
}

/** 
 * @brief Merges two given sub lists into destination 
 * @details Merge elements from two sub lists defined by [_firstbegin.._firstEnd)
 * and [_secondBegin.._secondEnd) in optionaly sorted order using _less function.
 * merged elements will be inserted before _destBegin
 * if a _less function is provided then merge will be sorted
 * 
 * @warning this will removes all merged items from source ranges.
 * O(?)
 *  
 */
ListItr ListItrMerge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
                     ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
    if (NULL == _destBegin || NULL == _firstBegin || NULL == _firstEnd || NULL == _secondBegin || NULL == _secondEnd)
    {
        return NULL;
    }
    /*splice first sub list*/
    ListItrSplice(_destBegin, _firstBegin, _firstEnd);

    /*splice sec sub list*/
    ListItrSplice(_destBegin, _secondBegin, _secondEnd);

    if(_less == NULL)
    {
        return _destBegin;
    }
    /*sort by bubble >> sort will established on the whole destination list*/
    while (ListItrEquals(_firstBegin, ListItrPrev(_firstBegin)) != TRUE)
    {
        _firstBegin = ListItrPrev(_firstBegin);
    }

    while (ListItrEquals(_destBegin, ListItrNext(_destBegin)) != TRUE)
    {
        _destBegin = ListItrNext(_destBegin);
    }

    ListItrSort(ListItrNext(_firstBegin), ListItrPrev(_destBegin), _less);
    return _destBegin;
}
