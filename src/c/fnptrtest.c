#include <stdio.h>


int (*fptr) (int);
int (*fptr2) (void);
void (*fptr3) (float);

int test(int);

int main(int argc, char *argv[]) {
    fptr = test;
    printf("%d\n", fptr(8));
    return 0;
}

int test(int x){
    if(x & 1)
        return 1;
    return 2;
}