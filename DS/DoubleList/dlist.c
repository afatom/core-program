#include "dlist.h"
#include <stdlib.h>     /*Malloc*/
#include <stdio.h>             /*Printf*/
#include "ADTDefs.h"

#define MAGIC 53177339
/******************************************************************************/
typedef struct Node{
    int             m_data;
    struct Node*    m_next;
    struct Node*    m_prev;
}Node;

/******************************************************************************/
struct List {
    Node   m_head;
    Node   m_tail;
};
/******************************************************************************/
List*     ListCreate(void)
{
    List* ptr = NULL;
    ptr = (List*)malloc(sizeof(List));
    /*malloc failure*/
    if(NULL == ptr)
    {
        return NULL;
    }
    /*Linking head with tail*/
    ptr->m_head.m_next = &(ptr->m_tail);
    ptr->m_head.m_prev = NULL;
    ptr->m_tail.m_next = NULL;
    ptr->m_tail.m_prev = &(ptr->m_head);
    /*initialize magics*/
    ptr->m_head.m_data = MAGIC;
    return ptr;
}
/******************************************************************************/
static ADTErr PopNode(Node *_ptr)
{
    (_ptr)->m_next->m_prev = (_ptr)->m_prev;
    (_ptr)->m_prev->m_next = (_ptr)->m_next;
    (_ptr)->m_next = NULL;
    (_ptr)->m_prev = NULL;
    free(_ptr);
    return ERR_OK;
}
/******************************************************************************/
void      ListDestroy(List* _list)
{
    Node *runPointer = NULL;
    runPointer = _list->m_head.m_next->m_next;
    if (_list == NULL || _list->m_head.m_data == 0)
    {
        return;
    }
    /*Avoid Double free*/
    _list->m_head.m_data = 0;
    for( ;runPointer != NULL; runPointer = runPointer->m_next)
    {
      free(runPointer->m_prev);
    }
    free(_list);
}
/******************************************************************************/
static ADTErr PushNode(Node *newNode, int _data)
{
    /*repetable lines no matter wich side (Tail or head)*/
    newNode->m_data = _data;
    newNode->m_next = newNode->m_prev->m_next;
    newNode->m_next->m_prev->m_next = newNode;
    newNode->m_next->m_prev = newNode;
    return ERR_OK;
}
/******************************************************************************/
static ADTErr CreateNode(Node **newNode)
{
  *newNode = (Node *)malloc(sizeof(Node));
  if (NULL == *newNode)
  {
      return ERR_ALLOCATION_FAILED;
  }
  return ERR_OK;
}
/******************************************************************************/
ADTErr    ListPushHead(List* _list, int _data)
{
    Node *newNode = NULL;
    ADTErr pushResult, createRes;
    if (NULL == _list)
    {
        return ERR_NOT_INITIALIZED;
    }
    /*Create New NODE*/
    if ((createRes = CreateNode(&newNode)) != ERR_OK)
    {
      return createRes;
    }
    newNode->m_prev = &(_list->m_head);
    /*Node** ptr = &newNode;*/
    if ((pushResult = PushNode(newNode, _data)) != ERR_OK)
    {
        return pushResult;
    }
    return ERR_OK;
}
/******************************************************************************/
ADTErr    ListPushTail(List* _list, int _data)
{
    Node *newNode = NULL;
    ADTErr pushResult, createRes;
    if (NULL == _list)
    {
        return ERR_NOT_INITIALIZED;
    }
    /*Create New NODE*/
    if ((createRes = CreateNode(&newNode)) != ERR_OK)
    {
      return createRes;
    }
    newNode->m_prev = (_list->m_tail.m_prev);
    if ((pushResult = PushNode(newNode, _data)) != ERR_OK)
    {
        return pushResult;
    }
    return ERR_OK;
}
/******************************************************************************/
ADTErr    ListPopHead(List* _list, int* _data)
{
    ADTErr popResult;
    Node *ptr = NULL;
    if(_list == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    /*Main send me invalid pointer. i cant dereference NULL Adress*/
    if(_data == NULL)
    {
        return ERR_GENERAL;
    }
    /*Check if list is empty*/
    if (ListIsEmpty(_list))
    {
      return ERR_UNDERFLOW;
    }
    ptr = _list->m_head.m_next;
    *_data = _list->m_head.m_next->m_data;
    if ((popResult = PopNode(ptr)) != ERR_OK)
    {
        return popResult;
    }
    /*first derefernce main pointer*/
    return ERR_OK;
}
/******************************************************************************/
ADTErr    ListPopTail(List* _list, int* _data)
{
    ADTErr popResult;
    Node* ptr = NULL;
    if(_list == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    /*Main send me invalid pointer. i cant dereference NULL Adress*/
    if(_data == NULL)
    {
        return ERR_GENERAL;
    }
    /*Check if list is empty*/
    if (ListIsEmpty(_list))
    {
      return ERR_UNDERFLOW;
    }
    ptr = _list->m_tail.m_prev;
    *_data = _list->m_tail.m_prev->m_data;
    if ((popResult = PopNode(ptr)) != ERR_OK)
    {
        return popResult;
    }
    return ERR_OK;
}
/******************************************************************************/
int       ListIsEmpty(const List* _list)
{
    if (NULL == _list || _list->m_head.m_next == &(_list->m_tail))
    {
        return 1;
    }
    return 0;
}
/******************************************************************************/
void      ListPrint(const List* _list)
{
    Node *ptr = _list->m_head.m_next;
    int i = 0;
    if (NULL == _list)
    {
        puts("{____Empty List____}");
    }
     if (ListIsEmpty(_list))
     {
        puts("{____Empty List____}");
     }
    /*for loop on NOdes*/
     for (; ptr != &(_list->m_tail); ptr = ptr->m_next, ++i)
     {
         printf(" ___________\n");
         printf("|NODE: %2d  |\n", i + 1);
         printf("|data: %2d  |\n", ptr->m_data);
         printf("|___________|\n");
         printf("      |\n");

        /* _list->m_head.m_next->m_next;*/
    }
}
/******************************************************************************/
size_t ListCountItems(const List *_list)
{
    size_t counter = 0;
    Node *Nptr = NULL;
    if (_list == NULL)
    {
        return 0;
    }
    /*for loop on NOdes*/
    Nptr = _list->m_head.m_next;
    for (; Nptr != &(_list->m_tail); Nptr = Nptr->m_next, ++counter)
    {

    }
    return counter;
}
