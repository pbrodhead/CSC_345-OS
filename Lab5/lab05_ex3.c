/*
Paul Brodhead
CSC345-01
Lab 5 Exercise 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

pthread_mutex_t lock;

int total_pts;
int pts_in_circle;

void * runner(void * param){
    for (int i = 0; i < (total_pts / NUM_THREADS); i++){
        //gerenate a random point
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        x = (x * 2.0) - 1.0;
        y = (y * 2.0) - 1.0;
        
        /* start crit section */
        pthread_mutex_lock(&lock);
        
        //check if point is in circle
        if(((x * x) + (y * y)) < 1.0)
            pts_in_circle++;
        
        /* end crit section */
        pthread_mutex_unlock(&lock);
    }
    
    pthread_exit(0);
}

int main(int argc, char** argv){
    pthread_t tid[NUM_THREADS];
    double pi_approx;
    
    pthread_mutex_init(&lock, NULL);
    
    total_pts = atoi(argv[1]);
    
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_create(&tid[i], NULL, runner, NULL);
    }
    
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }
    
    pthread_mutex_destroy(&lock);
    
    //calculate Monte Carlo approx of pi
    pi_approx = 4.0 * ((double)pts_in_circle / (double)total_pts);
    printf("Estimated PI = %f\n", pi_approx);
    
    return 0;
}