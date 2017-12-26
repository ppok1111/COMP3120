/*
2017-12-26
operating system
lecture 4 Q2

---test.txt---
parent
child hello
--------------
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main(){
	int pid;
	int *file;
	char buf[256] = {0};
	file = open("./test.txt",O_WRONLY);
	if (file == NULL){
		printf("error to file open\n");
		return 0;
	}
	else {
		pid = fork();
		if (pid == 0){//child
			strcpy(buf,"child hello\n");
		}
		else {//parent
			strcpy(buf,"parent\n");
		}
		write(file, buf, strlen(buf));
	}
	return 0;
}
