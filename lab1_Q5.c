/*
Q5
if wait() in child, noting happen. wait() return -1.
*/
#include<stdio.h>
void main(){
	int pid;
	pid = fork();
	int temp;
	if(pid==0){//child
		printf("child\n");
		temp = wait();
		printf("child wait() is %d\n",temp);
	}
	else{
		temp = wait();
		printf("parent wait() is %d\n",temp);
	}
}
