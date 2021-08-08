#include "stdafx.h"
#include "log.h"
#include <limits.h>
#include <stdio.h>

//记录用户设置的日志级别的全局变量
LogLevel log_level;
#define PATH_MAX 100
//日志文件的文件指针
FILE* ffp;
FILE* wfp;
FILE* efp;
FILE* ifp;

#define sprintf sprintf_s


//初始化日志
void log_init(const char* log_path, const char* program, LogLevel level)
{
    log_level = level;
#ifdef DEBUG
    ffp = stdout;
    wfp = stdout;
    efp = stdout;
    ifp = stdout;
#else
    char path[PATH_MAX] = {};

    sprintf(path, "%s/%s_fatal.log", log_path, program);
    ffp = fopen(path, "a");

    sprintf(path, "%s/%s_error.log", log_path, program);
    efp = fopen(path, "a");

    sprintf(path, "%s/%s_warning.log", log_path, program);
    wfp = fopen(path, "a");

    sprintf(path, "%s/%s_info.log", log_path, program);
    ifp = fopen(path, "a");
#endif

}