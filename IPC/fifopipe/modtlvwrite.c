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
#include <string.h>
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
  
  	char str[512]="hi, i am arriving from Proc one\n I hope this string will reach its distination\n";
	
	int trr[2]={'c',(int)strlen(str)};

 	 	 
	
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
	write(fd, trr, 2*sizeof(int));
	write(fd, str, (int)strlen(str) * sizeof(char));

	close(fd);
	unlink(fifoname);

	return 0;
}
