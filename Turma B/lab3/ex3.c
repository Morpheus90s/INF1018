#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
    return (x >> 4) | (x << 4);
}

unsigned char rotate_left(unsigned char x, int n) {
    return (x << n) | (x >> (8 - n));
}

int main() {
    unsigned char val = 0xAB;
    printf("Switch 0x%X: 0x%X\n", val, switch_byte(val)); 

    unsigned char r = 0x61; 
    printf("Rotate 0x%X por 1: 0x%X\n", r, rotate_left(r, 1)); 
    printf("Rotate 0x%X por 2: 0x%X\n", r, rotate_left(r, 2)); 
    
    return 0;
}
