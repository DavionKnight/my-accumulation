#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define BLOCK_SIZE 1024*1024

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

struct ZIPFILERECORD{
	uchar 	frSignature[4];
	ushort 	frVersion;
	ushort 	frFlags;
	ushort 	frCompression;
	ushort 	frFileTime;
	ushort 	frFileDate;
	uint 	frCrc;
	uint 	frCompressedSize;
	uint 	frUncompressedSize;
	ushort 	frFileNameLength;
	ushort 	frExtraFieldLength;
	uchar	frFileName[0];
}__attribute__ ((packed));

int transmit_seg_data(unsigned char *fname, int flag_head, int pt_size, int success);

int main(uint argc, uchar **argv)
{
	unsigned char headbuf[512];	
	unsigned char zipname[100],fname[64];	
	unsigned char databuf[BLOCK_SIZE];	
	int fd = -1;
	int fdw = -1;
	int ret = -1;
	int num = 0;
	uint pos = 0;
	uint flag_head = 0, flag_all_end = 0;
	uint  rwcount= 0;
	uint count= 0;
	uint seg_size = 0, real_seg_size = 0;
	DIR *dir;
	struct dirent *ptr;
//	unsigned char data_name[20];

	struct ZIPFILERECORD *rec = NULL;

	if(argc != 3)
	{
		printf("para num err\n");
		printf("Use: ./seg_upgrade [file_name] [seg_size,default MB<1-100>]\n");
		printf("eg.: ./seg_upgrade Duer_Dot_Speaker_v0.9.5-R_update.zip 1 \n");
		return 0;
	}

	ret = system("mkdir tmp");
	if(0 != ret)
	{
		printf("mkdir tmp error\n");
		return 0;
	}
	sprintf(fname, "unzip %s -d tmp", argv[1]);
	ret = system(fname);
	if(0 != ret)
	{
		printf("unzip error\n");
		return 0;
	}

	ret = system("cd tmp;zip -0 Duer_Dot_Speaker_Seg.zip boot.img tz.img rootfs.ubi");
	if(0 != ret)
	{
		printf("zip -0 error, can not find boot.img tz.img rootfs.ubi\n");
		return 0;
	}
	
//	return 0;
	memcpy(zipname, "tmp/Duer_Dot_Speaker_Seg.zip", sizeof(zipname));
	fd = open(zipname, O_RDONLY);
	if(fd < 0)
	{
		printf("file name err\n");
		return 0;
	}

	seg_size = atoi(argv[2]);
	if(seg_size <= 0 || seg_size > 100)
	{
		printf("Please input correct seg_size <1-100>\n");
		return 0;
	}
	printf("File name=%s, Seg_size=%dMB\n",argv[1], seg_size);
	seg_size =seg_size*1024*1024;

	/*get zip head*/
	do{
		memset(headbuf, 0, sizeof(headbuf));
		rwcount = read(fd, headbuf, sizeof(struct ZIPFILERECORD));	
		if(rwcount < sizeof(struct ZIPFILERECORD)){
			printf("file open error\n");
			return 0;
		}
		rec = (struct ZIPFILERECORD *)headbuf;

		/*the data head should be 0x50 0x4b 0x03 0x04*/
		if((0x50 != rec->frSignature[0]) || (0x4b != rec->frSignature[1]) ||
				(0x03 != rec->frSignature[2]) || (0x04 != rec->frSignature[3])){
			printf("come to end, sig[0]=%02x,sig[1]=%02x,sig[2]=%02x,sig[3]=%02x\n",rec->frSignature[0],
					rec->frSignature[1], rec->frSignature[2], rec->frSignature[3]);	
			break;
		}
		/*get img name*/
		memset(fname, 0 ,sizeof(fname));
		rwcount = read(fd, fname, rec->frFileNameLength);	
		if(rwcount != rec->frFileNameLength){
			printf("parse file name error\n");
			return 0;
		}
		fname[rec->frFileNameLength] = '\0';
		printf("nameseg_size=%d,fiseg_sizeame = %s\n",rec->frFileNameLength,fname);

		/*remeber how many files has got*/
		flag_all_end++;

		/*jump extra info*/
		pos = rec->frExtraFieldLength;
		lseek(fd, pos, SEEK_CUR);
//		printf("pos = %d\n",pos);

		count = 0;
		flag_head = 0;
		while(count < rec->frCompressedSize){
//							memset(data_name, 0, sizeof(data_name));
//							sprintf(data_name,"data%d.tmp", num++);
			fdw = open("data.tmp", O_RDWR | O_CREAT, 0600);
//			fdw = open(data_name, O_RDWR | O_CREAT, 0600);
			if(fdw < 0)
			{
				printf("open data.tmp err\n");
				return 0;
			}
			ftruncate(fdw, 0);
			lseek(fdw, 0, SEEK_SET);

			real_seg_size = 0;

			while(real_seg_size < seg_size)
			{
				if(count + BLOCK_SIZE < rec->frCompressedSize){
					rwcount = read(fd, databuf, BLOCK_SIZE);	
					if(rwcount != BLOCK_SIZE){
						printf("read file error!\n");
						return 0;
					}
				}
				else{
					rwcount = read(fd, databuf, rec->frCompressedSize-count);	
					if(rwcount != (rec->frCompressedSize-count)){
						printf("read file error!!\n");
						return 0;
					}
				}
				real_seg_size += rwcount;
				count += rwcount;
#if 1
				//		printf("databuf=%02x %02x %02x %02x\n",databuf[0],databuf[1],databuf[2],databuf[3]);

				ret = write(fdw, databuf, rwcount);	
				if(ret != rwcount)
				{
					printf("write data.tmp err\n");
					return 0;
				}
				if(rwcount != BLOCK_SIZE)
					break;
			}
			close(fdw);

#if 1
			/*if 3 file all transmit, the last seg should transmit a success flag, the last seg maybe 1. not full BLOCK_SIZE, 2. a full seg(but cout equal to frcompressedsize) */
			if((flag_all_end == 3) && ((rwcount < BLOCK_SIZE)||(count == rec->frCompressedSize)))
			{
				ret = transmit_seg_data(fname, flag_head++, real_seg_size, 1);
				if(ret != 0)
				{
					printf("transmit seg data err\n");
					return -1;
				}
				printf("send end flag OK\n");
			}
			else
			{
				ret = transmit_seg_data(fname, flag_head++, real_seg_size, 0);
				if(ret != 0)
				{
					printf("transmit seg data err\n");
					return -1;
				}
			}
#endif

#endif
		}

	}while(1);

	printf("end\n");
	system("rm data.tmp -f");
	close(fd);
	system("rm tmp -rf");

	return 0;
	
}


int transmit_seg_data(unsigned char *fname, int flag_head, int pt_size, int success)
{
	int ret = 0;
	unsigned char cmd[100];	
	

	memset(cmd, 0,sizeof(cmd));

#if 1
	ret = system("adb push ./data.tmp /tmp/update/update.bin");
	if(ret != 0)
	{
		printf("adb push err\n");
		return -1;
	}

#endif
	sprintf(cmd, "%s %s %d %d %d", "adb shell upgrade_app", fname, flag_head, pt_size, success);
	printf("%s\n",cmd);

#if 1
	ret = system(cmd);
	if(ret != 0)
	{
		printf("adb shell upgrade_app err\n");
		return -1;
	}
#endif

	return 0;
}




