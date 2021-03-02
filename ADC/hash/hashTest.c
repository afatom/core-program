#include <stdlib.h>		/*<< malloc & size_t*/
#include "HashMap.h"
#include "gdlist.h"
#include <stdio.h>
#include "list_itr.h"
#include "list_functions.h"
#include <assert.h>
#include <string.h>
#include <time.h>
#include "mu_test.h"
#include <unistd.h>

#define NDEBUG
#define TRUE 1
#define FALSE 0



/******************************************************************************************************/
UNIT(ssssrand)
srand((unsigned int)time(NULL));
END_UNIT
/******************************************************************************************************/
size_t idiotHash(const void* _key)
{
	int key = *(int*)_key;
	return (size_t)(key);
}
/******************************************************************************************************/
int IsEqual(const void* _firstKey,const void* _secondKey)
{
	return (*((int*)_firstKey) == (*(int*)_secondKey))?(TRUE):(FALSE);
}

/*
*Def: int alocated array. each element is the key and the value.
*out: key and value for derefernce.
*pointer to array
*inputs: array size.
*/
/******************************************************************************************************/
int* valueAndKeyCreator(size_t arrSize)
{
	int* arr = NULL;
	size_t i=0;
	arr = malloc(arrSize * sizeof(*arr));
	assert(arr != NULL);
	for(i = 0; i<arrSize; ++i)
	{
		*(arr+(int)i)= rand() % (int)arrSize;
	}
	
	return arr;
}
/******************************************************************************************************/
void keyDestroy(void *_key)
{
	return;
}
/******************************************************************************************************/
void valDestroy(void *_value)
{
	return;
}
/******************************************************************************************************/
/******************************************************************************************************/
UNIT(hash_Create_Test)
	HashMap* hash = NULL;

	hash =  HashMapCreate(10, idiotHash, IsEqual);
	ASSERT_THAT(hash != NULL);
	HashMapDestroy(&hash, keyDestroy,valDestroy );
	ASSERT_THAT(NULL == hash);
	hash = HashMapCreate(0, idiotHash, IsEqual);
	ASSERT_THAT(hash == NULL);
	hash = HashMapCreate(8, NULL, IsEqual);
	ASSERT_THAT(hash == NULL);
	hash = HashMapCreate(8, idiotHash, NULL);
	ASSERT_THAT(hash == NULL);

END_UNIT
/******************************************************************************************************/
UNIT(Hash_Insert_Test)
	HashMap* hash = NULL;
	int* ptr = NULL;
	size_t arrSize=0;
	int array[5]={90, 17, 30, 125,133};

	hash =  HashMapCreate(10, idiotHash, IsEqual);
	ASSERT_THAT(hash != NULL);
	assert(HashSize(hash)== 11);

	arrSize = 10;
	ptr = valueAndKeyCreator(arrSize);

	ptr[0]=88; /*0*/
	ptr[1] = 88; /*0*/
	ptr[2] = 90; /*2*/
	ptr[3] = 17; /*6*/
	ptr[4] = 18; /*7*/
	ptr[5] = 19; /*8*/
	ptr[6]  = 30; /*8*/

	ASSERT_THAT(HashMapInsert(hash, &ptr[0], &ptr[0]) == MAP_SUCCESS);
	ASSERT_THAT(HashMapInsert(hash, &ptr[1], &ptr[1]) == MAP_KEY_DUPLICATE_ERROR);
	

	ASSERT_THAT(HashMapInsert(hash, &ptr[2], &ptr[2]) == MAP_SUCCESS);
	ASSERT_THAT(HashMapInsert(hash, &ptr[3], &ptr[3]) == MAP_SUCCESS);
	ASSERT_THAT(HashMapInsert(hash, &ptr[4], &ptr[4]) == MAP_SUCCESS);
	ASSERT_THAT(HashMapInsert(hash, &ptr[5], &ptr[5]) == MAP_SUCCESS);

	/*check hash size*/
	/**ASSERT_THAT ( HashMapSize(hash) == 5);*/
	ASSERT_THAT(HashMapInsert(hash, &ptr[6], &ptr[6]) == MAP_SUCCESS);     
	ASSERT_THAT(HashMapInsert(hash, &array[0], &array[0]) == MAP_KEY_DUPLICATE_ERROR);
	ASSERT_THAT(HashMapInsert(hash, &array[1], &array[1]) == MAP_KEY_DUPLICATE_ERROR);
	ASSERT_THAT(HashMapInsert(hash, &array[2], &array[2]) == MAP_KEY_DUPLICATE_ERROR);
	ASSERT_THAT(HashMapInsert(hash, &array[3], &array[3]) == MAP_SUCCESS);
	ASSERT_THAT(HashMapInsert(hash, &array[4], &array[4]) == MAP_SUCCESS);

	
	HashMapDestroy(&hash, keyDestroy,valDestroy);
	free(ptr);

END_UNIT
/******************************************************************************************************/
/******************************************************************************************************/
UNIT(Hash_Remove_Test)
HashMap *hash = NULL;
int *ptr = NULL;
size_t arrSize = 0;
int array[7] = {90, 17, 30, 125, 133,777,951};

void* rm_key=NULL;
void* rm_val=NULL;


hash = HashMapCreate(10, idiotHash, IsEqual);
ASSERT_THAT(hash != NULL);
assert(HashSize(hash) == 11);

arrSize = 10;
ptr = valueAndKeyCreator(arrSize);

ptr[0] = 88; /*0*/
ptr[1] = 88; /*0*/
ptr[2] = 90; /*2*/
ptr[3] = 17; /*6*/
ptr[4] = 18; /*7*/
ptr[5] = 19; /*8*/
ptr[6] = 30; /*8*/

ASSERT_THAT(HashMapInsert(hash, &ptr[0], &ptr[0]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[1], &ptr[1]) == MAP_KEY_DUPLICATE_ERROR);

ASSERT_THAT(HashMapInsert(hash, &ptr[2], &ptr[2]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[3], &ptr[3]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[4], &ptr[4]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[5], &ptr[5]) == MAP_SUCCESS);


ASSERT_THAT(HashMapInsert(hash, &ptr[6], &ptr[6]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &array[0], &array[0]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[1], &array[1]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[2], &array[2]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[3], &array[3]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &array[4], &array[4]) == MAP_SUCCESS);


/*remove section*/
ASSERT_THAT((HashMapRemove(hash, &array[5], &rm_key, &rm_val)) == MAP_KEY_NOT_FOUND_ERROR);
ASSERT_THAT((HashMapRemove(hash, &array[6], &rm_key, &rm_val)) == MAP_KEY_NOT_FOUND_ERROR);



HashMapDestroy(&hash, keyDestroy, valDestroy);
free(ptr);

END_UNIT

/******************************************************************************************************/
UNIT(Hash_Find_Test)
HashMap *hash = NULL;
int *ptr = NULL;
size_t arrSize = 0;
int array[8] = {90, 17, 30, 125, 133,777,951,1024};

void* rm_key=NULL;
void* rm_val=NULL;

void* _pValue=NULL;

hash = HashMapCreate(10, idiotHash, IsEqual);
ASSERT_THAT(hash != NULL);
assert(HashSize(hash) == 11);

arrSize = 10;
ptr = valueAndKeyCreator(arrSize);

ptr[0] = 88; /*0*/
ptr[1] = 88; /*0*/
ptr[2] = 90; /*2*/
ptr[3] = 17; /*6*/
ptr[4] = 18; /*7*/
ptr[5] = 19; /*8*/
ptr[6] = 30; /*8*/

ASSERT_THAT(HashMapInsert(hash, &ptr[0], &ptr[0]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[1], &ptr[1]) == MAP_KEY_DUPLICATE_ERROR);

ASSERT_THAT(HashMapInsert(hash, &ptr[2], &ptr[2]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[3], &ptr[3]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[4], &ptr[4]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &ptr[5], &ptr[5]) == MAP_SUCCESS);



ASSERT_THAT(HashMapInsert(hash, &ptr[6], &ptr[6]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &array[0], &array[0]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[1], &array[1]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[2], &array[2]) == MAP_KEY_DUPLICATE_ERROR);
ASSERT_THAT(HashMapInsert(hash, &array[3], &array[3]) == MAP_SUCCESS);
ASSERT_THAT(HashMapInsert(hash, &array[4], &array[4]) == MAP_SUCCESS);



ASSERT_THAT(HashMapFind(hash, &array[4], &_pValue) == MAP_SUCCESS);
ASSERT_THAT(*((int*)_pValue) == array[4]);

ASSERT_THAT(HashMapFind(hash, &array[3], &_pValue) == MAP_SUCCESS);
ASSERT_THAT(*((int*)_pValue) == array[3]);

ASSERT_THAT(HashMapFind(hash, &array[4], &_pValue) == MAP_SUCCESS);
ASSERT_THAT(*((int*)_pValue) == array[4]);

ASSERT_THAT(HashMapFind(hash, &array[7], &_pValue) == MAP_KEY_NOT_FOUND_ERROR);
ASSERT_THAT(((int*)_pValue) == NULL);





ASSERT_THAT((HashMapRemove(hash, &array[5], &rm_key, &rm_val)) == MAP_KEY_NOT_FOUND_ERROR);
ASSERT_THAT((HashMapRemove(hash, &array[6], &rm_key, &rm_val)) == MAP_KEY_NOT_FOUND_ERROR);

/**ASSERT_THAT(HashMapSize(hash) == 8);*/


ASSERT_THAT((HashMapRemove(hash, &array[3], &rm_key, &rm_val)) == MAP_SUCCESS);
ASSERT_THAT( *(int*)rm_key == array[3]);
ASSERT_THAT( *(int*)rm_val == array[3]);

ASSERT_THAT(HashMapFind(hash, &array[3], &_pValue) == MAP_KEY_NOT_FOUND_ERROR);



ASSERT_THAT((HashMapRemove(hash, &array[4], &rm_key, &rm_val)) == MAP_SUCCESS);
ASSERT_THAT( *(int*)rm_key == array[4]);
ASSERT_THAT( *(int*)rm_val == array[4]);

ASSERT_THAT(HashMapFind(hash, &array[4], &_pValue) == MAP_KEY_NOT_FOUND_ERROR);


HashMapDestroy(&hash, keyDestroy, valDestroy);
free(ptr);

END_UNIT


void PrintStat(MapStats stat)
{
	printf("Pairs num:      	%lu\n",stat.pairs);
	printf("collisions num: 	%lu\n",stat.collisions);
	printf("buckets num:    	%lu\n",stat.buckets);
	printf("Chains  num:    	%lu\n",stat.chains);
	printf("max Chains num:    	%lu\n",stat.maxChainLength);
	printf("avg Chains len:    	%lu\n",stat.averageChainLength);
}

/**********************************************************************/
UNIT(Re_Hashing_Test)
HashMap *hash = NULL;

int i;
int *ptr=NULL;
size_t rehashsize = 2048;
size_t cap = 1024, arrSize = 4096;
/*
MapStats stat = {0, 0, 0, 0, 0, 0};	
*/


hash = HashMapCreate(cap, idiotHash, IsEqual);
ASSERT_THAT(hash != NULL);
/*
printf("Hash Size :: %lu\n", HashSize(hash));
*/


ptr = valueAndKeyCreator(arrSize);
for(i = 0; i < 12; ++i)
{
	ASSERT_THAT(&ptr[i] != NULL);
	HashMapInsert(hash, &ptr[i], &ptr[i]);
}

/*

stat = HashMapGetStatistics(hash);
PrintStat(stat);
*/

ASSERT_THAT(HashMapRehash(hash, rehashsize) == MAP_SUCCESS);
/*
printf("Hash Size :: %lu\n", HashSize(hash));
stat = HashMapGetStatistics(hash);
PrintStat(stat);*/
HashMapDestroy(&hash, keyDestroy, valDestroy);
free(ptr);

END_UNIT

/**********************************************************************/
TEST_SUITE(HashMap Generic Test)
TEST(ssssrand)
TEST(hash_Create_Test)
TEST(Hash_Insert_Test)
TEST(Hash_Remove_Test)
TEST(Hash_Find_Test)
TEST(Re_Hashing_Test)
END_SUITE
/******************************************************************************************************/
