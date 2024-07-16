#include <stdio.h>

#define BASE_SIZE 10

int readint(int ar[], unsigned size);
int sum_array(int ar[], unsigned size);
float avg_array(int ar[], unsigned size);
void print_array(int ar[], unsigned size);

int main(int argc, char *argv[]) {
    int base[BASE_SIZE];
    int number;
    for(int i=0; i < BASE_SIZE; i++){
        scanf("%d", &number);
        base[i] = number;
        print_array(base, i+1);
        printf("%d %f\n", sum_array(base, i+1), avg_array(base, i+1));
    }
    return 0;
}

int readint(int ar[], unsigned size){
    int i=0;
    for( ; i < size; i++){
        scanf("%d", ar + i);
    }
    return i;
}

int sum_array(int ar[], unsigned size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += ar[i];
    }
    return sum;
}

float avg_array(int ar[], unsigned size){
    float sum = sum_array(ar, size);
    return sum / size;
}

void print_array(int ar[], unsigned size){
    for(int i = 0; i < size; i++){
        printf("%d ", ar[i]);
    }
}