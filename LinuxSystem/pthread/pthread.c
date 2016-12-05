#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <string.h>
#include <pthread.h>


int fun_pthread(void *arg)
{
	if(*((char*)arg) == 0)
	{
		while(1)
		{
			printf("arg=%d, pid=%d ppid=%d\n",*((char*)arg),getpid(),getppid());
			sleep(1);
		}
	}
	else
	{
		while(1)
		{
			printf("arg=%d, pid=%d ppid=%d\n",*((char*)arg),getpid(),getppid());
			sleep(1);
		}
	}
}

int main(int argc, char *argv[])
{
	int pid;
	char arg1 = 1, arg2 = 2;
	pthread_t id_1,id_2;


	pthread_create(&id_1, NULL, (void *)fun_pthread, &arg1);
	pthread_create(&id_2, NULL, (void *)fun_pthread, &arg2);

	while(1)
	{
		printf("arg=%d, pid=%d ppid=%d\n",0,getpid(),getppid());
		sleep(1);
	}
	sleep(1);
	return 0;
}



