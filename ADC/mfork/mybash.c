#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1

static void TypeMyPrompt(void);
int main ()
{
	char cmd[64];
	char params[64];
	char* argv[64];
	
	int status=0;
	
	while (TRUE)
	{
		TypeMyPrompt();
		
		scanf("%s%s",cmd,params);
		TypeMyPrompt();
		printf("%s %s\n",cmd,params);
		argv[0]=cmd;
		argv[1]=params;
		argv[2]=NULL;
		
		if(fork() != 0) /*parent proc*/
		{
			waitpid(-1, &status,0);
		}
		else 
		{
			execvp(argv[0], argv);

		}
	}

return 0;
}


static void TypeMyPrompt(void)
{
	printf(":@ ");
	return;
}



