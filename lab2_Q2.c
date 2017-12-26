
#include<stdio.h>
#include<pthread.h>

#define MAX 9000000
#define MULTI_THREAD 10
#define USING_MUTEX_LOCK 1
#define SHOW 0
static int counter = 0;
int totalcount[MULTI_THREAD];
pthread_mutex_t mutex_lock;

void *mythread(void *arg);
int output;

void main(){
	int i;
	int thread_number[MULTI_THREAD];
	int totalsum = 0;
	pthread_t p[MULTI_THREAD];

	printf("count number is %d\n", MAX);
	for(i=0; i< MULTI_THREAD; i++){
		thread_number[i] = i;
		pthread_create(&p[i], NULL, mythread, &thread_number[i] );
	}

	for(i=0; i<MULTI_THREAD; i++){
		pthread_join(p[i], NULL);
		printf("thread%d is counted %d\n", i, totalcount[i]);
		totalsum += totalcount[i];
	}
	printf("total count is %d\n", totalsum);
}

void *mythread(void *arg){
	printf("thread%d is start.\n",*(int*)arg);
	int mycounter=0;
	int check = 1;
	while(check)
	{	
		
		if(USING_MUTEX_LOCK){//lock
			pthread_mutex_lock(&mutex_lock);
		}

		if(counter<MAX){
			counter++;
			mycounter++;
		}
		else {
			check = 0;
		}
		
		if(USING_MUTEX_LOCK){//unlock
			pthread_mutex_unlock(&mutex_lock);
		}
		if(SHOW){
			printf("thread%d count %d\n",*(int*)arg, counter);
		}
	}
	printf("thread%d is end.\n",*(int*)arg );
	totalcount[*(int*)arg] = mycounter;
}
