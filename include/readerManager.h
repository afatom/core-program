#ifndef __READERMANAGER_H_
#define __READERMANAGER_H_


typedef enum ReaderManager_Status{
	READERMANAGER_SUCCESS =0,
	READERMANAGER_ALLOCATION_ERROR,
	READERMANAGER_PAUSE_ERROR,
	READERMANAGER_SHUTDOWN_ERROR,
	READERMANAGER_NOT_INTIALIZED_ERROR,
	READERMANAGER_THREAD_CREATING_ERROR
	
	}ReaderManager_Status;




typedef struct ReaderManager ReaderManager;


ReaderManager* ReaderManagerCreate(const char* _configFile);

void ReaderManagerDestroy(ReaderManager** _pReaderManager);

ReaderManager_Status ReaderManagerPause(ReaderManager* _readerManager);

ReaderManager_Status ReaderManagerStart(ReaderManager* _readerManager);


ReaderManager_Status ReaderManagerResume(ReaderManager* _readerManager);

ReaderManager_Status ReaderManagerShutDown(ReaderManager* _readerManager);






#endif /*__READERMANAGER_H_*/
