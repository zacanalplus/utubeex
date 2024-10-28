#include <stdio.h>

int fibonacci(int num);

int main(int argc, char *argv[]) {
    int n = 2;
    for(; n < 11; n++){
        printf("fib(%d)=%d\n", n, fibonacci(n));
    }
    return 0;
}

int fibonacci(int num){
    int fib0 = 0;
    int fib1 = 1;
    int fibn;
    if(num == 0)
        return fib0;
    else if(num == 1){
        return fib1;
    } 
    else{
        fibn = fibonacci(num - 1) + fibonacci(num - 2);
    }
    return fibn;
}