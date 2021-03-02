#include "diary.h"
#include "ADTErr.h"
#include <stdio.h>
#include <stdlib.h>

#define MAGIC 813716292 /*Double free Uses*/

struct Meeting {
    float m_BeginHour;
    float m_EndHour;
    int m_RoomNumber;
};

struct ADPtr{
    int         m_Magic;
    size_t      m_Size;
    size_t      m_IncrBlock;
    size_t      m_NumOfMeetings;
    Meeting**   m_Meetings;
    Meeting*    m_NewMeeting;
};

ADPtr* CreateAD(size_t _Size, size_t _IncrBlock)
{
    ADPtr *ADPtrr = NULL; 
    if (_Size == 0 && _IncrBlock == 0)
    {
        return NULL;
    }
    /*Creating ADPtr*/
    ADPtrr = (ADPtr*)malloc(sizeof (ADPtr));
    /*check if malloc succeded*/
    if (NULL == ADPtrr)
    {
        return NULL;
    }
    /*Creating pointer to meeting (for new meeting creating)*/
    (ADPtrr->m_NewMeeting) = (Meeting*)malloc(sizeof(Meeting));
    if (NULL == ADPtrr->m_NewMeeting)
    {
        free(ADPtrr);
        return NULL;
    }
    /*Creating Meetings Array (Array of pointers to meetings)*/
    (ADPtrr->m_Meetings) = (Meeting**)malloc(_Size * sizeof(Meeting*));
    /*check if malloc succeded*/
    if (NULL==ADPtrr->m_Meetings)
    {
        /*free ADPtr and free ADPtr->newmeeting*/
        free(ADPtrr->m_NewMeeting);
        free (ADPtrr);
        return NULL;
    }
    /*ADPtr Members Initializing*/
    ADPtrr->m_Magic = MAGIC;
    ADPtrr->m_Size = _Size;
    ADPtrr->m_IncrBlock = _IncrBlock;
    ADPtrr->m_NumOfMeetings = 0;
    ADPtrr->m_NewMeeting = NULL;
    
    return ADPtrr;
}
/*
void DestroyDD(ADPtr **_ADPtr)
{
    int i = 0;
    if (NULL == *_ADPtr)
    {
        return;
    }
   
    for (i = 0; i < (*_ADPtr)->m_NumOfMeetings; ++i)
    {
        free((*_ADPtr)->m_Meetings[i]);
    }
    free((*_ADPtr)->m_Meetings);
    free((*_ADPtr)->m_NewMeeting);
    free(*_ADPtr);
	(*_ADPtr)=NULL;    
    return;
}
*/
void DestroyAD(ADPtr* _ADPtr)
{
    int i = 0;
    if (NULL == _ADPtr || _ADPtr->m_Magic == 0)
    {
        return;
    }
    /*freeing meetings pointers one by one*/
    for (i = 0; i < _ADPtr->m_NumOfMeetings; ++i)
    {
        free(_ADPtr->m_Meetings[i]);
    }
    free(_ADPtr->m_Meetings);
    free(_ADPtr->m_NewMeeting);
    _ADPtr->m_Magic=0; /*Avoid Double free*/
    free(_ADPtr);
    return;
}

void PrintAD(ADPtr* _ADPtr)
{
	size_t i;
    if (NULL==_ADPtr)
    {
        printf("ERR_POINTER_NOT_INTIALIZED.\n");
        return;
    }
    printf("**************************\n");
    printf("*AD_Size: %10lu\n",_ADPtr->m_Size);
    printf("*AD_NOE: %10lu\n",_ADPtr->m_NumOfMeetings);
    printf("*AD_IncrBlock: %10lu\n",_ADPtr->m_IncrBlock);
    printf("**************************\n");
    if (_ADPtr->m_NumOfMeetings==0)
    {
        printf("Empty Array: No Appointments To Print.\n");
        return;
    }
    for (i=0; i<_ADPtr->m_NumOfMeetings; ++i)
    {
        printf("........................\n");
        printf("Meeting Number %10lu Details:\n",i+1);
        printf("Begin Hour: %10f\n",_ADPtr->m_Meetings[i]->m_BeginHour);
        printf("End Hour: %10f\n",_ADPtr->m_Meetings[i]->m_EndHour);
        printf("Room Number: %10d\n",_ADPtr->m_Meetings[i]->m_RoomNumber);
        printf("........................\n");
    }
    return;
}

/***********************************************************************************/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
static int CheckMeetingInputs(float _beginHour, float _endHour, int _roomNumber)
{
    /*check begin hour*/
    if (!(_beginHour<=23.99 && _beginHour>=0.00))
    {
        return 1; /*invalid inputs*/
    }
    /*check end hour*/
    if (!(_endHour>_beginHour && (_endHour<=23.99 && _endHour>=0.00)))
    {
        return 1;
    }
    return 0; /*valid inputs*/
}

static int IsOverFlow(ADPtr* _ADPtr)
{
    if ((_ADPtr->m_NumOfMeetings == _ADPtr->m_Size) && _ADPtr->m_IncrBlock == 0)
    {
        return 1; /*over flow*/
    }
    return 0;
}

static int IsReallocNeeded(ADPtr* _ADPtr)
{
    if ((_ADPtr->m_NumOfMeetings == _ADPtr->m_Size) && (_ADPtr->m_IncrBlock != 0))
    {
        return 1; /*realloc needed*/
    }
    return 0;
}
/*Check if new meeting overlap with existing one.
*return: 1 = overlap . in success situation, func returns index for insertion*/
static int IsMeetingOverlap(ADPtr* _ADPtr, size_t *_index)
{
    size_t i=0;
    if (_ADPtr->m_NumOfMeetings == 0)
    {
        /*first arriving meeting*/
        *_index = 0;
        return 0;
    }
    /*new meeting end hour < begin hour at 0 index*/
    if (_ADPtr->m_NewMeeting->m_EndHour < _ADPtr->m_Meetings[i]->m_BeginHour)
    {
        *_index = 0;
        return 0;
    }
    for (i = 0; i < _ADPtr->m_NumOfMeetings - 1; ++i)
    {      
        /*collision situation*/
        if ((_ADPtr->m_NewMeeting->m_BeginHour > _ADPtr->m_Meetings[i]->m_BeginHour) &&
            (_ADPtr->m_NewMeeting->m_EndHour < _ADPtr->m_Meetings[i]->m_EndHour))
        {
            return 1; /*collision*/
        }

        /*proper situation*/
        if ((_ADPtr->m_NewMeeting->m_BeginHour > _ADPtr->m_Meetings[i]->m_EndHour) &&
            (_ADPtr->m_NewMeeting->m_EndHour < _ADPtr->m_Meetings[i + 1]->m_BeginHour))
        {
            ++i;
            *_index = i; 
            return 0;
        }
    }
    /* if ((_newMeeting->m_BeginHour > _ADPtr->m_Meetings[i]->m_EndHour) */
    ++i;
    *_index = i; /*place to insert the new meeting*/
    return 0;
}

static int ReallocMeetingsArray(ADPtr* _ADPtr, int _operation)
{
    size_t newSize = 0;
    Meeting **Meetings = NULL;
    if (_operation == -1)
    {
        newSize = _ADPtr->m_Size - _ADPtr->m_IncrBlock;
    }
    else 
    {
        newSize = _ADPtr->m_Size + _ADPtr->m_IncrBlock;
    }

    Meetings = (Meeting**)realloc((_ADPtr->m_Meetings), (newSize) * sizeof(Meeting*));
    if (NULL == Meetings)
    {
        return 1; /*realloc failure*/
    }
    _ADPtr->m_Meetings = Meetings;
    _ADPtr->m_Size = newSize;
    return 0;
}

static void MakeRoom(ADPtr *_ADPtr, size_t _fromIndex)
{
    size_t j;
    for (j = _ADPtr->m_NumOfMeetings; j > _fromIndex; --j)
    {
        _ADPtr->m_Meetings[j] = _ADPtr->m_Meetings[j - 1];
    }
    return;
}

static void CloseGap(ADPtr *_ADPtr, size_t _toIndex)
{
    size_t j;
    for (j = _toIndex; j < _ADPtr->m_NumOfMeetings; ++j)
    {
        _ADPtr->m_Meetings[j] = _ADPtr->m_Meetings[j + 1];
    }
    return;
}
static ADTErr SearchMeeting(ADPtr *_ADPtr, float _beginHour, size_t *_index)
{
    size_t i;
    for (i = 0; i < _ADPtr->m_NumOfMeetings; ++i)
    {
        if (_ADPtr->m_Meetings[i]->m_BeginHour == _beginHour)
        {
        	*_index = i;
            return ERR_OK;
        }
    }
    return ERR_MEETING_DOES_NOT_EXIST; /*meeting does not found*/
}
/***********************************************************************************/

ADTErr CreateMeetingAD(float _beginHour, float _endHour, int _roomNumber, ADPtr *_ADPtr)
{
    int result;
    if (result = CheckMeetingInputs(_beginHour, _endHour, _roomNumber))
    {
        return ERR_INVALID_MEETING_INPUTS;
    }
    if (_ADPtr->m_NewMeeting == NULL)
    {
        _ADPtr->m_NewMeeting = (Meeting*)malloc(sizeof(Meeting));
        if (NULL == _ADPtr->m_NewMeeting)
        {
            return ERR_ALLOCATION_FAILURE;
        }
    }
    _ADPtr->m_NewMeeting->m_BeginHour = _beginHour;
    _ADPtr->m_NewMeeting->m_EndHour = _endHour;
    _ADPtr->m_NewMeeting->m_RoomNumber = _roomNumber;
    return ERR_OK;
}

ADTErr InsertAD(ADPtr *_ADPtr)
{
    int result, reallocResult; 
    size_t indexToInsert = 0;
    if (NULL == _ADPtr)
    {
        return ERR_POINTER_NOT_INTIALIZED;
    }
    /*No meeting to insert*/
    if (NULL == _ADPtr->m_NewMeeting)
    {
        return ERR_MEETING_DOES_NOT_EXIST;
    }
    /*check overflow*/
    if (result = (IsOverFlow(_ADPtr)))
    {
        return ERR_MEETINGS_ARRAY_OVERFLOW;
    }
    /*isrealloc needed*/
    if (IsReallocNeeded(_ADPtr))
    {
        /*realloc needed- call realloc*/
        if ((reallocResult = ReallocMeetingsArray(_ADPtr, 1)))
        {
            return ERR_REALLOCATION_FAILURE;
        }
    }
    /*check meetings collisions*/
    if ((IsMeetingOverlap(_ADPtr, &indexToInsert)))
    {
        return ERR_MEETING_OVERLAP;
    }
    
    /*insertion*/
    MakeRoom(_ADPtr, indexToInsert);
    _ADPtr->m_Meetings[indexToInsert] = _ADPtr->m_NewMeeting;
    _ADPtr->m_NewMeeting = NULL; /*disconnecting the pointer for Next Meeting Creation*/
    ++_ADPtr->m_NumOfMeetings;
    
    return ERR_OK;
}

ADTErr RemoveAD(ADPtr *_ADPtr, float _beginHour)
{
    size_t i, indexToRemove;
    ADTErr result;
    if (NULL == _ADPtr)
    {
        return ERR_POINTER_NOT_INTIALIZED;
    }
    if (_beginHour < 0 || _beginHour > 23.99)
    {
        return ERR_INVALID_MEETING_INPUTS;
    }
    if (_ADPtr->m_NumOfMeetings == 0)
    {
        return ERR_MEETINGS_ARRAY_UNDERFLOW;
    }
    if ((result = SearchMeeting(_ADPtr, _beginHour, &indexToRemove)) != ERR_OK)
    {
        return result;
    }
    free(_ADPtr->m_Meetings[indexToRemove]);
    CloseGap(_ADPtr, indexToRemove);
    --_ADPtr->m_NumOfMeetings;
    return ERR_OK;
}

Meeting* FindMeeting(ADPtr *_ADPtr, float _beginHour)
{
    size_t i, index;
    ADTErr result;
    if (_ADPtr == NULL)
    {
        return NULL;
    }
    if (_beginHour < 0 || _beginHour > 23.99)
    {
        return NULL;
    }
    if (_ADPtr->m_NumOfMeetings == 0)
    {
        return NULL;
    }
    if ((result = SearchMeeting(_ADPtr, _beginHour, &index)) != ERR_OK)
    {
        return NULL;
    }

    return _ADPtr->m_Meetings[index];
}

void PrintOneMeeting(Meeting* _meeting)
{
	if (NULL == _meeting)
	{
		printf("Meeting Does Not Exist!\n");
		return;
	}
	printf("Meeting Begin Hour: %-10f.\n",_meeting->m_BeginHour);
	printf("Meeting Begin Hour: %-10f.\n",_meeting->m_EndHour);
	printf("Meeting Begin Hour: %-10d.\n",_meeting->m_RoomNumber);
	return;
}

/*Unit Test Only*/
ADTErr ADMeetingsNum(ADPtr *_ADPtr, size_t *_numOfMeetings)
{
    if (NULL == _ADPtr)
    {
        return ERR_POINTER_NOT_INTIALIZED;
    }
    if (NULL == _numOfMeetings)
    {
        return ERR_GENERAL;
    }
    *_numOfMeetings = _ADPtr->m_NumOfMeetings;
    return ERR_OK;
}


    

void FunctionStatus(ADTErr _status)
{
    switch (_status)
    {
        case (ERR_OK):
        printf("Function Return::  ERR_OK  ::Status\n");
        break;

        case (ERR_GENERAL):
        printf("Function Return::  ERR_GENERAL  ::Status\n");
        break;

        case (ERR_MEETINGS_ARRAY_OVERFLOW):
        printf("Function Return::  ERR_MEETINGS_ARRAY_OVERFLOW  ::Status\n");
        break;

        case (ERR_MEETINGS_ARRAY_UNDERFLOW):
        printf("Function Return::  ERR_MEETINGS_ARRAY_UNDERFLOW  ::Status\n");
        break;

        case (ERR_POINTER_NOT_INTIALIZED):
        printf("Function Return::  ERR_POINTER_NOT_INTIALIZED  ::Status\n");
        break;

        case (ERR_REALLOCATION_FAILURE):
        printf("Function Return::  ERR_REALLOCATION_FAILURE  ::Status\n");
        break;

        case (ERR_MEETING_DOES_NOT_EXIST):
        printf("Function Return::  ERR_MEETING_DOES_NOT_EXIST  ::Status\n");
        break;

        case (ERR_INVALID_MEETING_INPUTS):
        printf("Function Return::  ERR_INVALID_MEETING_INPUTS  ::Status\n");
        break;

        case (ERR_ALLOCATION_FAILURE):
        printf("Function Return::  ERR_ALLOCATION_FAILURE  ::Status\n");
        break;

        case (ERR_MEETING_OVERLAP):
        printf("Function Return::  ERR_MEETING_OVERLAP  ::Status\n");
        break;

        default: break;
    }
    return;
}

ADTErr LoadFromFileAD(ADPtr *_ADPtr,const char *_fileName)
{
	float beginHour, endHour;
	int roomNumber;
	ADTErr status;
	if (NULL == _ADPtr)
	{
		return ERR_POINTER_NOT_INTIALIZED;
	}
	FILE *fp = fopen(_fileName, "a+");
	if (NULL == fp)
	{
		return ERR_OCCURED_WHILE_OPENING_THE_FILE;
	}
	fseek(fp,0,0); /*make sure at the begining*/
	while (1)
	{
		fscanf(fp,"%f  %f  %d", &beginHour, &endHour, &roomNumber);
        if (feof(fp))
        {
            break;
        }
        /*create meeting*/
        if ((status = CreateMeetingAD(beginHour, endHour, roomNumber, _ADPtr) != ERR_OK))
        {
        	return status;
        }
        /*Insertion*/
        if ((status = InsertAD(_ADPtr)) != ERR_OK)
        {
        	return status;
        }
    }
	fclose(fp);
	return ERR_OK;
}

ADTErr SaveToFileAD(ADPtr *_ADPtr, const char *_fileName)
{
	float beginHour, endHour;
	int roomNumber, index;
	ADTErr status;
	if (NULL == _ADPtr)
	{
		return ERR_POINTER_NOT_INTIALIZED;
	}
	FILE *fp = fopen(_fileName, "w+");
	if (NULL == fp)
	{
		return ERR_OCCURED_WHILE_OPENING_THE_FILE;
	}
	fseek(fp,0,0); /*make sure at the begining*/
	for(index = 0; index < _ADPtr->m_NumOfMeetings; ++index)
	{
		fprintf(fp, "%.f  %.f  %.d\n", _ADPtr->m_Meetings[index]->m_BeginHour,
		_ADPtr->m_Meetings[index]->m_EndHour,_ADPtr->m_Meetings[index]->m_RoomNumber);
	}
	fclose(fp);
	return ERR_OK;

}















/*end of file*/
