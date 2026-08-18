#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  printf("------INT------\n");
  int i = 10000;
  dump(&i, sizeof(i));

  printf("------LONG------\n");
  long o = 10000;
  dump(&o, sizeof(o));

  printf("------SHORT------\n");
  short t = 10000;
  dump(&t, sizeof(t));
  printf("-----------------\n");

  char p[] = "7509";
  dump(p, sizeof(p));
  printf("-----------------\n");
  
  char u[] = "A";
  dump(u, sizeof(u));
  printf("-----------------\n");
  
  char q[] = "\n";
  dump(q, sizeof(q));
  printf("-----------------\n");
  
  char c[] = "$";
  dump(c, sizeof(c));
  return 0;
}
