/*
#include <stdio.h>

int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}
*/
.data
    Sf: .string "%d\n"

.text
.globl main
.extern printf

main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)

    movq    $1, %r12          # i = 1

L1:
    cmpq    $11, %r12         # if i >= 11, exit loop
    je      L2

    movq    %r12, %rax        # eax = i
    imulq   %rax, %rax        # eax = i * i

    movq    $Sf, %rdi         # format string
    movq    %rax, %rsi        # quadrado como argumento
    movl    $0, %eax
    call    printf            # chama printf

    addq    $1, %r12          # i++
    jmp     L1                # volta ao loop

L2:
    movq    $0, %rax
    movq    -16(%rbp), %r12
    movq    -8(%rbp), %rbx
    leave
    ret   