#include "word.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 512 /*file size*/
#define MAXLEN 32
#define MAX_LINE_LENGTH 512

struct Word
{
    size_t counter;
    char *str;
};

struct WC
{
    size_t m_NumOfWords;
    size_t m_Capacity;
    Word *m_WordsDA;
};

/************************************************************/
WC *CreateWC(size_t _capacity)
{
    WC *ptr = NULL;
    ptr = (WC *)malloc(sizeof(WC));
    if (NULL == ptr)
    {
        return NULL;
    }

    (ptr->m_WordsDA) = (Word *)malloc(_capacity * sizeof(Word));
    if (NULL == ptr->m_WordsDA)
    {
        free(ptr);
        return NULL;
    }

    ptr->m_NumOfWords = 0;
    ptr->m_Capacity = _capacity;
    return ptr;
}

/**************************************************************/
int AllocateWord(WC *ptr, size_t _len)
{
    char *tstr = NULL;
    tstr = (char*)malloc(_len * sizeof(char));
    if (NULL == tstr)
    {
        return 1; /*malloc failure*/
    }
    ptr->m_WordsDA[ptr->m_NumOfWords].str = tstr;
    return 0;
}

/****************************************************************/
int FindDuplicates(WC *ptr, const char *_str)
{
    for (size_t i = 0; i < ptr->m_NumOfWords; ++i)
    {
        if (!strcmp(ptr->m_WordsDA[i].str, _str))
        {
            return i;
        }
    }
    return -1;
}
/****************************************************************/
int IsReallocNeeded(WC *ptr)
{
    if (ptr->m_NumOfWords == ptr->m_Capacity)
    {
        return 1;
    }
    return 0;
}
/****************************************************************/
int ReallocWordsArray(WC *ptr)
{
    Word *tempArr = NULL;
    tempArr = (Word *)realloc(ptr->m_WordsDA, ptr->m_Capacity * 2 * sizeof(Word));
    if (NULL == tempArr)
    {
        return 1;
    }
    ptr->m_WordsDA = tempArr;
    ptr->m_Capacity += ptr->m_Capacity;
    return 0;
}
/******************************************************************/
/****************Print Words Array and there aperance**************/
void PrintWords(WC *ptr)
{
    int i;
    if (ptr->m_NumOfWords == 0)
    {
        printf("Empty File. No Words Have Been Found!\n");
        return;
    }
    printf("%lu___ different words\n",ptr->m_NumOfWords);
    
    //printf("Number Of Deferint Words");
    for (i = 0; i < ptr->m_NumOfWords; ++i)
    {
        printf(" %-10s   Appears  %10lu.\n", ptr->m_WordsDA[i].str, ptr->m_WordsDA[i].counter);
    }

    return;
}
/*******************************************************************/
void DestroyWC(WC **ptr)
{
    int i;
    if (NULL == *ptr)
    {
        return;
    }
    /*free string member*/
    for (i = 0; i < (*ptr)->m_NumOfWords; ++i)
    {
        free((*ptr)->m_WordsDA[i].str);
    }
    free((*ptr)->m_WordsDA);
    free(*ptr);
    *ptr = NULL;
    return;
}

/*******************************************************************/
void WordsCount(const char *_fileName)
{
    size_t len;
    int index, res;
    char tmpStr[32];
    FILE *fp = NULL;

    fp = fopen(_fileName, "r+");
    if (NULL == fp)
    {
        printf("Error Occured While Opening Your File!\n");
        return;
    }

    WC *ptr = CreateWC(CAPACITY);
    if (NULL == ptr)
    {
        printf("Unable To Claculating Words! Try Again\n");
        return;
    }
    /*make sure that offset =0*/
    fseek(fp, 0, 0);
    while (1)
    {
        if (IsReallocNeeded(ptr))
        {
            if (ReallocWordsArray(ptr))
            {
                printf("Error Occured While Working On File!\n");
                return;
            }
        }
        fscanf(fp, "%s", tmpStr);
        if (feof(fp))
        {
            break;
        }
        len = strlen(tmpStr);

        if ((index = FindDuplicates(ptr, tmpStr)) >= 0)
        {
            /*NO need for malloc - incr only*/
            ++ptr->m_WordsDA[index].counter;
            
        }
        else
        {
            AllocateWord(ptr, len + 1);
            strcpy(ptr->m_WordsDA[ptr->m_NumOfWords].str, tmpStr);
            ++ptr->m_WordsDA[ptr->m_NumOfWords].counter;
            ++ptr->m_NumOfWords;
        }
    }
        
    PrintWords(ptr);
    DestroyWC(&ptr);
    fclose(fp);
    return;
}

int CountLetters(const char *_destFileName)
{
    char letter;
    int ch;
    FILE *fp;
    int lcCounterArray['z'-'a'] = {0};
    int ucCounterArray['Z'-'A'] = {0};
    ucCounterArray['Z'-'A']= 0;

    fp = fopen(_destFileName, "r+");
    if (NULL == fp)
    {
        return -1;
    }
    fseek(fp, 0, 0);
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (feof(fp))
        {
        	break;
        }
        if (isalpha(ch))
        {
            if (islower(ch)) /*lower case*/
            {
                ++lcCounterArray[ch - 'a'];
            }
            /*upper case*/
            if (isupper(ch))
            {
                ++ucCounterArray[ch - 'A'];
            }
        }
    }
    fclose(fp);

    printf("Lower case arr\n");
    for (int i = 0; i < 26; ++i)
    {
        letter = i + 'a';
        printf("letter %c  appears %d times\n", letter, lcCounterArray[i]);
    }

    printf("Upper case arr\n");
    for (int i = 0; i < 26; ++i)
    {
        letter = i + 'A';
        printf("letter %c  appears %d times\n", letter, ucCounterArray[i]);
    }

    return 0;
}

int EraseBlinks(const char *_destinationFile, const char *_sourceFile)
{
    FILE* destPtr = NULL; 
    FILE* srcPtr = NULL;
    char str[MAXLEN];
    destPtr = fopen(_destinationFile, "r+");
    if (NULL == destPtr)
    {
        return 1;
    }

    srcPtr = fopen(_sourceFile, "r+");
    if (NULL == srcPtr)
    {
        fclose(destPtr); 
        return 1;
    }
    while(!feof(srcPtr))
    {
        fscanf(srcPtr,"%s",str);
        fprintf(destPtr,"%s",str);
    }
    fclose(srcPtr);
    fclose(destPtr);
    return 0;
}

void PrintLastNLines(const char *_destinationFile, size_t _num)
{
	if (_num == 0)
	{
		printf("Invalid Input!\n");
		return;
	}
	int counter = 0;
	unsigned int pos =0;
	size_t len = 0;
	char *str;
    FILE *fp = NULL;
    fp = fopen(_destinationFile, "r+");
    if (NULL == fp)
    {
        printf("Error Occured While Opening Your File!\n");
        return;
    }
    int *PosArr = NULL;
    PosArr = (int*)calloc(_num, sizeof(int));
    if (NULL == PosArr)
    {
        printf("Error Occured While Working On File!\n");
        return;
    }
    str = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (str == NULL)
    {
    	free(PosArr);
       	printf("Error Occured While Working On File!\n");
        return;
    }
    fseek(fp,0,0);
    PosArr[0]=0;
    ++counter;
    while (!feof(fp))
    {
    	fgets(str,MAX_LINE_LENGTH-1, fp);
    	if (NULL != fgets(str,MAX_LINE_LENGTH-1, fp))
    	{
    		/*
    		len = strlen(str);
    		len+=1;
    		printf("315 len = %lu\n", len);
    		sum += len;
    		*/
    		pos = ftell(fp);
    		PosArr[counter % _num]= pos;
    		++counter;
    		printf("Pos = %d\n", pos);
    		
    		//printf("309 cntr = %d\n", counter);
    	}
    	else
    	{
    		if (counter == 0) /*empty file*/
    		{
    			printf("Empty File !\n");
    			return;
    		}
    		break; /*counter != 0*/
    	}
    }
    fseek(fp, PosArr[(counter-1) % _num], 0); /*seek the begining of the _num line*/
    int i = 0;
    while (i<_num)
    {
    	fgets(str,MAX_LINE_LENGTH-1, fp);
    	printf("%s",str);
    	++i;
    }
    free(str);
    free(PosArr);
    fclose(fp);
    return;
}
    /*
    char *lineptr = NULL;
    size_t n = 0; size_t counter=0;
    size_t pos;
    fgets ( char * str, int num, FILE * stream )
    while ((nread != -1))
    {
        nread = getline(&lineptr, &n, destPtr);
        
        pos += nread;
        printf("pos = %lu\n", pos);
        PosArr[(counter % _num)] = pos;
        ++counter; 
    }
    
    for(size_t i =0; i<_num; ++i)
    {
        printf("Pos [ %lu ] = %lu\n", i,PosArr[i]);
    }
    
    
    free(lineptr);
    fclose(destPtr);

    return;
}*/
