#include "com.h"

int main(void)
{
	key_t key = ftok(PATHNAME, KEY_ID+1);
	if(key == -1)
	{
		perror("ftok");
		exit(1);
	}
	int msqid = msgget(key,IPC_CREAT);
	if(msqid == -1)
	{
		perror("msgget");
		exit(1);
	}

	struct msqid_ds buf;
	int ret = msgctl(msqid,IPC_STAT,&buf);
	if(ret == -1)
	{
		perror("msgctl");
		exit(1);
	}
#if 1	
	if(buf.msg_qnum == 0)
	{
		ret = msgctl(msqid, IPC_RMID, NULL);
		if(ret == -1)
		{
			perror("msgctl");
			exit(1);
		}
		perror("1111msgctl");

		exit(0);
	}
#endif

	MSG_T msg;
	ret = msgrcv(msqid, &msg, sizeof(MSG_T),3,IPC_NOWAIT);
	if(ret == -1)
	{
		perror("msgrcv");
		exit(1);
	}
	printf("name = %s\n",msg.stu.name);
	printf("chinese = %d\n", msg.stu.chinese);
	printf("math = %d\n",msg.stu.math);
	exit(0);
}
