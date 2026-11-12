#include "gera_codigo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo.lbs> <param>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Erro ao abrir %s\n", argv[1]);
        return 1;
    }

    unsigned char code[1024];
    funcp funcLBS = NULL;

    gera_codigo(fp, code, &funcLBS);
    fclose(fp);

    if (funcLBS == NULL) {
        printf("Falha na geracao!\n");
        return 1;
    }

    int arg = atoi(argv[2]);
    int res = (*funcLBS)(arg);
    printf("Resultado: %d\n", res);
    
    return 0;
}