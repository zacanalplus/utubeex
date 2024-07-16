#include <stdio.h>

#define MAXLEN 100

int getline1(char str[], unsigned int maxlen);
int reverse(char str[], unsigned int length);

int main(int argc, char *argv[]) {
    char text[MAXLEN + 1];
    int read_length = getline1(text, MAXLEN);
    reverse(text, read_length);
    printf("%s\n", text);
    return 0;
}

int getline1(char str[], unsigned int maxlen){
    int c, i;
    for(i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++){
        str[i] = c;
    }
    str[i] = '\0';
    return i;
}

int reverse(char str[], unsigned int length){
    int tmp;
    int half = length / 2;
    int counter = 0;
    for(int i = 0; i < half; i++){
        tmp = str [i];
        str[i] = str [length - i - 1];
        str [length - i - 1] = tmp;
        counter++;
    }
    return counter;
}