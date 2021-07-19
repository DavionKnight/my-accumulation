#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
void main()
{
	int fd,fd1;

	fd = open("./test.txt", O_RDWR |O_CREAT, 777);
	fd1 = open("./test.txt", O_RDWR |O_CREAT, 777);
	printf("fd=%d\n fd1=%d\n",fd,fd1);
	write(fd,"testaa\n\n", 5);	
	sleep(10);
	printf("after\n");
	fsync(fd);
	sleep(10);
	printf("after\n");
	return ;
}



