#ifndef __WATCHER_H_
#define __WATCHER_H_


typedef enum Watcher_Status{
	WATCHER_SUCCESS = 0,
	WATCHER_DIR_WATCHING_ERROR,
	WATCHER_ALLOCATION_ERROR,
	WATCHER_INOTIFY_INIT_ERROR,
	WATCHER_NOT_INITIALIZED
	
}Watcher_Status;


typedef struct Watcher Watcher;

#include <stddef.h>


Watcher* WatcherCreate(const char* _parserPath, const char* _cdrsPath, const char* _channelName);

/** Watcher* WatcherCreate(const char* _parserPath, const char* _cdrsPath, size_t _filesPerMinute, void* _channel);
**/


/** 
void WatcherDestroy(Watcher** _watcher, void(*ChannelDestroy)(void**));
**/
void WatcherDestroy(Watcher** _watcher);



Watcher_Status WatcherStartWatching(Watcher* _watcher);

Watcher_Status WatcherPauseWatching(Watcher* _watcher);

Watcher_Status WatcherResumeWatching(Watcher* _watcher);

Watcher_Status WatcherShutDown(Watcher* _watcher);




#endif /*__WATCHER_H_*/
