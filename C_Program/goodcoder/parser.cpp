#include "parser.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include "gcoder_log.h"

namespace vocabulary_parse {

    int Parser::parse_line(const char* line, const int column_num) {
        int ret = 0;
        int i = 0;
        int index = 0;

        _column_num = column_num;
        for (i = 0; i < COLUMN_MAX; ++i) {
            _column[i] = 0;
        }

        do {
            if (NULL == line || column_num <= 0) {
                LOG(COMLOG_FATAL, "parse_line para error");
                ret = 1;
                break;
            }
            for (i = 0; i < CHAR_MAX; ++i) {
                if (('\n' == line[i]) || ('\0' == line[i])) {
                    break;
                }
                if (0 == i) {
                    LOG(COMLOG_DEBUG, "parse_line get head word");
                    _column[index++] = line;
                }
                else if ('\t' == line[i]) {
                    LOG(COMLOG_DEBUG, "parse_line get new word");
                    _column[index++] = line+i+1;
                }
            }
            if (column_num != index) {
                _column_num = index;
                LOG(COMLOG_FATAL, "column num may be error");
                ret = 1;
                break;
            }
        } while (0);

        return ret;
    }

    int do_parse_column(const char* str, int* result) {
        int ret = 0;

        if ((NULL == str) || (NULL == result)) {
            LOG(COMLOG_FATAL, "do_parse_column int error");
            ret = 1;
            return ret;
        }
        if (1 == sscanf(str, "%d", result)) {
            LOG(COMLOG_DEBUG, "do_parse_column sscanf ok");
            ret = 0;
        }
        return ret;
    }

    int do_parse_column(const char* str, char* result) {
        int ret = 0;

        if (NULL != str && NULL != result) {
            const char* start_str = str;
            char* result_str = result;

            while (('\t' != *start_str) && ('\n' != *start_str) && ('\0' != *start_str)) {
                *result_str++ = *start_str++;
            }

            *result_str = '\0';
        }
        else {
            LOG(COMLOG_FATAL, "do_parse_column char func para error");
            ret = 1;
        }

        return ret; 
    }

    int do_parse_column(const char* str, float* result) {
        int ret = 0;

        if ((NULL == str) || (NULL == result)) {
            LOG(COMLOG_FATAL, "do_parse_column int error");
            ret = 1;
            return ret;
        }
        if (1 != sscanf(str, "%f", result)) {
            ret = 1;
        }
        return ret;
    }
}


