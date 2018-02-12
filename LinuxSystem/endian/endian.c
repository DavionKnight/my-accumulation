/*
*  COPYRIGHT NOTICE
*  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
*
*  Author       	:fzs
*  File Name        	:/home/kevin/works/projects/ACCUMULATION/LinuxSystem/endian/little_endian.c
*  Create Date        	:2017/03/12 17:34
*  Last Modified      	:2017/03/12 17:34
*  Description    	:
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <endian.h>

int main()
{
	unsigned int a = 0x12345678;
	unsigned int b;
	unsigned char *c;
	unsigned char *d;

#if 0
	b = ntohl(a);

	c = (unsigned char *)&a;
	d = (unsigned char *)&b;

	printf("a = 0x%x, b = 0x%x\n", a, b);
	printf("c0 = 0x%x, c1 = 0x%x, c2 = 0x%x, c3 = 0x%x\n", c[0],c[1],c[2],c[3]);
	printf("d0 = 0x%x, d1 = 0x%x, d2 = 0x%x, d3 = 0x%x\n", d[0],d[1],d[2],d[3]);
#endif
	#if __BYTE_ORDER == __LITTLE_ENDIAN
	        printf("little endian\n");
	    #endif

	    #if __BYTE_ORDER == __BIG_ENDIAN
	        printf("big endian\n");
	    #endif

	unsigned char cc[4] = {0x12,0x34,0x56,0x78};
		
	memcpy(&b, cc, 4);
	
	printf("b = 0x%x\n", b);


	return 0;
}



