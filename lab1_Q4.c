/*
Q4
*/

#include<stdio.h>

void main(){
	int pid;
	char *temp[3] = {"command-line", ".", NULL};
	pid = fork();
	if(pid==0){
		printf("\n");
		execvp("/bin/ls", temp);
	}
	else{}
}
