/* Pedro Augusto Beserra da Silva - 2321374 - 3WC */

#include <stdio.h>
#include "cria_func.h"

void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;           
    int cont_param = 0;  

    codigo[i++] = 0x55;             // pushq %rbp
    codigo[i++] = 0x48;             // movq %rsp, %rbp
    codigo[i++] = 0x89; 
    codigo[i++] = 0xe5;

    //(subq $32, %rsp)
    codigo[i++] = 0x48; 
    codigo[i++] = 0x83; 
    codigo[i++] = 0xec; 
    codigo[i++] = 0x20; 

    // movq %rdi, -8(%rbp)
    codigo[i++] = 0x48; codigo[i++] = 0x89; codigo[i++] = 0x7d; codigo[i++] = 0xf8;
    // movq %rsi, -16(%rbp)
    codigo[i++] = 0x48; codigo[i++] = 0x89; codigo[i++] = 0x75; codigo[i++] = 0xf0;
    // movq %rdx, -24(%rbp)
    codigo[i++] = 0x48; codigo[i++] = 0x89; codigo[i++] = 0x55; codigo[i++] = 0xe8;

    for (int p = 0; p < n; p++) {
        
        if (params[p].orig_val == PARAM) {
            int gaveta_origem = 0;
            if (cont_param == 0)      gaveta_origem = 0xf8; //-8(%rbp)
            else if (cont_param == 1) gaveta_origem = 0xf0; //-16(%rbp)
            else                      gaveta_origem = 0xe8; //-24(%rbp)

            // Coloca o gaveta no registrador
            codigo[i++] = 0x48; 
            codigo[i++] = 0x8b; 
            if (p == 0)      codigo[i++] = 0x7d; //%rdi
            else if (p == 1) codigo[i++] = 0x75; //%rsi
            else             codigo[i++] = 0x55; //%rdx
            
            codigo[i++] = (unsigned char)gaveta_origem;
            cont_param++; 
        }
        
        else if (params[p].orig_val == FIX) {
            if (params[p].tipo_val == INT_PAR) {
                //Coloca a constante no registrador32
                if (p == 0)      codigo[i++] = 0xbf; // Destino %edi
                else if (p == 1) codigo[i++] = 0xbe; // Destino %esi
                else             codigo[i++] = 0xba; // Destino %edx
                
                int val = params[p].valor.v_int;
                codigo[i++] = (unsigned char)(val & 0xFF);
                codigo[i++] = (unsigned char)((val >> 8) & 0xFF);
                codigo[i++] = (unsigned char)((val >> 16) & 0xFF);
                codigo[i++] = (unsigned char)((val >> 24) & 0xFF);
            } 
            else if (params[p].tipo_val == PTR_PAR) {
                //ponteiro
                codigo[i++] = 0x48;
                if (p == 0)      codigo[i++] = 0xbf; //%rdi
                else if (p == 1) codigo[i++] = 0xbe; //%rsi
                else             codigo[i++] = 0xba; //%rdx
                
                long val = (long)params[p].valor.v_ptr;
                for (int b = 0; b < 8; b++) {
                    codigo[i++] = (unsigned char)(val & 0xFF);
                    val >>= 8;
                }
            }
        }
        
        else if (params[p].orig_val == IND) {
            //lab13
            codigo[i++] = 0x48;
            codigo[i++] = 0xb8; 
            
            long endereco_var = (long)params[p].valor.v_ptr;
            for (int b = 0; b < 8; b++) {
                codigo[i++] = (unsigned char)(endereco_var & 0xFF);
                endereco_var >>= 8;
            }

            if (params[p].tipo_val == INT_PAR) {
                codigo[i++] = 0x8b;
                if (p == 0)      codigo[i++] = 0x38; // movl (%rax), %edi
                else if (p == 1) codigo[i++] = 0x30; // movl (%rax), %esi
                else             codigo[i++] = 0x10; // movl (%rax), %edx
            } 
            else if (params[p].tipo_val == PTR_PAR) {
                codigo[i++] = 0x48; codigo[i++] = 0x8b;
                if (p == 0)      codigo[i++] = 0x38; // movq (%rax), %rdi
                else if (p == 1) codigo[i++] = 0x30; // movq (%rax), %rsi
                else             codigo[i++] = 0x10; // movq (%rax), %rdx
            }
        }
    }

    codigo[i++] = 0x48;
    codigo[i++] = 0xb8; // movabsq $f, %rax
    
    long endereco_f = (long)f;
    for (int b = 0; b < 8; b++) {
        codigo[i++] = (unsigned char)(endereco_f & 0xFF);
        endereco_f >>= 8;
    }

    codigo[i++] = 0xff;
    codigo[i++] = 0xd0; // call *%rax

    codigo[i++] = 0xc9; // leave
    codigo[i++] = 0xc3; // ret
}