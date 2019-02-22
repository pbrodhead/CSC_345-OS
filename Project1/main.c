#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_LINE 80
#define MAX_ARGS (MAX_LINE/2 + 1)

int main(void){
    char *args[MAX_ARGS];//command line arguments
    char temp[MAX_LINE];
    char * token;
    const char s[2] = " ";
    int should_run = 1;   //flag to determine when to exit
    pid_t pid;
    int background = 0;
    char *hist = "hi";
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        int i = 0;
        
        fgets(temp,MAX_LINE,stdin);
        int len = strlen(temp);
        
        char *command = malloc(MAX_ARGS * sizeof(char));
        
        if(temp[len - 1] == '\n')
            temp[len - 1] = '\0'; 
        
        if(strcmp(temp,"!!") == 0)
            command = hist;
        else
            command = temp;
        
        token = strtok(command, s);
        while(token != NULL){
            args[i] = token;
            if(!strcmp(token,"&"))
                background = 1;
            token = strtok(NULL, s);
            i++;
        }
        args[i] = NULL;
        if(!strcmp(args[0],"exit")){
            should_run = 0;
            break;
        }
        
        if(!strcmp(args[0],"cd")){
            chdir(args[1]);
        }
        
        hist = malloc(len * sizeof(char));
        memcpy(hist,&temp[0],len);
        
        pid = fork();
        if(pid == 0){
            execvp(args[0],args);
        }
        else if(pid > 0){
            if(!background)
                wait(NULL);
        }
        
        
    }
    
    return 0;
}