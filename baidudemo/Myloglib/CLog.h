#ifndef __CLOG__
#define __CLOG__

#include <stdio.h>
#include <windows.h>
#include "direct.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "io.h"


#ifdef __cplusplus
extern "C" {
#endif
/***************************************************************************/

#define LOG_ERROR		73
#define LOG_WARN			72
#define LOG_INFO			71
#define LOG_DEBUG		70


////全局打开的文件指针
//FILE* g_pFile = NULL;
////当前日志的文件名
//char g_LogCurrFileName[256] = { 0 };
////设置日志文件大小
//int g_LogFileSize;
////设置日志文件数量
//int g_LogFileCount;
////文件名
//char g_AppName[32] = { 0 };
////当前文件运行路径
//char g_AppPath[MAX_PATH] = { 0 };
////日志级别
//int g_LogLevel = LOG_INFO;
//
////文件大小计数
//unsigned int g_filesizecount = 0;




int WriteToLog(char* str);

int Clog_Init(int filesize, int filecount, int level);
int Clog_Write(int  level ,char* srcpath, int srcline, char* log);
int Clog_Uninit();



//使用宏代替
#define LOG_ERROR_FILE(LOGMSG)				\
	do																\
{	if(g_LogLevel >= LOG_ERROR )				\
{																	\
	Clog_Write(LOG_ERROR, __FILE__, __LINE__, LOGMSG);		\
}																	\
} while (0)

#define LOG_WARN_FILE(LOGMSG)			\
	do																\
{	if(g_LogLevel >= LOG_WARN )				\
{																	\
	Clog_Write(LOG_WARN, __FILE__, __LINE__, LOGMSG);		\
}																	\
} while (0)

#define LOG_INFO_FILE(LOGMSG)					\
	do																\
{	if(g_LogLevel >= LOG_INFO )				\
{																	\
	Clog_Write(LOG_INFO, __FILE__, __LINE__, LOGMSG);		\
}																\
} while (0)

#define LOG_DEBUG_FILE(LOGMSG)				\
	do																\
{	if(g_LogLevel >= LOG_DEBUG )				\
{																	\
	Clog_Write(LOG_DEBUG, __FILE__, __LINE__, LOGMSG);		\
}																	\
} while (0)

#define  LOG_FFLUSH\
	do				\
{	fflush(g_pFile);				\
} while (0)





/***************************************************************************/


















#ifdef __cplusplus
}
#endif

#endif //__CLOG__