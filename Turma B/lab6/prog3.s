/*
# Código C equivalente:
char nums[] = {10, -21, -30, 45};
int main() {
    int i;
    char *p;
    for (i = 0, p = nums; i != 4; i++, p++)
        printf("%d\n", (int)*p); // Extensão de sinal ocorre aqui
    return 0;
}
*/

.data
nums:  .byte  10, -21, -30, 45    # Array de bytes (char)
Sf:    .string "%d\n"             # String de formato

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)
    /********************************************************/

    movl  $0, %ebx          /* i = 0 (contador) */
    movq  $nums, %r12       /* p = &nums (ponteiro) */

    L1:
     cmpl  $4, %ebx          /* i == 4? */
     je  L2                  /* se sim, encerra o loop */

     /* movsbl: Move with Sign-Extension from Byte to Long.
     Lê 1 byte de (%r12) e preenche os 32 bits de %eax 
     mantendo o sinal (positivo ou negativo).
     */
     movsbl (%r12), %eax     

     /*************************************************************/
     /* este trecho imprime o valor de %eax                       */
     movq    $Sf, %rdi       /* primeiro parametro: "%d\n"      */
     movl    %eax, %esi      /* segundo parametro: o valor lido */
     call  printf            
    /*************************************************************/

    addl  $1, %ebx          /* i++ */
    addq  $1, %r12          /* p++ (incrementa apenas 1 byte!) */
    jmp  L1                 

    L2:  
    /***************************************************************/
    /* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
        movq  $0, %rax          
        movq  -8(%rbp), %rbx
        movq  -16(%rbp), %r12
        leave
        ret      
    /***************************************************************/
}