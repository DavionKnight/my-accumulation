#include <stdio.h>
#include <iostream>
#include "gcoder_log.h"
#include "parser.h"
#include "user.h"

using vocabulary_parse::Parser;

enum FileLines {
    LINE_NUM = 3,
    LINE_LEN = 512,
};

char g_test[LINE_NUM][LINE_LEN] = {0};

int get_line_from_file(char* file_name) {
    int ret = 0;
    int i = 0;    
    FILE* fp = NULL;
    char* res = NULL;

    fp = fopen(file_name, "r");
    if (NULL == fp) {
        LOG(COMLOG_FATAL, "open file error");
        ret = -1;
        return ret;
    }

    for (i = 0; i < LINE_NUM; ++i) {
        res = fgets(g_test[i], LINE_LEN, fp);
        if (NULL == res) {
            LOG(COMLOG_FATAL, "read line %d error", i);
            ret = -1;
            break;
        }
    }

    fclose(fp);

    return ret;
}

int build_in_test() {

    int ret = 0;
    Parser test;
    char char_type[20] = {0};

    ret = test.parse_line(g_test[0], 5);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_line error");
        return 0;
    }

    int x = 0;
    ret = test.parse_column(3, &x);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_column error");
        return 0;
    }

    char* y = char_type;
    ret = test.parse_column(4, y);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_column error");
        return 0;
    }

    float z = 0.0;
    ret = test.parse_column(2, &z);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_column error");
        return 0;
    }

    LOG(COMLOG_NOTICE, "%d, %s, %f", x, y, z);
}

int main(int argc, char** argv) {

    int i = 0;
    int ret = 0;
    Parser test;

    if (2 > argc) {
        printf("Please input file name\n");
        return 0;
    }

    com_device_t dev[1];
    memcpy(dev[0].type, "TTY", sizeof("TTY"));
    COMLOG_SETSYSLOG(dev[0]);
    com_openlog("test", dev, 1, NULL);

    LOG(COMLOG_NOTICE, "comlog init done");

    ret = get_line_from_file(argv[1]);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "read file error");
        return 0;
    }

    build_in_test();

    struct MyStruct1 my_struct;
    ret = test.parse_line(g_test[2], 6);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_line error");
        return 0;
    }

    ret = test.parse_column(5, &my_struct);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_column error");
        return 0;
    }
    LOG(COMLOG_NOTICE, "%d %f %s", my_struct.a, my_struct.b, my_struct.c);

    struct MyStruct2 my_str;
    ret = test.parse_line(g_test[1], 6);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_line error");
        return 0;
    }

    ret = test.parse_column(5, &my_str);
    if (0 != ret) {
        LOG(COMLOG_FATAL, "parse_column error");
        return 0;
    }

    for (i = 0; i < my_str.num; ++i) {
        LOG(COMLOG_NOTICE, "arr[%d]=%d", i, my_str.array[i]);
    }

    com_closelog();

    return 0;
}


