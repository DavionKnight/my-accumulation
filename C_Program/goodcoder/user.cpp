#include <string.h>
#include "user.h"

namespace vocabulary_parse{

	int do_parse_column(const char* str, MyStruct1* result)
	{
		char buffer[USERDEFLEN + 9] = {0};
		char *str1 = NULL;
		char *str2 = NULL;
		char *str3 = NULL;
		int ret = -1;
		int i = 0;

		if ((str == NULL) || (result == NULL)){
			printf("user parse NULL\n");
			return ret;
		}

		printf("Start Parse User struct!!!\n");
		memcpy(buffer, str, sizeof(buffer));
		ret = sscanf(buffer, "%d", &result->a);
		if(1 != ret){
			ret = 1;
			return 1;
		}

		str1 = strtok_r(buffer, ",", &str2);
		if (str1 != NULL){
			if (1 == sscanf(str2, "%f", &result->b)){
				ret = 0;
			}

			str1 = strtok_r(str2, ",", &str3);
			if (str1 != NULL){
				for (i = 0; i < strlen(str3); i++){
					if(i >= USERDEFLEN){
						break;
					}
					result->c[i] = str3[i];
				}
			}
		}

		ret = 0;
		return ret;
	}
	int do_parse_column(const char* str, MyStruct2* result){
		char buffer[USERDEFLEN*4] = {0};
		char *str1 = NULL;
		char *str2 = NULL;
		char *str3 = NULL;
		int num = 0;
		int ret = -1;
		int i = 0;

		if ((str == NULL) || (result == NULL)){
			printf("user parse NULL\n");
			return ret;
		}

		printf("Start Parse User struct!!!\n");
		memcpy(buffer, str, sizeof(buffer));
		ret = sscanf(buffer, "%d", &num);
		if(1 != ret){
			ret = 1;
			return 1;
		}
		result->num = num;
		str1 = strtok_r(buffer, ":", &str2);
		while ((str1 != NULL) && (i < num)){
			str3 = str2;
			if (1 == sscanf(str2, "%d", &result->array[i++])){
				ret = 0;
			}

			str1 = strtok_r(str3, ",", &str2);
		}

		ret = 0;
		return ret;
	}

} 



