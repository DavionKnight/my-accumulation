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
    fd_set rfds;
    FD_ZERO(&rfds);
    int ret;
    
    char pipename[32]="./test_fifo";

    if (access("./test_fifo",F_OK)) { 
        if(-1==mkfifo(pipename,0666)) {
            perror("mkfifo");
            exit(1);
        }
    }
    
    char msg[1024]="";
    
    int mcu_fd; 
    mcu_fd = open(pipename, O_RDWR);
    if(mcu_fd==-1)
    {
        perror("open client");
        exit(1);
    }
    FD_SET(mcu_fd, &rfds);
    
    while(1) {
        ret = select(mcu_fd + 1, &rfds, NULL, NULL, NULL);
        if (ret && FD_ISSET(mcu_fd, &rfds)) {
            ret = read(mcu_fd, msg, 1024);
            printf("read %d data:%d\n", ret, msg[0]);
        }
    }
    close(mcu_fd);
}

