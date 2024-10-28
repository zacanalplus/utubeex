#include <stdio.h>

int count = 0;

int counter();
int count1();
int static_counter();

int main(int argc, char *argv[]) {
    int count = 10;
    printf("count in main\'s is %d.\n", count);
    
    for(int i=0; i < count; i++){
        int count = 12;
        if(i < 1){
            printf("count in for is %d.\n", count);
            {
                extern int count;
                printf("is it global count %d\?\n", count);
            }
        }
    }
    printf("count in main\'s is still %d.\n", count);
    count1();
    counter();
    counter();
    static_counter();
    static_counter();
    count1();
    return 0;
}

int counter(){
    count++;
    printf("global count is now %d.\n", count);
    return count;
}

int count1(){
    int count = 1;
    printf("count1\'s count is always %d.\n", count);
    return count;
}

int static_counter(){
    static int count = 100;
    count++;
    printf("static count keeps it\'s value and continue %d.\n", count);
    return count;
}