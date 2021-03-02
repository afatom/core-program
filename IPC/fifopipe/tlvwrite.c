#include <stdio.h>
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
/*
#define _POSIX_C_SOURCE
#define _BSD_SOURCE
#define _XOPEN_SOURCE 
*/
#define TRUE 1

/**
*

				 data
			<---------->
    00000000 16bytes int   1 int   1 int      
	-------+------------+-----+--+------+ 
	|End   |data fields |length  | type |   
    -------+------------+-----+--+------+ 


*/




int main ()
{

	char* fifoname="pff";
	int fd=0;
  
  	int arr[512];
  	int i;
  	/*data loop*/
	arr[0] = 512; /*data length*/
	for(i = 1 ;i < 512; ++i)
  	{
  		arr[i] = i;
  	}
 	
 	 	 
	
/*	mkfifo(fifoname,0777);*/
    if( mknod(fifoname, 0777|S_IFIFO, (dev_t)0) < 0)
    {
		perror("Mknod Creating ERROR On Wr Process");
  		exit(EXIT_FAILURE);
	}
		
/*	fd=open(fifoname, O_WRONLY);*/
	if( (fd=open(fifoname,O_WRONLY)) < 0)
	{
		perror("FIFO Pipe Open On Reading PROC Error");
  		exit(EXIT_FAILURE);
	}	
	

	puts("Sending Data Over FIFO...");
	sleep(1);
	write(fd, arr, sizeof(arr));
	close(fd);
	unlink(fifoname);

	return 0;
}
