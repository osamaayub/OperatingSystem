#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 9


void *EVEN_NUMBERS(void *num)
{
	int *n=(int*)num;
	for(int i=0;i<NUM_THREADS;i++)
	{
		if(n[i]%2==0)
		{
			printf("Even Number are%d:",n[i]);
		}
		printf("\n");
	}
	pthread_exit(NULL);
}
void *ODD_NUMBERS(void *num)
{
	int *arr=(int*)num;
	for(int i=0;i<NUM_THREADS;i++)
	{
		if(arr[i]%2!=0)
		{
			printf("ODD Number are%d:\n",arr[i]);
		}
		printf("\n");
	}
	pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
	int *array=(int*)malloc((argc-1)*sizeof(int));
	pthread_t pid,pid2;
	for(int i=0;i<argc-1;i++)
	{
		array[i]=atoi(argv[i]);
	}
	pthread_create(&pid,NULL,EVEN_NUMBERS,(void*)array);
	pthread_join(pid,(void*)array);
	pthread_create(&pid2,NULL,ODD_NUMBERS,(void*)array);
	pthread_join(pid2,(void*)array);
	pthread_exit(NULL);
}