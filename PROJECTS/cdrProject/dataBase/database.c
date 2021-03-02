#include "DataBase.h"
#include "HashMap.h"
#include <stdio.h>
static int DownloadDataBaseData(FILE* _fp)
{
	return 1; /** for phase b  its ok*/
}

static DataBase_Status HashStatToDataBaseStat(MapResult _hashStat);

/**********************************************************************/
 
 void* DataBaseCreate(size_t _initialCapacity, size_t _newCapacityInGrowthCondition,
 int (*UserEqualityFunction)(const void* _firstItem, const void* _secondItem),
size_t (*UserHashFunction)(const void* _key))
{	
	HashMap* hash = NULL;
	hash = HashMapCreate(_initialCapacity,(*UserHashFunction) ,(*UserEqualityFunction));
	
	return (void*)hash;

} 
/**********************************************************************/

DataBase_Status DataBaseDestroy(void** _pDataBase, const char* _destinationDirPath,
void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	FILE* fp = NULL;
	HashMap* hash = NULL;
	if(NULL == _pDataBase || NULL == *_pDataBase)
	{
		return DATA_BASE_NOT_INITIALIZED_ERROR;
	}
	
	fp = fopen(_destinationDirPath,"w+");
	if(!fp)
	{
		return DATA_BASE_IVALID_DIRECTORY_PATH_ERROR;
	}
	
	if(!DownloadDataBaseData(fp))
	{
		return DATA_BASE_DATA_DOWNLOAD_ERROR;
	}
	
	hash = *(HashMap**)_pDataBase;
	
	HashMapDestroy(&hash, (*_keyDestroy), (*_valDestroy));
	*(HashMap**)_pDataBase = NULL;
	fclose(fp);
	return DATA_BASE_SUCCESS;

}
/**********************************************************************/

DataBase_Status DataBaseInsertOrUpdate(void* _dataBase, const void* _key,
 void*(*ItemCreate)(void*), void(*ItemUpdate)(void*,void*),void(*KeyDestroyFunction)(void*),void* _context)
{
	MapResult stat;

	stat = HashMapInsertOrUpdate((HashMap*)_dataBase, _key,(*ItemCreate), (*ItemUpdate),(*KeyDestroyFunction),_context);
	return HashStatToDataBaseStat(stat);
}




DataBase_Status DataBaseFind(const void* _dataBase, const void* _searchKey, void** _pItem)
{
	MapResult ret;
	ret = HashMapFind((HashMap*)_dataBase, _searchKey, _pItem);
	return HashStatToDataBaseStat(ret);
}



size_t DB_Get_Size(void* _dataBase)
{


/*
size_t HashSize(const HashMap* _map);*/
	return HashSize((HashMap*)_dataBase);
}

/**********************************************************************/
static DataBase_Status HashStatToDataBaseStat(MapResult _hashStat)
{
	DataBase_Status stat;
	
	switch (_hashStat)
	{
		case MAP_SUCCESS:
			stat = DATA_BASE_SUCCESS;
			break;
			
		case MAP_UNINITIALIZED_ERROR:
			stat = DATA_BASE_NOT_INITIALIZED_ERROR;
			break;
			
		case MAP_KEY_NULL_ERROR:
			stat = DATA_BASE_NULL_DATA_INPUT_ERROR;
			break;
			
		case MAP_KEY_NOT_FOUND_ERROR:
			stat = DATA_BASE_DATA_DOES_NOT_EXIST;
			break;
			
		case MAP_ALLOCATION_ERROR:
			stat = DATA_BASE_ALLOCATION_FAILURE_ERROR;
			break;
			
		case MAP_INVALID_INCOMING_VALUE:
			stat = DATA_BASE_INVALID_DATA_IN;
			break;
		
		default:
			break;
	}
	return stat;
}

/**********************************************************************/




