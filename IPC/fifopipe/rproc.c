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


int main(void)
{
	int fd =0;
	char buffer[1024];
	char* buf;
	char* fifoname="pff";
	
	buf = &buffer[0];
	/*open fifo pipe*/
	
	if( (fd=open(fifoname,O_RDONLY)) < 0)
	{
		perror("FIFO Pipe Open On Reading PROC Error");
  		exit(EXIT_FAILURE);
	}
	while(1)
	{
		/*scanf from user and Wr to FIFO*/
		sleep(1);
		read(fd, buffer, 1024);
		printf("Reading Proc ::  %s\n", buffer);
	   
	}
	close(fd);	
return 0;
}
