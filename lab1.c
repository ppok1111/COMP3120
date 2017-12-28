#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

#define MAX_COUNT 4
#define MAIN_COUNT 1000000
int pid;
char path[32];
char path_memory[32];
char buf[1024];

void counter(int max);

void *profile(void *arg);
void *mythread(void *arg);
void *thread_memory(void *arg);
void inttochar(char *ch, int num);


void main(){
	pthread_t p1;
	pthread_t p2, p3;
	char c_pid[10];
	int count_main;

	pid = getpid();
	//pid = 1;

	strcpy(path,"/proc/");
	inttochar(c_pid, pid);
	strcat(path,c_pid );

	printf("path : %s\n",path);

	strcpy(path_memory, path);
	strcat(path, "/stat");
	strcat(path_memory, "/status");
	
	pthread_create(&p1, NULL, mythread, NULL);
	pthread_create(&p2, NULL, thread_memory, NULL);
	//pthread_create(&p3, NULL, profile, NULL);
	
	pthread_join(p3, NULL);
	//sleep(MAX_COUNT);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
}

void *profile(void *arg){
	FILE *fp;
        int count = 0;
        int i;
        char temp[256];
        int temp_n;
        long long utime, stime;
        char buf[256];
        int VmPeak;
        long long VmSize, VmData, VmStk, VmExe;

	for(count = 0; count < MAX_COUNT; count++){
                //cpu time start
                printf("(%d/%d)\n",count+1, MAX_COUNT);
                fp = fopen(path, "r");
                if(fp == -1){
                        perror("fail to open stat\n");
                        exit(1);
                }
                for(i=0; i<13; i++){
			fscanf(fp, "%s ", temp);
                }
                fscanf(fp, "%lld %lld", &utime, &stime);
                fclose(fp);
                printf("CPU time spent in user code: %lld\n", utime);
                printf("CPU time spent in kernel code: %lld\n", stime);
                printf("Total time : %lld\n", utime + stime);
                //cpu time end
		fp =fopen(path_memory, "r");
                if(fp == -1){
                        perror("fail to open status");
                        exit(1);
                }
		i=0;
                while(i<5){
                        fscanf(fp, "%s ",buf);
                        if (strcmp(buf, "VmPeak:")){
                                fscanf(fp, "%d ", &VmPeak);
                                i++;
                        }
                        else if (strcmp(buf, "VmSize:")){
				fscanf(fp, "%lld ", &VmSize);
                                i++;
                        }
                        else if (strcmp(buf, "VmData:")){
                                fscanf(fp, "%lld ", &VmData);
                                i++;
                        }
                        else if (strcmp(buf, "VmStk:")){
                                fscanf(fp, "%lld ", &VmStk);
				i++;
                        }
                        else if (strcmp(buf, "VmExe:")){
                                fscanf(fp, "%lld ", &VmExe);
                                i++;
                        }
                }
                printf("VmPeak: %d\n", VmPeak);
                printf("VmSize: %lld\n", VmSize);
                printf("VmData: %lld\n", VmData);
                printf("VmStk: %lld\n", VmStk);
                printf("VmExe: %lld\n", VmExe);
                fclose(fp);

	}
}

void *mythread(void *arg){
	FILE *fp;
	int count = 0;
	int i;
	char temp[512];
	int temp_n;
	long long utime, stime;
	for(count = 0; count < MAX_COUNT; count++){
		//cpu time start
		printf("(%d/%d)\n",count+1, MAX_COUNT);
		fp = fopen(path, "r");
		if(fp == -1){
			perror("fail to open stat\n");
			exit(1);	
		}	
		for(i=0; i<13; i++){		
			if(i==1){
				fscanf(fp, "%s ", temp);
			}
			else{
				fscanf(fp, "%d ",&temp_n);
			}
		}
		fscanf(fp, "%lld %lld", &utime, &stime);
		fclose(fp);
		printf("CPU time spent in user code: %lld\n", utime);
		printf("CPU time spent in kernel code: %lld\n", stime);
		printf("Total time : %lld\n", (utime + stime) *100);
		//cpu time end
		sleep(1);
	}
	
}
void *thread_memory(void *arg){
	FILE *fp;
	char buf[256];
	int VmPeak;
	long long VmSize, VmData, VmStk, VmExe;
	int i=0;
	int count=0;

	for(count=0; count<MAX_COUNT; count++){
		fp =fopen(path_memory, "r");
		if(fp == -1){
			perror("fail to open status");
			exit(1);
		}
		while(i<5){
			fscanf(fp, "%s ",buf);
			if (strcmp(buf, "VmPeak:")){
				fscanf(fp, "%d", &VmPeak);
				i++;
			}
			else if (strcmp(buf, "VmSize:")){
             	           fscanf(fp, "%lld", &VmSize);
                		i++;
			}
			else if (strcmp(buf, "VmData:")){
        	                fscanf(fp, "%lld", &VmData);
        	        	i++;
			}
			else if (strcmp(buf, "VmStk:")){
	                        fscanf(fp, "%lld", &VmStk);
				i++;
	                }
			else if (strcmp(buf, "VmExe:")){
	                        fscanf(fp, "%lld", &VmExe);
				i++;
	                }
		}
		printf("VmPeak: %d\n", VmPeak);
		printf("VmSize: %lld\n", VmSize);
		printf("VmData: %lld\n", VmData);
		printf("VmStk: %lld\n", VmStk);
		printf("VmExe: %lld\n", VmExe);
		fclose(fp);
		sleep(1);
	}
}
void inttochar(char *ch, int num){
	int i = 0;
	int j = 0;
	int temp;
	char tempchar;
	while(num){
		temp = num % 10;
		ch[i] = temp + '0';
		i++;
		num /= 10;
	}
	ch[i] = '\0';
	i--;
	while(j < i){
		tempchar = ch[j];
		ch[j] = ch[i];
		ch[i] = tempchar;
		i--;
		j++;
	}
}
void counter(int max){
	int counter = 0;
	sleep(1);
	while(counter<max){
		counter++;
	}
}
