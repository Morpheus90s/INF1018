#include <stdio.h>

typedef int (*funcp) (int x);

// Implementamos a função add que será o alvo do nosso salto call
int add (int x) {
    return x + 1;
}

int main (void) {
    // Array com os bytes do novo foo.s (push, mov, call zerado, pop, ret)
    unsigned char codigo[] = {
        0x55,                          // 0: push %rbp
        0x48, 0x89, 0xe5,              // 1: mov %rsp, %rbp
        0xe9, 0x00, 0x00, 0x00, 0x00,  // 4: call add (e8 seguido por 4 bytes que vamos corrigir)
        0x5d,                          // 9: pop %rbp
        0xc3                           // 10: ret
    };

    // 1. Identificar onde o call está posicionado
    int n = 4; // O opcode 0xe8 está no índice 4 do array
    int prox_inst = n + 5; // A próxima instrução (pop) está no índice 9

    // 2. Descobrir os endereços de memória reais de 64 bits (long)
    long addr_add = (long)add;
    long addr_prox = (long)&codigo[prox_inst];

    // 3. Calcular o deslocamento (cabe em um inteiro de 32 bits com sinal)
    int deslocamento = (int)(addr_add - addr_prox);

    // 4. Injetar o valor em Little-Endian nos índices n+1, n+2, n+3, n+4 
    codigo[n + 1] = (unsigned char)(deslocamento & 0xFF);         // Byte mais baixo
    codigo[n + 2] = (unsigned char)((deslocamento >> 8) & 0xFF);
    codigo[n + 3] = (unsigned char)((deslocamento >> 16) & 0xFF);
    codigo[n + 4] = (unsigned char)((deslocamento >> 24) & 0xFF); // Byte mais alto

    // 5. Testar o experimento!
    funcp f = (funcp)codigo;
    
    printf("Testando chamada dinamica com call calculado...\n");
    printf("Resultado esperado (51): %d\n", f(50));

    return 0;
}