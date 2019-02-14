#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int total_pts;
int pts_in_circle;

void * runner(void * param){
    for (int i = 0; i < total_pts; i++){
        //gerenate a random point
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        x = (x * 2.0) - 1.0;
        y = (y * 2.0) - 1.0;
        
        //check if point is in circle
        if(((x * x) + (y * y)) < 1.0)
            pts_in_circle++;
    }
    
    pthread_exit(0);
}

int main(int argc, char** argv){
    pthread_t tid;
    double pi_approx;
    
    total_pts = atoi(argv[1]);
    
    pthread_create(&tid, NULL, runner, NULL);
    pthread_join(tid, NULL);
    
    //calculate Monte Carlo approx of pi
    pi_approx = 4.0 * ((double)pts_in_circle / (double)total_pts);
    printf("Estimated PI = %f\n", pi_approx);
    
    return 0;
}