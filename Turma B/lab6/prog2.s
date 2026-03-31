.data
nums:  .int  10, -21, -30, 45
Sf:    .string "%d\n"

.text
.globl  main
main:
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $32, %rsp          /* Espaço para salvar registradores */
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
  movq    %r13, -24(%rbp)    /* Salvando r13 que usaremos para 'sum' */

  movl  $0, %ebx            /* i = 0 */
  movq  $nums, %r12         /* p = &nums */
  movl  $0, %r13d           /* sum = 0 */

  L1:
    cmpl  $4, %ebx
    je  L_PRINT               /* Se i == 4, vai para a impressão final */

    addl  (%r12), %r13d       /* sum += *p */

    addl  $1, %ebx            /* i++ */
    addq  $4, %r12            /* p++ */
  jmp  L1

  L_PRINT:
   movq    $Sf, %rdi
   movl    %r13d, %esi       /* Passa 'sum' para o printf */
   call    printf

  L2:  
    movq  $0, %rax
    movq  -8(%rbp), %rbx
    movq  -16(%rbp), %r12
    movq  -24(%rbp), %r13     /* Restaura r13 */
  leave
  ret