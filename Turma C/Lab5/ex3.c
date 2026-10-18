#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
  printf("\n");
}

struct X1 { char c1; int i; char c2; };
struct X2 { long l; char c; };
struct X3 { int i; char c1; char c2; };
struct X4 { struct X2 x; char c; };
struct X5 { char c1; char c2; char c3; };
struct X6 { short s1; int i; char c[3]; short s2; };
union U1 { int i; char c[5]; };
union U2 { short s; char c[5]; };

int main (void) {
  struct X1 x1 = { 0xaa, 0x11121314, 0xbb };
  struct X2 x2 = { 0x1112131415161718, 0xcc };
  struct X3 x3 = { 0x21222324, 0xdd, 0xee };
  struct X4 x4 = { { 0x3132333435363738, 0xfa }, 0xfb };
  struct X5 x5 = { 0x51, 0x52, 0x53 };
  struct X6 x6 = { 0x6162, 0x71727374, {0x81, 0x82, 0x83}, 0x9192 };

  union U1 u1 = { .c = {0xa1, 0xa2, 0xa3, 0xa4, 0xa5} };
  union U2 u2 = { .c = {0xb1, 0xb2, 0xb3, 0xb4, 0xb5} };

  printf("=== Struct X1 (Size: %zu) ===\n", sizeof(x1));
  dump(&x1, sizeof(x1));

  printf("=== Struct X2 (Size: %zu) ===\n", sizeof(x2));
  dump(&x2, sizeof(x2));

  printf("=== Struct X3 (Size: %zu) ===\n", sizeof(x3));
  dump(&x3, sizeof(x3));

  printf("=== Struct X4 (Size: %zu) ===\n", sizeof(x4));
  dump(&x4, sizeof(x4));

  printf("=== Struct X5 (Size: %zu) ===\n", sizeof(x5));
  dump(&x5, sizeof(x5));

  printf("=== Struct X6 (Size: %zu) ===\n", sizeof(x6));
  dump(&x6, sizeof(x6));

  printf("=== Union U1 (Size: %zu) ===\n", sizeof(u1));
  dump(&u1, sizeof(u1));

  printf("=== Union U2 (Size: %zu) ===\n", sizeof(u2));
  dump(&u2, sizeof(u2));

  return 0;
}
