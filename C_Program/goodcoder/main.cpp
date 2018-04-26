#include "parser.h"
#include "user.h"
#include <stdio.h>
#include <iostream>

using vocabulary_parse::Parser;
using vocabulary_parse::MyStruct1;
using vocabulary_parse::MyStruct2;

char* test1 = "abcdef\t123\t3.9\t456\tyiyg\n";
char* test2 = "abcdef\t3:4,5,6\t3.9\t456\tyiyg\t4:1,2,3,4\n";
char* test3 = "abcdef\t123\t3.9\t456\tyiyg\t22,33.22,aabb\n";


int main()
{
	int i = 0;
	Parser test;

	test.parse_line(test1, 5);
	int x;
	test.parse_column(3, &x);
	char* y = new char[20];
	test.parse_column(4, y);
	float z;
	test.parse_column(2, &z);
	printf("%d, %s, %f\n", x, y, z);

	test.parse_line(test3, 6);

	MyStruct1 my_struct;
	test.parse_column(5, &my_struct);
	printf("%d %f %s\n", my_struct.a, my_struct.b, my_struct.c);

	MyStruct2 my_str;
	test.parse_line(test2, 6);
	test.parse_column(1, &my_str);
	for(i = 0; i < my_str.num; i++){
		printf("arr[%d]=%d\n", i, my_str.array[i]);
	}

	return 0;

}


