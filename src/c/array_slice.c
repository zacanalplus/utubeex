#include <stdio.h>

void get_slice(int slice[], int len);
void get_slice2(const int slice1[], const int slice2[]);
void get_slice3(const int *base, size_t len, size_t startIdx, size_t endIdx);
const void *max(const void *addr1, const void *addr2);
const void *min(const void *addr1, const void *addr2);

int main(int argc, char *argv[]) {
    int natnums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //get_slice(&(natnums[9]), 3);
    //get_slice2(&(natnums[9]), &(natnums[10]));
    get_slice3(natnums, 10, 3, 10);
    return 0;
}

void get_slice(int slice[], int len){
    printf("get_slice function\n");
    for(int i = 0; i < len; i++){
        printf("%d\n", slice[i]);
    }
}

void get_slice2(const int slice1[], const int slice2[]){
    printf("get slice 2 function\n");
    const int *start = min(slice1, slice2);
    const int *end = max(slice1, slice2);
    for(const int *i=start; i < end; i++){
        printf("%d\n", *i);
    }
}

void get_slice3(const int *base, size_t len, size_t startIdx, size_t endIdx){
    if(startIdx >= len || endIdx >= len ){
        fprintf(stderr, "%s", "One of the start and end index is out of bound\n");
        return;
    } 
    if (startIdx > endIdx){
        fprintf(stderr, "%s%lu%s%lu\n", "Start index starts ", startIdx, " but end index is ", endIdx);
        return;
    }
    const int *end = base + endIdx;
    printf("get slice function 3\n");
    for(const int *start = base + startIdx; start < end; start++ ){
        printf("%d\n", *start);
    }
}

const void *max(const void *addr1, const void *addr2){
    return addr1 > addr2 ? addr1 : addr2;
}

const void *min(const void *addr1, const void *addr2){
    return addr1 < addr2 ? addr1 : addr2;
}