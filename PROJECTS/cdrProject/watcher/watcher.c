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
#include "watcher.h"
#include "parser.h"
#include "cdr.h"

#define TRUE 1

static void handle_events(int fd, int *wd, const char* _fn);
/*********************************************************************************************************************************/

struct Watcher{ 
	const char* m_channelName;
	const char* m_parserPath;
	const char* m_cdrsPath;
	};


/*********************************************************************************************************************************/
static void WatcherInit(Watcher* pWatcher, const char* _parserPath, const char* _cdrsPath, const char* _channelName)
{
	pWatcher->m_channelName = _channelName;
	pWatcher->m_parserPath = _parserPath;
	pWatcher->m_cdrsPath = _cdrsPath;
	return;
}

/*********************************************************************************************************************************/
Watcher* WatcherCreate(const char* _parserPath, const char* _cdrsPath, const char* _channelName)
{
	Watcher* pWatcher = NULL;
	
	pWatcher = (Watcher*)malloc(sizeof(Watcher));
	if(!pWatcher)
	{
		return NULL;
	}
	
	WatcherInit(pWatcher, _parserPath, _cdrsPath, _channelName);
	return pWatcher;
}

/*********************************************************************************************************************************/
/**
void WatcherDestroy(Watcher** _watcher, void(*ChannelDestroy)(void**))
{
	Watcher* ptr = *_watcher;
	
	if(!(_watcher) || !(*_watcher) || !(*ChannelDestroy))
	{
		return;
	}
	
	ChannelDestroy(&(ptr->m_channel));
	free(ptr);
	*_watcher = NULL;
	return;
}**/


void WatcherDestroy(Watcher** _watcher)
{	
	if(!(_watcher) || !(*_watcher) )
	{
		return;
	}
	
	free(*_watcher);
	*_watcher = NULL;
	return;
}


/*********************************************************************************************************************************/
Watcher_Status WatcherStartWatching(Watcher* _watcher)
{
	char buf;
	int fd, i, poll_num, status = 0;
	int *wd;
	nfds_t nfds;
	struct pollfd fds[1];
	
	if(!_watcher)
	{
		return WATCHER_NOT_INITIALIZED;
	}
	
	/* Create the file descriptor for accessing the inotify API */

   fd = inotify_init1(IN_NONBLOCK);
   if (fd == -1) 
   {
	   perror("inotify_init1");
	   return WATCHER_INOTIFY_INIT_ERROR;
   }
   
   /* Allocate memory for watch descriptors */
   wd = calloc(1, sizeof(int));
   if (wd == NULL) {
	   perror("calloc mem error");
	   return WATCHER_ALLOCATION_ERROR;
   }
   
   /* Mark directories for events - only if file was created/added */

   *wd = inotify_add_watch(fd, _watcher->m_cdrsPath ,IN_CREATE);
   if (*wd == -1) 
   {
	   perror("inotify_add_watch::watching dir error");
	   free(wd);
	   return WATCHER_DIR_WATCHING_ERROR;
   }
   
	/* Prepare for polling */

   nfds = 1;

   /* Inotify input */
   fds[0].fd = fd;
   fds[0].events = POLLIN;
   
    /* Wait for cdr file events */
   while (TRUE) 
   {
	   poll_num = poll(fds, nfds, -1);
	   if (poll_num == -1) 
	   {
		   if (errno == EINTR) /*A signal occurred before any requested event */
		   {
			   continue;
		   }
		   else
		   {
				perror("poll");
				free(wd);
				return WATCHER_DIR_WATCHING_ERROR;
			}
	   }

	   if (poll_num > 0) 
	   {

		   if (fds[0].revents & POLLIN) 
		   {

			   /* Inotify events are available */

			   handle_events(fd, wd, _watcher->m_cdrsPath);
		   }
	   }
	}
   /* Close inotify file descriptor */
	close(fd);

   free(wd);
   return WATCHER_SUCCESS;
	
}

/*********************************************************************************************************************************/

/* Read inotify events from the file descriptor 'fd' only in new cdr file is arrived.
  wd is the table of watch descriptors 

  _fn is the path of  watched directory.
*/

static void handle_events(int fd, int *wd, const char* _fn)
{
   /* Some systems cannot read integer variables if they are not
	  properly aligned. On other systems, incorrect alignment may
	  decrease performance. Hence, the buffer used for reading from
	  the inotify file descriptor should have the same alignment as
	  struct inotify_event. */
char newFn[64];
char newCdrRelativePath[512];
pid_t pid;
char* args[5];
    char buf[4096]
	   __attribute__ ((aligned(__alignof__(struct inotify_event))));
   const struct inotify_event *event;
   int i;
   ssize_t len;
   char *ptr;

   /* Loop while events can be read from inotify file descriptor. */

   for (;;) {

	   /* Read some events. */

	   len = read(fd, buf, sizeof buf);
	   if (len == -1 && errno != EAGAIN) {
		   perror("read");
		   exit(EXIT_FAILURE);
	   }

	   /* If the nonblocking read() found no events to read, then
		  it returns -1 with errno set to EAGAIN. In that case,
		  we exit the loop. */

	   if (len <= 0)
		   break;

	   /* Loop over all events in the buffer */

	   for (ptr = buf; ptr < buf + len;
			   ptr += sizeof(struct inotify_event) + event->len) {

		   event = (const struct inotify_event *) ptr;

		   /* Print event type */

		   if (event->mask == IN_CREATE)
			   printf("IN_CREATE: ");

		   /* Print the name of the file */

		   if (event->len)
			{
			  
			   printf("%s\n", event->name);
			   sprintf(newFn,"%s", event->name);
			   printf("%s\n",newFn);
			   
			   strcpy(newCdrRelativePath,_fn);
			   strcat(newCdrRelativePath,"/");
			   strcat(newCdrRelativePath,newFn);
			   printf("%s\n",newCdrRelativePath);
			 

			   /* /home/adhamfaris/work/PROJECTS/cdrProject/parser/parserMain.o */
			   
			   pid = fork();
			   if(pid<0)
			   {
				   perror("fork fails");
				   return;
			   }
			   else if(pid == 0)
			   {
				   
				   args[0] = "/home/adhamfaris/work/PROJECTS/cdrProject/parser/parTest.out";
				   args[1] = "../cdrs/cdr.txt";
				   args[2] = "256";
				   args[3]= "MSGQQ123WE";
				   args [4] = NULL;
				   execv(args[0],args);
				  
			   }
			   /*
			   else
			   {
				   wait(NULL); 
			   }
			   */
			   
			   
			   /*
			   FILE* _fp;
			   _fp = fopen();*/
			}
		   /* Print type of filesystem object */

		   if (event->mask & IN_ISDIR)
			   printf(" [directory]\n");
		   else
			   printf(" [file]\n");
	   }
   }
}






Watcher_Status WatcherPauseWatching(Watcher* _watcher)
{
	if(!_watcher)
	{
		return WATCHER_NOT_INITIALIZED;
	}
	
	return WATCHER_SUCCESS;
}

Watcher_Status WatcherResumeWatching(Watcher* _watcher)
{
	if(!_watcher)
	{
		return WATCHER_NOT_INITIALIZED;
	}
	
	return WATCHER_SUCCESS;
}

Watcher_Status WatcherShutDown(Watcher* _watcher)
{
	if(!_watcher)
	{
		return WATCHER_NOT_INITIALIZED;
	}
	
	return WATCHER_SUCCESS;
}























/*






void CopyFile(const char* _readfileName, const char* _WrFileName);  
int DeleteCdrFile(const char* _fileName);
int main(int argc, char* argv[])
{
int status;
	char* slep = argv[1];
	int ss = atoi(argv[1]);

   const char s[2] = " ";
   char *token;
		
		DIR *dir;
		struct dirent *dp;
		char * file_name;
		char buff[256];
		dir = opendir("/home/adhamfaris/work/PROJECTS/cdrProject/test");
		while ((dp=readdir(dir)) != NULL) 
		{
		    //printf("debug: %s\n", dp->d_name);
		    if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
		    {
		        // do nothing (straight logic)
		    } else {
		        file_name = dp->d_name; // use it
		     
		        //printf("files_names: \"%s\"\n",file_name);
		       // sprintf(buff,"%s ",dp->d_name);
		       printf("%s \n",dp->d_name);
		       
		    }
		  
		}
		
		//sleep(ss);
	
      closedir(dir);


	
    
    CopyFile("../test/asd.txt", "/home/adhamfaris/work/PROJECTS/cdrProject/done/newdone/wr.txt");  
    if(!DeleteCdrFile("../test/asd.txt"))
    {
		puts("File deleted successfully");
	}
	else
	{
		puts("Error: unable to delete the file");
	}  	     
    return 0;
}


int DeleteCdrFile(const char* _fileName)
{
	return remove(_fileName);
}


void CopyFile(const char* _readfileName, const char* _WrFileName)
{

	FILE *fptr1, *fptr2;
	char c;
 
 	
	// Open one file for reading
	fptr1 = fopen(_readfileName, "r");
	if (fptr1 == NULL)
	{
	    printf("Cannot open file %s \n", _readfileName);
	    exit(0);
	}
 
	// Open another file for writing
	fptr2 = fopen(_WrFileName, "w+");
	if (fptr2 == NULL)
	{
	    printf("Cannot open file %s \n", _WrFileName);
	    exit(0);
	}
 
	// Read contents from file
	c = fgetc(fptr1);
	while (c != EOF)
	{
	    fputc(c, fptr2);
	    c = fgetc(fptr1);
	}
 
	printf("\nContents copied to %s", _WrFileName);
 
	fclose(fptr1);
	fclose(fptr2);
	return;
}


/*
	if((status = mkdir("/home/adhamfaris/work/PROJECTS/cdrProject/done/newdone", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)))
	{
		puts("Mkdir Error\n");
	}
	*/













