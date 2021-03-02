
MapResult HashMapFind(const HashMap *_map, const void *_searchKey, void **_pValue)
{
	ListItr begin = NULL, end = NULL;
	Item *item = NULL;
	MapResult status;
	size_t searchingIndex = 0;
	void* first = NULL;

	if ((status = CheckFindParams(_map,_searchKey, _pValue)) != MAP_SUCCESS)
	{
		return status;
	}
	/*activate hash func - clculating index*/

	searchingIndex = (_map->m_hashFunction(_searchKey)) % (_map->m_hashSize);

	begin = ListItrBegin((_map->m_map[searchingIndex]));
	end = ListItrEnd((_map->m_map[searchingIndex]));

	while (ListItrEquals(begin, end) == FALSE)
	{
		first = ListItrGet(begin);
		item = (Item*)first;
		if(_map->m_isKeysEqual(item->m_key,_searchKey))
		{
			*_pValue = item->m_value;
			return MAP_SUCCESS;
		}
		
		begin 	= ListItrNext(begin);
	}
	*_pValue = NULL;
	return MAP_KEY_NOT_FOUND_ERROR;
}

static MapResult HashMapJustFind(const HashMap *_map, const void *_searchKey, void **_foundedItem)
{
	ListItr begin = NULL, end = NULL;
	Item *item = NULL;
	size_t searchingIndex = 0;
	void* first = NULL;

	searchingIndex = (_map->m_hashFunction(_searchKey)) % (_map->m_hashSize);

	begin = ListItrBegin((_map->m_map[searchingIndex]));
	end = ListItrEnd((_map->m_map[searchingIndex]));

	while (ListItrEquals(begin, end) == FALSE)
	{
		first = ListItrGet(begin);
		item = (Item*)first;
		if(_map->m_isKeysEqual(item->m_key,_searchKey))
		{
			*_foundedItem = (void*)item;
			return MAP_SUCCESS;
		}
		
		begin = ListItrNext(begin);
	}
	*_foundedItem = NULL;
	return MAP_KEY_NOT_FOUND_ERROR;
}


































MapResult HashMapRehash(HashMap *_map, size_t newCapacity)
{
	HashMap* newhash = NULL;
	HashMap* temp = NULL;
	size_t newFixedSize = 0;
	size_t index =0;
	if(newCapacity == 0 || NULL == _map )
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	
	newFixedSize = TurnToPrime(newCapacity);
	newhash = (HashMap*)calloc(1,sizeof(HashMap));
	if(NULL == newhash)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	newhash->m_map = (List**)calloc(newFixedSize, sizeof(List*));
	
	if(newhash->m_map == NULL)
	{
		free(newhash);
		return MAP_ALLOCATION_ERROR;
	}
		
	HashInitializing(newhash, newFixedSize, _map->m_hashFunction, _map->m_isKeysEqual);
	
	for(index = 0; index < _map->m_hashSize; ++index)
	{
		ConvertKeys(_map, newhash, index);
		
	}
	
	
	
	temp = _map;
	
	HashMapDestroy(&temp, NULL, NULL);
	_map = newhash;
	
	return MAP_SUCCESS;
}

static MapResult ConvertKeys(HashMap *_map, HashMap *_newHash, size_t _originalHashIndex)
{
	ListItr begin = NULL, end = NULL;
	Item *item = NULL;

	size_t newIndex=0;
	
	if(_map->m_map[_originalHashIndex] == NULL)
	{
		return MAP_SUCCESS;
	}
	
	begin = ListItrBegin((_map->m_map[_originalHashIndex]));
	end = ListItrEnd((_map->m_map[_originalHashIndex]));
	
	while (ListItrEquals(begin, end) == FALSE)
	{
		item = GetListElement(begin);
		
		newIndex = CalculateNewIndex(_newHash, item);
		_newHash->m_map[newIndex] = ListCreate();
		
		if(_newHash->m_map[newIndex] == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}

		
		if (ListPushHead(_newHash->m_map[newIndex], (void*)item) != LIST_SUCCESS)
		{
			free(item);
			return MAP_ALLOCATION_ERROR;
		}
		
		/*begin = ListItrNext(begin);*/
		begin = ListItrBegin((_map->m_map[_originalHashIndex]));
	}
	
	return MAP_SUCCESS;

}

static Item* GetListElement(ListItr _itr)
{
	void* element=NULL;
	
	element = ListItrRemove(_itr);
	return (Item*)element;
}

static size_t CalculateNewIndex(HashMap *_newHash, Item* _item)
{
	return (_newHash->m_hashFunction(_item->m_key)) % (_newHash->m_hashSize);
}












MapResult HashMapRehash(HashMap *_map, size_t newCapacity)
{
	size_t newFixedSize = 0;
	size_t index =0, originalSize=0;
	if(newCapacity == 0 || NULL == _map )
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	
	if(newCapacity == _map->m_hashSize)
	{
		return MAP_SUCCESS;
	}
	
	originalSize = _map->m_hashSize;
	
	newFixedSize = TurnToPrime(newCapacity);
	_map->m_hashSize = newFixedSize;
	
	
	for(index = 0; index < originalSize; ++index)
	{
		
		if(ConvertKeys(_map, newFixedSize, index) != MAP_SUCCESS)
		{
			
			return MAP_ALLOCATION_ERROR;
		}
		
	}
	
	
	return MAP_SUCCESS;
}

static MapResult ConvertKeys(HashMap *_map, size_t _newHashSize, size_t _originalHashIndex)
{
	ListItr begin = NULL, end = NULL;/**, current=NULL;*/
	Item *item = NULL;
	
	if(_map->m_map[_originalHashIndex] == NULL)
	{
		return MAP_SUCCESS;
	}
	
	begin = ListItrBegin((_map->m_map[_originalHashIndex]));
	end = ListItrEnd((_map->m_map[_originalHashIndex]));
	
	while (ListItrEquals(begin, end) == FALSE)
	{
		puts("*");
		/*current = begin;*/
		/*begin = ListItrNext(begin);*/
		item = GetListElement(begin);
		
		/*newIndex = CalculateNewIndex(_newHashSize, item);*/
		HashMapInsert(_map, item->m_key, item->m_value);
		
		
		begin = ListItrBegin((_map->m_map[_originalHashIndex]));
	}
	
	return MAP_SUCCESS;

}

static Item* GetListElement(ListItr _itr)
{
	void* element=NULL;
	
	element = ListItrRemove(_itr);
	return (Item*)element;
}
/*
static size_t CalculateNewIndex(size_t _newHashSize, Item* _item)
{
	return (_newHash->m_hashFunction(_item->m_key)) % (_newHashSize);
}


*/

	hash->m_map = (List**)calloc(fixedSize, sizeof(List*));
	for(i = 0; i < fixedSize; ++i)
	{
		printf("List at %d -> %p\n",(int)i,(void*)hash->m_map[i]);
	}
	
	if(hash->m_map == NULL)
	{
		free(hash);
		return NULL;
	}
	




























































































































































