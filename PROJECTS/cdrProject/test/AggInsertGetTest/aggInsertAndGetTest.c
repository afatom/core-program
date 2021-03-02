#include "cdr.h"
#include "aggregator.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


void _Insert_Agg_(const char* _eventsFile, Aggregator* agg)
{
	size_t i = 2500;
	FILE* fp;
	char _buffer[512];
	char* bufbegin;
	char* pos;
	Cdr* mcdr;
	
	fp = fopen(_eventsFile,"r");
	while (i--)
	{
		bufbegin = fgets(_buffer,512,fp);
		if (feof(fp))
		{
			break;
		}
		
		pos=strchr(_buffer, '\n'); /** remove /n from the string*/
		*pos = '\0';
		puts("");	
		mcdr = CDR_Create(_buffer);
		puts("");
		CdrPrint(mcdr);
		assert ((AggregatorInsertCdr(agg, mcdr))==AGGREGATOR_SUCCESS);
		printf("\n%d\n",i);
		/*CDR_Destroy(&mcdr);*/
		
	}
	fclose(fp);
}


int main (int argc, char* argv[])
{
	Aggregator* agg;
	char QueryReturn[1024];
	
	agg = AggregatorNewCreate(5000,10000);
	assert(agg!=NULL);
	
	_Insert_Agg_("cdr.txt", agg);
	assert(( AggGetSubscriberQuery(agg, 333333333, QueryReturn))==AGGREGATOR_SUCCESS);
	printf("Sub Queyr\n%s\n",QueryReturn);
	
	return 0;
}
