/******************************************************************************/
MapResult BucketsCreator(HashMap* _hash, size_t _fixedSize)
{
	size_t j = 0, i =0;
	for(j = 0; j < _fixedSize; ++j)
	{
		_hash->m_map[j] = ListCreate();
		if(NULL == hash->m_map[j])
		{
			/*free aloocations that have been allocated*/
			for(i = 0; i < j; ++j)
			{
				ListDestroy(&_hash->m_map[i], NULL);
			}
			return MAP_ALLOCATION_ERROR;
		} 
	}
	
	return MAP_SUCCESS;
}
/******************************************************************************/



















/******************************************************************************/
/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t i = 0;
	if(_map == NULL || *_map == NULL || (*_map)->m_magicNumber != HASH_IS_VALID)
	{
		return;
	}
	
	while(i < (*_map)->m_hashSize)
	{
		/*ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));
		*/
		/*pass on list with list for each*/
		void ActivateDestroyAction(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
		++i;
	}


return;
}


ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);









void ActivateDestroyAction(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{



}



/** 
 * @brief Insert a key-value pair into the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failuer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	if()
}
























/******************************************************************************/
/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t i = 0;
	if(_map == NULL || *_map == NULL || (*_map)->m_magicNumber != HASH_IS_VALID)
	{
		return;
	}
	
	while(i < (*_map)->m_hashSize)
	{
		/*ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));
		*/
		/*pass on list with list for each*/
		void ActivateDestroyAction(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
		++i;
	}


return;
}


ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);









void ActivateDestroyAction(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{



}



/** 
 * @brief Insert a key-value pair into the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failuer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	if()
}




void HashMapDestroy(HashMap **_map, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value))
{
	ListItr begin = NULL, end = NULL;
	size_t i =0;
	List* toBeRemoved = NULL;

	if(NULL == _map || *_map == NULL)
	{
		return;
	}
	if(_keyDestroy != NULL && _valDestroy != NULL)
	{
		while (i < (*_map)->m_hashSize)
		{
			if ((*_map)->m_map[i] != NULL)
			{
				begin = ListItrBegin((*_map)->m_map[i]);
				end = ListItrEnd((*_map)->m_map[i]);
				ListItrForEach(begin, end, ElementDestroyer, NULL);
			}
			++i;
		}
	}
	i =0;

	while (i < (*_map)->m_hashSize)
	{
		if ((*_map)->m_map[i] != NULL)
		{
			toBeRemoved = (*_map)->m_map[i];
			ListDestroy(&toBeRemoved, NULL);
		}
		++i;
	}
	free((*_map)->m_stats);
	free((*_map)->m_map);
	free(*_map);
	*_map= NULL;
}

int ElementDestroyer(void *elem, void *context)
{
	Item *element = NULL;

	element = (Item *)malloc(sizeof(Item));
	element = (Item *)elem;

	_keyDestroy(elem->m_key);
	_valDestroy(elem->m_value);
	free(elem);
	free(element);
	return TRUE;
}





int ElementDestroyer(void *elem, void *context)
{
	Item *element = NULL;

	element = (Item *)malloc(sizeof(Item));
	element = (Item *)elem;

	_keyDestroy(elem->m_key);
	_valDestroy(elem->m_value);
	free(elem);
	free(element);
	return TRUE;
}


