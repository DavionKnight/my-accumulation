/*
 *  COPYRIGHT NOTICE
 *  Copyright (C) 2016 HuaHuan Electronics Corporation, Inc. All rights reserved
 *
 *  Author       	:fzs
 *  File Name        	:/home/kevin/works/projects/ACCUMULATION/C_Program/quicksort/quickSort.c
 *  Create Date        	:2017/11/14 02:11
 *  Last Modified      	:2017/11/14 02:11
 *  Description    	:
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int length = 0;
void display(unsigned char arr[])
{
	int i = 0;
	for(i = 0; i < length; i++)
		printf("%02d ",arr[i]);
	printf("\n");
	usleep(500000);
}

void swap(unsigned char *a, unsigned char *b)
{
	*a ^= *b; 
	*b ^= *a; 
	*a ^= *b; 
}
int quicksort(unsigned char arr[], int begin, int end)
{
	int i = 0, j = 0;
	int privot = 0;

	if(begin < end)
	{
		i = begin;	
		j = end;
		while(i < j)
		{
			while(i<j && arr[j]>arr[i])
			{
				j--;
			}
			if(i<j)
			{
				swap(&arr[i++],&arr[j]);
				display(arr);
			}
			while(i<j && arr[i]<arr[j])
			{
				i++;
			}
			if(i<j)
			{
				swap(&arr[j--], &arr[i]);
				display(arr);
			}
		}
		display(arr);

		quicksort(arr, begin, i-1);
		quicksort(arr, i+1, end);
		//		display(arr, end+1);
	}
}

int main()
{
	unsigned char arr[] = {9,8,7,6,5,4,3,10,2,3,20,15,16,11,6,12,7,9,19,18,17,16,15};
	length = sizeof(arr);
	printf("data:\n");
	display(arr);

	quicksort(arr, 0, sizeof(arr)-1);

	printf("end data:\n");
	display(arr);
	return 0;
}

