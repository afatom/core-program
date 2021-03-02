#include "cdr.h"
#include "HashMap.h"
#include "aggregator.h"

#include <stdlib.h>
typedef unsigned long int ulong;
typedef unsigned int uint;
/******************************************************************************/
static void UpdateSubscriberRecord(Cdr* _cdr,SubscriberRecord* _pRecord, CALL_TYPE _callType);

size_t SubHashFunc(const void* _key)
{
	ulong ret = *(ulong*)_key;
	return ret;
}

int AggEqualityFunction(const void* _firstKey, const void* _secondKey)
{
	if(  *(ulong*)_firstKey ==  *(ulong*)_secondKey)
	{
		return 1;
	}
	return 0;
}


void* AggCreaeSubRecord(void* _cdr) 
{
	CALL_TYPE ct;
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
	return (void*)ptr;
}

void AggUpdateSubRecord(void* _existRecord, void* _cdr)
{
	CALL_TYPE ct;
	ct = CdrGetCallType((Cdr*)_cdr);
	UpdateSubscriberRecord((Cdr*)_cdr, (SubscriberRecord*)_existRecord, ct);
	return;
}




/******************************************************************************/
/*in phase 1.0 - there will be no saving to any file. destroying hash will destroy 
all saved pairs. 
in phase b - downloading and covering data to txt file will be implemented*/
/******************************************************************************/


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


#define SUCCESS 1 
#define FAIL 0


static void UpdateSubscriberRecord(Cdr* _cdr,SubscriberRecord* _pRecord, CALL_TYPE _callType);
static void UpdateOperatorRecord(Cdr* _cdr,OperatorRecord* _pRecord, CALL_TYPE _callType);



void* CreateOpCdrRecord(void* _pCdrRec)
{	
	CALL_TYPE ct;
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








void KeyDestroy(void* _key)
{
	KeyDestroyFunc destroy = CdrGetKeyDestroyFunction();
	
	destroy(_key);

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



/*
typedef size_t (*HashFunction)(const void* _key);

typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);
*/


/*

struct args{
	HashFunction 		m_subshash;
	HashFunction 		m_ophash;
	EqualityFunction 	m_subsEquality;
	EqualityFunction 	m_opEquality;
	const size_t 		m_subscribersNum;
	const size_t 		m_operatorsNum;
	const char* 		m_subscribersReportFilePath;
	const char* 		m_operatorsReportFilePath;
	
};

*/

/*static functions */


/**********************************************************************/

/******************************************************************************/
static Aggregator_Result MapResultToAggregatorResultConverter(MapResult _stat);
static int CheckAggCreateParams(const size_t _subscribersNum, const size_t _operatorsNum); 
/******************************************************************************/

Aggregator* AggregatorCreate(const size_t _subscribersNum, const size_t _operatorsNum,
 size_t (*OperatorsHashFunction)(const void* _key), size_t (*SubscribersHashFunction)(const void* _key))
{
	HashMap* subHash = NULL;
	HashMap* opHash = NULL;
	Aggregator* agg = NULL;
	EqualityFunction subEqualFunc = NULL;
	EqualityFunction opEqualFunc = NULL;
	
	
	
	if(!CheckAggCreateParams(_subscribersNum, _operatorsNum))
	{
		return NULL;
	}
	
	agg = (Aggregator*)calloc(1,sizeof(Aggregator));
	if(NULL == agg)
	{
		return NULL;
	}
	
	/******************************************/
	
	subEqualFunc = CdrGetSubEqualityFunction();
	opEqualFunc = CdrGetOpEqualityFunction();
	/******************************************/

	
	/*******************************************/
	subHash = HashMapCreate(_subscribersNum, (*SubscribersHashFunction), subEqualFunc);
	if(NULL == subHash)
	{
		free(agg);
		return NULL;
	}
	
	opHash = HashMapCreate(_operatorsNum,  (*OperatorsHashFunction), opEqualFunc);
	if(NULL == opHash)
	{
		HashMapDestroy(&subHash, NULL, NULL);
		free(agg);
		return NULL;
	}
	
	agg->m_subscribersHash = subHash;
	agg->m_operatorsHash = opHash;
	
	return agg;
}
/******************************************************************************/









Aggregator* AggregatorNewCreate(const size_t _initialSubscribersNum, 
const size_t _newCapacityInGrowthCondition)
{	
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



 

DataBase_Status DataBaseDestroy(void** _pDataBase, const char* _destinationDirPath,void (*_keyDestroy)(void* _key),
 void (*_valDestroy)(void* _value));














Aggregator_Result AggregatorDestroy(Aggregator** _pAggregator, const char* _subscribersReportFilePath, const char* _operatorsReportFilePath)
{
	if(NULL == _pAggregator || NULL == *_pAggregator)
	{
		return AGGREGATOR_UNINITIALIZED_ERROR;
	}
	
	
	
	HashMapDestroy(&(*_pAggregator)->m_subscribersHash, KeyDestroy, ValDestroy);
	HashMapDestroy(&(*_pAggregator)->m_operatorsHash, KeyDestroy, ValDestroy);
	free(*_pAggregator);
	*_pAggregator = NULL;
	return AGGREGATOR_SUCCESS;
}
/******************************************************************************/




Aggregator_Result AggregatorInsertCdr(Aggregator* _pAggregator, void* _cdr)
{
	MapResult stat;
	void* pOPRec = NULL;
	void* pSRec = NULL;
	void* pOPKey = NULL; /*providers key*/
	void* pSKey = NULL; /*subscriber key*/
	
	if(NULL == _pAggregator)
	{
		return AGGREGATOR_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _cdr)
	{
		return AGGREGATOR_INVALID_FUNCTION_ARGUMENTS_ERROR;
	}
	
	
	
	
	
	
	
	
	
	
	pOPRec = CreateOpCdrRecord(_cdr);  /*as void* _value*/
	pSRec = CreateSubCdrRecord(_cdr); /*as void* _value*/
	/**********************************************************/
	
	pOPKey = GetCdrOperatorKey(_cdr); 
	pSKey = GetCdrSubscriberKey(_cdr);
	/**********************************************************/

	/**********************************************************/
	/*phase A 1.0 - normal insert without update*/
	stat = HashMapInsert(_pAggregator->m_subscribersHash, pSKey, pSRec);
	if(stat != MAP_SUCCESS)
	{
		return MapResultToAggregatorResultConverter(stat);
	}
	stat = HashMapInsert(_pAggregator->m_operatorsHash, pOPKey, pOPRec);
	if(stat != MAP_SUCCESS)
	{
		return MapResultToAggregatorResultConverter(stat);
	}
	/*free cdrs*/
	/*
	CdrDestroy();
	CdrDestroy();*/
	
	return AGGREGATOR_SUCCESS;
}

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


