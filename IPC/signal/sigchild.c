#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
#ifndef _POSIX_C_SOURCE  199309L
#define _POSIX_C_SOURCE  199309L
#endif */


int receivedSignal_g;
int receivedSignalNo_g;


static void SigHandler(int _sigNUm);

int main(int argc, char** argv)
{
	struct sigaction act;
	struct sigaction oldact;
	int receivedSignal_g=0,receivedSignalNo_g=0;
	act.sa_handler =&SigHandler;
	sigfillset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGHUP,&act,&oldact);
	
	while(receivedSignalNo_g != SIGTERM)
	{
		if(receivedSignal_g) 
		{
			receivedSignal_g=0;
			receivedSignalNo_g=0;
		}
		puts("I'm Going to sleep for 5 sec!");
		sleep(5);
	}
	
	return 0;
}


static void SigHandler(int _sigNUm)
{
	receivedSignal_g=1;
	receivedSignalNo_g=_sigNUm;
}



