#include "zlog4c.h"
#include <stdio.h>      /*printf*/
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG
#define DENIED 0
#define CIRTIFIED 1
#define MAX_LINE_LENGTH 512

/*****************************************************************/
static char *GetLevel(char *str);
static char *GetPath(char *str, char* path);
static char *GetFile(char *str, char* logFile);
static void GetConfigData(FILE* fp, char* path, char* file, char* str);
static void DoAtExit(void);
static int CheckLevelPriority(LogVorbus _level);
/*****************************************************************/

struct Zlog
{
    FILE*       m_logFile;       /*<< error file to be written*/
    LogVorbus   m_levelMode; /*<< level mode*/
};
static struct Zlog data;
typedef struct Zlog Zlog;

/*****************************************************************/

void ZlogInit(const char* _configFileName)
{
    FILE *fp = NULL;
    char *str = NULL, *path = NULL, *file=NULL;

    str = (char*)malloc(MAX_LINE_LENGTH* sizeof(char));
    path = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    file = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));

    /*
    fdata=(struct Zlog*)malloc(sizeof(struct Zlog));
    */

    fp = fopen(_configFileName, "r");
    if (NULL == fp)
    {
        printf("Error Occured While Opening Config File!\n");
        return;
    }
    GetConfigData(fp, path, file,str);
    AtExit();
    return;
}
/*****************************************************************/
void AtExit(void)
{
    atexit(DoAtExit);
    return;
}
/*****************************************************************/

int zlogPrint(const char *_module, LogVorbus _level, const char *_message, const char *_file, int _line, const char *_func)
{
    time_t timer;
    char buffer[20];
    struct tm *tm_info;

    if (data.m_logFile == NULL || (CheckLevelPriority(_level)) != CIRTIFIED)
    {
        return 0;
    }

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(data.m_logFile, "%s %d %ld %c %s %s@%s:%-5d %s\n", buffer, getpid(), pthread_self(), 
    _level, _module, _func, _file, _line, _message);

    return 1;
}

/**************/
/*Static funcs*/

static int CheckLevelPriority(LogVorbus _level)
{
    char *pos = NULL;
    char EnumLevel[12] = "TDIWECSFN";
    char* currentLevel = NULL;
    pos = strchr(EnumLevel,_level);
    currentLevel = strchr(EnumLevel,data.m_levelMode);
    assert(currentLevel != NULL);
    if(pos == NULL || (pos-currentLevel) < 0)
    {
        return DENIED;
    }
    return CIRTIFIED;
}

    /*****************************************************************/
    static char *GetLevel(char *str)
{
    char* pos = NULL;
    pos = strstr(str, "= ");
    pos +=2;
    return pos;
}
/*****************************************************************/
static char *GetPath(char *str, char* path)
{
    char *pos = NULL;
    str = strstr(str, "/");
    sscanf(str,"%s",path);
    return pos;
}
/*****************************************************************/
static char *GetFile(char *str, char* logFile)
{
    char *pos = NULL;
    pos = strstr(str, "= ");
    pos += 2;
    sscanf(pos, "%s", logFile);
    return pos;
}
/*****************************************************************/
static void DoAtExit(void)
{
    time_t timer;
    char buffer[20];
    struct tm *tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(data.m_logFile, "%s %d %ld LOG EXIT\n", buffer, getpid(), pthread_self());
    fputs("@End Of Log File\n", data.m_logFile);
    fflush(data.m_logFile);
    fclose(data.m_logFile); 
    return;
}

/*****************************************************************/
static void GetConfigData(FILE* fp, char* path, char* file, char* str)
{
    char *level = NULL;
    int counter = 3;
    fseek(fp, 0, 0);
    while (fgets(str, MAX_LINE_LENGTH, fp) != NULL || counter > 0)
    {
        if (strstr(str, "Level") != NULL)
        {
            level = GetLevel(str);
            /*fdata->m_levelMode = *level;*/
            data.m_levelMode = *level;
            
            --counter;
        }
        else if (strstr(str, "Path") != NULL)
        {
            GetPath(str, path);
            --counter;
        }
        else if (strstr(str, "File") != NULL)
        {
            GetFile(str, file);
            --counter;
        }
        else
        {
        };
    }

    strcat(path, "/");
    strcat(path, file);
    /*fdata->m_logFile = fopen(path, "a+");*/
    data.m_logFile = fopen(path, "a+");
    assert(NULL != data.m_logFile);

    fclose(fp);
    free(path);
    free(file);
    free(str);
    return;
}
/*****************************************************************/
