# include <stdio.h>
# include <stdlib.h>
#include <time.h>

char *strcopy(char *desc, const char *src);
char *make0string(size_t len);
size_t strlength(const char *str);
void freestr(char *str);
char *strreverse(const char *ostr);
int *create_init(size_t size);
int *create_iarr(size_t size);

int reverse(char str[], unsigned int length);

const char *greeting = "How are u? CYOG!!!";

int main(int argc, char *argv[])
{
	/*char sarr[16];*/
	srand(time(NULL));
	int i;
	size_t len = strlength(greeting);
//	/* Below line will caught Memory error */
//	reverse(greeting, len);
	char *sarr = make0string(len + 1);
	if(sarr){
		strcopy(sarr, greeting);
		printf("%s\n", sarr);
		printf("%p is greeting\'s address\n", greeting);
		printf("The size of string literal variable is %zu. \n", sizeof(greeting));
		printf("%p is new string\'s address\n", sarr);
		printf("%p is local variable\'s address\n", &i);
		freestr(sarr);
	}
	char *reversed_greet = strreverse(greeting);
	printf("%s\n", reversed_greet);
	free(reversed_greet);
//	const int arr_size = 10;
//	int *ia1 = create_init(arr_size);
//	int *ia2 = create_iarr(arr_size);
//	for(int i =0; i < arr_size; i++){
//		ia2[i] = rand();
//	}
//	printf("initialized %p, un-initialized %p\n", ia1, ia2);
//	for(int i=0; i<arr_size; i++){
//		printf("initialized %d, un-initialized %d\n", ia1[i], ia2[i]);
//	}
//	free(ia1);
//	free(ia2);
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
	if(len > 0){
		char *s = (char *)malloc(sizeof(char) * len);
		return s;
	}
	return NULL;
}

size_t strlength(const char *str){
	size_t len = 0;
	while(*str++ != '\0')
		len++;
	return len;
}

void freestr(char *str){
	if(str)
		free(str);
}

char *strreverse(const char *ostr){
	if(ostr){
		size_t len = strlength(ostr);
		char *newstr = (char *)malloc(sizeof(char) * (len + 1));
		char *tmpstr = newstr;
		while (len)
			*tmpstr++ = ostr[--len];
		*tmpstr = '\0';
		return newstr;
	}
	return NULL;
}

int *create_init(size_t size){
	if(size < 1)
		return NULL;
	int *iarr = (int *)calloc(size, sizeof(int));
	return iarr;
}

int *create_iarr(size_t size){
	if(size < 1)
		return NULL;
	int *iarr = (int *)malloc(sizeof(int) * size);
	return iarr;
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