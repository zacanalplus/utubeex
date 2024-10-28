#include <stdio.h>

#define BASE_SIZE 10

int main(int argc, char *argv[]) {
    int base[BASE_SIZE];
    int sum = 0;
    for(int i = 0; i < BASE_SIZE; i++){
        printf("Integer? ");
        scanf("%d", base + i);
        for(int j=0; j <= i; j++){
            sum += base[j];
        }
        for(int j = 0; j <= i; j++){
            printf("%d ", base[j]);
        }
        printf("%d\n", sum);
        sum = 0;
    }
    return 0;
}