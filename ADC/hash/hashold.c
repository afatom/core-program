#include <stdlib.h>		/*<< malloc & size_t*/
#include "HashMap.h"
#include "gdlist.h"
#include "list_itr.h"
#include "list_functions.h"
#include <math.h>

#define HASH_IS_VALID 		0xBEEFBEEF
#define HASH_IS_DESTROYED 	0xDEADBEEF


#define TRUE 1
#define FALSE 0

#define NDEBUG




/******************************************************************************/
struct HashMap {
	size_t 				m_magicNumber; /*<< check if need*/
	List** 				m_map;
	MapStats* 			m_stats;
	size_t 				m_hashSize;
	HashFunction 		m_hashFunction;
	EqualityFunction	m_isKeysEqual;
	/*size_t  	m_originalSize;*/ /*check if need*/
}; 
/******************************************************************************/

typedef struct Item {
	void* m_key;
	void* m_value;
}Item;

MapStats EmptyStats = {0,0,0,0,0,0};
/* Static Functions      <<**/
/******************************************************************************/
static size_t TurnToPrime(size_t _num);

static MapResult CheckInsertParams (HashMap* _map, const void* _key, const void* _value);
static MapResult AlocateAndInsert(List* list,const void *_key, const void *_value);
static MapResult CheckRemoveParams(HashMap *_map, const void *_searchKey, void **_pKey, void **_pValue);
int ElementDestroyer(void* elem, void* context);
/******************************************************************************/
/** 
 * @brief Create a new hash map with given capcity and key characteristics.
 * @param[in] _capacity - Expected max capacity 
 * 						  actuall capacity will be equal to nearest larger prime number.
 * @param[in] _hashFunc - hashing function for keys
 * @param[in] _keysEqualFunc - equality check function for keys. 
 * @return newly created map or null on failure
 */
HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hash = NULL;
	size_t fixedSize = 0;
	
	if(_capacity == 0 || NULL == _hashFunc || NULL == _keysEqualFunc)
	{
		return NULL;
	}
	
	hash = (HashMap*)malloc(sizeof(HashMap));
	if(NULL == hash)
	{
		return NULL;
	}
	
	/*call nearest prime number function*/
	fixedSize = TurnToPrime(_capacity);
	
	hash->m_map = (List**)malloc(fixedSize * sizeof(List*));
	
	if(hash->m_map == NULL)
	{
		free(hash);
		return NULL;
	}
	
	hash->m_stats = (MapStats*)malloc(sizeof(MapStats));
	if(NULL == hash->m_stats)
	{
		free(hash->m_map);
		free(hash);
		return NULL;
	}
	
	hash->m_hashSize = fixedSize;
	hash->m_stats->pairs = 0; 			/* number of pairs stored */
	hash->m_stats->collisions = 0;  	/* total number of collisions encountered */
	hash->m_stats->buckets = fixedSize;			/* total number of buckets */
	hash->m_stats->chains = 0;			/* none empty buckets (having non zero length list) */
	hash->m_stats->maxChainLength =	0;	/* length of longest chain */
	hash->m_stats->averageChainLength = 0; /* average length of none empty chains */
	
	hash->m_hashFunction = _hashFunc;
	hash->m_isKeysEqual = _keysEqualFunc ;
	hash->m_magicNumber = HASH_IS_VALID;
	/**/
	return hash;
}
/******************************************************************************/
/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */

static void ElementsDestroy(List* list, )


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
/******************************************************************************/
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
 * @retval  MAP_ALLOCATION_ERROR on failer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	size_t insertionIndex = 0;
	ListItr begin = NULL, end = NULL, isExist = NULL;
	MapResult status;

	if((status = CheckInsertParams(_map, _key, _value))!= MAP_SUCCESS)
	{
		return status;
	}
	
	/*activate hash func - clculating index*/
	insertionIndex = (_map->m_hashFunction(_key)) % _map->m_hashSize;
	
	if(_map->m_map[insertionIndex] == NULL)  /*<< not created before. not collid*/
	{
		/*create list*/
		_map->m_map[insertionIndex] = ListCreate();
		if(_map->m_map[insertionIndex] == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
		++_map->m_stats->pairs;
		return AlocateAndInsert(_map->m_map[insertionIndex], _key,_value);
	}
	++_map->m_stats->collisions;
	begin = ListItrBegin(_map->m_map[insertionIndex]); /*<< collision case -search if duplicates */
	end = ListItrEnd(_map->m_map[insertionIndex]);

	/*improve the function. no consderation in duplicates*/
	isExist = ListItrFindFirst(begin, end, _map->m_isKeysEqual, NULL);
	if(NULL != isExist) /*found. duplicate!*/
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	++_map->m_stats->pairs;
	return AlocateAndInsert(_map->m_map[insertionIndex], _key, _value);
}
/******************************************************************************/
/** 
 * @brief Remove a key-value pair from the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */


/******************************************************************************/
MapResult HashMapRemove(HashMap *_map, void *_searchKey, void **_pKey, void **_pValue)
{
	ListItr begin = NULL, end = NULL, isExist = NULL;
	Item *removed = NULL;
	MapResult status;
	size_t searchingIndex = 0;

	if( (status = CheckRemoveParams(_map,_searchKey,_pKey,_pValue) )!= MAP_SUCCESS)
	{
		return status;
	}

	searchingIndex = (_map->m_hashFunction(_searchKey)) % _map->m_hashSize;
	begin = ListItrBegin(_map->m_map[searchingIndex]); 
	end = ListItrEnd(_map->m_map[searchingIndex]);

	/*improve the function. no consderation in duplicates*/
	isExist = ListItrFindFirst(begin, end, _map->m_isKeysEqual, _searchKey);
	if(isExist == end) /*doesnot founded*/
	{
		*_pKey = NULL;
		*_pValue = NULL;
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	removed = ListItrRemove(isExist);
	*_pKey = removed->m_key;
	*_pValue = removed->m_value;
	return MAP_SUCCESS;
}

/******************************************************************************/
/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 */
size_t HashMapSize(const HashMap *_map)
{
	if(NULL == _map)
	{
		return 0;
	}
	return _map->m_stats->pairs;
}
/******************************************************************************/

MapStats HashMapGetStatistics(const HashMap *_map)
{
	MapStats hashStat = EmptyStats; 
	if(NULL == _map)
	{
		return hashStat;
	}
	hashStat = *_map->m_stats;
	return hashStat;
}
/******************************************************************************/

/******************/
/* Static funcs <<*/
/******************/

/******************************************************************************/
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

	if (ListPushHead(list, newItem) != LIST_SUCCESS)
	{
		free(newItem);
		return MAP_ALLOCATION_ERROR;
	}
	return MAP_SUCCESS;
}
/************************************************************************************/

/******************************************************************************/
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




