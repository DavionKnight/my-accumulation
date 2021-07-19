#include "com.h"

int main(void)
{
	key_t key = ftok(PATHNAME, KEY_ID+1);
	if(key == -1)
	{
		perror("ftok");
		exit(1);
	}
printf("key=%d\n",key);
	int msqid = msgget(key,IPC_CREAT);
	if(msqid == -1)
	{
		perror("msgget");
		exit(1);
	}

	MSG_T msg;
	srand(time(NULL));
	strncpy(msg.stu.name,"h3c",4);
	msg.stu.chinese = 90+rand()%9;
	msg.stu.math = 80+rand()%6;
	msg.mtype = 3;

//	ret = msgrcv(msqid, &msg, sizeof(MSG_T),3,0);

//-sizeof(long)
	int ret = msgsnd(msqid, &msg, sizeof(MSG_T)-8,0);
	if(ret == -1)
	{
		perror("msgsnd");
		exit(1);
	}
	printf("chinese = %d\n",msg.stu.chinese);
	printf("math = %d\n",msg.stu.math);
	exit(0);
}
