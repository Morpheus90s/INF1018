#include <stdio.h>

typedef int (*funcp) (int x);

int main (void) {
    unsigned char codigo[] = {
        0x55,             // push %rbp
        0x48, 0x89, 0xe5, // mov %rsp, %rbp
        0x89, 0xf8,       // mov %edi, %eax
        0xff, 0xc0,       // inc %eax
        0x5d,             // pop %rbp
        0xc3              // ret
    };

    // Forçamos o array a se comportar como uma função através de um typecast de ponteiro
    funcp f = (funcp)codigo;
    int i = f(10);
    
    printf("Resultado esperado (11): %d\n", i);
    return 0;
}