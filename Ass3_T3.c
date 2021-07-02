#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t full,empty;

# define n 10

int buffer[10];
int nextin=0,nextout=0;

void *producer(void *args)
{
	for(unsigned int i=1;i<15;i++)
	{
		sem_wait(&empty);
		buffer[nextin]=i;
		nextin=(nextin+1)%n;
		sem_post(&full);
	}
	pthread_exit(0);
}
void *consumer(void *args)
{
	  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	for(int unsigned j=1;j<15;j++)
	{
		sem_wait(&full);
		printf("%d\n",buffer[nextout]);
		nextout=(nextout+1)%n;
		sem_post(&empty);
	}
	pthread_exit(0);
}
int main(int argc,char *argv[])
{
	pthread_t p1,p2;
	sem_init(&full,0,0);
	sem_init(&empty,0,10);
	pthread_create(&p1,NULL,&producer,NULL);
	pthread_create(&p2,NULL,&consumer,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
}