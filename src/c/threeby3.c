#include <stdio.h>
#include <time.h>
#include "magicsquare.h"

#define SQLEN 5

int main(int argc, char *argv[]) {
    
    int square[SQLEN * SQLEN];
    /* seedrand(time(NULL)); */
    /* compsquare(square, SQLEN);
    printsquare(square, SQLEN);
    if(check_magic(square, SQLEN)==0){
        print_anomalies();
    }
    ishuffle(square, SQLEN * SQLEN, SQLEN);
    if(check_magic(square, SQLEN)==0){
        print_anomalies();
    }
    
    while(check_magic(square, SQLEN)==0){
        ishuffle(square, SQLEN * SQLEN, SQLEN);
        printsquare(square, SQLEN);
    } */
    
    while(inputsquare(square, SQLEN) != EOF){
        if(check_magic(square, SQLEN) == 1)
            printsquare(square, SQLEN);
    }
    return 0;
}