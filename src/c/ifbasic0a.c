#include <stdio.h>

int main(int argc, char *argv[]) {
    int c = getchar();
    
    if(c == '+'){
        printf("\nplus sign\n");
    }
    else if(c == '-'){
        printf("\nminus sign\n");
    }
    else if(c == '*'){
        printf("\n star sign, multiply sign\n");
    }
    else if(c == '/'){
        printf("\ndivision sign\n");
    }
    else if(c >= 'a' && c <= 'z'){
        printf("\nIt was a small letter.\n");
    }
    else if(c >= 'A' && c <= 'Z'){
        printf("\nIt was a capital leter.\n");
    }
    else if(c >= '0' && c <= '9'){
        printf("\nIt was a digit.\n");
    }
    else{
        printf("\nIt was non-alphabetic, non-numeric character.\n");
    }
    return 0;
}