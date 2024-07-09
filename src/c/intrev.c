#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1
#define MAX_INT_LEN 16

int reverse(int num);

int main(int argc, char *argv[]) {
    int num = 1233;
    num = reverse(num);
    printf("After reverse %d\n", num);
    return 0;
}

int reverse(int num){
    int minus = FALSE;
    int digits[MAX_INT_LEN];
    if(num < 10 && num > -10)
        return num;
    if(num < 0){
        num = -num;
        minus = TRUE;
    }
    
    int idx = 0;
    do{
        digits[idx++] = num % 10;
    }while((num /= 10) > 0);  
    
    for(int i=0; i < idx; i++){
        int digit = digits[i] * pow(10, idx - i - 1);
        num += digit;
    }
    if(minus){
        num = -num;
    }
    return num; 
}