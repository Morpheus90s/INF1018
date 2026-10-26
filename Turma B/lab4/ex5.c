#include <stdio.h>

void dump(void *ptr, size_t tamanho) {
    unsigned char *b = (unsigned char *)ptr;
    printf("Dump da memória (Hex): ");
    for (size_t i = 0; i < tamanho; i++) {
        printf("%02x ", b[i]);
    }
    printf("\n");
}

int main(void) {
    signed char sc = -1;
    unsigned int ui = sc;

    printf("Valor em sc (signed char):  %d\n", sc);
    printf("Valor em ui (unsigned int): %u (Hex: 0x%08x)\n", ui, ui);

    dump(&ui, sizeof(ui));

    return 0;
}
