#include "diary.h"
#include "ADTErr.h"
#include <stdlib.h> /*for size_t*/
#include <stdio.h>


int main ()
{
    /*initilaizing calendar pointer. points to calendar struct*/
    ADPtr *_ADPtr = NULL; 
    /*user input - char input -*/
    char userInput;
    char fileName[32];
    float beginHour, endHour; 
    int roomNumber;
    ADTErr status;
    size_t size, IncrBlock;
    Meeting* meeting = NULL;

    _ADPtr = NULL;
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    printf("                    Welcome To Appointment Diary (AD) Generation Program                            \n");
    printf("      This App will helps u to make simple diary operation on your diary as mintioned bellow        \n");

    printf("                                                                                                    \n");

    printf("These Abbreviations Will Allows You To Manage & Control The App Functionality\n");

    printf("c) Create AD    m) Create meeting    i) Insert appointment into AD\n");
    printf("r) Remove appointment from AD     f) Find appointment in AD  j)print serched meeting   d) Destroy AD     p) Print AD\n");

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Chose C letter to build you diary");
    while (1)
    {
        printf("Waiting   For   An   Input:\n");
        userInput = (char)(getchar());
        switch (userInput)
        {
        case ('c'):
            printf("Insert Calendar Meetings Array Size\n");
            scanf("%lu", &size);
            printf("Insert Calendar Meetings Incr Block\n");
            scanf("%lu", &IncrBlock);
            /*calling function create AD*/
            _ADPtr = CreateAD(size, IncrBlock);
            if (NULL == _ADPtr)
            {
                printf("Operating System Fails To Allocate Memory! Try Again.\n");
            }
            break;

        case ('m'):
            printf("Insert begin hour\n");
            scanf("%f", &beginHour);
            
            printf("Insert Meeting End Hour\n");
            scanf("%f", &endHour);
            
            printf("Insert room_number: \n");
            scanf("%d", &roomNumber);
            
            status = CreateMeetingAD(beginHour, endHour, roomNumber, _ADPtr);
            FunctionStatus(status);
            break;

        case ('i'):
            printf("inserting the last Created Meeting\n");
            /*calling function insert*/
            status = InsertAD(_ADPtr);
            FunctionStatus(status);
            break;
            
		case('u'):
			printf("ENter File Name For Uploading your meetings: ");
			scanf("%s", fileName);
			printf("\n");
			status = LoadFromFileAD(_ADPtr, fileName);
			FunctionStatus(status);
			break;
			
		case('s'):
			status = SaveToFileAD(_ADPtr, fileName);
			FunctionStatus(status);
			printf("Saving Meeting To Txt File Was Accomplished!\n");
			break;
			
        case ('r'):
            printf("Insert Beging Hour For Removing Meeting\n");
            /*calling function remove*/
            printf("Please insert the beging hour of the meeting that you would to erase\n");
            scanf("%f", &beginHour);
            status = RemoveAD(_ADPtr, beginHour);
            FunctionStatus(status);
            break;

        case ('f'):
            printf("Insert begin hour to search Meetings array\n");
            scanf("%f", &beginHour);
            meeting = FindMeeting(_ADPtr, beginHour);
            break;
            
            case ('j'): 
            PrintOneMeeting(meeting);
            break;
            
        case ('p'):
            printf("Printing your Whole Daiary Calendar for today!\n");
            /*calling function print*/
            PrintAD(_ADPtr);
            break;
        case ('d'):
            printf("These Opperation will delete all dairy calendar for today!\n");
            DestroyAD(_ADPtr);
            break;
            
        case ('e'):
            printf("Exiting App\n");
            DestroyAD(_ADPtr); 
            exit(0);
            break;
        }
        
    }
    return 0;
}

