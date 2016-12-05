/*
*  COPYRIGHT NOTICE
*  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
*
*  Author       	:Kevin_fzs
*  File Name        	:/home/kevin/works/projects/ACCUMULATION/C_Program/addOob/addoob.c
*  Create Date        	:2016/07/21 16:18
*  Last Modified      	:2016/07/21 16:18
*  Description    	:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
        FILE *fd1, *fd2;
	char new[70] = {0}, *buf = NULL;
	int len = 0;

        if(argc<2)
        {
                printf("Please input pof name");
                return 0;
        }
        printf("file is %s\n",argv[1]);

	sprintf(new, "%s-spansion.filebin",argv[1]);

        if((fd1 = fopen(argv[1],"rb"))==NULL)
	{
		printf("open %s error\n", argv[1]);;
		return 0;
	}
        if((fd2 = fopen(new,"wb"))==NULL)
	{
		printf("open %s error\n", new);;
		return 0;
	}

	printf("processing..\n");

	if(NULL == (buf = malloc(2048+200)))
	{
		printf("malloc failed..\n");
		return 0;
	}
	memset(buf, 0xff, sizeof(buf));	

        while((len = fread(buf, 1, (2048+64), fd1))>0)
        {
		memset(buf+(2048+64), 0xff, 64);
		fwrite(buf, 1, (2048+128), fd2);
		memset(buf, 0xff, sizeof(buf));	
	}	
	free(buf);	

	fclose(fd1);
	fclose(fd2);

	printf("OK..\n");

	return 0;
}



