#ifndef __ZLOG4C_H_
#define __ZLOG4C_H_

#include <stdio.h>
#include <stdlib.h>     /* atexit */
#include <time.h> /*time stamp*/
#include <sys/types.h> /*get pid func*/
#include <unistd.h>    /*get pid func*/

#include <unistd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>

/*extern Zlog* fdata;
*/

typedef enum LogVorbus{
    LOG_TRACE = 'T',
    LOG_DEBUG = 'D',
    LOG_INFO = 'I',
    LOG_WARNINIG = 'W',
    LOG_ERROR = 'E',
    LOG_CRITICAL = 'C',
    LOG_SEVERE = 'S',
    LOG_FATAL = 'F',
    LOG_NONE = 'N'

}LogVorbus;

#define ZLOG(module, level, message) zlogPrint(module, level, message, __FILE__, __LINE__, __func__)
/*
#pragma GCC diagnostic error "-Werror"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic pop
*/
/** @brief Initializing zlogger function.  
 *  @details function takes config file name for loading data and 
 *  configuration/mode.
 * @params _fileName :full path to the config file or just the name of the file if
 * the file exist in the folder.
 * @returns void
 * @retval saving level log path and name of the log file for storing errors.
 * @warning config file must follow the shape here(Ex.):
 * Level = LOG_TRACE
 * Path = /home/user/...(full path to the dir )
 * File = filename.txt 
 */
void ZlogInit(const char* _configFileName);

/** @brief Exiting Zlog logger in agraceful way.
 *  @details call this function at Main end.
 * @params no params
 * @warning: data andd error log file Not guaranteed if user does not call this function
 * at the end of main func. 
 */
void AtExit(void);
/*
 ctime(&curtime), getpid(), gettid(),
*/


/**@brief macro function wich prints log entries in respect to LOG_TRACE level.
 * @params no Module name, log trace leve and user msg (all params given by user) 
 * @return log entires saved in log file 
 * @warning. 
 */

int zlogPrint(const char *_module, LogVorbus _level, const char *_message, const char *_file, int _line, const char *_func);
/*
#define ZlogPrintBegin(LOG_LEVEL, MODULE_NAME, FUNCTION_NAME, USER_MSG) {\
                    const char *msg = #USER_MSG;\
                    const char *trace = #LOG_LEVEL;\
                    const char* funcName = #FUNCTION_NAME;\
                    const char* modName = #MODULE_NAME;\
                    pthread_t threadid;\
                    time_t curtime;\
                    char EnumLevel[12]="TDIWECSFN";\
                    char* logPtr=NULL;\
                    char res[2];\
                    res[0]=trace[1];\
                    res[1]='\0';\
                    time(&curtime);\
                    logPtr = strstr(EnumLevel,res);\
                    if(NULL == logPtr) {\
                        exit(1);}\
                    threadid = pthread_self();\
                    fprintf(data.m_logFile, "\n%s %s %d %lu %c %s %s@%s %c %d %s\n", __DATE__, __TIME__,getpid(),threadid,\
                    trace[1],modName,funcName,__FILE__, ':',__LINE__,msg);\
                    data.m_levelMode = trace[1];\
                                                            };


*/



#endif /*__LOGGER_H_*/
