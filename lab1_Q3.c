/*
2017 12 26
operating system
lecture4 Q3
*/
#include<stdio.h>

int main(){
	int pid;
	int i;
	pid = fork();
	if(pid == 0){//child
		printf("hello\n");
	}
	else{//parent
		sleep(1);
		printf("good bye\n");
	}

}
