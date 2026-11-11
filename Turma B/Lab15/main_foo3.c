#include <stdio.h>
#include <math.h>

double foo3(double *a, int n);

int main(void) {
    double vet[] = {0.0, M_PI_2, M_PI, 3 * M_PI_2};
    printf("foo3 (4 elementos) = %lf\n", foo3(vet, 4));
    printf("foo3 (2 elementos) = %lf\n", foo3(vet, 2));
    return 0;
}
