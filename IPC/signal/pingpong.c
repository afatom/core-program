#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/*
#ifndef _POSIX_C_SOURCE  199309L
#define _POSIX_C_SOURCE  199309L
#endif */


#define DISC_ON 1
#define DISC_OFF 0

int __receivedSignalNo__g=DISC_ON;



static void SigHandler(int _sigNUm);


int main(int argc, char** argv)
{
	pid_t n;
	struct sigaction act;
	struct sigaction oldact;
	act.sa_handler =&SigHandler;

	act.sa_flags=0;
	
	sigaction(SIGUSR1,&act,&oldact);
	
	
	/*****************************/
	if(n<0)
	{
		puts("Fork Fails!");
		return 1;
	}
	/*****************************/
    else if(n>0)
    {   /*Parent proc*/	
    	puts("__Pong__");
    	
    	kill(n,SIGUSR1);
    			
		while(1)
		{
			if(__receivedSignalNo__g == DISC_ON) 
			{
				puts("__Pong__");
				
				/*sendt child signal*/
				kill(n,SIGUSR1);
				__receivedSignalNo__g = DISC_OFF;
			}
		} 
    }

    else 
    {
		while(1)
		{
			if(__receivedSignalNo__g == DISC_ON) 
			{
				puts("__Ping__");
				sleep(1);
				/*sendt child signal*/
				kill(getppid(),SIGUSR1);
				__receivedSignalNo__g = DISC_OFF;
			}
		} 
    }
	

	
	return 0;
}
/******************************************************************************/

static void SigHandler(int _sigNUm)
{
	/*set father globals discretes*/
	__receivedSignalNo__g = DISC_ON;
}
/******************************************************************************/









