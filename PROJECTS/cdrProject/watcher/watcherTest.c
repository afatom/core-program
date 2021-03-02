#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "channel.h"
#include "watcher.h"
#include <assert.h>
#include "parser.h"
#include "cdr.h"


void _ChanDest(void** _chan)
{
	ChannelDestroy((Channel**)_chan);
}

int main (void)
{
	Channel* ptr = ChannelCreate("MS880Q987",4096,CHANNEL_CREATE);
	Watcher* wt = WatcherCreate("ert", "/home/adhamfaris/work/PROJECTS/cdrProject/cdrs", 15, ptr);
	assert(wt!=NULL);
	
	
	WatcherStartWatching(wt);
	
	
	WatcherDestroy(&wt, _ChanDest);
	assert(wt==NULL);
	
return 0;	
}
