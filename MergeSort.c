#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define NUM_OF_THREADS 9
#define SIZE 15


int arr[NUM_OF_THREADS];
int check=0;
void MERGE_SORT(int Start,int Middle,int End)
{
	int *S=(int*)malloc((Middle-Start + 1)*sizeof(int));
	int *P=(int*) malloc((End-Middle) * sizeof(int));
	int size1=(Middle-Start+1);
	int size2=(End-Middle);
	int i,j=0,count=Start;
	for(i=0;i<size1;i++)
	{
		S[i]=arr[i+Start];
	}
	for( j=0;i<size2;j++)
	{
		P[j]=arr[j+Middle+1];
	}
	while(i<size1 && j<size2 )
	{
	  if(S[i]<=arr[j])

		  arr[count++]=S[i++];
		  
		    
	  else
		  arr[count++]=P[j++];
	}
	while(i<size1)
	{
		arr[count++]=S[i++];
		
	}
	while(j<size2)
	{
		arr[count++]=P[j++];
	}
	free(S);
	free(P);
}
void Merge_Sort(int Start,int End)
{
	int Middle=Start+(End-Start)/2;
	if(Start<End)
	{
		Merge_Sort(Start,Middle);//First half of array
	Merge_Sort(Middle+1,End);//Second half of array
	MERGE_SORT(Start,Middle,End);
	}
}
void *merge_sort(void *num)
{
	 int thread= check++;
	 int Low = thread* (SIZE/ NUM_OF_THREADS);
    int High = (thread + 1) * (SIZE / NUM_OF_THREADS) - 1;

    // evaluating mid point
    int Mid = Low + (High - Low) / 2;
    if (Low < high) {
        Merge_Sort(Low, Mid);
        Merge_Sort(Mid + 1, High);
       MERGE_SORT(Low, Mid, High);
    }
	pthread_exit(0);
}
int main(int argc,char *argv[])
{
	for(int i=0;i<SIZE;i++)
		arr[i]=rand()%10;
	clock_t c1,c2;
	c1=clock();
	c2=clock();
	 MERGE_SORT(0, (SIZE / 2 - 1) / 2, SIZE/ 2 - 1);
    MERGE_SORT(SIZE / 2, SIZE/2 + (SIZE-1-SIZE/2)/2, SIZE - 1);
    MERGE_SORT(0, (SIZE - 1)/2, SIZE - 1);
 
 pthread_t List[NUM_OF_THREADS];
	for(int i=0;i<NUM_OF_THREADS;i++)
	{
		pthread_create(&List[i],NULL,merge_sort,(void*)NULL);
	}
	for(int i=0;i<NUM_OF_THREADS;i++)
	{
		pthread_join(List[i],NULL);
	}
	for(int i=0;i<SIZE;i++)
	{
		printf("%ld",List[i]);
	}
	
}
