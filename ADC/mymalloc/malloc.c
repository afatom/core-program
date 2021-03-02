#include "mmalloc.h"
#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <assert.h>





#define UNVALID_PARAMS 0
#define VALID_PARAMS 1


#define VALID_POOL 	0xBEEFBEEF
#define INVALID_POOL 0xDEADBEEF

#define SPACE 16

#define BUFFER_HEADER_FLAG 8 /*<< sizeof int*/
#define ALLOCATED_BUFFER 1
#define EMPTY_BUFFER 0
#define OPTIONAL_PADDING_BUFFER 8

#define NDEBUG
/*
struct Node{
	Node* m_next;
};*/
/******************************************************************************/

struct Pool{
	void* 	m_next;
	size_t 	m_buffSize;
	size_t 	m_numOfBuffs;
	size_t 	m_freeBuffers;
};

/******************************************************************************/

static int CheckMalocCreateParams(size_t _buffSize, size_t _numOfBuffs)
{
	if(_buffSize==0 || _numOfBuffs==0 )
	{
		return UNVALID_PARAMS;
	}
	return VALID_PARAMS;
}

/******************************************************************************/
static size_t AlignBuffSize(size_t _buffSize)
{
	while((_buffSize % sizeof(void*)))
	{
		++_buffSize;
	}
	return _buffSize;
}
/******************************************************************************/
static void PoolStructInit(Pool* _pool,size_t _buffSize, size_t _numOfBuffs, void* _next)
{
	_pool->m_next = _next;
	_pool->m_buffSize = _buffSize;
	_pool->m_numOfBuffs = _numOfBuffs;
	_pool->m_freeBuffers = _numOfBuffs;
	return;
}

/******************************************************************************/
Pool* MmallocCreate(size_t _buffSize, size_t _numOfBuffs)
{
	size_t alignSize = 0;
	Pool* pool = NULL;
	
	if (CheckMalocCreateParams(_buffSize, _numOfBuffs) != VALID_PARAMS)
	{
		return NULL;	
	}
	
	alignSize = AlignBuffSize(_buffSize);
	pool = (Pool*)calloc((sizeof(struct Pool)+alignSize*_numOfBuffs),sizeof(char));
	PoolStructInit(pool, alignSize, _numOfBuffs, (void*)(pool + 1));
	return pool;
}
/******************************************************************************/
void MmallocDestroy(Pool** _pool)
{
	assert(NULL != _pool);
	assert(NULL != *_pool);
	
	if(NULL == _pool || NULL == *_pool)
	{
		return; 
	}

	/*(*_pool)->m_magic = INVALID_POOL;*/
	free(*_pool);
	*_pool=NULL;
	return;
}
/******************************************************************************/
void* MyMalloc(Pool* _pool)
{
	void* ptr = _pool->m_next; 
	
	if(NULL == _pool || _pool->m_freeBuffers == 0)
	{
		return NULL;
	}
	
	--_pool->m_freeBuffers;
	_pool->m_next = (void*)((int*)_pool->m_next + _pool->m_buffSize);
	
	return ptr;
}
/******************************************************************************/
void MyFree(Pool* _pool, void* _pBuffer)
{
	void* temp = NULL;
	
	if(NULL == _pBuffer || NULL == _pool)
	{
		return;
	}
	++_pool->m_freeBuffers;
	temp = (void*)_pool->m_next;
	_pool->m_next = _pBuffer;
	_pBuffer = temp;
	return;
}
/******************************************************************************/
size_t FreeBufsNum(Pool* _pool)
{
	if(NULL == _pool)
		return 0;
	return _pool->m_freeBuffers;
}
/******************************************************************************/






