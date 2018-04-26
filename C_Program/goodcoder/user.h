#ifndef  __USER_H_
#define  __USER_H_
#include <stdio.h>
#include "parser.h"

namespace vocabulary_parse{
	enum UserDef{
		USERDEFLEN = 32,
	};

	typedef struct MyStruct1
	{
		int a;
		float b;
		char c[USERDEFLEN];
	}MyStruct1;

	int do_parse_column(const char* str, MyStruct1* result);

	typedef struct MyStruct2
	{
		int num;
		int array[USERDEFLEN];
	}MyStruct2;

	int do_parse_column(const char* str, MyStruct2* result);
}

#endif

