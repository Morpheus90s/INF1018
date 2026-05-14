/*
int novonum(void) {
  int minhalocal;
  printf("numero: %d %");
  scanf("%d",&minhalocal);
  return minhalocal;
}
*/
.section .rodata  
st_p: .string "numero: "
st_c:  .string "%d"

.text
.globl novonum

novonum:
 
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp       

    #estrutura do print  sem argumentos
    leaq st_p(%rip), %rdi
    movl  $0, %eax         #pq é inteiro
    call  printf

    leaq  $str_c, %rdi
    leaq  -4(%rbp), %rsi  
    movl  $0, %eax
    call  scanf

    movl  -4(%rbp), %eax  

    leave
    ret
