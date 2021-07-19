#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <string.h>
#include <sys/time.h> 
#include <sys/resource.h>


int main(int argc, char *argv[])
{
	int  gpid;
//	cpu_set_t mycpuid;

	if(argc<2)
	{
		printf("Please input pof name");
		return 0;
	}
	printf("pid=%s\n",argv[1]);
	gpid = atoi(argv[1]);
	printf("pid=%d\n",gpid);

	printf("priority is %d\n",getpriority(PRIO_PROCESS, gpid));
//	sched_getaffinity(pid, sizeof(mycpuid), &mycpuid);

	
	return 0;
}



