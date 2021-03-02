#include "zlog4c.h"
#include <stdio.h> /*printf*/
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG

#define MAX_LINE_LENGTH 512

/*****************************************************************/
char *GetLevel(char *str);
char *GetPath(char *str, char *path);
char *GetFile(char *str, char *logFile);
/*****************************************************************/
typedef struct Zlog Zlog;

struct Zlog
{
    FILE *m_logFile;       /*<< error file to be written*/
    LogVorbus m_levelMode; /*<< level mode*/
};

struct Zlog data;

void ZlogInit(const char *_configFileName)
{
    FILE *fp = NULL;
    char *str = NULL;
    char *path = NULL;
    char *file = NULL;
    char *level = NULL;
    int counter = 3;

    str = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    path = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
    file = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));

    fp = fopen(_configFileName, "r");
    if (NULL == fp)
    {
        printf("Error Occured While Opening Config File!\n");
        return;
    }
    fseek(fp, 0, 0);
    while (fgets(str, MAX_LINE_LENGTH, fp) != NULL || counter > 0)
    {
        if (strstr(str, "Level") != NULL)
        {
            level = GetLevel(str);
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

    data.m_logFile = fopen(path, "a+");
    assert(NULL != data.m_logFile);

    fclose(data.m_logFile);
    fclose(fp);
    free(path);
    free(file);
    free(str);
    return;
}

char *GetLevel(char *str)
{
    char *pos = NULL;
    pos = strstr(str, "= ");
    pos += 2;
    return pos;
}

char *GetPath(char *str, char *path)
{
    char *pos = NULL;
    str = strstr(str, "/");
    sscanf(str, "%s", path);
    return pos;
}

char *GetFile(char *str, char *logFile)
{
    char *pos = NULL;
    pos = strstr(str, "= ");
    pos += 2;
    sscanf(pos, "%s", logFile);
    return pos;
}

void DoAtExit(void)
{
    fputs("@End Of Log File", data.m_logFile);
    fflush(data.m_logFile);
    fclose(data.m_logFile);
    return;
}

void AtExit(void)
{
    atexit(DoAtExit);
    return;
}

static void GetConfigData()