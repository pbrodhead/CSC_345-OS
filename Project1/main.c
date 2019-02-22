#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

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
    int in, out;
    int fdin, fdout;
    
    while(should_run){
        printf("osh>");
        fflush(stdout);
        int numArgs = 0;
        in = 0;
        out = 0;
        
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
            args[numArgs] = token;
            if(!strcmp(token,"&"))
                background = 1;
            token = strtok(NULL, s);
            numArgs++;
        }
        args[numArgs] = NULL;
        if(!strcmp(args[0],"exit")){
            should_run = 0;
            break;
        }
        
        if(!strcmp(args[0],"cd")){
            chdir(args[1]);
        }
        
        if(numArgs > 2){
            if(!strcmp(args[numArgs - 2], ">")){
                out = 1;
            }
            else if(!strcmp(args[numArgs - 2], "<")){
                in = 1;
            }
        }
        
        hist = malloc(len * sizeof(char));
        memcpy(hist,&temp[0],len);
        
        pid = fork();
        if(pid == 0){
            if(in){
                args[numArgs - 2] = NULL;
                if((fdin = open(args[numArgs - 1], O_RDONLY)) < 0){
                    printf("Failed to open file\n");
                    exit(0);
                }
                
                dup2(fdin, 0);
                close(fdin);
            }
            else if(out){
                args[numArgs - 2] = NULL;
                if((fdout = creat(args[numArgs - 1], 0644)) < 0){
                    printf("File error\n");
                    exit(0);
                }
                
                dup2(fdout, STDOUT_FILENO);
                close(fdout);
            }
            
            execvp(args[0],args);
        }
        else if(pid > 0){
            if(!background)
                wait(NULL);
        }
        
        
    }
    
    return 0;
}