/**/
#include<stdio.h>
#include<time.h>
#include<sys/time.h>

void main(){
	struct timeval val;
	struct tm *ptm;
	gettimeofday(&val, NULL);
	printf("sec: %d\nusec: %d\n",val.tv_sec, val.tv_usec);
	ptm = localtime(&val.tv_sec);
	
	printf("year: %d\n",ptm->tm_year + 1900);
	printf("month: %d\n",ptm->tm_mon + 1);
	printf("day: %d\n",ptm->tm_mday);
	printf("hour: %d\n",ptm->tm_hour);
	printf("minute: %d\n",ptm->tm_min);
	printf("second: %d\n", ptm->tm_sec);
	printf("millisecond %d\n", val.tv_usec /1000);
	printf("microsecond %d\n", val.tv_usec %1000);
	
}
