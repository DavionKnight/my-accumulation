#include "stdafx.h"
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
//日志级别
typedef enum LogLevel
{
    LOG_FATAL = 1,
    LOG_ERROR = 2,
    LOG_WARNING = 3,
    LOG_INFO = 4
}LogLevel;

//记录用户设置的日志级别的全局变量
extern LogLevel log_level;

//日志文件的文件指针
extern FILE* ffp;
extern FILE* wfp;
extern FILE* efp;
extern FILE* ifp;

//初始化日志
void log_init(const char* log_path, const char* program, LogLevel level);

#define flog(fmt,...)\
{\
	if(log_level >= LOG_FATAL)\
    	{\
		fprintf(ffp,"%s Line:%u Fatal:",__FUNCTION__,__LINE__);\
		fprintf(ffp,fmt,##__VA_ARGS__);\
    	}\
}\

#define elog(fmt,...)\
{\
	if(log_level >= LOG_ERROR)\
    	{\
		fprintf(efp,"%s Line:%u Error:",__FUNCTION__,__LINE__);\
		fprintf(efp,fmt,##__VA_ARGS__);\
    	}\
}\

#define wlog(fmt,...)\
{\
	if(log_level >= LOG_WARNING)\
    	{\
		fprintf(wfp,"%s Line:%u Warning:",__FUNCTION__,__LINE__);\
		fprintf(wfp,fmt,##__VA_ARGS__);\
    	}\
}\

#define ilog(fmt,...)\
{\
	if(log_level >= LOG_INFO)\
    	{\
		fprintf(ifp,"%s Line:%u Info:",__FUNCTION__,__LINE__);\
		fprintf(ifp,fmt,##__VA_ARGS__);\
    	}\
}\

#endif//LOG_H