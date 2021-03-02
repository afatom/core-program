#include <stdio.h>
#include <stddef.h>
#include <string.h>

/******************************************************************************/
char* myStrCpy (char* _destStr, const char* _srcStr)
{
    int i=0;
    while(_srcStr[i]!= '\0')
    {
        _destStr[i] = _srcStr[i];
        ++i;
    }
    _destStr[i]='\0';
    return _destStr;
}
/******************************************************************************/
char* myModStrCpy (char* _destStr, const char* _srcStr)
{
    while(*(_destStr)++ = *(_srcStr)++);
    *_destStr='\0';
    return _destStr;
}

void RRecStrCpy(char* _dest, const char* _src)
{
	if (*_src == '\0')
	{
		*_dest = '\0';
		return;
	}
	*_dest = *_src;
	RRecStrCpy((_dest+1), (_src+1));
	return;
}

char* myModRecStrCpy (char* _destStr, const char* _srcStr)
{
	char* ptr = _destStr;
   	RRecStrCpy(ptr, _srcStr);
    return _destStr;
}


/******************************************************************************/
char* myModStrNCpy (char* _destStr, const char* _srcStr, size_t _n)
{
	size_t i;
	for(i = 0; i < _n && (*(_destStr)++ = *(_srcStr)++) != 0; ++i);
    *_destStr='\0';
    return _destStr;
}


void RRecStrNNCpy(char* _dest, const char* _src, size_t _n)
{
	if (*_src == '\0')
	{
		*_dest = '\0';
		return;
	}
	if(_n == 0)
	{
		return;
	}
	*_dest = *_src;
	RRecStrNNCpy((_dest+1), (_src+1), _n-1);
	return;
}

char* myModRecStrNCpy (char* _destStr, const char* _srcStr, size_t _n)
{
	char* destPtr = _destStr;
	RRecStrNNCpy(_destStr, _srcStr ,_n);
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

int myModStrCmp (const char* _destStr, const char* _srcStr)
{
	char i=0;
	for(i = 0; (*(_destStr+i) - *(_srcStr+i)) == 0; ++i);
    return (*(_destStr+i)-*(_srcStr+i));
}
/******************************************************************************/
int myModRecStrCmp (const char* _destStr, const char* _srcStr)
{
	char i=0;
	if((*(_destStr) - *(_srcStr)) != 0)
	{
    	return *_destStr - *_srcStr+i;
	}
	return myModRecStrCmp (++_destStr, ++_srcStr);
	
}


/******************************************************************************/
char *mstrcat(char *_destStr, const char *_srcStr)
{
    while(*(_destStr)++);
    while(*(_destStr)++ = *(_srcStr)++);
    *_destStr='\0';
    return _destStr;
}
/******************************************************************************/
size_t mstrlen(const char *_destStr)
{
	size_t i=0;
	for(i = 0; *(_destStr)++!='\0'; ++i);
	return i;
}
/******************************************************************************/
size_t mRecStrlen(const char *_destStr)
{
	size_t counter =0;
	if(*_destStr == '\0')
	{
		return 0;
	}
	counter = mRecStrlen(++_destStr)+1;
	return counter;
}
/******************************************************************************/




/******************************************************************************/
const char* mstrstr ( const char *dest, const char *src)
{
	const char *srcptr = src;
	const char *dstptr = dest;
	int i, j;
	for(i=0; *(dest)++!='\0';++i)
	{
		srcptr = src;
		dstptr = dest;
		if(*dest == *srcptr)
		{
		/*
			while (*(srcptr)++ == *(dstptr)++ )
			{
			
			}*/
			for(j=0; (*(srcptr)++ == *(dstptr)++) && *srcptr !='\0' ; ++j);
			if(*srcptr=='\0') /*src was found in dest*/
			{
				return (dest);
			}
		
		}
	}
	return NULL;
}
/******************************************************************************/





int main()
{
	/*
    char _destStr[10]="a";
    char _srcStr[10]= "ABCD";
    myModStrCpy (_destStr, _srcStr);
    printf("%s\n", _destStr);
    
    char str1 [3]="aaa";
    char str2 [3]="aaa";
    myModStrNCpy (str2, str1,7);
    printf("%s\n", str2);
    
    myModStrCmp (str1, str2);
    
    char str4 [4]="aaa";
    char str5 [10]="c";
    
    printf("original strcmp = %d\n",  strcmp(str4, str5));
    printf("own strcmp = %d\n", myModStrCmp (str4, str5));
	
	strcat(str5, str4);
	mstrcat(str5, str4);
	
    printf("original strcat =  %s\n",  str5);
    printf("own strcat =       %s\n",  str5);
	
	size_t len1,len2;
	
	printf("original len1 =       %lu\n",   strlen(str5));
    printf("my func  len2 =       %lu\n",  mstrlen(str5));
    */
    //char dest[50]="adham is hero and and gever gever!!";
    //char src[6]="gever";
    //const char *find;
    //find = mstrstr (dest, src);
    //printf("my strstr func:  %c\n", *find);
    //find = strstr (dest, src);
	//printf("C  strstr func:  %c\n", *find);
    
    const char str1 [10]="aabab12599";
    const char str2 [100]="aa*84kkadadr4555555kkkk";    
    //printf("my strcmp = %d\n", myModStrCmp (str2, str1)); 
    //printf(" C strcmp = %d\n", strcmp(str2, str1)); 
    
    printf("Rec strlen %lu\n", mRecStrlen(str2)); 
    printf(" strlen %lu\n", mstrlen(str2)); 
    
    printf("original strcmp =   %d\n",  strcmp(str1, str2));
    printf("own strcmp =        %d\n", myModStrCmp (str1, str2));
    printf("own Rec strcmp =        %d\n", myModRecStrCmp (str1, str2));
    
    char strd [50]="aaaa";
    const char strs [100]="abc ddd ccc";  
    char* ptr;
  	puts("\n\n");
    ptr = myModRecStrNCpy (strd, strs, 9);
    printf("my rec strncpy %s\n",strd);
    ptr = strncpy(strd, strs,9);
    printf("C      strncpy %s\n",strd);
    
    
   
    
    
    return 0;
}









