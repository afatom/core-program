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
	pid_t childpid;
	int pipefd[2];
	
	char* buf;
	

    if (pipe(pipefd) == -1) 
    {
		perror("Pipe Creating Error");
  		exit(EXIT_FAILURE);
	}
	
	
	childpid = fork();
	/*check if fork success*/
	if(childpid < 0)
	{
		perror("fork  Error");
  		exit(EXIT_FAILURE);
	}
	
	else if(childpid > 0) /*parent process*/
	{
		/*parent Wr to buffer*/
		buf = "\nI am Arriving from Wr Edge !!\nand iam the Parent Process\n";
		
		write(pipefd[1], buf, strlen(buf));
		close(pipefd[1]);          /* Close unused write end */
		wait(NULL);                /* Wait for child */

	}
	
	else /*child process*/
	{
		puts("Reading from Pipe line, Please Wait...");
		sleep(3);/*<< illusion for reading*/
		/*child red from buffer and throw txt to stdout*/
		close(pipefd[1]);          /* Close unused write end */
	   while (read(pipefd[0], &buf, 1) > 0)
	   {
		   write(STDOUT_FILENO, &buf, 1);
	   }

	   write(STDOUT_FILENO, "\n", 1);
	   close(pipefd[0]);
	 
       exit(EXIT_SUCCESS);

	}

   /*_exit(EXIT_SUCCESS);*/

	
return 0;
}

