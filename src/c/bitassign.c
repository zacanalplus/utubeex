#include <stdio.h>

#define ARRAY_SIZ 7

int bit_count(long num);

int main(int argc, char *argv[]) {
    int test_data[ARRAY_SIZ] = { 10, 11, 7, 15, 6, 16, 24};
    for(int i=0; i < ARRAY_SIZ; i++){
        printf("%d has %d bit(s).\n", test_data[i], bit_count(test_data[i]));
    }
    return 0;
}

int bit_count(long num){
    int cnt = 0;
    while(num){
        num &= (num - 1);
        cnt++;
    }
    return cnt;
}