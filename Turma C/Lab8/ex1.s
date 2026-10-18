.data
s1: .string "ls -ls"

.text
.globl main
main:
/* prologo */
  pushq %rbp
  movq  %rsp, %rbp

/* coloque seu codigo aqui */
  movq $s1, %rdi        
  movl $0, %eax        
  call system           

  movl $0, %eax       

/* finalizacao */
  leave
  ret
