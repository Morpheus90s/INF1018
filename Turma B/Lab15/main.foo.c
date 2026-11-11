#include <stdio.h>

float foo(double a, float b);

int main(void) {
    double a = 5.0;
    float b = 3.0;

    printf("foo(5.0, 3.0) = %f\n", foo(a, b));
    return 0;
}
