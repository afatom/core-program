#ifndef _DIARY_H_
#define _DIARY_H_
#include "ADTErr.h"
#include <stddef.h> /*for size_t*/

typedef struct Meeting Meeting;
typedef struct ADPtr ADPtr;

/*******************************************************************************
*[Description]:Creating ADiary structure pointer.
*[Input]:size of the meetings array and incr block size for realloc uses) 
*[output]:return: ADptr - pointer to structure 
*[Errors]: NO ERRORS return
********************************************************************************/
ADPtr* CreateAD(size_t _Size, size_t _IncrBlock);

/*******************************************************************************
*[Description]:Distroying whole diary. 
*[Input]:AD pointer 
*[output]:Erasing the whole ADT. NO return   
*[Errors]:NONE
*******************************************************************************/
void DestroyAD(ADPtr *_ADPtr);
void DestroyDD(ADPtr *_ADPtr);
/*******************************************************************************
*[Description]:Printing whole diary. 
*[Input]:AD pointer 
*[output]:Meetings printing from the first one  
*[Errors]:NONE
*******************************************************************************/
void PrintAD(ADPtr *_ADPtr);

/*******************************************************************************
*[Description]:Creating New Meeting. 
*[Input]:Begin Hour, End Hour, room number and AD pointer) 
*[output]:ERR status and New meeting with link to ADPtr->m_newMeeting 
*[Errors]:ERR_OK, ERR_INVALID_MEETING_INPUTS,
*ERR_POINTER_NOT_INTIALIZED.
*******************************************************************************/
ADTErr CreateMeetingAD(float _beginHour, float _endHour, int _roomNumber, ADPtr *_ADPtr);

/*******************************************************************************
*[Description]:Search Meetings array By Begin Hour. 
*[Input]:Begin Hour and AD pointer) 
*[output]:Pointer to Searched Meeting (NULL - Meeting does not exist or invalid
*beginhour).
*[Errors]:NO Errors
*******************************************************************************/
Meeting* FindMeeting(ADPtr *_ADPtr, float _beginHour);

/*******************************************************************************
*[Description]:Remove Meeting By Begin Hour. 
*[Input]:Begin Hour and AD pointer) 
*[output]:ERR status and Meeting removing 
*[Errors]:ERR_OK, ERR_INVALID_MEETING_INPUTS, ERR_MEETING_DOES_NOT_EXIST,
*ERR_POINTER_NOT_INTIALIZED, ERR_ARRAY_UNDERFLOW
*******************************************************************************/
ADTErr RemoveAD(ADPtr *_ADPtr, float _beginHour);

/*******************************************************************************
*[Description]:Insert New Meeting in the prop place (insertion by begin hour) 
*[Input]:AD pointer) 
*[output]:ERR status and Meeting Insertion 
*[Errors]:ERR_OK, ERR_NO_MEETING_TO_INSERT,
*ERR_POINTER_NOT_INTIALIZED, ERR_ARRAY_OVERFLOW
*******************************************************************************/
ADTErr InsertAD(ADPtr *_ADPtr);

/*******************************************************************************
*[Description]:saves meetings diary to atxt file 
*[Input]:AD pointer and the file name (name givin vy user).
*[output]:ERR status! in success situation ERR_OK return!
*[Errors]:ERR_OK, ERR_NO_MEETING_TO_INSERT, ERR_INVALID_FILE
*******************************************************************************/
ADTErr SaveToFileAD(ADPtr *_ADPtr, const char *_fileName);

/*******************************************************************************
*[Description]:loads meetings diary from atxt file. loading and inserting them. 
*[Input]:AD pointer and the file name
*[output]:ERR status! in success situation ERR_OK return!
*[Errors]:ERR_OK, ERR_NO_MEETING_TO_INSERT, ERR_INVALID_FILE
*******************************************************************************/
ADTErr LoadFromFileAD(ADPtr *_ADPtr,const char *_fileName);


/******************************************************************************/
/****************     Unit Test Functions Only     ****************************/
ADTErr ADMeetingsNum(ADPtr *_ADPtr, size_t *_numOfMeetings);
void FunctionStatus(ADTErr _status);
void PrintOneMeeting(Meeting* _meeting);
/******************************************************************************/
#endif /*_DIARY_H_*/
