#include <stdio.h>
#include <stdlib.h>

const char *greeting = "How are u? JOHN!!!";


char *strcopy(char *desc, const char *src);
char *make0string(size_t len);
int strlength(const char *str);
int reverse(char str[], unsigned int length);
char *strreverse(const char *str);
int *init_arr(size_t len);

int main(int argc, char *argv[]) {
    char *sarr;
    size_t len = strlength(greeting) + 1;
    sarr = make0string(len);
    strcopy(sarr, greeting);
    printf("%s\n", sarr);
    free(sarr);
    char *reversed_greet = strreverse(greeting);
    printf("%s\n", reversed_greet);
    free(reversed_greet);
    return 0;
}

char *strcopy(char *desc, const char *src){
    if((!desc || !src) && desc == src)
        return NULL;
    while((*desc++ = *src++) != '\0')
        ;
    return desc;
}

char *make0string(size_t len){
    if(len < 1)
        return NULL;
    char *s = (char *)malloc(len * sizeof(char)); 
    return s;
}

int strlength(const char *s){
    int len = 0;
    while(*s++ != '\0')
        len++;
    return len;
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

char *strreverse(const char *str){
    size_t len = strlength(str);
    char *s = make0string(len + 1);
    char *rstr = s;
    while(len){
        *s++ = str[--len];
    }
    *s = '\0';
    return rstr;
}

int *init_arr(size_t len){
    int *iarr = (int *)calloc(len, sizeof(int));
    return iarr;
}