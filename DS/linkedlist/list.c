#include "list.h"
#include <stdio.h>      /*printf*/
#include <stdlib.h>     /*malloc*/

/*In Contrast with past DS 
*we Hold The struct in Hfile (API) thats for accessing members*/
/*******************************************************************/
Person* ListInsertHead(Person* _head, Person* _p)
{
    /*Invalid Inputs*/
    if (NULL == _p)
    {
        return NULL;
    }
    _p->m_next = _head;
    _head = _p;
    
    return _head;
}
/*******************************************************************/
void    PrintList(Person* _head)
{
    Person* ptr = _head;
    int i =0;
    if (_head == NULL)
    {
        printf("Empty List!\n");
        return;
    }
    puts("     head  ");
    puts("       |  ");
    for(i=0; ptr != NULL; ptr = ptr->m_next, ++i)
    {
        printf(" ___________\n");
        printf("|Person %2d  |\n", i+1);
        printf("|Id: %5d  |\n", ptr->m_id);
        printf("|___________|\n"); 
        printf("       |\n");  
    }
    puts("       |  ");
    puts("       *  ");
    puts("    NULL ");
}
/*******************************************************************/
Person* ListRemoveHead(Person* _head, Person** _item)
{
    if (NULL == _head)
    {
    	*_item = NULL;
        return _head;
    }
    if (_item == NULL)
    {
    	return _head;
    }
    /*before disconnecting head*/
    (*_item) = _head;
    _head = _head->m_next; /*link head to next Node*/
    /*disconnecting this person permanantly*/
    (*_item)->m_next = NULL;
    return _head;
}
/*******************************************************************/
Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
    Person* _ptr = _head;
    if (_p == NULL)
    {
        return _head;
    }
    /*case: first insertion to the list Or first ID node is biiger then _p.ID*/
    if (_head == NULL || (_head->m_id > _key))
    {
    	return ListInsertHead(_head, _p);
    }
    while(_ptr->m_next != NULL && _ptr->m_next->m_id <= _key)
    {
    	/*keep runinig*/
   		_ptr=_ptr->m_next;
    }
	
	(_p)->m_next = _ptr->m_next;
	_ptr->m_next = _p;
	return _head; 
}
/*******************************************************************/
Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
    Person* _ptr = _head;
    /*we cant link NULL pointer if we keep ON*/
    if (_p == NULL)
    {
    	return _head;
    }
    if (NULL == _head)
    {
    	*_p = NULL;
        return _head;
    }
    /*assumption in this function that we are working with asorted list*/
	/*keep runinig*/ /*tell list end or ID found*/
    while(_ptr->m_next != NULL && _ptr->m_next->m_id < _key)
    {
    	_ptr=_ptr->m_next;
    }
    if(_ptr->m_id == _key)
    {
    	/*found the one*/
    	(*_p) = _ptr->m_next;
    	_ptr->m_next = _ptr->m_next->m_next;
    	(*_p)->m_next = NULL;
    	return _head; 
    }
    /*Not found. return*/
    (*_p)= NULL;
    return _head;
}
/*******************************************************************/
Person *ListRemoveByKeyRec(Person *_head, int _key, Person **_p)
{
    /*we cant link NULL pointer if we keep ON*/
    if (_p == NULL)
    {
    	return _head;
    }
    if (NULL == _head || _head->m_id > _key)
    {
    	*_p = NULL;
        return _head;
    }
    /*assumption in this function that we are working with asorted list*/
	/*keep runinig*/ /*tell list end or ID found*/
    if(_head->m_id == _key)
    {
    	/*found the one*/
		return ListRemoveHead(_head,_p); 
    }
    /*Not found. return*/
    (*_p)= NULL;
    _head->m_next = ListRemoveByKeyRec(_head->m_next, _key, _p);
    return _head;

}
/*******************************************************************/
Person *ListInsertByKeyRec(Person *_head, int _key, Person *_p)
{
	if (_p == NULL)
	{
		return _head;
	}
    /*case: first insertion to the list Or first ID node is biiger then _p.ID*/
    if (_head == NULL || (_head->m_id > _key))
    {
    	return ListInsertHead(_head, _p);
    }
	_head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
	return _head;
}
/*******************************************************************/

























