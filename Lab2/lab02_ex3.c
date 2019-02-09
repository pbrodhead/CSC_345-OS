/*
Paul Brodhead
CSC345-01
Lab 2 Exercise 3
*/

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#define SLEEPTIME 10

int main(){
    pid_t pid;
    pid = fork();
    
    if(pid == 0)    //Child process
        return 0;
    else if(pid > 0){
        sleep(SLEEPTIME);
        return 0;
    }
}