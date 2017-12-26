/**/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main(){
	int pid1;
	int pid2;
	int pipefd[2];
	char buf;
	char input[256];
	if( pipe(pipefd)==-1){
		perror("pipe");
		exit(1);
	}
	
	
	pid1 = fork();
	
	if(pid1 == 0){	//child 1
		close(pipefd[1]);
		while(read(pipefd[0], &buf, 1)>0)
			write(1,&buf, 1);//stdout
		write(1,"\n",1);
		close(pipefd[0]);
		exit(1);
	}
	else{
		pid2 = fork();
		
		if(pid2 == 0){//child 2
		close(pipefd[0]);
		printf("input text:");
		scanf("%s",&input);
		write(pipefd[1], input, strlen(input));
		close(pipefd[1]);
		exit(1);
		}
		else{
			wait(NULL);
		}
	}
	
}
