.globl add
add:
    movl $0, %eax         
.loop:
    cmpq $0, %rdi         
    je .Soma          
    addl (%rdi), %eax     
    movq 8(%rdi), %rdi    
    jmp .Soma
.Loop:
    ret
