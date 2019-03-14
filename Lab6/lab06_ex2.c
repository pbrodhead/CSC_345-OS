/*
Paul Brodhead
CSC345-01
Lab 6 Exercise 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_WAIT 3

typedef struct _FARMER{
    pthread_t t;
    int isNorth; /* 0 for south 1 for north */
    int idx;     /* index within each bound */
    int waitfor; /* will take this amount of seconds < MAX_WAIT */
} FARMER;

pthread_mutex_t t;
pthread_cond_t  c;

int num_waiting_north = 0;
int num_waiting_south = 0;
int prev = 0; //0 for north, 1 for south
int on_bridge = 0;

void enter_bridge_north(){
    ++num_waiting_north;
    pthread_mutex_lock(&t);
    while ((on_bridge == 1) || (prev == 0 && num_waiting_south > 0)){
        pthread_cond_wait(&c, &t);
    }
    pthread_mutex_unlock(&t);
    --num_waiting_north;
    prev = 0;
    on_bridge = 1;
}

void enter_bridge_south(){
    ++num_waiting_south;
    pthread_mutex_lock(&t);
    while ((on_bridge == 0) || (prev == 1 && num_waiting_north > 0)){
        pthread_cond_wait(&c, &t);
    }
    pthread_mutex_unlock(&t);
    --num_waiting_south;
    prev = 1;
    on_bridge = 1;
}

void exit_bridge_north(){
    on_bridge = 0;
    pthread_cond_broadcast(&c);
}

void exit_bridge_south(){
    on_bridge = 0;
    pthread_cond_broadcast(&c);
}

void* pass_bridge(void* param){
    FARMER* f = (FARMER*) param;

    if(f->isNorth){
        enter_bridge_north();
        printf("Northbound farmer %d will pass in %d seconds\n",
            f->idx, f->waitfor);
    }
    else{
        enter_bridge_south();
        printf("Southbound farmer %d will pass in %d seconds\n",
            f->idx, f->waitfor);
    }
    
    
    if(f->isNorth)
        printf(" Northbound farmer %d is on bridge...\n", f->idx);
    else    
        printf(" Southbound farmer %d is on bridge...\n", f->idx);
    sleep(f -> waitfor);
    
    if(f->isNorth){
        exit_bridge_north();
        printf("Northbound farmer %d crossed in %d seconds\n",
            f->idx, f->waitfor);
    }
    else{
        exit_bridge_south();
        printf("Southbound farmer %d crossed in %d seconds\n",
            f->idx, f->waitfor);
    }

    pthread_exit(0);
}

int main(int argc, char** argv){
    FARMER* farmerN;
    FARMER* farmerS;
    int total_north, total_south;
    
    total_north = atoi(argv[1]);
    total_south = atoi(argv[2]);
    
    printf("%d northbound farmers, %d southbound farmers\n",
        total_north, total_south);
    
    pthread_mutex_init(&t,NULL);
    pthread_cond_init(&c,NULL);
    
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
    
    pthread_cond_destroy(&c);
    
    free(farmerN);
    free(farmerS);
    
    return 0;
}