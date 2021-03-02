#include "cdr.h"
#include "aggregator.h"
#include <stdlib.h>
#include "HashMap.h"
#include "mu_test.h"
#include <stdio.h>
#include <unistd.h>


#define _subscribersNum 1024
#define _operatorsNum 64


typedef unsigned long int ulong;
typedef unsigned int uint;




typedef struct TestCDR
{
	ulong m_imsi; ulong m_msidn; ulong m_imei;
	char m_obn[64]; uint m_mcc; char m_ctype[8];
	char m_cd[8];char m_ctime[16]; uint m_dur;
	uint m_dwn; uint m_up; uint m_pms; uint m_pop;
}TestCDR;


TestCDR* TestCDR_Create(void)
{
	return (TestCDR*)calloc(1,sizeof(TestCDR));
}



size_t OpHashFunc(const void* _key)
{
	uint ret = *(uint*)_key;
	return ret;
}

size_t SubHashFunc(const void* _key)
{
	ulong ret = *(ulong*)_key;
	return ret;
}
/*****************************************************************************************/

UNIT(Aggregator_Create_And_Destroy_Test)
	Aggregator* agg = NULL;
	Aggregator_Result retval;
	const char* _subscribersReportFilePath = "~/usr/";
	const char* _operatorsReportFilePath = "~/usr/";
	 
	agg = AggregatorCreate(_subscribersNum, _operatorsNum, OpHashFunc, SubHashFunc);
	ASSERT_THAT(agg != NULL);
	retval = AggregatorDestroy(&agg, _subscribersReportFilePath, _operatorsReportFilePath);
	ASSERT_THAT(retval == AGGREGATOR_SUCCESS);
	ASSERT_THAT(NULL == agg);
END_UNIT


/*****************************************************************************************/

UNIT(Aggregator_Insert_Test)
	Aggregator_Result sstat;
	const char* fpn = "cdr.txt";
	Aggregator* agg = NULL;
	TestCDRModule* tcm;

	void* pCDR;
	Aggregator_Result retval;
	const char* _subscribersReportFilePath = "~/usr/";
	const char* _operatorsReportFilePath = "~/usr/";
	 
	agg = AggregatorCreate(_subscribersNum, _operatorsNum, OpHashFunc, SubHashFunc);
	ASSERT_THAT(agg != NULL);
	

	
	
	
	tcm = TestCDRModule_Create(fpn);
	while (1)
	{			
		pCDR=ParseAndGivMeCdr(tcm);	
		CdrPrint(pCDR);
		sstat = AggregatorInsertCdr(agg, pCDR);
		/*DestroyTestCDRModule(tcm);*/
		ASSERT_THAT (sstat == AGGREGATOR_SUCCESS);
		sleep(1);
	}
	
	
	
	retval = AggregatorDestroy(&agg, _subscribersReportFilePath, _operatorsReportFilePath);
	ASSERT_THAT(retval == AGGREGATOR_SUCCESS);
	ASSERT_THAT(NULL == agg);
END_UNIT

/*****************************************************************************************/
TEST_SUITE(Generic Aggregator Unit Tests)
TEST(Aggregator_Create_And_Destroy_Test)
TEST(Aggregator_Insert_Test)
END_SUITE
