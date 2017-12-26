//2017 12 26
//operating system
//lecture 4 Q1

#include<stdio.h>

void main(){
	int x=0;
	int i;
	int pid;

	x = 100;
	pid = fork();
	
	if(pid == 0){
		printf("\nthis child process\n");
		printf("x is %d\n",x);
		x += 10;
		printf("x + 10 is %d\n",x);
	}
	else{
		printf("\nthis parent process\n");
		printf("x is %d\n",x);
		x = 50;
		printf("x = 50 is %d\n",x);
	}
	printf("\n");
	
}
