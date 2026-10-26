.globl add2
add2:
    cmpq $0, %rdi         
    jne .Fora
    movl $0, %eax         
    ret

.Fora:
    pushq %rbx            
    movl (%rdi), %ebx     
    movq 8(%rdi), %rdi    
    call add2             
    addl %ebx, %eax       
    popq %rbx             
    ret
