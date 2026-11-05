#include <stdio.h>
#include <limits.h>
#include "fp.h"

int main() {
    float f1 = 1.5f;
    float f2 = 0.0f;
    printf("float2(%.2f) = %.2f\n", f1, float2(f1));
    printf("float2(%.2f) = %.2f\n\n", f2, float2(f2));

    int testes[] = {0, 1, -1, 1024, -5000, INT_MAX, INT_MIN};
    int num_testes = sizeof(testes) / sizeof(testes[0]);

    for (int t = 0; t < num_testes; t++) {
        int val = testes[t];
        float res_nacional = (float)val;
        float res_minha = int2float(val);
        
        printf("Int: %d | Nativo: %f | Minha Funçao: %f -> %s\n", 
               val, res_nacional, res_minha, 
               (res_nacional == res_minha) ? "OK" : "ERRO");
    }

    return 0;
}
