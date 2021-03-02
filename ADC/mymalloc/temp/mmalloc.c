#include "mmalloc.h"
#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <assert.h>

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

struct Pool{
	void* 	m_next;
	size_t 	m_magic;
	size_t 	m_buffSize;
	size_t 	m_numOfBuffs;
	size_t 	m_allocatedCounter;
};



Pool* MmallocCreate(size_t _buffSize, size_t _numOfBuffs)
{

	
	size_t fixedSize=0;
	Pool* pool = NULL;
	int* stPool=NULL;

	
	#ifdef NDEBUG
	printf("mmalloc.c Line 32::sizeof Pool: %lu\n",sizeof(struct Pool) );
	#endif
		
	if(_buffSize==0 || _numOfBuffs==0 )
	{
		return NULL;
	}
	
	if((_buffSize + sizeof(int)) % sizeof(void*)==0)
	{
		fixedSize = _buffSize+sizeof(int);
	}
	else
	{
		fixedSize = _buffSize + sizeof(int) + OPTIONAL_PADDING_BUFFER + 
		sizeof(void*) - ((OPTIONAL_PADDING_BUFFER + _buffSize + sizeof(int)) % sizeof(void*));
	
	}
	/*calloc*/
	pool = (Pool*)calloc((sizeof(struct Pool)+fixedSize*_numOfBuffs),sizeof(char)); /*pool pointer*/
	
	pool->m_buffSize = fixedSize;
	pool->m_numOfBuffs = (sizeof(struct Pool)+fixedSize*_numOfBuffs);
	pool->m_allocatedCounter = 0;
	pool->m_magic = VALID_POOL;
	
	stPool=(int*)pool;
	stPool = stPool + sizeof(struct Pool);
	
	/*stPool=pool;*/
	pool->m_next = (void*)stPool;
	
	#ifdef NDEBUG
	printf("mmaloc Line 75::Pool Pointer: %p stPool Pointer: %p sizeof(Pool):%lu\n",(void*)pool,(void*)stPool,sizeof(struct Pool) );
	#endif
	
	
	return pool;
}


void MmallocDestroy(Pool** _pool)
{
	assert(NULL != _pool);
	assert(NULL != *_pool);
	
	if(NULL == _pool || NULL == *_pool || (*_pool)->m_magic != VALID_POOL)
	{
		puts("@@");
		return; 
	}
	puts("########");
	
	#ifdef NDEBUG
	printf("Line 121::Pool Pointer: %p\n",(void*)*_pool);
	#endif
	(*_pool)->m_magic = INVALID_POOL;
	free(*_pool);
	*_pool=NULL;
	
	#ifdef NDEBUG
	printf("Line 135::Pool Pointer: %p\n",(void*)*_pool);
	#endif
	
}




/*|__Pool Header__|>>Flag_cha,____Buff_____<<|,,,,,,,,,,,,*/

void* MyMalloc(Pool* _pool)
{
	void* current =NULL;
	size_t i =0;
	if(NULL == _pool || _pool->m_magic != VALID_POOL)
	{
		return NULL;
	}
	current = _pool->m_next;
	
	while(i < _pool->m_numOfBuffs)
	{
		if((int*)current == EMPTY_BUFFER)
		{
			*((int*)current)=ALLOCATED_BUFFER; /*assign it as allocated buffer*/
			current=(int*)current +1; 
			++_pool->m_allocatedCounter;
			current = (int*)((int*)current +_pool->m_buffSize);
			return (void*)((int*)current);
		}
		/*
		if( _pool->m_numOfBuffs - _pool->m_allocatedCounter > 0)
		{
			current = _pool->m_next;
			_pool->m_next = (Node*)(_pool->m_next +_pool->m_buffSize);
			++_pool->m_allocatedCounter;
			return current;
		}
		*/
		current = (int*)((int*)current +_pool->m_buffSize);
		++i;
	}
	
	return NULL;
}


void MyFree(void* _buff)
{
	int* encr = NULL;
	if(NULL == _buff)
	{
		return;
	}
	
	encr = (int*)_buff;
	--encr;
	*(encr)=EMPTY_BUFFER;
	return;	
}





void PrintPool(Pool* _pool)
{
	void* current =NULL;
	size_t i =0;
	
	if(NULL == _pool)
	{
		puts("Pool Not Exist!");
	}
	
	current = _pool->m_next;
	
	while(i < _pool->m_numOfBuffs)
	{
		printf("%d ", *((char*)current));	
		current=(char*)current +1; 
		++i;
	}
	puts("\n");
	return;
}









