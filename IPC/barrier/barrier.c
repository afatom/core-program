#include "barrier.h"
#include <stdlib.h>
#include <pthread.h>

#define SUCCESS 0
#define FAIL 1

#define BARRIER_IS_VALID 0xBEEFBEEF
#define BARRIER_IS_INVALID 0xDEADBEEF

/**********************************************************************/
struct Barrier{
	size_t m_magic;
	size_t m_latingThreads;
	size_t m_count;
	pthread_cond_t m_cv;	
	pthread_mutex_t m_mutex;
	};



/**********************************************************************/
static void CvAndMutexDestroy(Barrier* _bar)
{
	pthread_cond_destroy(&_bar->m_cv);
	pthread_mutex_destroy(&_bar->m_mutex);
	return;
}


/**********************************************************************/
static int BarrierInit(Barrier* _bar, const size_t _count)
{
	if (pthread_mutex_init(&_bar->m_mutex, NULL) != 0 )
	{
		return FAIL;
	}
	
	if(pthread_cond_init(&_bar->m_cv, NULL)!= 0)
	{
		pthread_mutex_destroy(&_bar->m_mutex);
		return FAIL;
	}
	_bar->m_count = _count;
	_bar->m_latingThreads = (size_t)_count;
	_bar->m_magic = BARRIER_IS_VALID;
	return SUCCESS;
}
/**********************************************************************/
Barrier* BarrierCreate(const size_t _count)
{
	Barrier* bar = NULL;
	
	if(_count == 0)
	{
		return NULL;
	}
	
	bar = (Barrier*)malloc(sizeof(Barrier));
	if(NULL == bar)
	{
		return bar;
	}
	
	if((BarrierInit(bar,_count)) != SUCCESS)
	{
		free(bar);
		return NULL;
	}
	
	return bar;
}

/**********************************************************************/
void BarrierDestroy(Barrier** _barrier)
{
	if(NULL == _barrier || NULL == *_barrier || (*_barrier)->m_magic != BARRIER_IS_VALID)
	{
		return;
	}
	/** Release waiting threads before destroy*/
	pthread_cond_broadcast(&(*_barrier)->m_cv);
	
	(*_barrier)->m_magic = BARRIER_IS_INVALID;
	CvAndMutexDestroy(*_barrier);
	free(*_barrier);
	*_barrier = NULL;
}

/**********************************************************************/
Barrier_Result BarrierWait(Barrier* _barrier)
{
	if(NULL == _barrier || _barrier->m_magic != BARRIER_IS_VALID)
	{
		return BARRIER_NOT_INITIALIZED;
	}
	
	if((pthread_mutex_lock(&_barrier->m_mutex))!=0)
	{
		return BARRIER_INTERNAL_ERROR;
	}
	
	while(--_barrier->m_latingThreads != 0)
	{
		pthread_cond_wait(&_barrier->m_cv, &_barrier->m_mutex);
	}
	
	_barrier->m_latingThreads = _barrier->m_count; /*for future usess*/
	/*wake the basterds*/
	pthread_mutex_unlock(&_barrier->m_mutex);
	pthread_cond_broadcast(&_barrier->m_cv);
	
	return BARRIER_SUCCESS;
	
}
/**********************************************************************/

