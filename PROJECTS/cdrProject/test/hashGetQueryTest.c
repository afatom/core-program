#define _GNU_SOURCE
#include "cdr.h"
#include "aggregator.h"
#include <stdlib.h>
#include "HashMap.h"
#include "mu_test.h"
#include "DataBase.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <string.h>


#define NDEBUG


#define SUBS_NUM 4096
#define OPS_NUM 4096

char cdrString1[256]="11111 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 215 | 151 | 163 | 855 | 978";
char cdrString2[256]="11111 | 125667789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 58 | 190 | 550 | 85 | 125";
char cdrString3[256]="11111 | 125512789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 86 | 18 | 560 | 5 | 155";

char cdrString4[256]="23145 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 33 | 8 | 16 | 85 | 91";
char cdrString5[256]="13554 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 88 | 19 | 50 | 15 | 12";
char cdrString6[256]="10101 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 99s | 77 | 66 | 5 | 1";

char cdrString7[256]="99999 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 215 | 151 | 163 | 855 | 978";
char cdrString8[256]="23455 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 58 | 190 | 550 | 85 | 125";
char cdrString9[256]="21342 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 86 | 18 | 560 | 5 | 155";

char cdrString10[256]="14423 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 33 | 8 | 16 | 85 | 91";
char cdrString11[256]="56898 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 88 | 19 | 50 | 15 | 12";
char cdrString12[256]="88789 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 99s | 77 | 66 | 5 | 1";

char cdrString13[256]="41355 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 215 | 151 | 163 | 855 | 978";
char cdrString14[256]="10022 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 58 | 190 | 550 | 85 | 125";
char cdrString15[256]="10585 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 86 | 18 | 560 | 5 | 155";

char cdrString16[256]="44311 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | SMS-MT | DD/MM/YYYY | HH:MM:SS | 33 | 8 | 16 | 85 | 91";
char cdrString17[256]="56665 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MOC | DD/MM/YYYY | HH:MM:SS | 88 | 19 | 50 | 15 | 12";
char cdrString18[256]="10000 | 125555789 | 123456789 | 1234156450000000000000000007878988 | 1234 | MTC | DD/MM/YYYY | HH:MM:SS | 99s | 77 | 66 | 5 | 1";



















typedef struct arg {
	Aggregator* agg;
	void* cdr1;
	void* cdr2;
	void* cdr3;
	void* cdr4;
	void* cdr5;
	void* cdr6;
	void* cdr7;
	void* cdr8;
	void* cdr9;
	void* cdr10;
	void* cdr11;
	void* cdr12;
	char* filepath;
	char* filepath2;
	}arg;





void* Thread_1_Function(void* parg)
{Aggregator_Result stat;
	FILE* fp;
	size_t i=0;
	char* bufbegin;
	char *pos;
	char* _buffer;
	Cdr* mcdr;

	_buffer = (char*)malloc(512* sizeof(char));
	if(!_buffer)
	{
		return (void*)(1);
	}
	
	fp = fopen(((arg*)parg)->filepath,"r");
	if(!fp)
	{
		#ifdef DEBUG
		puts("Error fopen");
		#endif
		
		return (void*)(1);
	}

	while (i<512)
	{
		puts("Hellow from thread 1\n\n");
		bufbegin = fgets(_buffer,512,fp);
		if (feof(fp))
		{
			break;
		}
		
		pos=strchr(_buffer, '\n'); /** remove /n from the string*/
		*pos = '\0';
		
		
		#ifdef DEBUG
		printf("%s\n",bufbegin);
		#endif
		
		mcdr = CDR_Create(_buffer);
		stat = AggregatorInsertCdr(((arg*)parg)->agg, mcdr);	
		assert(stat == AGGREGATOR_SUCCESS);	
		++i;
		sleep(1);
	}
	free(_buffer);
	fclose(fp);
	
	return (void*)(1);

}





void* Thread_2_Function(void* parg)
{Aggregator_Result stat;
	FILE* fp;
	size_t i=0;
	char* bufbegin;
	char *pos;
	char* _buffer;
	Cdr* mcdr;

	_buffer = (char*)malloc(512* sizeof(char));
	if(!_buffer)
	{
		return (void*)(1);
	}
	
	fp = fopen(((arg*)parg)->filepath,"r");
	if(!fp)
	{
		#ifdef DEBUG
		puts("Error fopen");
		#endif
		
		return (void*)(1);
	}

	while (i<512)
	{
		puts("Hellow from thread 2\n\n\n");
		bufbegin = fgets(_buffer,512,fp);
		if (feof(fp))
		{
			break;
		}
		
		pos=strchr(_buffer, '\n'); /** remove /n from the string*/
		*pos = '\0';
		
		
		#ifdef DEBUG
		printf("%s\n",bufbegin);
		#endif
		
		mcdr = CDR_Create(_buffer);
		stat = AggregatorInsertCdr(((arg*)parg)->agg, mcdr);	
		assert(stat == AGGREGATOR_SUCCESS);	
		sleep(1);
		++i;
	}
	free(_buffer);
	fclose(fp);
	
	return (void*)(1);

}


/*
void* Thread_2_Function(void* parg)
{
	puts("#");
	size_t i = 0;
	void* _pQueryRet;
	for(i =0; i<64;++i )
	{
		puts("Hellow from thread 2");
		assert((AggregatorInsertCdr(((arg*)parg)->agg, ((arg*)parg)->cdr2))== AGGREGATOR_SUCCESS);
		AggGetSubscriberQuery(((arg*)parg)->agg, 11111, &_pQueryRet);
		sleep(1);
	}
(void*)0;
}

void* Thread_3_Function(void* parg)
{
	puts("@");
	size_t i = 0;
	void* _pQueryRet;
	for(i =0; i<64;++i )
	{
		puts("Hellow from thread 3");
		assert((AggregatorInsertCdr(((arg*)parg)->agg, ((arg*)parg)->cdr3))== AGGREGATOR_SUCCESS);
		AggGetSubscriberQuery(((arg*)parg)->agg, 11111, &_pQueryRet);
		printf("Threa 3 Query Get ::: %lu\n",*(size_t*)_pQueryRet);
		sleep(1);
	}
(void*)0;
}


void* Thread_4_Function(void* parg)
{
	puts("*");
	size_t i = 0;
	void* _pQueryRet;
	for(i =0; i<64;++i )
	{
		puts("Hellow from thread 4");
		assert((AggregatorInsertCdr(((arg*)parg)->agg, ((arg*)parg)->cdr4))== AGGREGATOR_SUCCESS);
		AggGetSubscriberQuery(((arg*)parg)->agg, 11111, &_pQueryRet);
		printf("Threa 4 Query Get ::: %lu\n",*(size_t*)_pQueryRet);
		sleep(1);
	}
	(void*)0;
}



*/


UNIT(Hash_Test_Insert_And_Get_Query_Test)
	Aggregator_Result stat;
	
	Cdr* cdr1;
	Cdr* cdr2;
	Cdr* cdr3;
	Cdr* cdr4;
	Cdr* cdr5;
	Cdr* cdr6;
	Cdr* cdr7;
	Cdr* cdr8;
	Cdr* cdr9;
	Cdr* cdr10;
	Cdr* cdr11;
	Cdr* cdr12;
	Cdr* cdr13;
	Cdr* cdr14;
	Cdr* cdr15;
	Cdr* cdr16;
	Cdr* cdr17;
	Cdr* cdr18;
	
	Aggregator* agg = NULL;
	void* _pQueryRet=NULL;
	
	cdr1 = CDR_Create(cdrString1);
	cdr2 = CDR_Create(cdrString2);
	cdr3 = CDR_Create(cdrString3);
	
	cdr4 = CDR_Create(cdrString4);
	cdr5 = CDR_Create(cdrString5);
	cdr6 = CDR_Create(cdrString6);
	
	cdr7 = CDR_Create(cdrString7);
	cdr8 = CDR_Create(cdrString8);
	cdr9 = CDR_Create(cdrString9);
	
	cdr10 = CDR_Create(cdrString10);
	cdr11 = CDR_Create(cdrString11);
	cdr12 = CDR_Create(cdrString12);
	
	cdr13 = CDR_Create(cdrString13);
	cdr14 = CDR_Create(cdrString14);
	cdr15 = CDR_Create(cdrString15);
	
	cdr16 = CDR_Create(cdrString16);
	cdr17 = CDR_Create(cdrString17);
	cdr18 = CDR_Create(cdrString18);
	
	

	agg =  AggregatorNewCreate(SUBS_NUM, OPS_NUM);
	ASSERT_THAT(agg != NULL);

	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr1))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr2))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr3))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr4))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr5))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr6))== AGGREGATOR_SUCCESS);
	
	

	stat = AggGetSubscriberQuery(agg, 11111, &_pQueryRet);
	printf("Get Result :::::::: %lu\n",*((size_t*)_pQueryRet));
	
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr7))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr8))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr9))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr10))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr11))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr12))== AGGREGATOR_SUCCESS);
	
	
	stat = AggGetSubscriberQuery(agg, 11111, &_pQueryRet);
	printf("Get Result :::::::: %lu\n",*((size_t*)_pQueryRet));
	
	
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr13))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr14))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr15))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr16))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr17))== AGGREGATOR_SUCCESS);
	ASSERT_THAT((AggregatorInsertCdr(agg, (void*)cdr18))== AGGREGATOR_SUCCESS);
	
	
	
	
	stat = AggGetSubscriberQuery(agg, 11111, &_pQueryRet);
	printf("Get Result :::::::: %lu\n",*((size_t*)_pQueryRet));
	
	ASSERT_THAT((AggregatorDestroy(&agg, "backup.txt","backup.txt" )) == AGGREGATOR_SUCCESS);
	ASSERT_THAT(agg == NULL);
	
END_UNIT



UNIT(Hash_MT_Test_Insert_And_Get_Query_Test)
	pthread_t pthread_1;
	pthread_t pthread_2;
	pthread_t pthread_3;
	pthread_t pthread_4;
	arg* parg;
	Aggregator_Result stat;
	

	
		Cdr* cdr1;
	Cdr* cdr2;
	Cdr* cdr3;
	Cdr* cdr4;
	Cdr* cdr5;
	Cdr* cdr6;
	Cdr* cdr7;
	Cdr* cdr8;
	Cdr* cdr9;
	Cdr* cdr10;
	Cdr* cdr11;
	Cdr* cdr12;
	Cdr* cdr13;
	Cdr* cdr14;
	Cdr* cdr15;
	Cdr* cdr16;
	Cdr* cdr17;
	Cdr* cdr18;
	
	Aggregator* agg = NULL;
	void* _pQueryRet=NULL;
	
	cdr1 = CDR_Create(cdrString1);
	cdr2 = CDR_Create(cdrString2);
	cdr3 = CDR_Create(cdrString3);
	
	cdr4 = CDR_Create(cdrString4);
	cdr5 = CDR_Create(cdrString5);
	cdr6 = CDR_Create(cdrString6);

	cdr7 = CDR_Create(cdrString7);
	cdr8 = CDR_Create(cdrString8);
	cdr9 = CDR_Create(cdrString9);
	
	cdr10 = CDR_Create(cdrString10);
	cdr11 = CDR_Create(cdrString11);
	cdr12 = CDR_Create(cdrString12);
	
	cdr13 = CDR_Create(cdrString13);
	cdr14 = CDR_Create(cdrString14);
	cdr15 = CDR_Create(cdrString15);
	
	cdr16 = CDR_Create(cdrString16);
	cdr17 = CDR_Create(cdrString17);
	cdr18 = CDR_Create(cdrString18);
	
	agg =  AggregatorNewCreate(SUBS_NUM, OPS_NUM);
	ASSERT_THAT(agg != NULL);
	
	parg = (arg*)malloc(sizeof(arg));
	
	parg->agg=agg;
	parg->cdr1=(void*)cdr1;
	parg->cdr2=(void*)cdr2;
	parg->cdr3=(void*)cdr3;
	parg->cdr4=(void*)cdr4;
	
	parg->cdr5=(void*)cdr5;
	parg->cdr6=(void*)cdr6;
	parg->cdr7=(void*)cdr7;
	parg->cdr8=(void*)cdr8;
	
	parg->cdr9=(void*)cdr9;
	parg->cdr10=(void*)cdr10;
	parg->cdr11=(void*)cdr11;
	parg->cdr12=(void*)cdr12;
	parg->filepath = "cdr.txt";
	parg->filepath2 = "cdr2.txt";
	ASSERT_THAT((pthread_create(&pthread_1,NULL,Thread_1_Function, parg))==0);

	
	ASSERT_THAT((pthread_create(&pthread_2,NULL,Thread_2_Function, parg))==0);
/**
	ASSERT_THAT((pthread_create(&pthread_3,NULL,Thread_3_Function, parg))==0);

	ASSERT_THAT((pthread_create(&pthread_4,NULL,Thread_4_Function, parg))==0);
	puts("*");

	puts("*99999999");

 
 

 
    ASSERT_THAT ((pthread_join(pthread_3, NULL))==0);
    ASSERT_THAT ((pthread_join(pthread_4, NULL))==0);
**/
    
    ASSERT_THAT ((pthread_join(pthread_1, NULL))==0);
        ASSERT_THAT ((pthread_join(pthread_2, NULL))==0);
	ASSERT_THAT((AggregatorDestroy(&agg, "backup.txt","backup.txt" )) == AGGREGATOR_SUCCESS);
	ASSERT_THAT(agg == NULL);

END_UNIT
	


TEST_SUITE(Hash_MT_Safe_Insert_And_Get_Query_Test)
	/**TEST(Hash_Test_Insert_And_Get_Query_Test)*/
	TEST(Hash_MT_Test_Insert_And_Get_Query_Test)
	
END_SUITE


