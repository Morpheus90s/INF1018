.data
str_printf: .string "numero: "
str_scanf:  .string "%d"

.text
.globl novonum

novonum:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp          
                            
    movq $str_printf, %rdi  
    movl $0, %eax           
    call printf

    movq $str_scanf, %rdi   
    leaq -4(%rbp), %rsi     
    movl $0, %eax
    call scanf

    movl -4(%rbp), %eax    

    leave                   
    ret
