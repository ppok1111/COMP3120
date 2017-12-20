#include<stdio.h>

int main(){

 
 FILE *input;
 FILE *output;

 if(( input = fopen("input.txt", "r")) == NULL){
  printf("cannot open input file");
 }
 if(( output = fopen("output.txt", "w")) == NULL){
  printf("cannot open file");
 }
 return 0;
}
