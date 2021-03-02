#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char* argv[]) 
{
	srand((unsigned int)(time(NULL)));	
   FILE * fp;
   size_t x;
	char buff[16];
	int i=0;
   strcmp(buff,argv[1]);
   fp = fopen (buff, "w");
   while(i<15)
   {
   x= (size_t)(rand() % 100000000);
   fprintf(fp, "%lu %s", x,"| 123456789 | 123456789 | 1234156454564655446465465487878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 56858 | 17000 | 5000 | 8585 | 9878");
   ++i;
   }
   fclose(fp);
   
   return(0);
}
