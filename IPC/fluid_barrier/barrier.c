#include "FluidBarrier.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NDEBUG

#define SUCCESS 1
#define FAIL 0


/********************************************************************************************************/
struct Barrier{
	size_t m_threadsNumAtFirstBarrier;
	size_t m_threadsNumAtSecBarrier; 	
	size_t m_threadsCounterAtFirstBarrier;	
	size_t m_threadsCounterAtSecBarrier;
	size_t m_gatesLock;
	pthread_cond_t m_firstBarrierCV;
	pthread_cond_t m_secBarrierCV;	
	pthread_mutex_t m_firstBarrierMutex;
	pthread_mutex_t m_secBarrierMutex;
	};

/********************************************************************************************************/
static Barrier_Result WaitAtFirstBarrier(Barrier* _barrier);
static Barrier_Result WaitAtSecBarrier(Barrier* _barrier);
/********************************************************************************************************/

static void CvAndMutexDestroy(Barrier* _bar)
{
	pthread_cond_destroy(&_bar->m_firstBarrierCV);
	pthread_cond_destroy(&_bar->m_secBarrierCV);
	
	pthread_mutex_destroy(&_bar->m_firstBarrierMutex);
	pthread_mutex_destroy(&_bar->m_secBarrierMutex);
	
	return;
}

/********************************************************************************************************/
static int BarrierInit(Barrier* _bar, const size_t _threadsNumAtFirstBarrier, const size_t _threadsNumAtSecBarrier)
{
	if (pthread_mutex_init(&_bar->m_firstBarrierMutex, NULL) != 0 )
	{
		return FAIL;
	}
	
	if (pthread_mutex_init(&_bar->m_secBarrierMutex, NULL) != 0 )
	{
		pthread_mutex_destroy(&_bar->m_firstBarrierMutex);
		return FAIL;
	}
	
	if(pthread_cond_init(&_bar->m_firstBarrierCV, NULL)!= 0)
	{
		pthread_mutex_destroy(&_bar->m_firstBarrierMutex);
		pthread_mutex_destroy(&_bar->m_secBarrierMutex);
		return FAIL;
	}
	
	if(pthread_cond_init(&_bar->m_secBarrierCV, NULL)!= 0)
	{
		pthread_mutex_destroy(&_bar->m_firstBarrierMutex);
		pthread_mutex_destroy(&_bar->m_secBarrierMutex);
		pthread_cond_destroy(&_bar->m_firstBarrierCV);
		return FAIL;
	}
	
	_bar->m_threadsNumAtFirstBarrier = _threadsNumAtFirstBarrier;
	_bar->m_threadsNumAtSecBarrier = _threadsNumAtSecBarrier;
	
	/**
	#ifdef NDEBUG
	printf("%lu \n",_bar->m_threadsCounterAtFirstBarrier);
	printf("%lu \n",_bar->m_threadsCounterAtSecBarrier);
	printf("%lu \n",_bar->m_gatesLock);
	#endif
	*/
	return SUCCESS;
}
/********************************************************************************************************/
static int BarrierCreateCheckArgs(const size_t _threadsNumAtFirstBarrier, const size_t _threadsNumAtSecBarrier)
{
	if(_threadsNumAtFirstBarrier == 0 || _threadsNumAtSecBarrier == 0 || _threadsNumAtSecBarrier > _threadsNumAtFirstBarrier)
	{
		return FAIL;
	}
	return SUCCESS;
}
/********************************************************************************************************/
Barrier* BarrierCreate(const size_t _threadsNumAtFirstBarrier, const size_t _threadsNumAtSecBarrier)
{
	Barrier* bar = NULL;
	
	if(!BarrierCreateCheckArgs(_threadsNumAtFirstBarrier, _threadsNumAtSecBarrier))
	{
		return NULL;
	}
	
	bar = (Barrier*)calloc(1,sizeof(Barrier));
	if(NULL == bar)
	{
		return bar;
	}
	
	if(!BarrierInit(bar, _threadsNumAtFirstBarrier, _threadsNumAtSecBarrier))
	{
		free(bar);
		return NULL;
	}
	
	return bar;
}
/********************************************************************************************************/

void BarrierDestroy(Barrier** _barrier)
{
	if(NULL == _barrier || NULL == *_barrier )
	{
		return;
	}
	/** Release waiting threads before destroy*/
	pthread_cond_broadcast(&(*_barrier)->m_firstBarrierCV);
	pthread_cond_broadcast(&(*_barrier)->m_secBarrierCV);
	
	CvAndMutexDestroy(*_barrier);
	free(*_barrier);
	*_barrier = NULL;
	return;
}

/********************************************************************************************************/

Barrier_Result BarrierWait(Barrier* _barrier)
{
	Barrier_Result stat;
	
	if(!_barrier)
	{
		return BARRIER_NOT_INITIALIZED_ERROR;
	}
	
	if((stat = WaitAtFirstBarrier(_barrier)) != BARRIER_SUCCESS)
	{
		return stat;
	}
	
	if((stat = WaitAtSecBarrier(_barrier)) != BARRIER_SUCCESS)
	{
		return stat;
	}
	
	return BARRIER_SUCCESS;
	
}
/********************************************************************************************************/

static Barrier_Result WaitAtFirstBarrier(Barrier* _barrier)
{

	
	if((pthread_mutex_lock(&_barrier->m_firstBarrierMutex))!=0)
	{
		return BARRIER_INTERNAL_ERROR;
	}
	
	while(++_barrier->m_threadsCounterAtFirstBarrier != _barrier->m_threadsNumAtFirstBarrier)
	{
		pthread_cond_wait(&_barrier->m_firstBarrierCV, &_barrier->m_firstBarrierMutex);
	}
	
	_barrier->m_threadsCounterAtFirstBarrier = 0; 

	pthread_mutex_unlock(&_barrier->m_firstBarrierMutex);

	pthread_cond_broadcast(&_barrier->m_firstBarrierCV);
	
	return BARRIER_SUCCESS;
}	
	
/********************************************************************************************************/

static Barrier_Result WaitAtSecBarrier(Barrier* _barrier)
{	
	if((pthread_mutex_lock(&_barrier->m_secBarrierMutex))!=0)
	{
		return BARRIER_INTERNAL_ERROR;
	}
	
	while(++_barrier->m_threadsCounterAtSecBarrier != _barrier->m_threadsNumAtSecBarrier)
	{
		pthread_cond_wait(&_barrier->m_secBarrierCV, &_barrier->m_secBarrierMutex);
	}
	
	_barrier->m_threadsCounterAtSecBarrier = 0; 

	pthread_mutex_unlock(&_barrier->m_secBarrierMutex);

	pthread_cond_broadcast(&_barrier->m_secBarrierCV);
	
	return BARRIER_SUCCESS;
}		
/********************************************************************************************************/






