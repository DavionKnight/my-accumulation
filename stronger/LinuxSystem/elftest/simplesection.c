/*
*  COPYRIGHT NOTICE
*  Copyright (C) 2016 Baidu Corporation, Inc. All rights reserved
*
*  Author             :zhangjiajie@baidu.com
*  File Name          :simplesection.c
*  Create Date        :2020/03/29 13:16
*  Last Modified      :2020/03/29 13:18
*  Description        :NA
*/

int printf(const char* format, ...);

int global_init_var = 84;
int global_uninit_var;

void func1(int i) {
    printf("%d\n", i);
}

int main(void) {
    static int static_var = 85;
    static int static_var2;
    int a = 1;
    int b;

    func1(static_var + static_var2 + a + b);
    return a;
}


