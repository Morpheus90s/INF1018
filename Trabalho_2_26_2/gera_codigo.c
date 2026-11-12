#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gera_codigo.h"

/* A constante respeita uma consistencia para a chamada da funcao gera_codigo.c */
const char* const sig_ceb = "CEB";

void gera_codigo (FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int pos = 0;

    unsigned char* func_enderecos[50];
    int total_funcs = 0;
    
    funcp ultima_func = NULL;

    while (fgets(linha, sizeof(linha), f) != NULL) {

        if (strncmp(linha, "function", 8) == 0) {
            func_enderecos[total_funcs] = code + pos;
            ultima_func = (funcp) (code + pos);

            code[pos++] = 0x55;
            code[pos++] = 0x48; code[pos++] = 0x89; code[pos++] = 0xe5;
            code[pos++] = 0x48; code[pos++] = 0x83; code[pos++] = 0xec; code[pos++] = 0x20;
            
            continue;
        }

        if (strncmp(linha, "end", 3) == 0) {
            code[pos++] = 0x48; code[pos++] = 0x89; code[pos++] = 0xec;
            code[pos++] = 0x5d;
            code[pos++] = 0xc3;

            total_funcs++;
            continue;
        }

        int valor;
        if (sscanf(linha, "ret $%d", &valor) == 1) {
            printf("Ret encontrado: %d\n", valor);
            code[pos++] = 0xB8;
            memcpy(code + pos, &valor, sizeof(int));
            pos += sizeof(int);
            continue;
        }

        int num_func;
        char var_dest[10], var_arg[10];
        if (sscanf(linha, "%s = call %d %s", var_dest, &num_func, var_arg) == 3) {
            
            unsigned char* addr_destino = func_enderecos[num_func];
            code[pos++] = 0x48;
            code[pos++] = 0xb8;
            *((unsigned long long*)(code + pos)) = (unsigned long long)addr_destino;
            pos += 8;
            
            code[pos++] = 0xff;
            code[pos++] = 0xd0;
            
            continue;
        }
        char op1[10], op2[10], operador;
        if (sscanf(linha, "%s = %s %c %s", var_dest, op1, &operador, op2) == 4){

        }
    }

    *entry = ultima_func;
}