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
	
	char* lsargs[]={"/bin/ls","-l",NULL};
	char* wsargs[]={"/usr/bin/wc","-w",NULL};
	

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
	
	else if(childpid > 0) /*ls cmd/parent process*/
	{
		close(STDOUT_FILENO);          /* Close stdout */
		
	    if (dup(pipefd[1]) == -1) 
    	{
			perror("Pipe Duplicating stdout Error");
  			exit(EXIT_FAILURE);
		}
		/*open pipe again after dup2 close it*/
		/**
		*
		*/
		execv(lsargs[0],lsargs);
		/*parent Wr to buffer*/
		close(pipefd[1]);          /* Close unused write end */ 
		wait(NULL);                /* Wait for child */

	}
	
	else /*child process*/
	{
	/*
		puts("Reading from Pipe line, Please Wait...");
		sleep(1);*//*<< illusion for reading*/
		/*child red from buffer and throw txt to stdout*/
		close(STDIN_FILENO);          /* Close stdint */
		close(pipefd[1]);          /* Close unused write end */
	    if (dup(pipefd[0]) == -1) 
    	{
			perror("Pipe Duplicating stdin Error");
  			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);          /* Close unused write end */
		execv(wsargs[0],wsargs);
	   	close(pipefd[0]);
       	exit(EXIT_SUCCESS);

	}

   /*_exit(EXIT_SUCCESS);*/

	puts("\n");
return 0;
}

