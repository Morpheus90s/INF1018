#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
    unsigned char v1 = (x & 0xF0) >> 4; 
    unsigned char v2 = (x & 0x0F) << 4; 
    
    return v1 | v2; 
}

unsigned char rotate_left(unsigned char x, int n) {
    return (x << n) | (x >> (8 - n));
}

int main() {

    unsigned char valor0 = 0xAB;
    unsigned char valor1 = 0x61; 

    printf("--- Testes da funcao switch_byte ---\n");
    printf(" Inverte bit: 0x%02X\n", switch_byte(valor0));

    printf("--- Testes da funcao rotate_left ---\n");
    printf("Valor original: 0x%02X\n\n", valor1);
    printf("Rotate left de 1 bit:  0x%02X\n", rotate_left(valor1, 1));
    printf("Rotate left de 2 bits: 0x%02X\n", rotate_left(valor1, 2));
    printf("Rotate left de 7 bits: 0x%02X\n", rotate_left(valor1, 7));


    return 0;
}
