#include <stdio.h>

int main(int argc, char *argv[]) {
    int day = -4;
    switch(day){
        case 1 : 
            printf("%s\n", "Monday");
            break;
        case 2 :
            printf("%s\n", "Tuesday");
            break;
        case 3 :{
            printf("%s\n", "Wednesday");
            break;
        }
        case 4 :
            printf("%s\n", "Thursday");
            break;
        case 5 :
            printf("%s\n", "Friday");
            break;
        case 6 :
            
        case 0 :
            printf("%s\n", "Weekend");
            break;
        default : {
            printf("%s\n", "Unknown Day");
            break;
        }
    }
    return 0;
}