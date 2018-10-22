#ifndef  GOODCODER_KEVIN_USER_H
#define  GOODCODER_KEVIN_USER_H
#include <stdio.h>
#include "parser.h"

enum Userdef {
    USERDEFLEN = 32,
};

struct MyStruct1 {
    int a;
    float b;
    char c[USERDEFLEN];
};

int do_parse_column(const char* str, struct MyStruct1* result);

struct MyStruct2 {
    int num;
    int array[USERDEFLEN];
};

int do_parse_column(const char* str, struct MyStruct2* result);

#endif

