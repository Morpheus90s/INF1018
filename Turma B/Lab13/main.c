#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_START(P) ((intptr_t)(P)&~(pagesize-1))
#define PAGE_END(P) (((intptr_t)(P)+pagesize-1)&~(pagesize-1))

typedef int (*funcp) (int x);

int execpage(void *ptr, size_t len) {
    int ret;
    const long pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) return -1;
    ret = mprotect((void *)PAGE_START(ptr),
         PAGE_END((intptr_t)ptr + len) - PAGE_START(ptr),
         PROT_READ | PROT_WRITE | PROT_EXEC);
    if (ret == -1) return -1;
    return 0;
}

int add (int x) {
    return x + 1;
}

int main() {
    unsigned char codigo[] = {0xe9, 0x00, 0x00, 0x00, 0x00};

    if (execpage(codigo, sizeof(codigo)) != 0) {
        perror("Erro ao mudar permissoes");
        return 1;
    }

    unsigned char *proxima_instrucao = &codigo[5];

    int32_t deslocamento = (int32_t)((unsigned char *)add - proxima_instrucao);

    codigo[1] = (deslocamento & 0xFF);
    codigo[2] = ((deslocamento >> 8) & 0xFF);
    codigo[3] = ((deslocamento >> 16) & 0xFF);
    codigo[4] = ((deslocamento >> 24) & 0xFF);

    funcp f = (funcp)codigo;
    int i = (*f)(10);

    printf("Resultado de foo_jmp(10): %d\n", i); 
    return 0;
}
