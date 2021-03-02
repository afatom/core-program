#ifndef __CDR_H_
#define __CDR_H_


#include <stddef.h>

/** 
 *  @file cdr.h
 *  @brief Create and Implement CDR ADT
 * 
 *  @details Implementing cdr module with functionalities listed bellow.
 * 
 *  @author Author Adham (faresadham@gmail.com) 
 * 
 *  @bug No known bugs.
 * 	@last update: 07.04.2018 00:45:21
 * 
 */ 
 
 
 typedef enum CALL_TYPE {
	IN_NETWORK_INCOMING_VOICE_CALL   =0,
	IN_NETWORK_OUTGOING_VOICE_CALL     ,
	OUT_NETWORK_INCOMING_VOICE_CALL    ,
	OUT_NETWORK_OUTGOING_VOICE_CALL    ,
	IN_NETWORK_INCOMING_SMS      ,
	IN_NETWORK_OUTGOING_SMS      ,
	OUT_NETWORK_INCOMING_SMS     ,
	OUT_NETWORK_OUTGOING_SMS     ,
	GPRS_CALL_TYPE
	
 }CALL_TYPE;
 

/*************************************************************/
	
typedef struct Cdr Cdr; 



/*************************************************************/

 
 
 
typedef int (*KeysEqualityFunction)(const void* _firstKey, const void* _secondKey);

typedef void (*KeyDestroyFunc)(void* _Key);




typedef struct  TestCDRModule TestCDRModule;

TestCDRModule* TestCDRModule_Create(const char* _fileName);
Cdr* ParseAndGivMeCdr(TestCDRModule* tcm);
void DestroyTestCDRModule(TestCDRModule* tcm);





typedef struct CDR CDR;

Cdr* CDR_Create(const char* _parsedLine);

Cdr* CDR_Create_Empty_Cdr(void);

void CDR_Destroy(Cdr** _pCdr);

void CdrPrint(Cdr* _cdr);


size_t CdrGetSize(void);


size_t GetCallDuration(Cdr* _cdr);


size_t GetDownloadData(Cdr* _cdr);


size_t GetUploadData(Cdr* _cdr);



Cdr* ParseAndSendCdr(CDR* _pCDR);


/**
CDR_Insert_Line(CDR* _pCDR, );**/




/************************************************************/

Cdr* CdrCreate(const char* _fileName);

void CdrDestroy(Cdr** _pCdr);



void CdrPrint(Cdr* _cdr);


char* CdrTurnToString(Cdr* _cdr, char* _buffer);


KeysEqualityFunction CdrGetSubEqualityFunction(void);

KeysEqualityFunction CdrGetOpEqualityFunction(void);

KeyDestroyFunc CdrGetKeyDestroyFunction(void);




CALL_TYPE CdrGetCallType(Cdr* _cdr);





void* GetCdrSubscriberKey(Cdr* _cdr);

void* GetCdrOperatorKey(Cdr* _cdr);



void* CdrGetImsiAddress(Cdr* _cdr);

void* CdrGetMccAddress(Cdr* _cdr);

unsigned long int CdrGetImsi(Cdr* _cdr);
unsigned int CdrGetMcc(Cdr* _cdr);


int isDestroyMsg(Cdr* _msg);









#endif /*__CDR_H_*/
