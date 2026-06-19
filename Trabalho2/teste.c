
/* Pedro Augusto Beserra da Silva - 2321374 - 3WC */

#include <stdio.h>
#include <string.h>
#include "cria_func.h"

int total_ok = 0;
int total_testes = 0;

void checa(const char* nome, int esperado, int obtido) {
    total_testes++;
    if (esperado == obtido) {
        total_ok++;
        printf("[OK]    %s -> %d\n", nome, obtido);
    } else {
        printf("[ERRO]  %s -> esperado %d, obtido %d\n", nome, esperado, obtido);
    }
}

int f_original(int a, int b, int c) {
    return a + (b * 10) + (c * 100);
}

int mult(int x, int y) {
    return x * y;
}

char fixa[] = "quero saber se a outra string e teste";

int main (void) {
    unsigned char codigo[500];
    DescParam params[3];

    {
        typedef int (*func_ptr)(int, int, int);
        func_ptr f;

        params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
        params[1].tipo_val = INT_PAR; params[1].orig_val = PARAM;
        params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;

        cria_func(f_original, params, 3, codigo);
        f = (func_ptr) codigo;

        checa("3 parametros, todos PARAM", f_original(1, 2, 3), f(1, 2, 3));
    }

    {
        typedef int (*func_ptr)(int, int);
        func_ptr f;

        params[0].tipo_val = INT_PAR; params[0].orig_val = FIX;
        params[0].valor.v_int = 5;
        params[1].tipo_val = INT_PAR; params[1].orig_val = PARAM;
        params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;

        cria_func(f_original, params, 3, codigo);
        f = (func_ptr) codigo;

        checa("FIX + PARAM + PARAM", f_original(5, 3, 2), f(3, 2));
    }

    {
        typedef int (*func_ptr)(void);
        func_ptr f;
        int i;

        params[0].tipo_val = INT_PAR; params[0].orig_val = IND;
        params[0].valor.v_ptr = &i;
        params[1].tipo_val = INT_PAR; params[1].orig_val = FIX;
        params[1].valor.v_int = 10;

        cria_func(mult, params, 2, codigo);
        f = (func_ptr) codigo;

        i = 7;
        checa("IND (variavel) + FIX", mult(i, 10), f());

        i = 42;
        checa("IND (variavel atualizada) + FIX", mult(i, 10), f());
    }

    {
        typedef int (*func_ptr)(void*, size_t);
        func_ptr f;
        char s1[] = "quero saber tudo";
        char s2[] = "quero saber outra coisa";

        params[0].tipo_val = PTR_PAR; params[0].orig_val = FIX;
        params[0].valor.v_ptr = fixa;
        params[1].tipo_val = PTR_PAR; params[1].orig_val = PARAM;
        params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;

        cria_func(memcmp, params, 3, codigo);
        f = (func_ptr) codigo;

        checa("memcmp prefixo igual (n=12)", memcmp(fixa, s1, 12), f(s1, 12));
        checa("memcmp prefixo diferente", memcmp(fixa, s2, strlen(s2)), f(s2, strlen(s2)));
    }

    {
        typedef int (*func_ptr)(void);
        func_ptr f;
        char* p_str;
        char alvo[] = "quero saber se a outra string e teste";

        params[0].tipo_val = PTR_PAR; params[0].orig_val = IND;
        params[0].valor.v_ptr = &p_str;
        params[1].tipo_val = PTR_PAR; params[1].orig_val = FIX;
        params[1].valor.v_ptr = fixa;
        params[2].tipo_val = INT_PAR; params[2].orig_val = FIX;
        params[2].valor.v_int = 10;

        cria_func(memcmp, params, 3, codigo);
        f = (func_ptr) codigo;

        p_str = alvo;
        checa("IND ponteiro + FIX ponteiro + FIX int", memcmp(alvo, fixa, 10), f());
    }

    printf("\nResumo: %d/%d testes passaram\n", total_ok, total_testes);

    return 0;
}