#include <ctype.h>
#include <stdio.h>

int string2num (char *s, int n) {
  int a = 0;

  for (; *s; s++){
    int digito;

    if (isdigit((unsigned char)*s)){
       digito = *s - '0'; 
    }

    else{
        char letra = tolower((unsigned char)*s);

        digito = letra -'a'+ 10;
    }
    a = a*n + digito;
  }
  return a;
}

int main (void) {
  printf("%d\n", string2num("1a", 16));
  printf("%d\n", string2num("a09b", 16));
  printf("%d\n", string2num("z09b", 36));
  return 0;
}