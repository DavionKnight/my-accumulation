/*
 *  COPYRIGHT NOTICE
 *  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
 *
 *  Author       	:fzs
 *  File Name        	:/home/kevin/works/projects/ACCUMULATION/LinuxSystem/mmap/mmap.c
 *  Create Date        	:2016/11/13 21:18
 *  Last Modified      	:2016/11/13 21:18
 *  Description    	:
 */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>             
#include <sys/types.h>  
#include <sys/stat.h>   
#include <sys/time.h>   
#include <time.h>
#include <unistd.h>             
#include <errno.h>
#include <signal.h>
#include <termios.h>
#include <pthread.h>

#include <sys/ipc.h>  
#include <sys/sem.h>  
#include <semaphore.h>
#include <sys/shm.h>  

#include <linux/types.h> 

int fd_mmap;
unsigned int *mapbase = NULL;
unsigned int *mapbase1 = NULL;
#define MAP_SIZE                        4096UL
#define MAP_MASK                        (MAP_SIZE - 1)

int main( void  )
{
	int fd;
	void *int_mapbase, *virt_addr;
	unsigned int  reg_val = 0, temp;
	/* mmap SERIAL_IO_SEL register */
	if ( ( fd_mmap = open ( "/dev/mem", O_RDWR | O_SYNC ) ) == -1 )
	{
		return -1;
	}
	mapbase =(unsigned int *) mmap ( NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mmap, 0x18000000);
	printf("mapbse = %p,*mapbse = 0x%x\n",mapbase,*mapbase);
	close(fd_mmap);
#if 1
	if ( ( fd_mmap = open ( "/dev/mem", O_RDWR | O_SYNC ) ) == -1 )
	{
		return -1;
	}
#endif

	mapbase1 =(unsigned int *) mmap ( NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mmap, 0x18000000);
	printf("mapbse1 = %p,*mapbse = 0x%x\n",mapbase1,*mapbase);
	printf("mapbse = %p,*mapbse = 0x%x\n",mapbase,*mapbase);

	return 0;
}

