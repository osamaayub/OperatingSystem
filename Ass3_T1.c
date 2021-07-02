#include<stdio.h>
#include<pthread.h>
#include <stdbool.h>
#define NUM_OF_THREADS 4
#define Size 9


int arr[Size]={11, 15, 17, 100, 122, 24, 125, 18, 20};
bool check=false;
int Value=20;
void *Linear_Search(void*Num)
{
	for(int i=0;i<Size;i++)
	{
		if(arr[i]==Value)
		{
			check=true;
		}
		
	}
	pthread_exit(0);
}
int main(int argc,char *argv[])
{
	pthread_t List[NUM_OF_THREADS];
	for(int i=0;i<NUM_OF_THREADS;i++)
	{
		pthread_create(&List[i],NULL,Linear_Search,(void*)NULL);
	}
	for(int i=0;i<NUM_OF_THREADS;i++)
	{
		pthread_join(List[i],NULL);
	}
	if(check==true)
	{
		printf("Element is found");
	}
	else
	{
		printf("Element is not found");
	}
}