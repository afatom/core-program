#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stddef.h>
/*******************************************************************************
DESCRIPTION: The strcpy() function copies the string pointed to by src, including
the terminating null byte ('\0'), to the buffer pointed to by dest.
The strings may not overlap, and the destination string dest must be
large enough to receive the copy.  Beware of buffer overruns!  (See
BUGS.)

RETURN VALUE:  The strcpy() and strncpy() functions return a pointer to the
       destination string dest.
*******************************************************************************/
char* StrCopy(char *_destStr, const char *_srcStr);

/*******************************************************************************
DESCRIPTION: The strcpy() function copies the string pointed to by src, including
the terminating null byte ('\0'), to the buffer pointed to by dest.
The strings may not overlap, and the destination string dest must be
large enough to receive the copy.  Beware of buffer overruns!  (See
BUGS.)

RETURN VALUE:  The strcpy() and strncpy() functions return a pointer to the
       destination string dest.
*******************************************************************************/
char* ModifiedStrCopy(char *_destStr, const char *_srcStr);

/*******************************************************************************
DESCRIPTION: The strcpy() function copies the string pointed to by src, including
the terminating null byte ('\0'), to the buffer pointed to by dest.
The strings may not overlap, and the destination string dest must be
large enough to receive the copy.  Beware of buffer overruns!  (See
BUGS.)

RETURN VALUE:  The strcpy() and strncpy() functions return a pointer to the
       destination string dest.
*******************************************************************************/
char* RecorsiveStrCopy(char *_destStr, const char *_srcStr);
/*******************************************************************************
 DESCRIPTION: The strncpy() function is similar, except that at most n bytes of src
       are copied.  Warning: If there is no null byte among the first n
       bytes of src, the string placed in dest will not be null-terminated.

       If the length of src is less than n, strncpy() writes additional null
       bytes to dest to ensure that a total of n bytes are written.
*******************************************************************************/
char* StrNCopy(char *_destStr, const char *_srcStr, size_t _numOfChars);

/*******************************************************************************
 DESCRIPTION: The strncpy() function is similar, except that at most n bytes of src
       are copied.  Warning: If there is no null byte among the first n
       bytes of src, the string placed in dest will not be null-terminated.

       If the length of src is less than n, strncpy() writes additional null
       bytes to dest to ensure that a total of n bytes are written.
*******************************************************************************/
char *RecorsiveStrNCopy(char *_destStr, const char *_srcStr, size_t _numOfChars);

/*******************************************************************************
DESCRIPTION: The strcmp() function compares the two strings s1 and s2.  It returns
       an integer less than, equal to, or greater than zero if s1 is found,
       respectively, to be less than, to match, or be greater than s2.

       The strncmp() function is similar, except it compares only the first
       (at most) n bytes of s1 and s2.
RETURN VALUE        
       The strcmp()  function return an integer less than,
       equal to, or greater than zero if s1 (or the first n bytes thereof)
       is found, respectively, to be less than, to match, or be greater than
       s2.
********************************************************************************/
int StrCompare(const char *_destStr, const char *_srcStr);

/*******************************************************************************
DESCRIPTION: The strcmp() function compares the two strings s1 and s2.  It returns
       an integer less than, equal to, or greater than zero if s1 is found,
       respectively, to be less than, to match, or be greater than s2.

       The strncmp() function is similar, except it compares only the first
       (at most) n bytes of s1 and s2.
RETURN VALUE        
       The strcmp()  function return an integer less than,
       equal to, or greater than zero if s1 (or the first n bytes thereof)
       is found, respectively, to be less than, to match, or be greater than
       s2.
********************************************************************************/
int RecorsiveStrCompare(const char *_destStr, const char *_srcStr);

/*******************************************************************************
DESCRIPTION:        The strcat() function appends the src string to the dest string,
       overwriting the terminating null byte ('\0') at the end of dest, and
       then adds a terminating null byte.  The strings may not overlap, and
       the dest string must have enough space for the result.  If dest is
       not large enough, program behavior is unpredictable; buffer overruns
       are a favorite avenue for attacking secure programs.
RETURN VALUE: The strcat() and strncat() functions return a pointer to the
       resulting string dest.     
       
********************************************************************************/
char* StrCat(char *_destStr, const char *_srcStr);

/*******************************************************************************
DESCRIPTION: The strlen() function calculates the length of the string pointed to
       by s, excluding the terminating null byte ('\0').
RETURN VALUE: The strlen() function returns the number of characters in the string
       pointed to by s.     
********************************************************************************/
size_t StrLength(const char *_destStr);

/*******************************************************************************
DESCRIPTION: The strlen() function calculates the length of the string pointed to
       by s, excluding the terminating null byte ('\0').
RETURN VALUE: The strlen() function returns the number of characters in the string
       pointed to by s.     
********************************************************************************/
size_t RecorsiveStrLength(const char *_destStr);

/*******************************************************************************
DESCRIPTION: The strstr() function finds the first occurrence of the src string
in the string dest. The terminating null bytes ('\0') are not compared.
RETURN VALUE: This function return a pointer to the beginning of the located
src string, or NULL if the src string is not found.
*******************************************************************************/
const char *StrStr(const char *dest, const char *src);

#endif /* "_STRINGS_H_"*/
