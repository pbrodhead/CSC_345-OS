/*
Paul Brodhead
CSC345-01
Lab 2 Exercise 1
*/

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int value = 5;
int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        value += 15;
        printf("CHILD: value = %d\n", value); //expect output to be 20
        return 0;
    }
    else if(pid > 0){
        wait(NULL);
        printf("PARENT: value = %d\n", value); //expect output to be 5
        return 0;
    }
}