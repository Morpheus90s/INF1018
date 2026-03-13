#include <stdio.h>

int odd_ones(unsigned int x) {
  int count = 0;
    while (x > 0) {
        // Verifica se o bit menos significativo (o da direita) é 1
        if (x & 1) {
        count++;
        }
        // "Empurra" os bits para a direita para testar o próximo
        x = x >> 1;
    }
    return (count & 1);
}

int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}