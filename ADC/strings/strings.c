#include "strings.h"
#include <stddef.h>

#include <stdio.h>
#include <stddef.h>
#include <string.h>

/******************************************************************************/
char *StrCopy(char *_destStr, const char *_srcStr)
{
    int i = 0;
    while (_srcStr[i] != '\0')
    {
        _destStr[i] = _srcStr[i];
        ++i;
    }
    _destStr[i] = '\0';
    return _destStr;
}
/******************************************************************************/
char *ModifiedStrCopy(char *_destStr, const char *_srcStr)
{
    while (*(_destStr)++ = *(_srcStr)++)
        ;
    *_destStr = '\0';
    return _destStr;
}
/******************************************************************************/
static void RRecStrCpy(char *_dest, const char *_src)
{
    if (*_src == '\0')
    {
        *_dest = '\0';
        return;
    }
    *_dest = *_src;
    RRecStrCpy((_dest + 1), (_src + 1));
    return;
}
/******************************************************************************/
char *RecorsiveStrCopy(char *_destStr, const char *_srcStr)
{
    char *ptr = _destStr;
    RRecStrCpy(ptr, _srcStr);
    return _destStr;
}
/******************************************************************************/
char *StrNCopy(char *_destStr, const char *_srcStr, size_t _numOfChars)
{
    size_t i;
    for (i = 0; i < _numOfChars && (*(_destStr)++ = *(_srcStr)++); ++i);
    *(_destStr) = '\0';
    return _destStr;
}
/******************************************************************************/
void RRecStrNNCpy(char *_dest, const char *_src, size_t _numOfChars)
{
    if (*_src == '\0')
    {
        *_dest = '\0';
        return;
    }
    if (_numOfChars == 0)
    {
        return;
    }
    *_dest = *_src;
    RRecStrNNCpy((_dest + 1), (_src + 1), _numOfChars - 1);
    return;
}
/******************************************************************************/
char *RecorsiveStrNCopy(char *_destStr, const char *_srcStr, size_t _numOfChars)
{
    char *destPtr = _destStr;
    RRecStrNNCpy(_destStr, _srcStr, _numOfChars);
    return _destStr;
}

/******************************************************************************/
/*
int myModStrCmp (const char* _destStr, const char* _srcStr)
{
	int i=0;
	for(i = 0; (*(_destStr)++ - *(_srcStr)++) != 0; ++i);
    return (*(_destStr) - *(_srcStr));
}
*/
/*
int myModStrCmp (const char* _destStr, const char* _srcStr)
{
	int i=0;
	for(i = 0; (*(_destStr+i) - *(_srcStr+i)) == 0 && (*(_srcStr)!='\0') && (*(_destStr)!='\0'); ++i);
    return (*(_destStr+i)-*(_srcStr+i));
}
*/
/******************************************************************************/
int StrCompare(const char *_destStr, const char *_srcStr)
{
    char i = 0;
    for (i = 0; (*(_destStr + i) - *(_srcStr + i)) == 0; ++i);
    return (*(_destStr + i) - *(_srcStr + i));
}
/******************************************************************************/
int RecorsiveStrCompare(const char *_destStr, const char *_srcStr)
{
    char i = 0;
    if ((*(_destStr) - *(_srcStr)) != 0)
    {
        return *_destStr - *_srcStr + i;
    }
    return RecorsiveStrCompare(++_destStr, ++_srcStr);
}
/******************************************************************************/
char *StrCat(char *_destStr, const char *_srcStr)
{
    while (*(_destStr)++);
    --_destStr;
    while (*(_destStr)++ = *(_srcStr)++);
    *_destStr = '\0';
    return _destStr;
}
/******************************************************************************/
size_t StrLength(const char *_destStr)
{
    size_t i = 0;
    for (i = 0; *(_destStr)++ != '\0'; ++i);
    return i;
}
/******************************************************************************/
size_t RecorsiveStrLength(const char *_destStr)
{
    size_t counter = 0;
    if (*_destStr == '\0')
    {
        return 0;
    }
    counter = RecorsiveStrLength(++_destStr) + 1;
    return counter;
}
/******************************************************************************/
const char *StrStr(const char *dest, const char *src)
{
    const char *srcptr = src;
    const char *dstptr = dest;
    int i, j;
    for (i = 0; *(dest)++ != '\0'; ++i)
    {
        srcptr = src;
        dstptr = dest;
        if (*dest == *srcptr)
        {
            /*
			while (*(srcptr)++ == *(dstptr)++ )
			{
			
			}*/
            for (j = 0; (*(srcptr)++ == *(dstptr)++) && *srcptr != '\0'; ++j)
                ;
            if (*srcptr == '\0') /*src was found in dest*/
            {
                return (dest);
            }
        }
    }
    return NULL;
}
/******************************************************************************/
