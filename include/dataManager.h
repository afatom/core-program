#ifndef __DATAMANAGER_H_
#define __DATAMANAGER_H_

typedef enum DataManager_Status{
	DATAMANAGER_SUCCESS=0,
	DATAMANAGER_ALLOCATION_FAILURE,
	DATAMANAGER_NOT_INITIALIZED,
	DATAMANAGER_COMM_ERROR_ON_DATA_CHANNEL,
	DATAMANAGER_RECEIVER_MT_ERROR
	}DataManager_Status;



typedef struct DataManager DataManager;


DataManager* DataManagerCreate(const char* _configFile);

void DataManagerDestroy(DataManager** _dataManager);

DataManager_Status DataManagerRun(DataManager* _dataManager);
#endif /** __DATAMANAGER_H_*/
