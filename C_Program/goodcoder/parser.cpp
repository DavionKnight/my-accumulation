#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include "parser.h"

namespace vocabulary_parse{

	int Parser::parse_line(const char* line, const int column_num){
		int ret = 0;
		int i = 0;
		int index = 0;

		_column_num = column_num;

		do{
			if (NULL == line || column_num <= 0){
				ret = 1;
				break;
			}
			for (i = 0; i < CHAR_MAX; i++){
				if(('\n' == line[i]) || ('\0' == line[i])){
					break;
				}
				if (0 == i){
					_column[index++] = line;
					//printf("%s\n", _column[0]);
				}
				else if ('\t' == line[i]){
					_column[index++] = line+i+1;
					//printf("%s\n", _column[index-1]);
				}
			}
			if (column_num != index){
				_column_num = index;
				printf("column num may be error\n");
				ret = 1;
				break;
			}
		} while(0);

		return ret;
	}


	int do_parse_column(const char* str, int* result){
		int ret = 0;

		if((NULL == str) || (NULL == result)){
			printf("do_parse_column int error\n");
			ret = 1;
			return ret;
		}
		if (1 == sscanf(str, "%d", result)) {
			ret = 0;
		}
		return ret;
	}
	int do_parse_column(const char* str, char* result){
		int ret = 0;

		if (NULL != str && NULL != result){
			const char* start_str = str;
			char* result_str = result;

			while (('\t' != *start_str) && ('\n' != *start_str) && ('\0' != *start_str)){
				*result_str++ = *start_str++;
			}

			*result_str = '\0';
		}
		else{
			ret = 1;
		}

		return ret; 
	}

    int do_parse_column(const char* str, float* result){
		int ret = 0;

		if((NULL == str) || (NULL == result)){
			printf("do_parse_column int error\n");
			ret = 1;
			return ret;
		}
		if (1 == sscanf(str, "%f", result)) {
			ret = 0;
		}
		return ret;
	}

#if 0
	template<class T>
	int Parser::parse_column(const int index, T* result){
			int ret = 0;

			if((0 == _column_num) || (index >= _column_num)){
				ret = 1;
				return ret;
			}
			ret = do_parse_column(_column[index], result);

			return ret;
	}
#endif
}

