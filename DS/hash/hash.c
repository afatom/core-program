#include "hash.h"
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

/*#define HashFunc (value) ((value)>=0 ? (value):-(value))*/

#define MAGIC 9874562541
#define REMOVED -1
#define EMPTY_ADRESS 0

struct Hash {
    size_t  m_magicNumber;
    int*    m_data;
    size_t  m_originalSize;
    size_t  m_hashSize;
    size_t  m_maxCollisions;
    size_t  m_numberOfInsertions;
    size_t  m_totalCollisions;
};

static size_t HashFunc(const Hash* _hash, int _num);
static size_t ModHashFunc(const Hash *_hash, int _num);
static size_t TurnToPrime(size_t _num);

Hash* HashCreate(size_t _size)
{
    Hash *hashPtr = NULL;
    if(0 == _size)
    {
        return NULL;
    }
    hashPtr = (Hash*)malloc(sizeof(Hash));
    if(NULL == hashPtr)
    {
        return NULL;
    }
    hashPtr->m_data = (int*)calloc((_size * 13)/10, sizeof(int));
    if(NULL == hashPtr)
    {
        free(hashPtr);
        return NULL;
    }
    /*struct initialize*/
    hashPtr->m_magicNumber = MAGIC;
    hashPtr->m_originalSize = _size;
    hashPtr->m_hashSize = (_size * 13)/10; /*TODO convert to prime size*/
    hashPtr->m_maxCollisions = 0;
    hashPtr->m_numberOfInsertions = 0;
    hashPtr->m_totalCollisions = 0;
    return hashPtr;
}

void HashDestroy(Hash* _hash)
{
    if (NULL == _hash || _hash->m_magicNumber == 0)
    {
        return;
    }
    _hash->m_magicNumber = 0;
    free(_hash->m_data);
    free(_hash);
}

size_t HashNumOfItems(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }
    return _hash->m_numberOfInsertions;
}

size_t HashCapacity(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }
    return _hash->m_originalSize;
}

double HashAverageCollisions(const Hash* _hash)
{
    if(NULL == _hash || _hash->m_numberOfInsertions == 0)
    {
        return 0;  /*Null case*/
    }
    return ((double)_hash->m_totalCollisions/(double)_hash->m_numberOfInsertions);
}

size_t HashMaxCollisions(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }
    return _hash->m_maxCollisions;
}

void HashPrint(const Hash* _hash)
{
    size_t i;
    if(NULL == _hash)
    {
        puts("Empty Hash!");
        return;
    }
    for(i = 0; i < _hash->m_hashSize; ++i)
    {
        printf("%2lu ",i);
    }
    printf("\n");
    for(i = 0; i < _hash->m_hashSize; ++i)
    {
        printf("%2d ",_hash->m_data[i]);
    }
    puts("\n");
}

ADTErr HashInsert(Hash* _hash, int _data)
{
    size_t insertionIndex, startIndex, collisionsCounter, i;
    if(_data == 0 || _data == -1)
    {
        return ERR_INVALID_DATA;
    }

    if (NULL == _hash)
    {
        return ERR_NOT_INITIALIZED;
    }

    if(_hash->m_numberOfInsertions == _hash->m_originalSize)
    {
        return ERR_OVERFLOW;
    }
    /*call hash func*/
    insertionIndex = HashFunc(_hash, _data);
    switch(_hash->m_data[insertionIndex])
    {
        /*panoi*/
        case(EMPTY_ADRESS):
        _hash->m_data[insertionIndex] = _data;
        ++_hash->m_numberOfInsertions; 
        break;

        /*was and erased*/
        case(REMOVED):
        startIndex = insertionIndex; /*save this index*/
        /*size_t collisionsCounter = 0;*/
        i = 0;
        while (i <= _hash->m_maxCollisions)
        {
            if(_hash->m_data[insertionIndex] == _data)
            {
                return ERR_DATA_EXIST;
            }
            /*++collisionsCounter;*/
            insertionIndex = (insertionIndex + 1) % _hash->m_hashSize;
            ++i;
        }
        _hash->m_data[startIndex] = _data;
        ++_hash->m_numberOfInsertions; 
        /*Tafoos*/
        default:
        collisionsCounter = 0; 
        startIndex = insertionIndex;
        while(_hash->m_data[startIndex] != 0)
        {
            if(_hash->m_data[startIndex] == _data)
            {
                return ERR_DATA_EXIST;
            }
            ++collisionsCounter;
            ++_hash->m_totalCollisions;
            ++startIndex;
        }
        _hash->m_data[startIndex] = _data;
        ++_hash->m_numberOfInsertions; 
        if(collisionsCounter > _hash->m_maxCollisions)
        {
            _hash->m_maxCollisions = collisionsCounter;
        }
        break;
    }
    return ERR_OK;
}

ADTErr HashRemove(Hash* _hash, int _data)
{
    size_t erasingIndex, i;
    if(_data == 0 || _data == -1)
    {
        return ERR_INVALID_DATA;
    }

    if (NULL == _hash)
    {
        return ERR_NOT_INITIALIZED;
    }

    if(_hash->m_numberOfInsertions == 0)
    {
        return ERR_UNDERFLOW;
    }
    erasingIndex = HashFunc(_hash, _data);
    
    for (i = 0; i <= _hash->m_maxCollisions; ++i)
    {
        if(_hash->m_data[erasingIndex] == _data)
        {
            _hash->m_data[erasingIndex] = REMOVED;
            --_hash->m_numberOfInsertions;
            break;
        }
        if(_hash->m_data[erasingIndex] == EMPTY_ADRESS)
        {
            return ERR_DATA_DOES_NOT_EXIST;
        }
        
        erasingIndex = (erasingIndex + 1) % _hash->m_hashSize;
    }
    
    return ERR_OK;
}

int HashIsFound(const Hash* _hash, int _data)
{
    size_t erasingIndex, i;
    if(_data == 0 || _data == -1)
    {
        return 0;
    }

    if (NULL == _hash)
    {
        return 0;
    }

    if(_hash->m_numberOfInsertions == 0)
    {
        return 0;
    }

    erasingIndex = HashFunc(_hash, _data);
    for (i = 0; i <= _hash->m_maxCollisions; ++i)
    {
        if(_hash->m_data[erasingIndex] == _data)
        {
            return 1;
        }
        if(_hash->m_data[erasingIndex] == EMPTY_ADRESS)
        {
            return 0;
        }
        erasingIndex = (erasingIndex + 1) % _hash->m_hashSize;
    }
    
    return 0;
}










/*****************************************************************************/

static size_t HashFunc(const Hash* _hash, int _num)
{
    if(_num >= 0)
    {
        return (size_t)(_num) % (_hash->m_hashSize);
    }
    _num = _num * (-1);
    return (size_t)(_num) % (_hash->m_hashSize);
}
/*
static size_t ModHashFunc(const Hash *_hash, int _num)
{
    double a; size_t index;
    a = (sqrt(5) - 1)/2;
    index = (size_t)(((size_t)(_num * a) % _hash->m_hashSize));
    return index;

}
*/
/*
static size_t TurnToPrime(size_t _num)
{
	double root;
	size_t i = 2;
	
	(size_t)(root) = sqrt(_num);
	while (1)
	{
		while(i <= root)
		{
			if(_num % i == 0)
			{
			
			}
		}	
	}
}
*/








