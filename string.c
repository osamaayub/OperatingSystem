#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

char *filename=NULL;

void *Search(void *args)
{
	char *str=(char*)args;
	FILE *fp;
	int line=0;
	int result=0;
	int column=0;
	char temp[50];
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("cannot open file");
		exit(0);
		return (void*)0;
	}
	else
	{
		while(fgets(temp,50,fp)!=NULL)
		{
			if(strstr(temp,str)!=NULL)
			{
				printf("A match found  on line %d\n",line);
				printf("A mathc found at column %d\n",column);
				printf("string is%s\n",temp);
				result++;
				
			}
			line++;
			column++;
		}
		if(fp)
		{
			fclose(fp);
		}
		if(result==0)
		{
			printf("sorry  could not find match ");
		}
		return (void*)0;
		
	}
	return(void*)1;
	pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
	int numofthreads=atoi(argv[2]);
	pthread_t threads[numofthreads];
	filename=(char*)malloc(strlen(argv[1])*sizeof(char*));
	stpcpy(filename,argv[1]);
	int rc;
	long t;
	void *result=0;
	for(t=0;t<numofthreads;t++)
	{
		rc=pthread_create(&threads[t],NULL,Search,(void*)argv[3]);
		pthread_join(threads[t],&result);
		if((long)result==1)
		{
			pthread_cancel(threads[t]);
		}
		break;
	}
	if(rc)
	{
		printf("Error return code from pthread_create() is%d\n",rc);
		exit(-1);
	}
	pthread_exit(NULL);
}