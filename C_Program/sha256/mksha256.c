/*
*  COPYRIGHT NOTICE
*  Copyright (C) 2016 Baidu Corporation, Inc. All rights reserved
*
*  Author       	    :fzs
*  File Name        	:/home/meteor/Downloads/bumblebee/test.c
*  Create Date        	:2018/10/19 17:13
*  Last Modified      	:2018/10/19 17:13
*  Description     	:
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
/*
// C prototype : void StrToHex(char *pbDest, char *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 输出缓冲区
//	[IN] pbSrc - 字符串
//	[IN] nLen - 16进制数的字节数(字符串的长度/2)
// return value:
// remarks : 将字符串转化为16进制数
*/
void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
	unsigned char h1,h2;
	unsigned char s1,s2;
	unsigned int i;

	printf("nLen=%d\n",nLen);
	for (i=0; i<nLen; i++)
	{
		h1 = pbSrc[2*i];
		h2 = pbSrc[2*i+1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1*16 + s2;
	}
}
/* a fast way to get file size */
int file_size(char* filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;

    return size;
}

unsigned char *GetFilename(unsigned char *p)
{
    char ch = '/';
    unsigned char *q = strrchr(p,ch);
	if(NULL != q)
		return q+1;
	else
		return q;
}

#define RDLEN     512
int main(int argc, unsigned char *argv[])
{
	unsigned char sha256_32[32];
	unsigned char sha256_64[65];
	unsigned char cmdline[200];
	unsigned char newfile[100];
	unsigned char newfile1[100];
	unsigned char buf[RDLEN];
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	unsigned int len = 0;
	unsigned int clen = 0;
	unsigned int i = 0;
	int ret;
	char *fname = NULL;

	srand((unsigned int)time(NULL));

	if(2 != argc) {
		printf("argc err\n");
		return -1;
	}
	memset(cmdline, 0, sizeof(cmdline));
	snprintf(cmdline, 200, "%s %s > ./sha256.txt","sha256sum", argv[1]);
//	printf("cmd=%s\n",cmdline);
	ret = system(cmdline);
	if(0 != ret) {
		printf("%d, err\n",__LINE__);
		return -1;
	}

	/*get sha256*/
	fp = fopen("./sha256.txt", "r");
	if(NULL == fp) {
		printf("%d, err\n",__LINE__);
		return -1;
	}
	fgets(sha256_64, 65, fp);
	fclose(fp);
	StrToHex(sha256_32, sha256_64, 32);
	system("rm ./sha256.txt");

	/*write sha256*/
	memset(newfile, 0, sizeof(newfile));
	memset(newfile1, 0, sizeof(newfile1));
	memcpy(newfile, argv[1], sizeof(newfile));
	fname = GetFilename(newfile);
	if(NULL == fname) {
		snprintf(newfile1, 100, "sha256-%s", newfile);
		memset(newfile, 0, sizeof(newfile));
		memcpy(newfile, newfile1, strlen(newfile1)+1);
	}
	else {
		snprintf(newfile1, 100, "sha256-%s", fname);
		memcpy(fname, newfile1, strlen(newfile1)+1);
	}
	printf("new file name: %s\n",newfile);
	if(!access(newfile, 0)) {
		memset(cmdline, 0, sizeof(cmdline));
		snprintf(cmdline, 200, "rm %s", newfile);
		system(cmdline);
	}
	fp1 = fopen(newfile, "a");
	if(NULL == fp1) {
		printf("%d, err\n",__LINE__);
		return -1;
	}
	fwrite(sha256_32, 32, 1, fp);

	/*add orgin file without last 4 bytes*/
	len = file_size(argv[1]);
	fp2 = fopen(argv[1],"r");
	if(NULL == fp2) {
		printf("%d, err\n",__LINE__);
		return -1;
	}
	clen = 0;
	while(clen + RDLEN < len) {
		fread(buf, RDLEN, 1, fp2);
		fwrite(buf, RDLEN, 1, fp1);
		clen += RDLEN;
	}
	if(len == (clen + 4)) {
	}
	else if(len <= (clen + 4)){
		printf("error, len=%d,clen=%d\n",len,clen);
	}
	else{
		fread(buf, (len-clen-4), 1, fp2);
		fwrite(buf, (len-clen-4), 1, fp1);
		clen += (len-clen-4);
	}

	/*add 4 random bytes*/
	printf("start replace...\n");
	unsigned short rval[4] = {0};
	for(i = 0; i < 4; i++) {
		rval[i] = rand()%0xff;
	}
	fwrite(rval, 4, 1, fp1);

	fclose(fp1);
	fclose(fp2);
	printf("replace successfully...\n");

	return 0;
}






