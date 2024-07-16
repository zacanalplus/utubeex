#include <stdio.h>

int count = 11;

int count1();
int counter_static();
int Count1();

int main(int argc, char *argv[]) {
    int count = 10;
    printf("Main\'s count is %d.\n", count);
    for(int count = 0; count < 1; count++){
        printf("For loop counter is %d.\n", count);
        {
            float count = 1.1;
            printf("inner code block count is %f.\n", count);
            if(count > 1){
                extern int count;
                printf("Global count is now %d.\n", count);
                
                printf("count1 function always returns %d.\n", count1());
                printf("count1 function always returns %d.\n", count1());
                printf("counter_static function returned %d.\n", counter_static());
                printf("counter_static function returned %d.\n", counter_static());
                printf("Count1 function return global count value %d.\n", Count1());
                printf("Global count value is now %d.\n", count); 
            }
        }
    }
    return 0;
}

int count1(){
    int count = 0;
    return ++count;
}

int counter_static(){
    static int count = 0;
    return ++count;
}

int Count1(){
    extern int count;
    count = 22;
    return count;
}