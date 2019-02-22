#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define MAX_ARGS (MAX_LINE/2 + 1)

int main(void){
    char args[MAX_ARGS][MAX_LINE];//command line arguments
    char temp[MAX_LINE];
    char * token;
    const char s[2] = " ";
    int should_run = 1;   //flag to determine when to exit
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        int i = 0;
        
        fgets(temp,MAX_LINE,stdin);
        token = strtok(temp, s);
        while(token != NULL){
            sprintf(args[i],"%s\n",token);
            token = strtok(NULL, s);
            i++;
        }
        
        //DEBUG
        for(int j = 0; j < 2; j++){
            printf("args[%d]: %s",j,args[j]);
        }
        printf("%d",strcmp(args[0],"exit"));
        
        if(strcmp(args[0],"exit") == 10)
            should_run = 0;
        else
            printf("That is not a valid command\n");
    }
    
    return 0;
}