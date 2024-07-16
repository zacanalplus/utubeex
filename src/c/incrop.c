#include <stdio.h>

int remove_letter(char *text, int letter);

int main(int argc, char *argv[]) {
    char greeting[] = "Hello from C program";
    int ch = 'o';
    int nremoved = remove_letter(greeting, ch);
    printf("%s, %d letters removed\n", greeting, nremoved);
    int i = 5, j = 5;
    int i1 = i++;
    int j1 = ++j;
    printf("i1 = %d, j1=%d\n", i1, j1);
    printf("i = %d, j = %d\n", i, j);
    return 0;
}

int remove_letter(char *text, int letter){
    int i = 0, j = 0, removed_count = 0;
    for(; text[i] != '\0'; i++){
        if(text[i] != letter){
            text[j++] = text[i];
        }
        else{
            removed_count++;
        }
    }
    text[j] = '\0';
    return removed_count;
}