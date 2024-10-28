#include <stdio.h>

#define FACT_SIZE 11

int factorial(int n);

int main(int argc, char *argv[]) {
    int facts[FACT_SIZE];
    for(int i = 0; i < FACT_SIZE; i++){
        facts[i] = factorial(i);
    }
    
    for(int i = 0; i < FACT_SIZE; i++){
        printf("%d ", facts[i]);
    }
    printf("\n");
    return 0;
}

int factorial(int n){
    int prod = 1;
    if(n == 0 || n == 1){
        return prod;
    }
    
    return n * factorial(n - 1);
}