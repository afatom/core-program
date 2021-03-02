#include "cdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
       
#define MAX_LINE_LENGTH 256

#define TRUE 1
#define FALSE 0


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef unsigned long int ulong;
typedef unsigned int uint;

static FILE* FileInit(const char* _fileName);
static void ParseLine(FILE* _fp, Cdr* _pCdr);
void CdrPrint(Cdr* _cdr);
/**
struct Cdr
{
	char m_imsi[16]; char m_msidn[16]; char m_imei[16];
	char m_obn[64]; char m_mcc[8]; char m_ctype[8];
	char m_cd[8];char m_ctime[16];char m_dur[8];
	char m_dwn[8];char m_up[8];char m_pms[8];char m_pop[8];
};
*/

struct Cdr
{
	ulong m_imsi; ulong m_msidn; ulong m_imei;
	char m_obn[64]; uint m_mcc; char m_ctype[8];
	char m_cd[8];char m_ctime[16]; uint m_dur;
	uint m_dwn; uint m_up; uint m_pms; uint m_pop;
};

/**********************************************************************/

struct TestCDRModule {
	FILE* m_fp;
	};



TestCDRModule* TestCDRModule_Create(const char* _fileName)
{
	FILE* fp = NULL;
	TestCDRModule* ptr;
	
	fp = FileInit(_fileName);
	printf("fp   %p",(void*)fp);
	ptr = (TestCDRModule*)malloc(sizeof(TestCDRModule));
	ptr->m_fp = fp;
	return ptr;
}

Cdr* ParseAndGivMeCdr(TestCDRModule* tcm)
{
	Cdr* mcdr = NULL;
	mcdr = (Cdr*)calloc(1,sizeof(Cdr));
	ParseLine(tcm->m_fp, mcdr);
	CdrPrint(mcdr);
	return mcdr;
}

void DestroyTestCDRModule(TestCDRModule* tcm)
{
	fclose(tcm->m_fp);
	free(tcm);
	return;
	
}


/**********************************************************************/


Cdr* CDR_Create(const char* _parsedLine)
{
	Cdr* _pCdr;
	_pCdr = (Cdr*)calloc(1,sizeof(Cdr));
	sscanf(_parsedLine, "%lu | %lu | %lu | %s | %u | %s | %s | %s | %u | %u | %u | %u | %u",
	   &_pCdr->m_imsi, &_pCdr->m_msidn, &_pCdr->m_imei, _pCdr->m_obn, &_pCdr->m_mcc, _pCdr->m_ctype, _pCdr->m_cd,
	   _pCdr->m_ctime, &_pCdr->m_dur, &_pCdr->m_dwn, &_pCdr->m_up, &_pCdr->m_pms, &_pCdr->m_pop);
	
	return _pCdr;

}



       

Cdr* CDR_Create_Empty_Cdr(void)
{
	Cdr* pcdr = NULL;
	pthread_mutex_lock(&mutex);
	pcdr = (Cdr*)calloc(1,sizeof(Cdr));
	pthread_mutex_unlock(&mutex);
	return pcdr;
}


void CDR_Destroy(Cdr** _pCdr)
{
	free(*_pCdr);
	*_pCdr=NULL;
	return;
}

void CdrPrint(Cdr* _cdr)
{
	
	printf("%lu | %lu | %lu | %s | %u | %s | %s | %s | %u | %u | %u | %u | %u\n",
	_cdr->m_imsi, _cdr->m_msidn, _cdr->m_imei, _cdr->m_obn, _cdr->m_mcc, _cdr->m_ctype, _cdr->m_cd,
	_cdr->m_ctime, _cdr->m_dur, _cdr->m_dwn, _cdr->m_up, _cdr->m_pms, _cdr->m_pop);
	
	return;
}

size_t CdrGetSize(void)
{
	return sizeof(struct Cdr);
}



size_t GetCallDuration(Cdr* _cdr)
{
	return _cdr->m_dur;
}






static int SubKeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	if(*((ulong*)_firstKey)==*((ulong*)_secondKey))
	{
		return 1; /**yes*/
	}
	return 0;
}

static int OpKeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	if(*((uint*)_firstKey)==*((uint*)_secondKey))
	{
		return 1; /**yes*/
	}
	return 0;
}





void DestroyKey(void* _key)
{
	return;
}



/**


static char* SkipFirstLine(FILE* _fp)
{
	char buffer[MAX_LINE_LENGTH];
	fgets(buffer,MAX_LINE_LENGTH,_fp);
	return buffer;
}

**/

static FILE* FileInit(const char* _fileName)
{
	FILE* fp = NULL;
	fp = fopen(_fileName,"r");
	if(NULL == fp)
	{
		puts("File Open Err");	
	}
	rewind(fp);
	return fp;
}

static void ParseLine(FILE* _fp, Cdr* _pCdr)
{	
	fscanf(_fp, "%lu | %lu | %lu | %s | %u | %s | %s | %s | %u | %u | %u | %u | %u",
	   &_pCdr->m_imsi, &_pCdr->m_msidn, &_pCdr->m_imei, _pCdr->m_obn, &_pCdr->m_mcc, _pCdr->m_ctype, _pCdr->m_cd,
	   _pCdr->m_ctime, &_pCdr->m_dur, &_pCdr->m_dwn, &_pCdr->m_up, &_pCdr->m_pms, &_pCdr->m_pop);
	   CdrPrint(_pCdr);
	return;
}



Cdr* CdrCreate(const char* _fileName)
{
	Cdr* mcdr = NULL;
	FILE* fp = NULL;
	
	mcdr = (Cdr*)calloc(1,sizeof(Cdr));
	fp = FileInit(_fileName);
	ParseLine(fp, mcdr);
	
	return mcdr;
	
}


void CdrDestroy(Cdr** _pCdr)
{
	if(NULL == _pCdr || NULL == *_pCdr)
	{
		return;
	}
	
	free(*_pCdr);
	*_pCdr = NULL;
	return;
}











char* CdrTurnToString(Cdr* _cdr, char* _buffer)
{
	sprintf(_buffer, "%lu | %lu | %lu | %s | %u | %s | %s | %s | %u | %u | %u | %u | %u",
	_cdr->m_imsi, _cdr->m_msidn, _cdr->m_imei, _cdr->m_obn, _cdr->m_mcc, _cdr->m_ctype, _cdr->m_cd,
	_cdr->m_ctime, _cdr->m_dur, _cdr->m_dwn, _cdr->m_up, _cdr->m_pms, _cdr->m_pop);
	
	return _buffer;
}



KeysEqualityFunction CdrGetSubEqualityFunction(void)
{
	return SubKeysEqualFunc;
}

KeysEqualityFunction CdrGetOpEqualityFunction(void)
{
	return OpKeysEqualFunc;
}



KeyDestroyFunc CdrGetKeyDestroyFunction(void)
{
	return DestroyKey;
}



CALL_TYPE CdrGetCallType(Cdr* _cdr)
{
	if(!strcmp(_cdr->m_ctype, "MOC") && _cdr->m_pop == _cdr->m_mcc)
	{
		return IN_NETWORK_OUTGOING_VOICE_CALL;
	}
	
	else if(!strcmp(_cdr->m_ctype, "MOC") && _cdr->m_pop != _cdr->m_mcc)
	{
		return OUT_NETWORK_OUTGOING_VOICE_CALL;
	}
	
	else if(!strcmp(_cdr->m_ctype, "MTC") && _cdr->m_pop == _cdr->m_mcc)
	{
		return IN_NETWORK_INCOMING_VOICE_CALL;
	}
	
	else if(!strcmp(_cdr->m_ctype, "MTC") && _cdr->m_pop == _cdr->m_mcc)
	{
		return OUT_NETWORK_INCOMING_VOICE_CALL;
	}
	
	else if(!strcmp(_cdr->m_ctype, "SMS-MO") && _cdr->m_pop == _cdr->m_mcc)
	{
		return IN_NETWORK_OUTGOING_SMS;
	}
	
	else if(!strcmp(_cdr->m_ctype, "SMS-MO") && _cdr->m_pop != _cdr->m_mcc)
	{
		return OUT_NETWORK_OUTGOING_SMS;
	}
	
	else if(!strcmp(_cdr->m_ctype, "SMS-MT") && _cdr->m_pop == _cdr->m_mcc)
	{
		return IN_NETWORK_INCOMING_SMS;
	}
	
	else if(!strcmp(_cdr->m_ctype, "SMS-MT") && _cdr->m_pop != _cdr->m_mcc)
	{
		return OUT_NETWORK_INCOMING_SMS;
	}
	
	else {
		return GPRS_CALL_TYPE;
	}
	
}


size_t GetDownloadData(Cdr* _cdr)
{
	return _cdr->m_dwn;
}

size_t GetUploadData(Cdr* _cdr)
{
	return _cdr->m_up;
}





void* GetCdrSubscriberKey(Cdr* _cdr)
{
	return &_cdr->m_imsi;
}

void* GetCdrOperatorKey(Cdr* _cdr)
{

	return &_cdr->m_mcc;
}

unsigned long int CdrGetImsi(Cdr* _cdr)
{
	return _cdr->m_imsi;
}
unsigned int CdrGetMcc(Cdr* _cdr)
{
	return _cdr->m_mcc;
}


void* CdrGetImsiAddress(Cdr* _cdr)
{
	&_cdr->m_imsi;
}

void* CdrGetMccAddress(Cdr* _cdr)
{
	return &_cdr->m_mcc;
}

int isDestroyMsg(Cdr* _msg)
{
	if(_msg->m_imsi == 0 && _msg->m_msidn == 0 && _msg->m_imei == 0)
	{
		return TRUE;	
	}
	
	return FALSE;
}















