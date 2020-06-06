#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void (*PRINT_INT)(int *);
typedef void (*PRINT_INT_VALUE)(int);

void PrintDouble(double *a) {
    printf("%u\n", a);
    printf("%f\n", *a);
}

void PrintDoubleValue(double a) {
    printf("%d\n", a);
    printf("%f\n", a);
}

struct yabai {
    void (*yahoo)(int *);
    void (*yahoo2)(int);
};
struct yabai p = { .yahoo=PrintDouble, .yahoo2=PrintDoubleValue };

int main(void) {
    PRINT_INT f = (PRINT_INT)PrintDouble;
    double p = 2.2356;
    f(&p);
    PrintDouble(&p);
    
    PRINT_INT_VALUE ff = (PRINT_INT_VALUE)PrintDoubleValue;
    ff(p);
    PrintDoubleValue(p);

    return 0;
}