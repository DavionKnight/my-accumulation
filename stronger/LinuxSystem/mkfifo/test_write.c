#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
    int fd_send;
    char msg[1024]="";
    
    char pipename[32]="./test_fifo";
    
    fd_send = open(pipename,O_RDWR);
    if(fd_send==-1)
    {
        perror("open client");
        exit(1);
    }
    
    int i = 0;
    while(1) {
        memset(msg, 0, 1024);
        msg[0] = i++;
        write(fd_send, msg, strlen(msg));
        printf("write %d\n", i);
        usleep(1000000);
    }

    close(fd_send);
}

