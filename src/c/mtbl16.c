#include <stdio.h>

int main(int argc, char *argv[]) {
    int number = 1;
    do{
        if(number == 10 || number == 11)
            continue;
        for(int multiplier = 1; multiplier <= 12; multiplier++){
            printf("%d x %d = %d\n", number, multiplier, number * multiplier);
        }
        printf("------------\n");
    }while(++number <= 16);
    return 0;
}