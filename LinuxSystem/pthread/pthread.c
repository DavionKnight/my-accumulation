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
#include <sys/prctl.h>


int fun_pthread(void *arg)
{
	if(*((char*)arg) == 0)
	{
		prctl(PR_SET_NAME, "fun_pthread1");
		while(1)
		{
			printf("arg=%d, pid=%d ppid=%d\n",*((char*)arg),getpid(),getppid());
			sleep(5);
		}
	}
	else
	{
		prctl(PR_SET_NAME, "fun_pthread2");
		while(1)
		{
			printf("arg=%d, pid=%d ppid=%d\n",*((char*)arg),getpid(),getppid());
			sleep(6);
		}
	}
}

int main(int argc, char *argv[])
{
	int pid;
	char arg1 = 0, arg2 = 1;
	pthread_t id_1,id_2;


	pthread_create(&id_1, NULL, (void *)fun_pthread, &arg1);
	pthread_create(&id_2, NULL, (void *)fun_pthread, &arg2);

	while(1)
	{
		printf("arg=%d, pid=%d ppid=%d\n",0,getpid(),getppid());
		sleep(7);
	}
	sleep(1);
	return 0;
}



