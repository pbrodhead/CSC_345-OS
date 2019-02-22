#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main(void){
    char * args[MAX_LINE/2 + 1];//command line arguments
    int should_run = 1;         //flag to determine when to exit
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        
        gets(args);
        
        if(strcmp(args,"exit") == 0)
            break;
        else
            printf("That is not a valid command\n");
    }
    
    return 0;
}