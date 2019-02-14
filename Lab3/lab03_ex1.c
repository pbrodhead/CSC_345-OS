#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int len = 7;
int nums[7] = {90, 81, 78, 95, 79, 72, 85};
int r_min;
int r_max;
int r_avg;

void * myMin(void * param){
    int i;
    r_min = nums[0];
    for (i = 0; i < len; i++){
        if (r_min > nums[i])
            r_min = nums[i];
    }
    
    pthread_exit(0);
}

void * myMax(void * param){
    r_max = nums[0];
    for (int i = 0; i < len; i++){
        if (r_max < nums[i])
            r_max = nums[i];
    }
	
    pthread_exit(0);
}

void * myAvg(void * param){
    r_avg = 0;
    for (int i = 0; i < len; i++)
        r_avg += nums[i];
        
    r_avg = r_avg / len;
}

int main(int argc, char** argv){
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    
    pthread_create(&tid1, 0, myMin, NULL);
    pthread_create(&tid2, 0, myMax, NULL);
    pthread_create(&tid3, 0, myAvg, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    
    printf("Min = %d\n", r_min);
    printf("Max = %d\n", r_max);
    printf("Avg = %d\n", r_avg);
    
    return 0;
}