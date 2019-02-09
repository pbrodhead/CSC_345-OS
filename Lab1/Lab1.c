#include<stdio.h>
#define NUMPRINT 5

/* function to print string to console */
void helloWorld(){
    char output[] = "Hello World!";
    printf("%s \n", output);
}

/* main function designed to call helloWorld 5 times */
int main(void){
    for(int i = 0; i < NUMPRINT; i++){
        helloWorld();
    }
}