#ifndef __DATABASE_H_
#define __DATABASE_H_


#include <stddef.h>
/** 
 * @brief Create generic data Base over a generic ADT (will be implemented over
 * ageneric HashMap).
 * @author 
 * 
 */ 

typedef enum DataBase_Status {
	DATA_BASE_SUCCESS = 0,
	DATA_BASE_NOT_INITIALIZED_ERROR,
	DATA_BASE_ALLOCATION_FAILURE_ERROR,
	DATA_BASE_IVALID_DIRECTORY_PATH_ERROR,
	DATA_BASE_NULL_DATA_INPUT_ERROR,
	DATA_BASE_NULL_FUNCTION_INPUT_ARGS_ERROR,
	DATA_BASE_INVALID_DATA_IN,
	DATA_BASE_DATA_DOES_NOT_EXIST,
	DATA_BASE_DATA_DOWNLOAD_ERROR
	
	
} DataBase_Status;

/**  
 * @brief Create data base and return pointer to created DB. 
 * @details : by Inserting Database user equality items function. equality function will 
 * serve data base for inserting,updating and finding stored elements in data base. 
 * @param[in] _initialCapacity - initial size of DataBase (elements num to be stored).
 * @param[in] _newCapacityInGrowthCondition - future Capacity In Growth Condition
 * @param[in] _(*UserEqualityFunction) - equality user function wich takes 2 items 
 * and return 1 if they are equal or any other value if they are not equal. 
 * @return void* - on success (Generic data base pointer)
 * @retval NULL on fail (allocation err or invalid params in)
 *
 * @warnings: None
 */

void* DataBaseCreate(size_t _initialCapacity, size_t _newCapacityInGrowthCondition,
 int (*UserEqualityFunction)(const void* _firstItem, const void* _secondItem),
size_t (*UserHashFunction)(const void* _key));

/**  
 * @brief Destroy previously created data base and Backup data to txt file
 * corresponding to dir path name.
 * @param[in] _pDataBase - address of prev allocated data base pointer
 * @param[in] _destinationDirPath - full path to dir for saving db elements
 * @return DataBase_Status
 * @retval 	DATA_BASE_SUCCESS - on success
 			DATA_BASE_NOT_INITIALIZED - invalid database pointer 
 			DATA_BASE_IVALID_DIRECTORY_PATH - invalid and wrong path dir
 			DATA_BASE_DATA_DOWNLOAD_ERROR - error occured while data download. 
 			call this function again.
 *
 * @warnings: None
 */
DataBase_Status DataBaseDestroy(void** _pDataBase, const char* _destinationDirPath,void (*_keyDestroy)(void* _key),
 void (*_valDestroy)(void* _value));


/**  
 * @brief Insert data/element to previously created data base
 * @param[in] _dataBase - prev allocated data base pointer
 * @param[in] _data     - user/caller data 
 * @return DataBase_Status
 * @retval 	DATA_BASE_SUCCESS - on success
 			DATA_BASE_NOT_INITIALIZED - invalid database pointer 
 			DATA_BASE_ALLOCATION_FAILURE - on memory failure 
 *			DATA_BASE_NULL_DATA_INPUT - Null data input
 * @warnings: None
 */
/*
DataBase_Status DataBaseInsert(void* _dataBase, const void* _key,
void(*ItemCreate)(void*),void*(*ItemUpdate)(void*,void*),void* _context);
context is cdr* as void*, key is given by cdr.h to agg.h and agg pass it to me 

*/


size_t DB_Get_Size(void* _dataBase);


DataBase_Status DataBaseInsertOrUpdate(void* _dataBase, const void* _key,
 void*(*ItemCreate)(void*), void(*ItemUpdate)(void*,void*),void(*KeyDestroyFunction)(void*),void* _context);
 
 
 
 /**  
 * @brief Search all data base for agiven user key 
 * @param[in] _dataBase - prev allocated data base pointer
 * @param[in] _searchKey     - user key to be searched
 * @param[in] _pItem - user Item pointer for retval. 
 * @return DataBase_Status
 * @retval 	DATA_BASE_SUCCESS - on success
 			DATA_BASE_NOT_INITIALIZED - invalid database pointer 
 *			DATA_BASE_NULL_DATA_INPUT - Null data input _searchkey or pitem
 *			DATA_BASE_DATA_DOES_NOT_EXIST - search key does not exist
 * @warnings: None
 */

DataBase_Status DataBaseFind(const void* _dataBase, const void* _searchKey, void** _pItem);





#endif /*__DATABASE_H_*/
