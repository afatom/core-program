#include <stdio.h>
#include <string.h>
#include <stddef.h>
/*
size_t MyStrLen (const char* str)
{
    int i=0; size_t counter=0;
    if (NULL==str)
    {
        return 0;
    }
    while (str[i]!='\0')
    {
        ++i;
        ++counter;
    }
    return counter;
}
*/

size_t MyStrLen (const char* str)
{
    int count=0;
    for (count;str[count]!='\0';++count)
    { }
    return count;
}
/*
size_t MyStrLen (const char* str)
{
    char* strPtr=0;
    while (*strPtr++!='\0')
    {}
    return s;
}
*/
char* Mystrtok (char* str, const char* tokens)
{
    size_t len = MyStrLen(str);
    const char** tokensArr[len];
    char* tok = strpbrk (str, tokens);
    /*if we didnt found matching chars from tokens str in str*/
    if (tok==NULL)
    {
        return tok;
    }
    /*if we found we replace its position with null and save this place*/
    str[*tok]='\0';
    return NULL;
}

int main ()
{
    /*
    char name [10]; char lastname [25]="ABCDEFGH";
    printf("Enter your first name bellow:\n");
    scanf("%s",name);
    printf("Hellow %s  . [name length =%lu]\n",name,strlen(name));
    printf("Hello %s\n", lastname);
    return 0;*/
    char* namee = "Adham";
    char name[]= "Adham";
    size_t length1 = MyStrLen (namee);
    size_t length2 = MyStrLen (name);
    printf("String length = %lu\n",length1);
    printf("String length = %lu\n",length2);
    return 0;
}