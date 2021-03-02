#include <stdlib.h>
#include "aggregator.h"
#include "distributor.h"
#include <pthread.h>


struct Distributor{
	size_t m_aggregatorsNum;
	Aggregator** m_aggregatorsArray;
	pthread_mutex_t m_mutex;
	};


Distributor* DistributorCreate(Aggregator** _aggregatorsArray, size_t _aggregatorsNum)
{
	Distributor* ptr = NULL;
	if(!_aggregatorsNum || !*_aggregatorsArray)
	{
		return NULL;
	}
	
	ptr = (Distributor*)calloc(1,sizeof(Distributor));
	if(!ptr)
	{
		return NULL;
	}
	
	if(pthread_mutex_init(&(ptr->m_mutex),NULL))
	{
		free(ptr);
		return NULL;
	}
	ptr->m_aggregatorsNum = _aggregatorsNum;
	ptr->m_aggregatorsArray = _aggregatorsArray;
	
	return ptr;
}

/*
Aggregator** DistributorDestroy(Distributor** _distributor)
{
	Aggregator** ptr;
	
	if(!_distributor || !*_distributor)
	{
		return;
	}
	
	ptr = (*_distributor)->m_aggregatorsArray;
	pthread_mutex_destroy(&((*_distributor)->m_mutex));
	free(*_distributor);
	*_distributor = NULL; 
	return;
}
*/


void DistributorDestroy(Distributor** _distributor, Aggregator*** _retvalAggregatorsArray)
{
	
	if(!_distributor || !*_distributor || !_retvalAggregatorsArray )
	{
		return;
	}
	
	*_retvalAggregatorsArray = (*_distributor)->m_aggregatorsArray;
	pthread_mutex_destroy(&((*_distributor)->m_mutex));
	free(*_distributor);
	*_distributor = NULL; 
	return;
}



Distributor_Status DistributorInsert(Distributor* _distributor, void* _data)
{
	size_t j =0;
	/*Thread safety - Lock Function*/
	if(pthread_mutex_lock(&(_distributor->m_mutex)))
	{
		return DISTRIBUTOR_THREAD_SAFETY_ERROR;
	}
	
	if(!_distributor)
	{
		return DISTRIBUTOR_NOT_INITIALIZED_ERROR;
	}
	
	if(!_data)
	{
		return DISTRIBUTOR_NULL_DATA_INPUT;
	}
	
	for(j = 0; j < _distributor->m_aggregatorsNum; ++j)
	{
		if((AggregatorInsertCdr(_distributor->m_aggregatorsArray[j], _data)) != AGGREGATOR_SUCCESS)
		{
			return DISTRIBUTOR_RECEIVED_ERROR_WHILE_DATA_PASSING;
		}
	}
	/*Thread safety/MT Enabling - UnLock Function*/
	if(pthread_mutex_unlock(&(_distributor->m_mutex)))
	{
		return DISTRIBUTOR_THREAD_SAFETY_ERROR;
	}
	
	return DISTRIBUTOR_SUCCESS;
}



