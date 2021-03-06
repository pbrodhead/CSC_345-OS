/*
Paul Brodhead
CSC345-01
Lab 6 Exercise 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_WAIT 3

typedef struct _FARMER{
    pthread_t t;
    int isNorth; /* 0 for south 1 for north */
    int idx;     /* index within each bound */
    int waitfor; /* will take this amount of seconds < MAX_WAIT */
} FARMER;

/* bridge */
sem_t sem;

void enter_bridge(){
    sem_wait(&sem);
}

void exit_bridge(){
    sem_post(&sem);
}

void* pass_bridge(void* param){
    FARMER* f = (FARMER*) param;

    if(f->isNorth)
        printf("Northbound farmer %d will pass in %d seconds\n",
            f->idx, f->waitfor);
    else
        printf("Southbound farmer %d will pass in %d seconds\n",
            f->idx, f->waitfor);

    enter_bridge();
    if(f->isNorth)
        printf(" Northbound farmer %d is on bridge...\n", f->idx);
    else    
        printf(" Southbound farmer %d is on bridge...\n", f->idx);
    sleep(f -> waitfor);
    exit_bridge();
    
    if(f->isNorth)
        printf("Northbound farmer %d crossed in %d seconds\n",
            f->idx, f->waitfor);
    else
        printf("Southbound farmer %d crossed in %d seconds\n",
            f->idx, f->waitfor);

    pthread_exit(0);
}

int main(int argc, char** argv){
    FARMER* farmerN;
    FARMER* farmerS;
    int total_north, total_south;
    
    total_north = atoi(argv[1]);
    total_south = atoi(argv[2]);
    
    printf("%d northbound farmers, %d southbound farmers",
        total_north, total_south);
    
    sem_init(&sem, 0, 1);
    
    farmerN = (FARMER*)malloc(sizeof(FARMER) * total_north);
    farmerS = (FARMER*)malloc(sizeof(FARMER) * total_south);
    for (int i = 0; i < total_north; i++){
        farmerN[i].isNorth = 1;
        farmerN[i].waitfor = rand() % MAX_WAIT;
        farmerN[i].idx = i;
    }
    for (int i = 0; i < total_south; i++){
        farmerS[i].isNorth = 0;
        farmerS[i].waitfor = rand() % MAX_WAIT;
        farmerS[i].idx = i;
    }
    
    for (int i = 0; i < total_north; i++){
        pthread_create(&(farmerN[i].t),NULL,pass_bridge,&farmerN[i]);
    }
    for (int i = 0; i < total_south; i++){
        pthread_create(&(farmerS[i].t),NULL,pass_bridge,&farmerS[i]);
    }
    
    for (int i = 0; i < total_north; i++){
        pthread_join(farmerN[i].t,NULL);
    }
    for (int i = 0; i < total_south; i++){
        pthread_join(farmerS[i].t,NULL);
    }
    
    sem_destroy(&sem);
    
    free(farmerN);
    free(farmerS);
    
    return 0;
}