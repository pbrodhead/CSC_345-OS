#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

int main(void){
    char * args[MAX_LINE/2 + 1];//command line arguments
    int should_run = 1;         //flag to determine when to exit
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
    }
    
    return 0;
}