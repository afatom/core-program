


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
#include <sys/file.h>
#include <sys/inotify.h>
  #include <assert.h>     


int main(void)
{
	       
	FILE *fp1, *fp2;
	char buf[64];
 	int wd=0;
 	const char* pathname = "/home/adhamfaris/work/PROJECTS/cdrProject/watcher";
 	int inotifyfd = inotify_init();
	
	assert(inotifyfd != -1);
	
	wd = inotify_add_watch(inotifyfd,pathname, IN_CREATE);
 	assert(wd!=-1);
 	
 	
 	assert (inotify_rm_watch(inotifyfd, wd) == 0);
 	
 	
 	
 	
	// Open one file for reading
	fp1 = fopen("new.txt", "r");
	if (fp1 == NULL)
	{
	    printf("Cannot open new.txt file \n");
	    exit(0);
	}
	else
	{
	    if(flock(fileno(fp1), LOCK_EX))
	    {
			printf("Cannot LOCK new.txt file \n");
			exit(0);
		} 
	    
	}
	
	fp2 = fopen("new.txt", "r");
	if (fp2 == NULL)
	{
		
	    printf("Cannot open ____again__ new.txt file \n");
	    exit(0);
	}
	
	
	while(!feof(fp1))
	{
		fscanf(fp1,"%s",buf);
		printf("%s\n",buf);
		
	}
	
	
	fclose(fp1);
	fclose(fp2);
	
	
return 0;	
}
