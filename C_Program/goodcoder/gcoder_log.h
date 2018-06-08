#ifndef  GOODCODER_KEVIN_GCODER_LOG_H
#define  GOODCODER_KEVIN_GCODER_LOG_H

#include <comlog/comlog.h>

#define LOG(level, fmt, args...) do { \
    com_writelog(level, fmt, ##args); \
} while (0)

#endif

