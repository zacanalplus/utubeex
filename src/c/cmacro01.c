#include <stdio.h>
#include "max.h"


int main(int argc, char *argv[]) {
    int n1 = 2;
    infinite_loop{
        printf("Square sum of %d = %d, sum square = %d\n", n1, SQSUM(n1), SUMSQ(n1));
        n1++;
        if(n1 > 10)
            break;
    }
    int n2 = 100;
    printf("Max of %d and %d is %d.\n", n1, n2, MAX(n1, n2));
    printf("Max = %d\n", max(n1++, n2++));
    debug_variable("No side effect with function ", n1, "%d");
    debug_variable(" ", n2, "%d\n");
    swap(int, n1, n2);
    printf("After swap : n1=%d, n2=%d\n", n1, n2);
    double m_pi = 3.141592, r = 2.1;
    printf("Max of pi and r = %g\n", MAX(m_pi, r));
    cat(double, circle, area) = m_pi * r * r;
    debug_variable("Area of circle is ", circlearea, "%g\n");
    return 0;
}

int max(int x, int y){
    return MAX(x, y);
}