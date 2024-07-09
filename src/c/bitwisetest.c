#include <stdio.h>

int main(int argc, char *argv[]) {
    int num = 10;
    
    if(num & 1){
        printf("%d is odd number.\n", num);
    }
    else{
        printf("%d is even number.\n", num);
    }
    
    int sieve_7 = num & 7;
    printf("%d & 7 = %d\n", num, sieve_7);
    
    int onecompl_num = ~num;
    printf("~%d = %d\n", num, onecompl_num);
    
    num = 0x64;
    printf("%d = 0%o = 0x%x\n", num, num, num);
    int numless = num >> 1;
    printf("%d >> 1 = %d\n", num, numless);
    printf("%d << 1 = %d\n", num, num << 1);
    sieve_7 = num | 7;
    printf("%d | 7 = %d\n", num, sieve_7);
    sieve_7 = num ^ 7;
    printf("%d ^ 7 = %d\n", num, sieve_7);
    
    printf("Before 1: %d, %d\n", num, sieve_7);
    num ^= sieve_7;
    printf("After 1: %d, %d\n", num, sieve_7);
    sieve_7 ^= num;
    printf("After 2: %d, %d\n", num, sieve_7);
    num ^= sieve_7;
    printf("After 3: %d, %d\n", num, sieve_7);
    return 0;
}