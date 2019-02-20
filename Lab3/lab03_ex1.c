#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int len;
int * nums;
int r_min;
int r_max;
double r_avg;
double r_stdDev;
int r_med;

int compare_function(const void *a,const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}

double getAvg(int * nums, int len){
    double avg = 0.0;
    for (int i = 0; i < len; i++)
        avg += (double)nums[i];
    
    return avg / (double)len;
}

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
    
    pthread_exit(0);
}

void * myStdDev(void * param){
    r_stdDev = 0.0;
    double avg;
    avg = getAvg(nums, len);
    
    for (int i = 0; i < len; i++)
        r_stdDev += (nums[i] - avg) * (nums[i] - avg);
    r_stdDev = r_stdDev / len;
    r_stdDev = sqrt(r_stdDev);
    
    pthread_exit(0);
}

void * myMed(void * param){
    r_med = 0;
    qsort(nums, len, sizeof(int), compare_function);
    r_med = nums[len/2];
    
    pthread_exit(0);
}

int main(int argc, char** argv){
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_t tid5;
    
    nums = (int *) malloc(sizeof(int) * (argc - 1));
    len = argc - 1;
    for (int i = 0; i < (argc - 1); i++)
        nums[i] = atoi(argv[i + 1]);
    
    pthread_create(&tid1, 0, myMin, NULL);
    pthread_create(&tid2, 0, myMax, NULL);
    pthread_create(&tid3, 0, myAvg, NULL);
    pthread_create(&tid4, 0, myStdDev, NULL);
    pthread_create(&tid5, 0, myMed, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    
    printf("Min = %d\n", r_min);
    printf("Max = %d\n", r_max);
    printf("Avg = %f\n", r_avg);
    printf("Std Dev = %f\n", r_stdDev);
    printf("Med = %d\n", r_med);
    
    return 0;
}