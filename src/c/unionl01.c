#include <stdio.h>

#define MAXMAPSIZ 8

/* integer code for data types */
enum TYPES{INT, CHR, LNG, FLT, DBL};

/*typedef int int32b;*/

/* (single precision) floating point represntation in bits */
typedef union {
    float f;
    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
}frep;

/* double precision floating point representation in bits */
typedef union{
    double d;
    struct {
        unsigned long mantissa : 52;
        unsigned int exponent : 11;
        unsigned int sign : 1;
    }parts;
}drep;

/* miscellaneous types in union in struct */
struct bits{
    union types{
        int i;
        char c;
        long l;
        frep f;
        drep d;
        unsigned char map[MAXMAPSIZ];
    }v;
    enum TYPES t;
};

void init_bmap(struct bits *bmap);
void print_bits(struct bits *bmap);
void print_bytes(struct bits * bmap, size_t size);
void print_hexa(struct bits * bmap, size_t size);
void print_byte(unsigned char c);

int main(int argc, char *argv[]) {
    struct bits bmap;
    init_bmap(&bmap);
    bmap.v.i = -100;
    bmap.t = INT;
    print_bits(&bmap);
    bmap.v.c='G';
    bmap.t=CHR;
    print_bits(&bmap);
    bmap.v.l = 100;
    bmap.t = LNG;
    print_bits(&bmap);
    bmap.v.f.f = 3.17;
    bmap.t=FLT;
    print_bits(&bmap);
    bmap.v.d.d = 3.17l;
    bmap.t=DBL;
    print_bits(&bmap);
    return 0;
}

void init_bmap(struct bits *bmap){
    if(bmap){
        for(int i=0; i<MAXMAPSIZ; i++)
            bmap->v.map[i] = '\0';
    }
}

void print_bits(struct bits *bmap){
    size_t loopctrl;
    if(bmap){
        switch (bmap->t) {
            case INT:
                printf("%d = ", bmap->v.i);
                loopctrl = sizeof(int);
                break;
            case CHR:
                printf("%c = ", bmap->v.c);
                loopctrl = sizeof(char);
                break;
            case LNG:
                printf("%ld = ", bmap->v.l);
                loopctrl = sizeof(long);
                break;
            case FLT:
                printf("%f = ", bmap->v.f.f);
                loopctrl = sizeof(float);
                break;
            case DBL:
                printf("%lf = ", bmap->v.d.d);
                loopctrl = sizeof(double);
                break;
            
        }
        print_bytes(bmap, loopctrl);
        print_hexa(bmap, loopctrl);
        printf("\n");
    }
}

void print_bytes(struct bits *bmap, size_t size){
    if(bmap){
        /*if(bmap->t == FLT || bmap->t == DBL){
            for(int i=0; i < size; i++){
                print_byte(bmap->v.map[i]);
            }
        }
        else*/{
            for(int i=size - 1; i >= 0; i--){
                print_byte(bmap->v.map[i]);
            }
        }
    }
}

void print_byte(unsigned char c){
    char bits[8];
    for(int i = 7; i >= 0; i--){
        if(c > 0){
            bits[i] = (c & 1 ? '1' : '0');
            c >>= 1;
        }
        else 
            bits[i]='0';
    }
    printf("%c%c%c%c%c%c%c%c", bits[0], bits[1], bits[2], bits[3], bits[4], bits[5], bits[6], bits[7]);
}

void print_hexa(struct bits *bmap, size_t size){
    if(bmap){
        printf(", hexa = 0x");
        if(bmap->t == FLT){
            printf("%x ", bmap->v.f.parts.sign);
            printf("%x ", bmap->v.f.parts.exponent);
            printf("%x", bmap->v.f.parts.mantissa);
        }
        else if(bmap->t == DBL){
            printf("%x ", bmap->v.d.parts.sign);
            printf("%x ", bmap->v.d.parts.exponent);
            printf("%lx", bmap->v.d.parts.mantissa);
        }
        else{
            for(int i=size - 1; i >= 0; i--){
                printf("%02x", bmap->v.map[i]);
            }
        }
    }
}

/*
         0011100
        -      1
         0011011
         1100100
*/