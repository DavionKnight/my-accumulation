#ifndef  __PARSER_H_
#define  __PARSER_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdint.h>

namespace vocabulary_parse{

	enum para{
		COLUMN_MAX = 32,
		CHAR_MAX = 512,
	};


			int do_parse_column(const char* str, int* result);
			int do_parse_column(const char* str, char* result);
			int do_parse_column(const char* str, float* result);

	class Parser{

		public:
			Parser(){
				_column_num = 0;
			}

			int parse_line(const char* line, const int column_num);
#if 0
	        template<class T>
			int parse_column(const int index, T* result);
#endif

	template <class T>
	int parse_column(const int index, T* result){
			int ret = 0;

			if((0 == _column_num) || (index >= _column_num)){
				ret = 1;
				return ret;
			}
			ret = do_parse_column(_column[index], result);

			return ret;
	}
		private:
			int _column_num;
			const char *_column[COLUMN_MAX];


	};
}

#endif

