#include <stdio.h>
#include <time.h>
#include <unistd.h> 


int myfactorial(int x)
{
	if(x==0)
	{
		return 1;
	}
	return myfactorial(x-1)*x;
}


int main(void)
{
    struct timespec ts;
    struct timespec tsf;
    struct timespec tss;
    
    
    char buff[100];
    
   	int res;
    
    timespec_get(&ts, TIME_UTC);
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    printf("first Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
    
    res=myfactorial(300);
    timespec_get(&tsf, TIME_UTC);
    strftime(buff, sizeof buff, "%D %T", gmtime(&tsf.tv_sec));
    printf("sec Current time: %s.%09ld UTC\n", buff, tsf.tv_nsec);
    
    printf("Tottal proc time: %09ld\n",tsf.tv_nsec - ts.tv_nsec);
    
  	tss.tv_sec = tsf.tv_sec -ts.tv_sec;
  	tss.tv_nsec = tsf.tv_nsec -ts.tv_nsec;
  	
  	strftime(buff, sizeof buff, "%D %T", gmtime(&tss.tv_sec));
    printf("Delta struct time: %s.%09ld UTC\n", buff, tss.tv_nsec);
    
    
    
    
    


}
