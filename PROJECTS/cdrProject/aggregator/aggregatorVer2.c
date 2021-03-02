#include "cdr.h"
#include "HashMap.h"
#include "aggregator.h"
#include "DataBase.h"
#include <stdlib.h>
#include <stdio.h>		/**<< printf*/
/********************************************************************************************/
typedef unsigned long int ulong;
typedef unsigned int uint;


struct Aggregator {
	HashMap* m_subscribersHash;
	HashMap* m_operatorsHash;
	void* m_dataBase;
};


typedef struct OperatorRecord{
	size_t m_inVcDurations;
	size_t m_outVcDurations;
	size_t m_inSMSCounter;
	size_t m_outSMSCounter;
	
}OperatorRecord;

typedef struct SubscriberRecord{
	size_t	m_inNetworkIncomingVc;
	size_t	m_inNetworkOutgoingVc;
	size_t  m_outNetworkIncomingVc;
	size_t  m_outNetworkOutgoingVc;
	size_t	m_inNetworkIncomingSMS;
	size_t	m_inNetworkOutgoingSMS;
	size_t  m_outNetworkIncomingSMS;
	size_t  m_outNetworkOutgoingSMS;
	size_t	m_downloadInMb;
	size_t	m_uploadInMb;
}SubscriberRecord;


typedef struct Key {
	ulong m_imsi;
}Key;
/********************************************************************************************/


static void UpdateSubscriberRecord(Cdr* _cdr,SubscriberRecord* _pRecord, CALL_TYPE _callType);
static Aggregator_Result DBStatToAggStat(DataBase_Status _stat);
static void PrintSubCdrRecord(SubscriberRecord* ptr);

/********************************************************************************************/

size_t SubHashFunc(const void* _key)
{
	return ((Key*)_key)->m_imsi;
}

int AggEqualityFunction(const void* _firstKey, const void* _secondKey)
{
	if(  *(ulong*)_firstKey ==  *(ulong*)_secondKey)
	{
		return 1;
	}
	return 0;
}

/**********************************************************************/
void* AggCreaeSubRecord(void* _cdr) 
{
	Cdr* x;
	
	
	CALL_TYPE ct;
	SubscriberRecord* ptr = NULL;
	
	/*************************************/
	
	x = (Cdr*)_cdr;
	
	ptr = (SubscriberRecord*)calloc(1,sizeof(SubscriberRecord));
	if(!ptr)
	{
		return NULL;
	}
	
	ct = CdrGetCallType((Cdr*)_cdr);
	UpdateSubscriberRecord((Cdr*)_cdr, ptr, ct);
	/*@*/
	CDR_Destroy(&x);
	
	#ifdef DEBUG
	PrintSubCdrRecord(ptr);
	#endif
	
	return (void*)ptr;
}
/******************************************************************************/

void AggUpdateSubRecord(void* _existRecord, void* _cdr)
{
	Cdr* x;
	
	
	CALL_TYPE ct;
	ct = CdrGetCallType((Cdr*)_cdr);
	UpdateSubscriberRecord((Cdr*)_cdr, (SubscriberRecord*)_existRecord, ct);
	/*@*/
	x = (Cdr*)_cdr;
	#ifdef DEBUG
	PrintSubCdrRecord((SubscriberRecord*)_existRecord);
	#endif
	CDR_Destroy(&x);
	return;
}

/******************************************************************************/


/******************************************************************************/
/*in phase 1.0 - there will be no saving to any file. destroying hash will destroy 
all saved pairs. 
in phase b - downloading and covering data to txt file will be implemented*/
/******************************************************************************/





#define SUCCESS 1 
#define FAIL 0


static void UpdateSubscriberRecord(Cdr* _cdr,SubscriberRecord* _pRecord, CALL_TYPE _callType);
static void UpdateOperatorRecord(Cdr* _cdr,OperatorRecord* _pRecord, CALL_TYPE _callType);



void* CreateOpCdrRecord(void* _pCdrRec)
{	
	CALL_TYPE ct;
	Cdr* x;
	OperatorRecord* ptr = NULL;
	/*************************************/

	/*************************************/
	
	ptr = (OperatorRecord*)calloc(1,sizeof(OperatorRecord));
	if(!ptr)
	{
		return NULL;
	}
		/*************************************/
	ct = CdrGetCallType((Cdr*)_pCdrRec);
		/*************************************/
	UpdateOperatorRecord((Cdr*)_pCdrRec, ptr, ct);
	/*@*/
	x = (Cdr*)_pCdrRec;
	CDR_Destroy(&x);
	return (void*)ptr;
}

/*
static OperatorRecord* BuildCdrOperatorRecord(Cdr* _cdr)
{	
	OperatorRecord* ptr = NULL;
	ptr = (OperatorRecord*)calloc(1,sizeof(OperatorRecord));
	if(!ptr)
	{
		return NULL;
	}
	
	ptr->
	return 
}*/

/*
static SubscriberRecord* BuildCdrSubscriberRecord(Cdr* _cdr)
{
	CALL_TYPE ct;
	
	SubscriberRecord* ptr = NULL;
	ptr = (SubscriberRecord*)calloc(1,sizeof(SubscriberRecord));
	if(!ptr)
	{
		return NULL;
	}
	
	ct = CdrGetCallType(_cdr);
	UpdateSubscriberRecord(ptr, ct);
	return ptr;
}
*/

void* CreateSubCdrRecord(void* _pCdrRec)
{
	CALL_TYPE ct;
	Cdr* x;
	SubscriberRecord* ptr = NULL;
	
	/*************************************/

	/*************************************/
	
	ptr = (SubscriberRecord*)calloc(1,sizeof(SubscriberRecord));
	if(!ptr)
	{
		return NULL;
	}
	
	ct = CdrGetCallType((Cdr*)_pCdrRec);
	UpdateSubscriberRecord((Cdr*)_pCdrRec, ptr, ct);
	/*@*/
	x = (Cdr*)_pCdrRec;
	CDR_Destroy(&x);
	return (void*)ptr;
}


 



static void UpdateSubscriberRecord(Cdr* _cdr,SubscriberRecord* _pRecord, CALL_TYPE _callType)
{
	switch(_callType)
	{
		case IN_NETWORK_INCOMING_VOICE_CALL:		
			_pRecord->m_inNetworkIncomingVc += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_OUTGOING_VOICE_CALL:		
			_pRecord->m_inNetworkOutgoingVc += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_INCOMING_VOICE_CALL:		
			_pRecord->m_outNetworkIncomingVc += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_OUTGOING_VOICE_CALL:		
			_pRecord->m_outNetworkOutgoingVc += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_INCOMING_SMS:		
			_pRecord->m_inNetworkIncomingSMS += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_OUTGOING_SMS:		
			_pRecord->m_inNetworkOutgoingSMS += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_INCOMING_SMS:		
			_pRecord->m_outNetworkIncomingSMS += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_OUTGOING_SMS:		
			_pRecord->m_outNetworkOutgoingSMS += GetCallDuration(_cdr);
			break;
			
		default:
			_pRecord->m_downloadInMb += GetDownloadData(_cdr);
			_pRecord->m_uploadInMb += GetUploadData(_cdr);
			break;
	}
	return;
}




static void UpdateOperatorRecord(Cdr* _cdr,OperatorRecord* _pRecord, CALL_TYPE _callType)
{
	switch(_callType)
	{
		case IN_NETWORK_INCOMING_VOICE_CALL:		
			_pRecord->m_inVcDurations += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_OUTGOING_VOICE_CALL:		
			_pRecord->m_outVcDurations += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_INCOMING_VOICE_CALL:		
			_pRecord->m_inVcDurations +=GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_OUTGOING_VOICE_CALL:		
			_pRecord->m_outVcDurations += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_INCOMING_SMS:		
			_pRecord->m_inSMSCounter += GetCallDuration(_cdr);
			break;
			
		case IN_NETWORK_OUTGOING_SMS:		
			_pRecord->m_outSMSCounter += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_INCOMING_SMS:		
			_pRecord->m_inSMSCounter += GetCallDuration(_cdr);
			break;
			
		case OUT_NETWORK_OUTGOING_SMS:		
			_pRecord->m_outSMSCounter += GetCallDuration(_cdr);
			break;
			
		default:
			break;
	}
	return;
}




void* KeyGenerate(size_t _subIdentity)
{
	Key* pKey;
	pKey=(Key*)malloc(sizeof(Key));
	if(!pKey)
	{
		return NULL;
	}
	
	pKey->m_imsi =_subIdentity;
	return (void*)pKey;
}



void KeyDestroy(void* _key)
{
	/*KeyDestroyFunc destroy = CdrGetKeyDestroyFunction();
	destroy(_key);*/
	
	if(!_key)
	{
		return;
	}
	free(_key);
	return;
}


void ValDestroy(void* _value)
{
	if(!_value)
	{
		return;
	}
	free(_value);
	return;
}

/**********************************************************************/

/******************************************************************************/
static Aggregator_Result MapResultToAggregatorResultConverter(MapResult _stat);
static int CheckAggCreateParams(const size_t _subscribersNum, const size_t _operatorsNum); 
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/






/******************************************************************************************************************************************/
Aggregator* AggregatorNewCreate(const size_t _initialSubscribersNum, 
const size_t _newCapacityInGrowthCondition)
{	
	Aggregator* agg = NULL;
	
	if(!_initialSubscribersNum)
	{
		return NULL;
	}
	
	agg = (Aggregator*)calloc(1,sizeof(Aggregator));
	if(NULL == agg)
	{
		return NULL;
	}
	
	if(!(agg->m_dataBase = DataBaseCreate(_initialSubscribersNum, _newCapacityInGrowthCondition, AggEqualityFunction, SubHashFunc)))
	{
		free(agg);
		return NULL;
	}
	return agg;
}

/******************************************************************************************************************************************/


Aggregator_Result AggregatorDestroy(Aggregator** _pAggregator, const char* _subscribersReportFilePath, const char* _operatorsReportFilePath)
{
	if(NULL == _pAggregator || NULL == *_pAggregator)
	{
		return AGGREGATOR_UNINITIALIZED_ERROR;
	}
	
	
	DataBaseDestroy(&(*_pAggregator)->m_dataBase, _subscribersReportFilePath , KeyDestroy,ValDestroy);
	

	free(*_pAggregator);
	*_pAggregator = NULL;
	return AGGREGATOR_SUCCESS;
}
/******************************************************************************************************************************************/




Aggregator_Result AggregatorInsertCdr(Aggregator* _pAggregator, void* _cdr)
{
	void* pkey =NULL;
	
	if(NULL == _pAggregator)
	{
		return AGGREGATOR_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _cdr)
	{
		return AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
	}
	
	/**DataBaseInsertOrUpdate(_pAggregator->m_dataBase, CdrGetImsiAddress(_cdr),AggCreaeSubRecord, AggUpdateSubRecord, KeyDestroy,_cdr);*/
	pkey = KeyGenerate(CdrGetImsi((Cdr*)_cdr));
	DataBaseInsertOrUpdate(_pAggregator->m_dataBase, pkey, AggCreaeSubRecord, AggUpdateSubRecord, KeyDestroy, _cdr);
	
	return AGGREGATOR_SUCCESS;
}
/******************************************************************************/
/*UNIT TEST ONLY*/
size_t Agg_Get_Size(Aggregator* _pAggregator)
{
	return DB_Get_Size(_pAggregator->m_dataBase);
}






/******************************************************************************/

Aggregator_Result AggGetSubscriberQuery(Aggregator* _pAggregator,size_t _subscriberImsi, char* _pQueryRet)
{
	DataBase_Status ret;
	void* pkey;
	void* val = NULL;
	SubscriberRecord* rec;
	if(!_pAggregator)
	{
		return AGGREGATOR_UNINITIALIZED_ERROR;
	}
	
	pkey = KeyGenerate(_subscriberImsi);
	
	ret = DataBaseFind(_pAggregator->m_dataBase, pkey, &val);
	if(ret != DATA_BASE_SUCCESS)
	{
		return DBStatToAggStat(ret);
	}
	/**val = &(((SubscriberRecord*)val)->m_downloadInMb);
	*_pQueryRet=val;
	*/
	rec = (SubscriberRecord*)val;
	sprintf(_pQueryRet,"IMSI %lu, InNetIncomVC %lu, InNetOutVc %lu, OutNetIncomVc %lu, OutNetOutVc %lu, InNetIncomSMS %lu, InNetOutSMS %lu, OutNetIncomSMS %lu, OutNetOutSMS %lu, Download_MB %lu, Upload_MB %lu",_subscriberImsi,rec->m_inNetworkIncomingVc,
	rec->m_inNetworkOutgoingVc,
	rec->m_outNetworkIncomingVc,
	rec->m_outNetworkOutgoingVc,
	rec->m_inNetworkIncomingSMS,
	rec->m_inNetworkOutgoingSMS,
	rec->m_outNetworkIncomingSMS,
	rec-> m_outNetworkOutgoingSMS,
	rec->m_downloadInMb,
	rec->m_uploadInMb);
	return DBStatToAggStat(ret);
}

	

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
static int CheckAggCreateParams(const size_t _subscribersNum, const size_t _operatorsNum)
{
	if(_subscribersNum == 0 || _operatorsNum == 0)
	{
		return FAIL;
	}
	return SUCCESS;
}

/******************************************************************************/
static Aggregator_Result MapResultToAggregatorResultConverter(MapResult _stat)
{
	Aggregator_Result aggStat;
	switch(_stat)
	{
		case MAP_UNINITIALIZED_ERROR :
         aggStat = AGGREGATOR_UNINITIALIZED_ERROR;
         break;
    
      case MAP_KEY_NULL_ERROR :
         aggStat = AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
         break;
         
      case MAP_KEY_NOT_FOUND_ERROR :
          aggStat = AGGREGATOR_SUBSCRIBER_OR_OPERATOR_NOT_FOUND_ERROR;
         break;
         
      case MAP_ALLOCATION_ERROR :
         aggStat = AGGREGATOR_ALLOCATION_ERROR;
         break;
         
     case MAP_INVALID_INCOMING_VALUE :
         aggStat = AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
         break;
         
      default :
          aggStat = AGGREGATOR_SUCCESS;
          break;
	}
	return aggStat;
}
/******************************************************************************/
/******************************************************************************/
static Aggregator_Result DBStatToAggStat(DataBase_Status _stat)
{
	Aggregator_Result aggStat;
	switch(_stat)
	{
		case DATA_BASE_NOT_INITIALIZED_ERROR :
         aggStat = AGGREGATOR_UNINITIALIZED_ERROR;
         break;
    
      case DATA_BASE_INVALID_DATA_IN :
         aggStat = AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
         break;
         
      case DATA_BASE_DATA_DOES_NOT_EXIST :
          aggStat = AGGREGATOR_SUBSCRIBER_OR_OPERATOR_NOT_FOUND_ERROR;
         break;
         
      case DATA_BASE_ALLOCATION_FAILURE_ERROR :
         aggStat = AGGREGATOR_ALLOCATION_ERROR;
         break;
         
     case DATA_BASE_NULL_FUNCTION_INPUT_ARGS_ERROR :
         aggStat = AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
         break;
         
      default :
          aggStat = AGGREGATOR_SUCCESS;
          break;
	}
	return aggStat;
}

/*******************************************************************************
 * 
 * UNIT Test Section Only
 * 
 * 
 * 
 * /
/******************************************************************************/
/**UNIT Test Functions*/
static void PrintSubCdrRecord(SubscriberRecord* ptr)
{
	printf("After Updating\n");
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_inNetworkIncomingVc);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_inNetworkOutgoingVc);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_outNetworkIncomingVc);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_outNetworkOutgoingVc);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_inNetworkIncomingSMS);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_inNetworkOutgoingSMS);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_outNetworkIncomingSMS);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_outNetworkOutgoingSMS);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_downloadInMb);
	printf("m_inNetworkIncomingVc  %lu\n",ptr->m_uploadInMb);
	return;
	
}



static void PrintOpCdrRecord(OperatorRecord* ptr)
{
	printf("After Updating\n");
	printf("m_inVcDurations  %lu\n",ptr->m_inVcDurations);
	printf("m_outVcDurations  %lu\n",ptr->m_outVcDurations);
	printf("m_inSMSCounter  %lu\n",ptr->m_inSMSCounter);
	printf("m_outSMSCounter  %lu\n",ptr->m_outSMSCounter);

	return;
	
}


















