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

int main ()
{

	char buf[256];
	char* fifoname="pff";
	int fd=0;
  
	
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
	

	while(1)
	{
		/*scanf from user and Wr to FIFO*/
		puts("Enter your msg bellow.");
		fscanf(stdin,"%s",buf);
		
	   	write(fd, buf, sizeof(buf));
	   
	
	}
	close(fd);
	unlink(fifoname);

	return 0;
}
