/*
#include <stdio.h>
#define LIM 1

int filtro(int x, int lim);

int nums[5] = {3,-5,7,8,-2};

int filtro(int x, int lim) {
  if (x < lim)
    return 0;
  else
    return x;
}

int main() {
  int i;
  int *p = nums;
  for (i = 0; i < 5; i++) {
    printf("%d\n", filtro(*p,LIM));
    p++;
  }
  return 0;
}

*/

  .data
  nums: .int 3, -5, 7, 8, -2
  s1:   .string "%d\n"

  .text
  .globl main
  main:
  /* prologo */
     pushq %rbp
     movq  %rsp, %rbp
     subq  $16, %rsp
     movq  %rbx, -8(%rbp)
     movq  %r12, -16(%rbp)

   loop:
   cmpl $5, %r12d           # Compara i com 5
   jge  fim_loop            # Se i >= 5, pula para o fim do loop

   # Chamada: filtro(*p, LIM)
   movl (%rbx), %edi        # %edi = *p (conteúdo do endereço em rbx)
   movl $1, %esi            # %esi = 1 (nosso LIM definido no C)
   call filtro              # Chama a função. O retorno (int) estará em %eax

   movq $s1, %rdi           # %rdi = endereço da string de formato "%d\n"
   movl %eax, %esi          # %esi = valor que filtro devolveu
   movl $0, %eax            # printf exige %eax = 0 para indicar zero args de ponto flutuante
   call printf

   # Atualização
   addq $4, %rbx            # rbx += 4 (p++. Como int tem 4 bytes, pulamos para o próximo)
   addl $1, %r12d           # r12d += 1 (i++)
   jmp loop                 # Volta para o início do loop

  fim_loop:
    movl $0, %eax            # return 0 (sucesso da main)

  /* finalizacao */
     movq -8(%rbp), %rbx
     movq -16(%rbp), %r12
     leave
     ret
