

#include "CLog.h"


//全局打开的文件指针
FILE* g_pFile = NULL;
//当前日志的文件名
char g_LogCurrFileName[256] = { 0 };
//设置日志文件大小
int g_LogFileSize;
//设置日志文件数量
int g_LogFileCount;
//文件名
char g_AppName[32] = { 0 };
//当前文件运行路径
char g_AppPath[MAX_PATH] = { 0 };
//日志级别
int g_LogLevel = LOG_INFO;

//文件大小计数
unsigned int g_filesizecount = 0;

// _DEBUG_LOG
int WriteToLog(char* str)
{
	FILE* log;
	log = fopen("D:\\MyServer\\n123.txt", "a+");
	if (log == NULL){
		OutputDebugString("Log file open failed.");
		return -1;
	}
	fprintf(log, "%s\n", str);
	fclose(log);
	return 0;
}


/***************************************************************************/
int Clog_Init(int filesize, int filecount, int level)
{


	if (!(level < LOG_DEBUG || level > LOG_ERROR))
	{
		g_LogLevel = level;
	}

	//文件数量不能超过10份 默认3份
	if (filecount < 1 || filecount >10)
	{
		g_LogFileCount = 3;
	}
	else
	{
		g_LogFileCount = filecount;
	}


	//存储的文件大小每份不能超过10兆
	if (filesize < 1 || filesize >10)
	{
		g_LogFileSize = 4;
	}
	else
	{
		g_LogFileSize = filesize * 1024;
	}

	//1
	char curDirPath[MAX_PATH] = {0};
	//取当前执行模块的全路径,如果此模块是被其它程序调用的,返回的路径还是这个程序的路径
	GetModuleFileName(NULL, curDirPath, MAX_PATH);



	int pathlen = strlen(curDirPath);

	do
	{
		if (curDirPath[pathlen] == '\\')
		{
			pathlen++;
			break;
		}
	} while (pathlen--);

	strncpy(g_AppPath, curDirPath, pathlen-1);

	int i = 0;
	do
	{
		if (curDirPath[pathlen + i] == '.')
		{
			g_AppName[i + 1] = '\0';
			break;
		}
		g_AppName[i] = curDirPath[pathlen + i];

	} while (++i);
#ifdef _DEBUG_LOG
	printf("this App Path: %s\n", g_AppPath);
	printf("this App Name: %s\n", g_AppName);
	WriteToLog(g_AppPath);
	WriteToLog(g_AppName);
#endif

	char temp[260] = {0};
	sprintf(temp,"%s\\log",g_AppPath);
#ifdef _DEBUG_LOG
	WriteToLog(temp);
#endif
	//检查日志文件夹是否存在
	if (_access(temp, 0) == -1)
	{
#ifdef _DEBUG_LOG
		WriteToLog("log文件夹不存在，即将创建log文件夹\n");
#endif
		if (!_mkdir(temp))
		{
#ifdef _DEBUG_LOG
			WriteToLog("文件夹创建成功...\n");
#endif
		}else
		{
#ifdef _DEBUG_LOG
			WriteToLog("文件夹创建失败...\n");
#endif
			return -1;
		}
	}


	//查找文件
	char isLogFile[MAX_PATH] = { 0 };
	i = 0;
	do 
	{
		sprintf(g_LogCurrFileName, "%s\\%s%02d.log", temp,g_AppName, i);

#ifdef _DEBUG_LOG
		WriteToLog(g_LogCurrFileName);
#endif

		if(_access(g_LogCurrFileName, 0) == -1)
		{
			break;
		}
		//目前默认10份日志
	} while (++i < filecount);
	if (i == filecount)
	{
		sprintf(g_LogCurrFileName, "%s\\%s00.log", temp,g_AppName);
	}
#ifdef _DEBUG_LOG
	WriteToLog(g_LogCurrFileName);
#endif

	g_pFile = fopen(g_LogCurrFileName, "w");
	if(g_pFile == NULL)
	{

#ifdef _DEBUG_LOG
		WriteToLog("文件打开失败...\n");
#endif
		return -2;
	}
	g_filesizecount = 0;

	//	fprintf(g_pFile, "%s,%d\n", __FILE__, __LINE__);
	//	fprintf(g_pFile, "%s,%d\n", __FILE__, __LINE__);
	//	fprintf(g_pFile, "%s,%d\n", __FILE__, __LINE__);
	//	fprintf(g_pFile, "%s\n", __DATE__);
	//
	//	fclose(g_pFile);

	return 0;
}

//写文件操作

int Clog_Write(int  level ,char* srcpath, int srcline, char* log)
{

	//测试用100字节分文件 / 40
	if (g_filesizecount >= (unsigned int)g_LogFileSize * 1024/*/ 40*/) 
	{
		//关闭上一个文件
		fclose(g_pFile);
		g_pFile = NULL;

		//char isLogFile[MAX_PATH] = { 0 };

		//接上一个文件继续保存日志
		char newlogfilename[32] = { 0 };
		int logfilenamelen = strlen(g_LogCurrFileName);

		do
		{
			if (g_LogCurrFileName[logfilenamelen] == '.')
			{
				logfilenamelen -=2;
				break;
			}
		} while (logfilenamelen--);



		printf("%s\n", &g_LogCurrFileName[logfilenamelen]);
		int filecount = atoi(&g_LogCurrFileName[logfilenamelen]);
		if ((filecount += 1) >= g_LogFileCount)
		{
			filecount = 0;
		}

		sprintf(g_LogCurrFileName, "%s\\log\\%s%02d.log", g_AppPath, g_AppName, filecount);
#ifdef _DEBUG_LOG
		WriteToLog("多份分割");
		WriteToLog(g_LogCurrFileName);
#endif

		g_pFile = fopen(g_LogCurrFileName, "w");
		g_filesizecount = 0;
	}




	//[级别][日期][文件][行号]：[自定义日志(log)]
	//取源码文件名方便定位
	char srcfilename[32] = { 0 };
	int srcpathlen = strlen(srcpath);

	do
	{
		if (srcpath[srcpathlen] == '\\')
		{
			srcpathlen++;
			break;
		}
	} while (srcpathlen--);

	//错误级别
	char szlevel[16] = { 0 };
	switch (level)
	{
	case LOG_ERROR:
		sprintf(szlevel,"%s","ERROR");
		break;
	case LOG_WARN:
		sprintf(szlevel, "%s", "WARN");
		break;
	case LOG_INFO:
		sprintf(szlevel, "%s", "INFO");
		break;
	case LOG_DEBUG:
		sprintf(szlevel, "%s", "DEBUG");
		break;
	default:
		break;
	}

	//获取当前时间
	time_t now = time(NULL);
	struct tm* tmnow = localtime(&now);
	char logheader[256] = { 0 };

	sprintf(logheader, "[%04d-%02d-%02d %02d:%02d:%02d][%s][%d][%s]", \
		tmnow->tm_year + 1900,\
		tmnow->tm_mon + 1,\
		tmnow->tm_mday,\
		tmnow->tm_hour, \
		tmnow->tm_min, \
		tmnow->tm_sec,\
		&srcpath[srcpathlen],\
		srcline,\
		szlevel);

	g_filesizecount += fprintf(g_pFile,"%s : %s\n",logheader,log);
	//fflush(g_pFile);
	//fwrite("ceshi\n", 1, strlen("ceshi\n"), g_pFile);


	return 0;
}
int Clog_Uninit()
{
	//防止二次关闭
	if (g_pFile != NULL)
	{
		fclose(g_pFile);
		g_pFile = NULL;
		return 0;
	}

	return 0;
}


/***************************************************************************/
