/*
Paul Brodhead
CSC345-01
Lab 2 Exercise 4
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define SIZE 4096

int main(int argc, char** argv){
    int shm_fd;
    void * ptr;
    char * name = "OS";
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    int n = atoi(argv[1]);
    pid_t id = fork();
    int nums = 0;
    
    if(id == 0){
        while (n > 1){
            ptr += (sizeof(char) * sprintf(ptr,"%d ",n));
            
            if(n % 2 == 0)
                n /= 2;
            else
                n = (3 * n) + 1;
        }
        sprintf(ptr,"%d\n", n);
    }
    else{
        wait(NULL);
        printf("%s", (char *)ptr);
    }
        
    return 0;
}