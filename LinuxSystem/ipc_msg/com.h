#ifndef _COMM_H
#define _COMM_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8000


typedef struct{
	char name[20];
	int chinese;
	int math;
}SCORE_T;

typedef struct{
	long mtype;
	SCORE_T stu;
}MSG_T;
#define PATHNAME "/etc/passwd"
#define KEY_ID 30
#endif
