#include <stdio.h>
#include <unistd.h>

#define TRUE 1

#define MCL 32

static void TypePrompt(void);

int main (int argc, char* argv[])
{
	char cmd[MCL];
	char params[MCL];
		
   while(TRUE)
   {
		TypePrompt();
		scanf("MCL%s MCL%s",cmd,params);
		printf("%S %S\n",cmd,params);
		break;
		/**
		*typeprompt(); my logo like unix $
		*read command (the command and exe i want to run)
		*
		*fork() - generate child process
		*wait untell child process terminates (child finish the job)
		*execlp/ve/v/ do the command
		*back to while 1
		*/
   }

    return 0;

}

static void TypePrompt(void)
{
	fprintf(stdout, ":@ "); /*dont jump to new line*/
	return;
}
/*
static ReadCmd(char* _cmd, char* _params)
{
	char
}*/
