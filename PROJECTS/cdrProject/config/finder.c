#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int GetStrInConfigFile(const char* configFile, const char* str, char* buffer)
{
	/** char str[64] = "initial sub num"; example **/
	FILE *fp;
	char temp[512];
	char* pos;
	char* npos;
	int retval = 0;

	if((fp = fopen(configFile, "r")) == NULL) {
		return(0);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			
			npos=strchr(temp, '\n'); /** remove /n from the string*/
			*npos = '\0';
		
			pos = temp;
			pos = pos + 1 + strlen(str);
			sscanf(pos,"%s",buffer);
			retval =1;
			break;
		}
	}

	if(fp) 
	{
		fclose(fp);
	}
   	return(retval);
}


int main (int argc, char* argv[])
{
	char str[64] = "channel name";
	char buf[64];
	char fn[16]="config.txt";
	size_t t = GetStrInConfigFile(fn, str,buf);
	printf("%s\n",buf);
return 0;
}
