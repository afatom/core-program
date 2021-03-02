#ifndef __QUERYMANAGER_H_
#define __QUERYMANAGER_H_

#include "aggregator.h"

typedef enum QueryManager_Status {
	QUERYMANAGER_SUCCESS   =0,
	QUERYMANAGER_CHANNEL_COMM_UI_ERROR,
	QUERYMANAGER_NOT_INITIALIZED,
	QUERYMANAGER_ALLOCATION_ERROR,
	QUERYMANAGER_THREAD_CREATE_ERROR,
	QUERYMANAGER_THREAD_JOIN_ERROR
	
	}QueryManager_Status;

typedef struct QueryManager QueryManager; 

QueryManager* QueryManagerCreate(Aggregator** _aggregatorsArray, const char* _uiChannelName);

void QueryManagerDestroy(QueryManager** _pQueryManager, Aggregator*** _retvalAggregatorsArray);



QueryManager_Status QueryManagerStartListening(QueryManager* _queryManager);

 




#endif /** __QUERYMANAGER_H_*/
