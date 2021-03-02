
template<class ITEM>
List_t<ITEM>& List_t<ITEM>::operator= (const List_t<ITEM>& _list)
{
	if (this == &_list) return *this;

	m_head.SetNext(&m_tail);
	m_tail.SetPrev(&m_head);
	RemoveAll();

	Node_t<ITEM>* temp = (_list.m_head).Next();
	int nItems = _list.Count();
	for (int i = 0; i < nItems; ++i)
	{
		Insert(temp->GetItem());
		temp = temp->Next();
	}

	return *this;
}
template<class ITEM>
void List_t<ITEM>::Append(const ITEM& _item, int _index)
{
	InsertAfter(_item, ResolvePosition(++_index));
}
template<class ITEM>
void List_t<ITEM>::Prepend(const ITEM& _item, int _index)
{
	InsertAfter(_item, ResolvePosition(_index));
}
template<class ITEM>
void List_t<ITEM>::Insert(const ITEM& _item)
{
	InsertAfter(_item, ResolvePosition(Count()));
}
template<class ITEM>
ITEM List_t<ITEM>::GetItem(int _index)
{
	Node_t<ITEM>* tempNode = ResolvePosition(_index);
	tempNode = tempNode->Next();
	return tempNode->GetItem();
}

template<class ITEM>
ITEM List_t<ITEM>::Remove(int _index)
{
	return DeleteNode(ResolvePosition(++_index));
}

template<class ITEM>	
void List_t<ITEM>::RemoveAll()
{
	if (Count() == 0) return ;

	Node_t<ITEM>* currentNode = m_head.Next();
	int nItems = Count();
	
	if (currentNode != &m_tail)
	{
		for (int i = 0; i < nItems; ++i)
		{
			currentNode = currentNode->Next();
			delete currentNode->Prev();
		}
	}
	m_head.SetNext(&m_tail);
	m_tail.SetPrev(&m_head);

	Container_t<ITEM>::RemoveAll();
}

template<class ITEM>
int List_t<ITEM>::Find(const ITEM& _item) const
{
	Node_t<ITEM>* currentNode = m_head.Next();
	ITEM storedItem;
	
	int nItems = Count();
	for (int i = 0; i < nItems; ++i)
	{
		storedItem = currentNode->GetItem();
		if (storedItem == _item) return i;
		currentNode = currentNode->Next();
	}
	return -1;
}

template<class ITEM>
int List_t<ITEM>::Count() const
{
	return Container_t<ITEM>::Count();
};

template<class ITEM>
void List_t<ITEM>::Print() const
{
	Node_t<ITEM>* currentNode = m_head.Next();
	
	int nItems = Count();
	for (int i = 0; i < nItems; ++i)
	{
		cout << currentNode->GetItem() << "  ";
		currentNode = currentNode->Next();
	}
	cout<<endl;
}





template<class ITEM>
Node_t<ITEM>* List_t<ITEM>::ResolvePosition(int _index)
{
	if (_index < 0 || _index > Count()) throw TException_t<int>(3,"Index out of boundries" ,__FILE__ ,__LINE__);

	Node_t<ITEM>* position = &m_head;
	for (int i = 0; i < _index; ++i)
	{
		position = position->Next();
	}

	return position;
}

template<class ITEM>
void List_t<ITEM>::InsertAfter(ITEM _item, Node_t<ITEM>* _currentNode)
{
	Node_t<ITEM>* newNode = new Node_t<ITEM>(_item, _currentNode, _currentNode->Next());
	if (!newNode) throw TException_t<int>(2,"Allocation Failure" ,__FILE__ ,__LINE__);
	(_currentNode->Next())->SetPrev(newNode);
	_currentNode->SetNext(newNode);
	Container_t<ITEM>::IncreaseNItems();
}

template<class ITEM>
ITEM List_t<ITEM>::DeleteNode(Node_t<ITEM>* _currentNode)
{
	ITEM returnItem = _currentNode->GetItem();
	(_currentNode->Next())->SetPrev(_currentNode->Prev());
	(_currentNode->Prev())->SetNext(_currentNode->Next());
	Container_t<ITEM>::DecreaseNItems();
	delete _currentNode;
	return returnItem;
}

#endif 
