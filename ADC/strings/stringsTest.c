#include <stdio.h>
#include "strings.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mu_test.h"
#include <time.h>

UNIT(Srand_init)
srand((unsigned int)time(NULL));
END_UNIT
/************************************************************/

UNIT(Strlen_Test)
char str[150] = "adsjgkja asdag dr $ sd kgbab sbdk bastryiritwer56565 99898 9823492348 3492341";
ASSERT_THAT (StrLength(str) == strlen(str));
ASSERT_THAT (RecorsiveStrLength (str)== strlen(str));
END_UNIT

UNIT(StrStr_Test)
char str[150] = "adsjgkja asdag dr $ sd kgbab sbdk ba IoT stryiritwer56565 99898 9823492348 3492341";
char src[10]="IoT";
ASSERT_THAT(StrStr(str, src) == strstr(str,src));
END_UNIT

UNIT(StrCat_Test)
char str[150] = "abcd  ";
char strt[150] ="abcd  ";

char src[15] = "IoT";
StrCat(str, src);
strcat(strt,src);
printf("%s     %s",str,strt);
ASSERT_THAT(strcmp(str,strt) == 0);
END_UNIT

UNIT(StrComp_Test)
char str[150] = "adsjgkja asdag dr $ sd kgbab sbdk ba      ";
char strt[150] = "adsjgkja asdag dr    ";
ASSERT_THAT(strcmp(str, strt) == StrCompare(str,strt));
ASSERT_THAT(strcmp(str, strt) == RecorsiveStrCompare(str, strt));
END_UNIT

UNIT(StrNcopy_Test)
char str1[150] = "adsjgkja asdag       adhkjh aa36663 ";
char str2[150] = "a $$";
char str3[150] = "a  g   b";
strncpy(str1,str2,10);
StrNCopy(str3,str2,10);
//ASSERT_THAT(strcmp(str1,str3)==0);
printf("\n%s             %s", str1, str3);
char str11[150] = "adsjgkja asdag       adhkjh aa36663 ";
char str22[150] = "adsjgkja asdag dr   $$$$$  ";
char str33[150] = "adsjgkja asdag dr   $$$$$  ";
strncpy(str11,str22,10);
//RecorsiveStrNCopy(str33,str22,10);
////ASSERT_THAT(strcmp(str11,str33)==0);

END_UNIT

UNIT(StrCopy_Test)
char str1[150] = "adsjgkja asdag       adhkjh aa36663 ";
char str2[150] = "adsjgkja asdag dr   $$$$$  ";
char str3[150] = "adsjgkja asdag dr   $$$$$  ";
strcpy(str1, str2);
ModifiedStrCopy(str3, str2);
ASSERT_THAT(strcmp(str1, str3) == 0);

char str11[150] = "adsjgkja asdag       adhkjh aa36663 ";
char str22[150] = "adsjgkja asdag dr   $$$$$  ";
char str33[150] = "adsjgkja asdag dr   $$$$$  ";
strcpy(str11, str22);
RecorsiveStrCopy(str33, str22);
ASSERT_THAT(strcmp(str11, str33) == 0);

END_UNIT

/*************************************************************************/

TEST_SUITE(Strings Tests)
TEST(StrStr_Test)
TEST(Strlen_Test)
TEST(StrCat_Test)
TEST(StrComp_Test)
TEST(StrNcopy_Test)
TEST(StrCopy_Test)
END_SUITE