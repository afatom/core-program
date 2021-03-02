#include <stdlib.h>		/*<< malloc & size_t*/
#include "HashMap.h"
#include "gdlist.h"
#include "list_itr.h"
#include "list_functions.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>


#define NDEBUG

#define MUTEXES_NUM 15

#define SUCCESS 1
#define FAIL 0


#define HASH_IS_VALID 		0xBEEFBEEF
#define HASH_IS_DESTROYED 	0xDEADBEEF

#define _REGION_WIDTH_(a,b) (a/b)

#define TRUE 1
#define FALSE 0


/**

typedef struct Statistic {
    size_t  m_originalSize;
    size_t  m_hashSize;
    size_t  m_maxCollisions;
    size_t  m_numberOfInsertions;
    size_t  m_totalCollisions;
}Statistic;*/


/******************************************************************************/
struct HashMap {
	size_t 				m_magicNumber;
	size_t 				m_hashSize;
	size_t 				m_collisions;
	List** 				m_map;
	pthread_mutex_t	    *m_mutexArray;
	HashFunction 		m_hashFunction;
	EqualityFunction	m_isKeysEqual;
	size_t testpairs;
}; 
/******************************************************************************/

typedef struct Item {
	void* m_key;
	void* m_value;
}Item;



#ifdef NDEBUG
MapStats EmptyStats = {0, 0, 0, 0, 0, 0};	
#endif /** NDEBUG*/


/****************************/
/* Static Functions      <<**/
/*******************************************************************************************************/
static void HashInitializing(HashMap *_hash, size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
static size_t TurnToPrime(size_t _num);
static MapResult CheckInsertParams (HashMap* _map, const void* _key, const void* _value);
static MapResult AlocateAndInsert(List* list,const void *_key, const void *_value);
static MapResult CheckRemoveParams(HashMap *_map, const void *_searchKey, void **_pKey, void **_pValue);
static MapResult CheckFindParams(const HashMap *_map, const void *_searchKey, void **_pValue);
static void ItemsDestroy(ListItr _begin, ListItr _end, _keyDestroy _freeKey, _valDestroy _freeValue);
static MapResult HashMapJustFind(const HashMap *_map, const void *_searchKey, void **_foundedItem);
static size_t CalculateNewIndex(HashMap *_map, Item* _item);
static Item* GetListElement(ListItr _itr);
static MapResult CheckInsertOrUpdateParams(HashMap* _map, const void* _key,
 void*(*ItemCreate)(void*), void(*ItemUpdate)(void*,void*),void* _context);
 
#ifdef NDEBUG
static void PrintHashStat(MapStats* ptr);
static void GetHashStat(const HashMap* _map, MapStats* _stat);
#endif /** NDEBUG*/
static MapResult ConvertKeys(HashMap *_map,List** _pNewHash ,size_t _newHashSize, size_t _originalHashIndex);
static int MutexArrInit(pthread_mutex_t* _arr, size_t _size);
static void DestroyMutixArr(pthread_mutex_t* _arr, size_t _size);

/*******************************************************************************************************/

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hash = NULL;
	size_t fixedSize = 0;	
	
	if(_capacity == 0 || NULL == _hashFunc || NULL == _keysEqualFunc)
	{
		return NULL;
	}

	fixedSize = TurnToPrime(_capacity);
	hash = (HashMap*)malloc(sizeof(HashMap));
	if(NULL == hash)
	{
		return NULL;
	}
	
	
	hash->m_map = (List**)calloc(fixedSize, sizeof(List*));
	
	if(hash->m_map == NULL)
	{
		free(hash);
		return NULL;
	}
	
	hash->m_mutexArray = (pthread_mutex_t*)malloc(MUTEXES_NUM * sizeof(pthread_mutex_t));
	assert(hash->m_mutexArray!=NULL);
	
	assert((MutexArrInit(hash->m_mutexArray, MUTEXES_NUM)) == SUCCESS);
	
	HashInitializing(hash, fixedSize, _hashFunc, _keysEqualFunc);
	return hash;
}
/******************************************************************************************************/
static void HashInitializing(HashMap* _hash, size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	_hash->m_hashSize = _capacity;
	_hash->m_hashFunction = _hashFunc;
	_hash->m_isKeysEqual = _keysEqualFunc;
	_hash->m_collisions = 0;
	_hash->m_magicNumber = HASH_IS_VALID;
	_hash->testpairs=0;
	return;
}
/******************************************************************************************************/

void HashMapDestroy(HashMap **_map, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value))
{
	ListItr begin = NULL, end = NULL;
	size_t i =0;
	List* toBeRemoved = NULL;
	

	if(NULL == _map || *_map == NULL)
	{
		return;
	}
	
	DestroyMutixArr((*_map)->m_mutexArray, MUTEXES_NUM);
	
	if(_keyDestroy != NULL && _valDestroy != NULL)
	{
		while (i < (*_map)->m_hashSize)
		{
			if ((*_map)->m_map[i] != NULL)
			{
				begin = ListItrBegin((*_map)->m_map[i]);
				end = ListItrEnd((*_map)->m_map[i]);
				ItemsDestroy(begin, end, _keyDestroy, _valDestroy);
				toBeRemoved  = (*_map)->m_map[i];
				ListDestroy(&toBeRemoved, NULL);
			}
			++i;
		}
	}
	/*****added sec begin*/
	else
	{	
		while (i < (*_map)->m_hashSize)
		{
			if ((*_map)->m_map[i] != NULL)
			{
				toBeRemoved  = (*_map)->m_map[i];
				ListDestroy(&toBeRemoved, NULL);
			}
			++i;
		}
	}
	/*****added sec end*/
	free((*_map)->m_mutexArray);
	free((*_map)->m_map);
	free(*_map);
	*_map= NULL;
}

/*******************************************************************************************************/
MapResult HashMapInsert(HashMap *_map, const void *_key, const void *_value)
{
	size_t insertionIndex = 0;
	MapResult status;
	void* _pValue = NULL;
	

	if((status = CheckInsertParams(_map, _key, _value))!= MAP_SUCCESS)
	{
		return status;
	}
	
	insertionIndex = (_map->m_hashFunction(_key)) % (_map->m_hashSize);
			/**<< lock area*/
	if(_map->m_map[insertionIndex] == NULL)  /*<< not created before. not collid*/
	{
		_map->m_map[insertionIndex] = ListCreate();
		if(_map->m_map[insertionIndex] == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
		printf("iam in insert function.  pairs %lu\n", _map->testpairs);
		return AlocateAndInsert(_map->m_map[insertionIndex], _key,_value);
 
	}

	/**
	if( HashMapFind(_map, _key, &_pValue) == MAP_SUCCESS  ) found. duplicate!
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}**/
	
	++_map->m_collisions;
	
	return  AlocateAndInsert(_map->m_map[insertionIndex], _key, _value);
}
/*******************************************************************************************************/
/*******************************************************************************************************/


MapResult HashMapInsertOrUpdate(HashMap* _map, const void* _key,
 void*(*ItemCreate)(void*), void(*ItemUpdate)(void*,void*), void(*KeyDestroyFunction)(void*),void* _context)
 {
	 MapStats st = EmptyStats;
	 size_t insertionIndex = 0, j=0;
	 void* val = NULL;
	 MapResult stat;
	 
	 insertionIndex = (_map->m_hashFunction(_key)) % (_map->m_hashSize);
	if(pthread_mutex_lock(&(_map->m_mutexArray[insertionIndex % MUTEXES_NUM])))
		{
			return MAP_SAFETY_ERROR;
		}
	 
	 stat = CheckInsertOrUpdateParams(_map, _key,(*ItemCreate), (*ItemUpdate),_context);
	 if(stat != MAP_SUCCESS)
	 {
		 return stat;
	 }
	 
	 stat = HashMapFind(_map, _key, &val);
	 if(stat == MAP_KEY_NOT_FOUND_ERROR)
	 {
		 
		val = ItemCreate(_context);
		stat = HashMapInsert(_map, _key, val);
		++_map->testpairs;
		printf("pairs %lu\n", _map->testpairs);
		
		if(pthread_mutex_unlock(&(_map->m_mutexArray[insertionIndex % MUTEXES_NUM])))
		{
			return MAP_SAFETY_ERROR;
		}
		
		++_map->testpairs;
		printf("pairs %lu\n", _map->testpairs);
		puts("Insert action");
		GetHashStat(_map, &st);		
		PrintHashStat(&st);
		return stat;
	 }
	 
	 
	ItemUpdate(val,_context);
	/*No nned for allocated Key in update case. so we destroy it because its already
	exist in hash*/
	KeyDestroyFunction((void*)_key);
	if(pthread_mutex_unlock(&(_map->m_mutexArray[insertionIndex % MUTEXES_NUM])))
		{
			return MAP_SAFETY_ERROR;
		}
		puts("Update action");
		GetHashStat(_map, &st);		
		PrintHashStat(&st);
	return MAP_SUCCESS;
 }

/*******************************************************************************************************/
/*******************************************************************************************************/

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

/*******************************************************************************************************/
/**
 * This function search the list for an item. if item/key is found, the Node adress wich holds
 * the item will be returned. if Not NULL will return in _foundedItem 
 * 
 * 
 * 
 * */
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
			/** *_foundedItem = (void*)item;*/
			*_foundedItem = (void*)begin;		/** return NODE adress wich holds the item */
			return MAP_SUCCESS;
		}
		
		begin = ListItrNext(begin);
	}
	*_foundedItem = NULL;
	return MAP_KEY_NOT_FOUND_ERROR;
}


/*******************************************************************************************************/
MapResult HashMapRemove(HashMap *_map, const void *_searchKey, void **_pKey, void **_pValue)
{
	
	void *removed = NULL;
	MapResult status;
	void* find=NULL;

	if( (status = CheckRemoveParams(_map,_searchKey,_pKey,_pValue) )!= MAP_SUCCESS)
	{
		return status;
	}

	if( HashMapJustFind(_map, _searchKey, &find) != MAP_SUCCESS  ) /*not found*/
	{
		*_pKey = NULL;
		*_pValue = NULL;
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	
	removed = ListItrRemove((ListItr)find);
	*_pKey = ((Item*)removed)->m_key;
	*_pValue = ((Item*)removed)->m_value;
	return MAP_SUCCESS;
}

/******************************************************************************/
/**
size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t i = 0;
	Item* item = NULL;
	void *_foundedItem = NULL;
	if(NULL == _map || NULL == _action)
	{
		return 0;
	}
	
	 int	_action(const void* _key, void* _value, void* _context);
	HashMapJustFind(_map, const void *_searchKey, &_foundedItem);
	first = ListItrGet(begin);
		item = (Item*)first;
}
*/

		

size_t HashSize(const HashMap* _map)
{
	if(NULL == _map)
	{
		return 0;
	}
	return _map->m_hashSize;
}
/******************************************************************************/
#ifdef NDEBUG
MapStats HashMapGetStatistics(const HashMap *_map)
{
	MapStats hashStat = EmptyStats; 
	if(NULL == _map)
	{
		return hashStat;
	}
	
	GetHashStat(_map, &hashStat);
	

	hashStat.collisions = _map->m_collisions;

	hashStat.buckets = _map->m_hashSize;

	return hashStat;
}
#endif /**NDEBUG*/

#ifdef NDEBUG
static void GetHashStat(const HashMap* _map, MapStats* _stat)
{	
	size_t i = 0, temp=0;

	for(i=0; i<_map->m_hashSize; ++i)
	{
		 if((temp = ListSize(_map->m_map[i])) > 0)
		 {
			++_stat->chains;
			_stat->pairs += temp; 
			_stat->averageChainLength += temp;
			if(temp > _stat->maxChainLength)
			{
				_stat->maxChainLength = temp;
			} 
		 }
	}
	_stat->averageChainLength /= _stat->chains;
	return;  
}
#endif /**NDEBUG*/

#ifdef NDEBUG

static void PrintHashStat(MapStats* ptr)
{

	puts("HashMap statistics data");
	printf("Pairs Num          :: %lu\n", ptr->pairs);
	printf("collisions Num     :: %lu\n", ptr->collisions);
	printf("buckets Num        :: %lu\n", ptr->buckets);
	printf("chains Num         :: %lu\n", ptr->chains);
	printf("maxChainLength     :: %lu\n", ptr->maxChainLength);
	printf("averageChainLength :: %lu\n", ptr->averageChainLength);
}
#endif /**NDEBUG*/
MapResult HashMapRehash(HashMap *_map, size_t newCapacity)
{
	size_t newFixedSize = 0;
	size_t index =0, originalSize=0,i=0;
	List** temp;
	List* toBeRemoved = NULL;

	
	if(newCapacity == 0 || NULL == _map )
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	
	if(newCapacity == _map->m_hashSize)
	{
		return MAP_SUCCESS;
	}
	
	originalSize = _map->m_hashSize;
	
	_map->m_hashSize = newFixedSize = TurnToPrime(newCapacity);
	 
	temp = (List**)calloc(newFixedSize, sizeof(List*));
	if(temp == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	/*
	for(i = 0; i < newFixedSize; ++i)
	{
		printf("List at %d -> %p\n",(int)i,(void*)_map->m_map[i]);
	}
	*/
	for(index = 0; index < originalSize; ++index)
	{
		
		if(ConvertKeys(_map, temp,newFixedSize, index) != MAP_SUCCESS)
		{
			
			return MAP_ALLOCATION_ERROR;
		}
		
	}
	
	i=0;
	/**free prev list** */		
	while (i < originalSize)
	{
		if ((_map)->m_map[i] != NULL)
		{
			toBeRemoved  = (_map)->m_map[i];
			ListDestroy(&toBeRemoved, NULL);
		}
		++i;
	}

	/*****added sec end*/
	free((_map)->m_map);
	_map->m_map = temp;
	
	return MAP_SUCCESS;
}

static MapResult ConvertKeys(HashMap *_map,List** _pNewHash ,size_t _newHashSize, size_t _originalHashIndex)
{
	ListItr begin = NULL, end = NULL;/**, current=NULL;*/
	Item *item = NULL;
	size_t newIndex =0;
	if(_map->m_map[_originalHashIndex] == NULL)
	{
		return MAP_SUCCESS;
	}
	
	begin = ListItrBegin((_map->m_map[_originalHashIndex]));
	end = ListItrEnd((_map->m_map[_originalHashIndex]));
	
	while (ListItrEquals(begin, end) == FALSE)
	{
		
		item = GetListElement(begin);
		
		newIndex = CalculateNewIndex(_map, item);
		
		if(_pNewHash[newIndex] == NULL) /** list not created before*/
		{
			_pNewHash[newIndex] = ListItrCut(begin, ListItrNext(begin));

		}
		else
		{
			ListItrSplice(ListItrBegin((_pNewHash[newIndex])), begin, ListItrNext(begin));
		}
		
		
		/**begin = ListItrNext(begin);*/
		begin = ListItrBegin(_map->m_map[_originalHashIndex]);
	}
	
	return MAP_SUCCESS;

}

static Item* GetListElement(ListItr _itr)
{
	void* element=NULL;
	
	element = ListItrGet(_itr);
	return (Item*)element;
}

static size_t CalculateNewIndex(HashMap *_map, Item* _item)
{
	return (_map->m_hashFunction(_item->m_key)) % (_map->m_hashSize);
}




/******************************************************************************
 * Static Functions Implementation
 * 
 * 
 * 
 ******************************************************************************/
static MapResult CheckInsertParams (HashMap* _map, const void* _key, const void* _value)
{

	if (_map == NULL || _map->m_magicNumber != HASH_IS_VALID)
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	if (NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if (_value == NULL)
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	return MAP_SUCCESS;
}
/************************************************************************************/
static MapResult CheckFindParams(const HashMap *_map, const void *_searchKey, void **_pValue)
{
	if (_map == NULL || _map->m_magicNumber != HASH_IS_VALID)
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	if (NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if (_pValue == NULL)
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	return MAP_SUCCESS;
}

/************************************************************************************/
static MapResult CheckRemoveParams(HashMap *_map, const void *_searchKey, void **_pKey, void **_pValue)
{
	if (_map == NULL || _map->m_magicNumber != HASH_IS_VALID)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if(NULL == _pKey || NULL == _pValue)
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	return MAP_SUCCESS;
}
/************************************************************************************/

static MapResult AlocateAndInsert(List* list,const void *_key, const void *_value)
{
	void* newItem = NULL;
	if ((newItem = (Item *)malloc(sizeof(Item))) == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}

	((Item*)newItem)->m_key = (void*)_key;
	((Item *)newItem)->m_value = (void*)_value;

	if (ListPushHead(list, newItem) != LIST_SUCCESS)
	{
		free(newItem);
		return MAP_ALLOCATION_ERROR;
	}
	return MAP_SUCCESS;
}
/************************************************************************************/
static size_t TurnToPrime(size_t _num)
{
	double root;
	size_t i = 2;
	
	root = sqrt((double)_num);
	while (1)
	{
		++_num;
		if(_num %2 == 0)
		{
		++_num;
		}
		
		root = sqrt((double)_num);
		i=2;
		while(i <= (size_t)root)
		{
			if(_num % i == 0) /*not prime*/
			{
				break;
			}
			++i;
		}
		
		if(i > (size_t)root)
		{
			return _num;
		}
			
	}
}
/********************************************************************************************/
static void ItemsDestroy(ListItr _begin, ListItr _end, _keyDestroy _freeKey, _valDestroy _freeValue)
{
	ListItr itemToBeDeleted = NULL;
	void* item = NULL;

	while (ListItrEquals(_begin, _end) == FALSE)
    {
		itemToBeDeleted = _begin;
		_begin = ListItrNext(_begin); /*take itr begin one step right (next) before any freeing operation*/
        item = ListItrRemove(itemToBeDeleted);
		_freeKey(((Item*)item)->m_key);
		_freeValue(((Item*)item)->m_value);
		free(item);
    }
	return;
}
/********************************************************************************************/
static MapResult CheckInsertOrUpdateParams(HashMap* _map, const void* _key,
 void*(*ItemCreate)(void*), void(*ItemUpdate)(void*,void*),void* _context)
 {
	if (_map == NULL || _map->m_magicNumber != HASH_IS_VALID)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if(NULL == _context || NULL == (*ItemCreate) || NULL == (*ItemUpdate))
	{
		return MAP_INVALID_INCOMING_VALUE;
	}
	return MAP_SUCCESS;
 }
/********************************************************************************************/
static int MutexArrInit(pthread_mutex_t* _arr, size_t _size)
{
	size_t i =0;
	for(i = 0; i < _size; ++i)
	{
		if(pthread_mutex_init(&_arr[i],NULL))
		{
			DestroyMutixArr(_arr,i);
			return FAIL;
		}
	}
	return SUCCESS;
}
/********************************************************************************************/
static void DestroyMutixArr(pthread_mutex_t* _arr, size_t _size)
{
	
	size_t i =0;
	for(i = 0; i < _size; ++i)
	{
		pthread_mutex_destroy(&_arr[i]);
	}
	return;
}
/********************************************************************************************/


