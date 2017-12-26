
#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<sys/time.h>
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
	struct timeval timeA, timeB;
	int thread_number[MULTI_THREAD];
	int totalsum = 0;
	pthread_t p[MULTI_THREAD];
	
	gettimeofday(&timeA, NULL);
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
	gettimeofday(&timeB, NULL);
	printf("total count is %d\n", totalsum);
	printf("time : %.3fms\n",(timeB.tv_sec - timeA.tv_sec)*1000.0 + (timeB.tv_usec - timeA.tv_usec) * 0.001);
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
