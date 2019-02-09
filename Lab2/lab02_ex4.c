/*
Paul Brodhead
CSC345-01
Lab 2 Exercise 4
*/

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>

int main(int argc, char** argv){
    int n = atoi(argv[1]);
    pid_t id = fork();
    
    if(id == 0){
        while (n > 1){
            printf("%d ", n);
            if(n % 2 == 0)
                n /= 2;
            else
                n = (3 * n) + 1;
        }
        printf("%d\n", n);
    }
    else
        wait(NULL);
        
    return 0;
}