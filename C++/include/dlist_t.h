#ifndef __LIST_T_H__
#define __LIST_T_H_

#include <iostream>
#include <container_t.h>


using namespace std;


template<class T>
class List_t : public Container_t<T>
{
public:
	List_t();
	virtual ~List_t();
	List_t(const List_t<T>& _list);
	virtual int PushBack(T* _object);//push head
	virtual int Append(const T* _object, int _index);
	virtual int Prepend(const T* _object, int _index);
	virtual T* Remove(const T& _object);
	virtual T* Find(const T& _object)const;
	virtual void RemoveAndDelete(const T& _object);
	virtual void RemoveAll();
	virtual void RemoveAndDeleteAll();
	//virtual const T& GetItem(int _index)const;
	virtual bool IsContains(const T& _object)const;
	virtual int ElementIndex(const T& _value)const;
	
	virtual List_t<T>& operator = (const List_t<T>& _list);
	//virtual bool operator == (T& _object)const;


private:
class Node_t{ //nested class
	public:
	T* m_item;
	Node_t* m_next;
	Node_t* m_prev;
	};
	
	Node_t m_head;
	Node_t m_tail;
	
	Node_t* AllocateNode(void)
	{
		Node_t* pNode = new Node_t;
		return pNode;
	}
	
	void PushNode(Node_t* _nodeToPush, T* _item)
	{
		 /*repetable lines no matter wich side (Tail or head)*/
		_nodeToPush->m_item = _item;
		_nodeToPush->m_next = _nodeToPush->m_prev->m_next;
		_nodeToPush->m_next->m_prev->m_next = _nodeToPush;
		_nodeToPush->m_next->m_prev = _nodeToPush;
	}
	
	T* PopNode(Node_t* _nodeToPopFrom)
	{
		T* temp = _nodeToPopFrom->m_item; 
		_nodeToPopFrom->m_next->m_prev = _nodeToPopFrom->m_prev;
		_nodeToPopFrom->m_prev->m_next = _nodeToPopFrom->m_next;
		_nodeToPopFrom->m_next = NULL;
		_nodeToPopFrom->m_prev = NULL;
		delete(_nodeToPopFrom);
		return temp;
	}
	
};

#endif


template<class T>//DFLT CTOR
List_t<T>::List_t() 
{	
	//init sentenails of dlist 
	m_head.m_prev= NULL; 
	m_head.m_next= &m_tail;
	m_head.m_item = NULL; 
	
	m_tail.m_prev= &m_head; 
	m_tail.m_next= NULL;
	m_tail.m_item = NULL; 
	
}

template<class T> //DTOR
List_t<T>::~List_t()
{
	RemoveAndDeleteAll();
}

template<class T> //copy CTOR
List_t<T>::List_t(const List_t<T>& _list) : Container_t<T>(_list)
{
	*this = _list;
}



template<class T>
int List_t<T>::PushBack(T* _object)
{
	Node_t* _pNode = NULL;
	if(!_object)
	{
		return -1;
	}
	
	//create node
	_pNode = this->AllocateNode();
	
	 _pNode->m_prev = &(this->m_head);
    
    this->PushNode(_pNode, _object);
    this->IncrNumOfOfElements();
	return 0;//success
}

template<class T>
int List_t<T>::Append(const T* _object, int _index)
{
	Node_t* _pNode = NULL;
	Node_t* itr = &(this->m_head);
	if(_index < 0 || _index >= this->GetNumOfElements() || !_object)
	{
		return -1;
	}
	
	//create node
	_pNode = this->AllocateNode();
	for(int j = 0; j < _index; ++j)
	{
		itr = itr->m_next;
	}
	
	 _pNode->m_prev = itr;
    
    this->PushNode(_pNode, (T*)_object);
    this->IncrNumOfOfElements();
	return 0;//success
}

template<class T>
int List_t<T>::Prepend(const T* _object, int _index)
{
	Node_t* _pNode = NULL;
	Node_t* itr = &(this->m_head);
	if(_index < 0 || _index >= this->GetNumOfElements() || !_object)
	{
		return -1;
	}
	
	//create node
	_pNode = this->AllocateNode();
	for(int j = 0; j < _index - 1; ++j)
	{
		itr = itr->m_next;
	}
	
	 _pNode->m_prev = itr;
    
    this->PushNode(_pNode, (T*)_object);
    this->IncrNumOfOfElements();
	return 0;//success
}




template<class T>
T* List_t<T>::Find(const T& _object)const
{
	Node_t* itr = (this->m_head.m_next);
	if(!this->GetNumOfElements())
	{
		return NULL;
	}
	
	for(int j = 0; j < this->GetNumOfElements() ; ++j)
	{
		if(*(itr->m_item) == _object)
		{
			return itr->m_item;
		}
		itr = itr->m_next;
	}
	
	return NULL;
}



template<class T>
T* List_t<T>::Remove(const T& _object)
{
	T* retval = NULL;
	Node_t* itr = (this->m_head.m_next);
	if(!this->GetNumOfElements())
	{ }
	else
	{	
		for(int j = 0; j < this->GetNumOfElements() ; ++j)
		{
			if(*(itr->m_item) == _object)
			{
				retval = PopNode(itr);
				this->DecrNumOfOfElements();
				break;
			}
			itr = itr->m_next;
		}
	}
	
	return retval;
}


template<class T>
void List_t<T>::RemoveAndDelete(const T& _object)
{
	T* temp = this->Remove(_object);
	if(temp)
	{
		delete(temp);
	}
}

template<class T>
void List_t<T>::RemoveAll()
{
	int noe = this->GetNumOfElements();
	Node_t* itr = this->m_head.m_next;
	if(!noe)
	{}
	else
	{
		for(int j = 0; j < noe ; ++j)
		{
			PopNode(itr);
			itr = this->m_head.m_next;
		}
	}
	this->SetNumOfOfElements(0);
}



template<class T>
void List_t<T>::RemoveAndDeleteAll()
{
	int noe = this->GetNumOfElements();
	Node_t* itr = this->m_head.m_next;
	if(!noe)
	{}
	else
	{
		for(int j = 0; j < noe ; ++j)
		{
			delete(itr->m_item);
			delete(itr);
			itr = this->m_head.m_next;
		}
	}
}

/*
template<class T>
const T& List_t<T>::GetItem(int _index)const //if index out of bounds return last elem
{
	int noe = this->GetNumOfElements();
	Node_t* itr = (this->m_head->m_next);
	if(_index < 0 || _index > noe - 1)
	{
		itr = &(this->m_tail);
		return *(itr->m_prev->m_item);
	}
	
	for(int i =0; i < _index; ++i)
	{
		itr = itr->m_next;
	}
	return *(itr->m_item);
}
*/

template<class T>
bool List_t<T>::IsContains(const T& _object)const
{
	T* temp = Find(_object);
	return (temp)?(true):(false);
}

template<class T>	
int List_t<T>::ElementIndex(const T& _value)const
{
	Node_t* itr = (this->m_head.m_next);
	if(!this->GetNumOfElements())
	{
		return -1;
	}
	
	for(int j = 0; j < this->GetNumOfElements() ; ++j)
	{
		if(*(itr->m_item) == _value)
		{
			return j;
		}
		itr = itr->m_next;
	}
	
	return -1;
}


	
	


template<class T>
List_t<T>& List_t<T>::operator = (const List_t<T>& _list)
{

	if(this == &_list) //list address
	{
		return *this;
	}
	
	//remove exisiting list
	this->RemoveAll();
	this->m_head.m_next= &m_tail;	
	this->m_tail.m_prev= &m_head; 

	Node_t* itr = _list.m_head.m_next;
	int nItems = _list.GetNumOfElements();
	for (int i = 0; i < nItems; ++i)
	{
		this->PushBack(itr->m_item);
		itr = itr->m_next;
	}

	return *this;
}

