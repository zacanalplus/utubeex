#include <stdio.h>

#define BITS_IN_BYTE 8

int check_odd(int n);
int check_even(int n);
int check_nthbit(int n, int nth);
int turnon_nthbit(int *ptrn, int nth);
void swap(int *plnum, int *prnum);

int main(int argc, char *argv[]) {
    int num = 10;
    printf("%d >> 1 = %d\n", num, num >> 1); /* 1010 >> 1 => 0101 */
    printf("10 & 7 = %d\n", num & 7);
    printf("~10 = %d\n", ~num);
    if(check_odd(num)){
        printf("%d is odd number. \n", num);
    }
    else{
        printf("%d is even number. \n", num);
    }
    if(check_nthbit(num, 1)){
        printf("First bit from leftmost bit of %d is 1. \n", num);
    }
    else{
        printf("First bit from leftmost bit of %d is 0. \n", num);
    }
    turnon_nthbit(&num, 1); /* turn on rightmost bit of 10 => 11 */
    printf("The value of num is now %d. \n", num);
    int num2 = 199;
    swap(&num, &num2);
    printf("First num = %d, second num = %d\n", num, num2);
    return 0;
}

int check_odd(int n){
    return n & 1;
}

int check_even(int n){
    return (n & 1) == 0;
}

int check_nthbit(int n, int nth){
    if(nth > (sizeof(n) * BITS_IN_BYTE))
        return 0;
    int right_op = 1 << (nth - 1);
    return (n & right_op) != 0;
}

int turnon_nthbit(int *ptrn, int nth){
    if(nth > (sizeof(*ptrn) * BITS_IN_BYTE))
        return 0;
    int right_op = 1 << (nth - 1);
    return (*ptrn |= right_op);
}

void swap(int *plnum, int *prnum){
    *plnum ^= *prnum;
    *prnum ^= *plnum;
    *plnum ^= *prnum;
}