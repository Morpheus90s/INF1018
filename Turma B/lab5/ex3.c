#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

struct X1 { char c1; int i; char c2; } y = {0x01, 0xb1b2, 0x11};
struct X2 { long l; char c; } z = {0xa1a2a3a4a5a6a7a8, 0x01};
struct X3 { int i; char c1; char c2; } a = {0xa1a2a3a4, 0x01, 0x01};
struct X4 { struct X2 x; char c; } b = {{0xa1a2a3a4, 0x01}, 0x02}; 
struct X5 { char c1; char c2; char c3; } c = {0x01, 0x01, 0x01};
struct X6 { short s1; int i; char c[3]; short s2; } d = {0xb1b2, 0xa1a2a3a4, {0x01, 0x02, 0x03}, 0xb1b3};

union U1 { int i; char c[5]; } e = {0xa1a2a3a4}; 
union U2 { short s; char c[5]; } f = {0xb1b2};

int main(void) {
    printf("--- X1 ---\n");
    dump(&y, sizeof(y));

    printf("\n--- X2 ---\n");
    dump(&z, sizeof(z));

    printf("\n--- X3 ---\n");
    dump(&a, sizeof(a));

    printf("\n--- X4 ---\n");
    dump(&b, sizeof(b));

    printf("\n--- X5 ---\n");
    dump(&c, sizeof(c));

    printf("\n--- X6 ---\n");
    dump(&d, sizeof(d));

    printf("\n--- U1 ---\n");
    dump(&e, sizeof(e));

    printf("\n--- U2 ---\n");
    dump(&f, sizeof(f));

    return 0;
}
