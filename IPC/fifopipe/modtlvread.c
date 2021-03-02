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
	
	int length = 0;
	int header[2]={0};
	int type = 0;
	int j=0;
	int zeroCounter=0;
	
	buf = &buffer[0];
	/*open fifo pipe*/
	
	if( (fd=open(fifoname,O_RDONLY)) < 0)
	{
		perror("FIFO Pipe Open On Reading PROC Error");
  		exit(EXIT_FAILURE);
	}
	
	read(fd, header, 2 * sizeof(int));
	puts("Printing Buffer...");

	if(header[0] == 'c') /*char buffer*/
	{
		read(fd, buffer, header[1] * sizeof(char));
		while (j < header[1] - 1)
		{
			printf("%c ", buffer[j]);
			++j;
		}
		puts(" ");
		close(fd);
	}
	else /*int buffer*/
	{
		read(fd, buffer, header[1] * sizeof(char));
		while (j < header[1] - 1)
		{
			printf("%d ", buffer[j]);
			++j;
		}
		puts(" ");
		close(fd);
	}
	
return 0;
}
