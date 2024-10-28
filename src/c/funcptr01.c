#include <stdio.h>
#include <math.h>

#define SQR_SIZ 8

typedef double (*fltcalc) (double, double);

typedef struct matrix{
    double vals[SQR_SIZ][SQR_SIZ];
    double (*funcs[SQR_SIZ][SQR_SIZ]) (double, double);
}matrix;

void init_matrix(matrix *mx, double seed);

double add(double x, double y);
double sub(double x, double y);
double mul(double x, double y);
double div(double x, double y);
double gcd(double x, double y);
double lcm(double x, double y);

int react(matrix *lop, matrix *rop, matrix *res);
void print(const matrix *m);

int main(int argc, char *argv[]) {
    /*printf("%0.2lf ", gcd(10.5, 20.7));
    printf("%0.2lf", lcm(10.5, 20.7));*/
    matrix a, b, c;
    init_matrix(&a, 10.35);
    init_matrix(&b, 3.75);
    init_matrix(&c, 0);
    react(&a, &b, &c);
    print(&c);
    return 0;
}

void init_matrix(matrix *mx, double seed){
    fltcalc func[SQR_SIZ] = {pow, fmod, add, sub, mul, div, gcd, lcm};
    for(int r = 0; r < SQR_SIZ; r++)
        for(int c = 0; c < SQR_SIZ; c++){
            mx->vals[r][c] = seed;
            mx->funcs[r][c] = func[c];
        }
}

double add(double x, double y){
    return x + y;
}

double sub(double x, double y){
    return x - y;
}

double mul(double x, double y){
    return x * y;
}

double div(double x, double y){
    return x / y;    
}

double gcd(double x, double y)
{
    x = floor(x);
    y = floor(y);
    double temp;
    while (y != 0.0)
    {
        temp = fmod (x, y);
        x = y;
        y = temp;
    }
    return x;
}

double lcm(double x, double y){
    x = floor(x);
    y = floor(y);
    return x * y / gcd(x, y);
}

/*
    lop : left operand of react function
    rop : right operand of react function
    res : result of 'lop react rop'
*/
int react(matrix *lop, matrix *rop, matrix *res){
    if(lop == NULL || rop == NULL || res == NULL)
        return -1;
    for(int r = 0; r < SQR_SIZ; r++)
        for(int c = 0; c < SQR_SIZ; c++){
            res->vals[r][c] = lop->funcs[r][c](lop->vals[r][c], rop->vals[r][c]);
        }
    return 1;
}

void print(const matrix *m){
    for(int r = 0; r < SQR_SIZ; r++){
        for(int c = 0; c < SQR_SIZ; c++){
            printf("%0.2lf ", m->vals[r][c]);
        }
        printf("\n");
    }
}