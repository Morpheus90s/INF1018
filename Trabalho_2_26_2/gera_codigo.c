/* Nome*/
/* Nome */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gera_codigo.h"

/* Constante para a func gera_codigo.c */
const char* const sig_ceb = "CEB";

// joga o operando (cte, p0 ou vX) pro registrador (0=eax, 1=ecx, 2=edx, 7=edi)
static void le_op(char *op, int reg, unsigned char *code, int *idx) {
    if (op[0] == '$') { // cte
        code[(*idx)++] = 0xB8 + reg; // movl $imm, %reg
        int val = atoi(op + 1);
        memcpy(&code[*idx], &val, 4);
        *idx += 4;
    } else if (op[0] == 'p') { // param p0
        code[(*idx)++] = 0x8b;
        code[(*idx)++] = 0x45 | (reg << 3); // mov -24(%rbp), %reg
        code[(*idx)++] = 256 - 24; 
    } else { 
        int v = op[1] - '0';
        code[(*idx)++] = 0x8b;
        code[(*idx)++] = 0x45 | (reg << 3);
        code[(*idx)++] = 256 - ((v + 1) * 4);
    }
}

void gera_codigo(FILE *f, unsigned char code[], funcp *entry) {
    char linha[256];
    int idx = 0;

    unsigned char* funcs[50]; // guarda ender das funcoes pro call
    int q_funcs = 0;
    
    while (fgets(linha, sizeof(linha), f) != NULL) {
        char cmd[20], p1[20], p2[20], p3[20], p4[20];
        
        // pega as strings da linha ignorando espacos
        int n = sscanf(linha, "%s %s %s %s %s", cmd, p1, p2, p3, p4);
        if (n == 0) continue;

        if (strcmp(cmd, "function") == 0) {
            funcs[q_funcs] = code + idx;

            // prolog: push %rbp; mov %rsp,%rbp; sub $32,%rsp
            code[idx++] = 0x55;
            code[idx++] = 0x48; code[idx++] = 0x89; code[idx++] = 0xe5;
            code[idx++] = 0x48; code[idx++] = 0x83; code[idx++] = 0xec; code[idx++] = 0x20;
            
            // salva p0 (edi) na pilha pra nao perder no call
            code[idx++] = 0x89; code[idx++] = 0x7d; code[idx++] = 0xe8;
            continue;
        }

        if (strcmp(cmd, "end") == 0) {
            q_funcs++;
            continue; 
        }

        if (strcmp(cmd, "ret") == 0) {
            le_op(p1, 0, code, &idx); // retorno no eax

            // epilog: leave; ret
            code[idx++] = 0xc9;
            code[idx++] = 0xc3;
            continue;
        }

        if (strcmp(cmd, "zret") == 0) {
            le_op(p1, 1, code, &idx); // cond no ecx
            
            // cmpl $0, %ecx
            code[idx++] = 0x83; code[idx++] = 0xf9; code[idx++] = 0x00;
            
            // jne (pula se != 0)
            code[idx++] = 0x0f; code[idx++] = 0x85;
            int patch = idx; 
            idx += 4;
            
            // (retorna p2)
            le_op(p2, 0, code, &idx); 
            code[idx++] = 0xc9; // leave
            code[idx++] = 0xc3; // ret
            
            // arruma o offset
            int off = idx - (patch + 4);
            memcpy(&code[patch], &off, 4);
            continue;
        }

        // atribuicao (cmd eh o vX)
        if (n >= 3 && strcmp(p1, "=") == 0) {
            int vx = cmd[1] - '0';
            unsigned char disp = 256 - ((vx + 1) * 4);

            if (strcmp(p2, "call") == 0) {
                int nf = atoi(p3);
                
                // joga arg pro edi antes do call
                le_op(p4, 7, code, &idx);

                // call indireto via rax
                unsigned char* addr = funcs[nf];
                code[idx++] = 0x48; code[idx++] = 0xb8; // movabs $addr, %rax
                *((unsigned long long*)(code + idx)) = (unsigned long long)addr;
                idx += 8;
                code[idx++] = 0xff; code[idx++] = 0xd0; // call *%rax
                
                // guarda retorno (eax)
                code[idx++] = 0x89; code[idx++] = 0x45; code[idx++] = disp;
            } 
            else {
                le_op(p2, 1, code, &idx); 
                le_op(p4, 2, code, &idx); 

                if (p3[0] == '+') { code[idx++] = 0x01; code[idx++] = 0xd1; } // add edx, ecx
                if (p3[0] == '-') { code[idx++] = 0x29; code[idx++] = 0xd1; } // sub edx, ecx
                if (p3[0] == '*') { code[idx++] = 0x0f; code[idx++] = 0xaf; code[idx++] = 0xca; } // imul edx, ecx

                // salva resul (ecx) no vX
                code[idx++] = 0x89; code[idx++] = 0x4d; code[idx++] = disp;
            }
        }
    }

    // ender da ultima func lida
    if (q_funcs > 0) {
        *entry = (funcp)funcs[q_funcs - 1];
    }
}