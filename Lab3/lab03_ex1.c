#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int len = 7;
int nums[7] = {90, 81, 78, 95, 79, 72, 85};
int r_min;

void * myMin(void * param){
    int i;
    r_min = nums[0];
    for (i = 0; i < len; i++){
        if (r_min > nums[i])
            r_min = nums[i];
    }
    
    pthread_exit(0);
}

int main(int argc, char** argv){
    pthread_t tid;
    pthread_create(&tid, 0, myMin, NULL);
    pthread_join(tid, NULL);
    printf("Min = %d\n", r_min);
    return 0;
}