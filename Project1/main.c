/*
Paul Brodhead
CSC345-01
Project 1
*/

/* import all necessary libraries */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

/* define all constants */
#define MAX_LINE 80
#define MAX_ARGS (MAX_LINE/2 + 1)

int main(void){
    /* instantiating variables */
    char *args[MAX_ARGS]; //command line arguments
    char temp[MAX_LINE];  //user input 
    char *token;          //string used in arg parsing
    const char s[2] = " ";//comparator for arg parsing
    int should_run = 1;   //flag to determine when to exit
    pid_t pid;            //process ID
    int background = 0;   //bool to determine if parent waits
    char *hist = " ";     //string containing previous args
    char *command;        //final args to be parsed
    int in, out;          //bool to determine file redirection
    int fdin, fdout;      //file read/write vars
    int numArgs;          
    int len;              //length of user input
    
    /* shell loop */
    while(should_run){
        /* reset shell for next command */
        printf("osh>");
        fflush(stdout);
        numArgs = 0;
        in = 0;
        out = 0;
        
        /* retrieve user input & input len */
        fgets(temp,MAX_LINE,stdin);
        len = strlen(temp);
        
        /* prep command string for arg input */
        command = malloc(MAX_ARGS * sizeof(char));
        
        /* remove newline char for proper arg passing */
        if(temp[len - 1] == '\n')
            temp[len - 1] = '\0'; 
        
        /* check for history command, and prep proper arg */
        if(strcmp(temp,"!!") == 0){
            command = hist;
            printf("%s\n",hist);
        }
        else
            command = temp;
        
        /* parse input for different args in command */
        token = strtok(command, s);
        while(token != NULL){
            args[numArgs] = token;
            if(!strcmp(token,"&"))
                background = 1;
            token = strtok(NULL, s);
            numArgs++;
        }
        args[numArgs] = NULL;   //null terminate array
        
        /* check for exit command */
        if(!strcmp(args[0],"exit")){
            should_run = 0;
            break;
        }
        
        /* check for directory change command */
        if(!strcmp(args[0],"cd")){
            chdir(args[1]);
        }
        
        /* check for file redirection command */
        if(numArgs > 2){
            if(!strcmp(args[numArgs - 2], ">")){
                out = 1;
            }
            else if(!strcmp(args[numArgs - 2], "<")){
                in = 1;
            }
        }
        
        /* reserve memory for previous args */
        hist = malloc(len * sizeof(char));
        memcpy(hist,&temp[0],len);
        
        /* fork parent and child processes */
        pid = fork();
        if(pid == 0){   //CHILD
            /* command input redirection */
            if(in){
                args[numArgs - 2] = NULL;   //remove "<" char
                /* error handling & file opening */
                if((fdin = open(args[numArgs - 1], O_RDONLY)) < 0){
                    printf("Failed to open file\n");
                    exit(0);
                }
                
                /* redirect STDIN to be file */
                dup2(fdin, 0);
                close(fdin);
            }
            /* command output redirection */
            else if(out){
                args[numArgs - 2] = NULL;   //remove ">" char
                /* error handling & file opening */
                if((fdout = creat(args[numArgs - 1], 0644)) < 0){
                    printf("File error\n");
                    exit(0);
                }
                
                /* redirect STDOUT to be file */
                dup2(fdout, STDOUT_FILENO);
                close(fdout);
            }
            
            execvp(args[0],args);   //change child process to arg
        }
        else if(pid > 0){   //PARENT
            /* background process handling */
            if(!background)
                wait(NULL); //only wait if no "&" included in args
        }
        
        
    }
    
    return 0;
}