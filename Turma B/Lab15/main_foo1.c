#include <stdio.h>
#include <math.h>

float foo1(float a, float b);

int main(void) {
    printf("foo1(0, 2.5) = %f\n", foo1(0.0f, 2.5f));
    printf("foo1(PI/2, 2.5) = %f\n", foo1((float)M_PI_2, 2.5f));
    return 0;
}
