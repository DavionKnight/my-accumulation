#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<signal.h>

int pipe_process()
{
        struct sigaction newact,oldact;
        newact.sa_handler = SIG_IGN;
        sigemptyset(&newact.sa_mask);
        newact.sa_flags = 0;
        
        sigaction(SIGPIPE,&newact,&oldact);
        return 0;
}

int main()
{
                int server_sockfd,client_sockfd;
                int server_len,client_len;
                struct sockaddr_un server_address;
                struct sockaddr_un client_address;
                const char path_unix[] = "/dev/logtest";
                int len_unix;
                char buf[1024];
                int n;

                unlink("MY_SOCKET");
                server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

                server_address.sun_family = AF_UNIX;
                strncpy(server_address.sun_path, path_unix,sizeof(server_address.sun_path));
                server_len = sizeof(server_address);
                len_unix = 11;
                bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
                
//                pipe_process();
                listen(server_sockfd, 5);
                while(1){

                                printf("server waiting\n");
  
                                client_len = sizeof(client_address);
                                client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
                
                                memset(buf,0,sizeof(buf)/sizeof(buf[0]));
                                n = read(client_sockfd,buf,1024);
                             if(n < 0)
                                {
                                 fprintf(stderr,"read failed\n");
                                        return -1;
                                }
                                fprintf(stderr,"recv : %s\n",buf);
                                close(client_sockfd);
                }
}
