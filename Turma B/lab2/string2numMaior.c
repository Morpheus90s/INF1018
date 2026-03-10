#include <stdio.h>
#include <ctype.h>

int string2num(char *s, int base) {
    int a = 0;
    for (; *s; s++) {
        int digito;
        if (isdigit(*s))
            digito = *s - '0';
        else
            digito = tolower(*s) - 'a' + 10;
            
        a = a * base + digito;
    }
    return a;
}

int main (void) {
  printf("%d\n", string2num("1a", 16));
  printf("%d\n", string2num("a09b", 16));
  printf("%d\n", string2num("z09b", 36));
  return 0;
}