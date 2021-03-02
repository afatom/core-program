#include "word.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define CAPACITY 512 /*file size*/

typedef struct Word 
{
    size_t  counter;
    char*   str; 
} Word;

typedef struct WC
{
    size_t  m_NumOfWords;
    size_t  m_Capacity;
    Word*   m_WordsDA; 
} WC;

/*************************************************/
WC* CreateWC(size_t _capacity)
{
    WC* ptr = NULL;
    ptr = (WC*)malloc(sizeof(WC));
    if (NULL == ptr)
    {
        return NULL;
    }
    
    (ptr->m_WordsDA) = (Word*)malloc(_capacity * sizeof(Word));
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
int AllocateWord(WC* ptr, size_t _len)
{
    char* tstr = NULL;
    tstr = (char*)malloc(_len * sizeof(char));
    if (NULL == tstr)
    {
        return 1; /*malloc failure*/
    }
    ptr->m_WordsDA[ptr->m_NumOfWords].str = tstr;
    return 0;
}

/****************************************************************/
int FindDuplicates(WC* ptr, const char* _str)
{
    for (size_t i=0; i < ptr->m_NumOfWords ; ++i)
    {
        if (!strcmp ( ptr->m_WordsDA[i].str, _str))
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
int ReallocWordsArray(WC* ptr)
{
    Word* tempArr = NULL;
    tempArr = (Word*)realloc(ptr->m_WordsDA, ptr->m_Capacity*2*sizeof(Word));
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
void PrintWords(WC* ptr)
{
    int i;
    if (ptr->m_NumOfWords == 0)
    {
        printf("Empty File. No Words Have Been Found!\n");
        return;
    }
    for (i =0; i < ptr->m_NumOfWords; ++i)
    {
        printf("%s Appears %lu.\n", ptr->m_WordsDA[i].str, ptr->m_WordsDA[i].counter);
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
    for(i = 0; i < (*ptr)->m_NumOfWords; ++i)
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
    FILE* fp = NULL;
    
    fp = fopen(_fileName, "r+");
    if (NULL == fp)
    {
        printf("Error Occured While Opening Your File!\n");
        return;
    }

    WC* ptr =  CreateWC(CAPACITY);
    if (NULL == ptr)
    {
        printf("Unable To Claculating Words! Try Again\n");
        return;
    }
    /*make sure that offset =0*/
    fseek(fp,0,0);
    while(!feof(fp))
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
        len = strlen(tmpStr);
		
        if ((index = FindDuplicates(ptr, tmpStr)) > 0)
        {
            /*NO need for malloc - incr only*/
            ++ptr->m_WordsDA[index].counter;
        }
        /*new word. we need malloc and insert*/
        if (res = AllocateWord(ptr, len+1))
        {
            printf("Error Occured While Working On File!\n");
            return;
        }
        strcpy(ptr->m_WordsDA[ptr->m_NumOfWords].str, tmpStr);
        ++ptr->m_WordsDA[ptr->m_NumOfWords].counter;
        ++ptr->m_NumOfWords;
	}
    PrintWords(ptr);
    DestroyWC(&ptr);
    fclose(fp);
    return;
}
