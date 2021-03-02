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


int main(int argc, char* argv[])
{
	int pipefd[2];
	char buf[256] = "\nI am Arriving from Wr Edge !!\nand iam the hero of myself\n";
	
	
    if (pipe(pipefd) == -1) 
    {
		perror("pipe");
  		exit(EXIT_FAILURE);
	}
	
	
	write(pipefd[1], buf, strlen(buf));

	close(pipefd[1]);          /* Close unused write end */
   while (read(pipefd[0], &buf, 1) > 0)
   {
       write(STDOUT_FILENO, &buf, 1);
   }

   write(STDOUT_FILENO, "\n", 1);
   close(pipefd[0]);
   /*_exit(EXIT_SUCCESS);*/

	
return 0;
}

