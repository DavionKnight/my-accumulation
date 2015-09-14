#include <stdio.h>
#include <string.h>

double 	price[12];
int 	total_num = 0;
FILE 	*fd;

void resput(char *p, int len)
{
	fwrite(p,1,len,fd);
	memset(p,0,len);
}

int get_price()
{
	int i = 0;
	int num = 0;
	while(1)
	{		
		printf("Please Input Price(input 0 end input):\n");
		
		scanf("%lf",&price[num++]);
		if((price[num-1]==0)||(num == 11))
		{
			break;
		}
	}
	if(num != 11)
	num--;
	printf("You input %d num:\n",num);
	for(i = 0;i <num; i++)
		printf("%f ",price[i]);
	printf("\n");
	total_num = num-1;	
	return 0;
}



int 	x[10];
int 	x_[10];
double 	least = 999;
int 	get_flag = 0;
char 	pbuf[50];

int calc(double old_price,int num)
{
	int i = 0, j = 0;
	double new_price;
	int  max = (price[total_num])/(price[num])+1;
	
	for(i = 0;i<max;i++)
	{
		new_price = old_price+i*price[num];
		if(new_price > price[total_num]+1)
			return;
		if(num == (total_num-1))
		{
			double new_least = new_price>price[total_num]?(new_price - price[total_num]):(price[total_num] - new_price);

			if(new_least < 0.001)
			{
				get_flag++;
				if(get_flag == 1)
				{
					strcpy(pbuf,"The exact result:\n\n");
					resput(pbuf,strlen(pbuf));
				}
				sprintf(pbuf, "%dth:\n",get_flag);
				resput(pbuf,strlen(pbuf));
				for(j = 0;j<total_num-1;j++)
				{
					sprintf(pbuf,"x%d:%3d  ",j+1,x[j]);
					resput(pbuf,strlen(pbuf));
				}
				sprintf(pbuf,"x%d:%3d\n",j+1,i);
				resput(pbuf,strlen(pbuf));
				printf("find %d result\n",get_flag);
			}
			else
			{
				if(new_least <least)
				{
					least = new_least;

					for(j = 0;j<total_num-1;j++)
						x_[j] = x[j];
					x_[j] = i;
				}
			}
		}
		else
		{
			x[num] = i;
			calc(new_price,num+1);
		}
	}
	return 0;
}
#if 0
double tprice=0;
#define FOR_BEGAIN(i,a)	if(i==total_num)for(a=0;a<max;a++)tprice=a*price[i];else
#define FOR_END		}}
int calc(double price,int num)
{
	int i = 0;
	
	for(i=0;i<total_num;i++)
	{
		FOR_BEGAIN(i,x##i)
	}
	for(i=0;i<total_num;i++)
	{
		FOR_END
	}
		
}
#endif
int main()
{
	int j = 0;

	fd = fopen("result.txt","w+");
	memset(pbuf,0,sizeof(pbuf));

	get_price();
	
	printf("Calculating...\n");

	calc(0,0);

	if(get_flag == 0)
	{
		sprintf(pbuf,"%s","Theres no result,the nearest result is:\n");
		resput(pbuf,strlen(pbuf));

                for(j = 0;j<total_num;j++)
		{
                        sprintf(pbuf,"x%d:%3d ",j+1,x_[j]);
			resput(pbuf,strlen(pbuf));
		}
		sprintf(pbuf,"%s","\n");
		resput(pbuf,strlen(pbuf));
	}
	fclose(fd);
	printf("Done..\n\n");
	printf("You can get the result in result.txt..\n\n");
	system("pause");
}


