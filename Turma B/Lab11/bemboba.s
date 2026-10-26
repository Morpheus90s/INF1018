.text
.globl bemboba

bemboba:

    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp          
   
    movl $0, %ecx          
    leaq -16(%rbp), %rdx    

.L_loop:
    cmpl $4, %ecx          
    jge .L_fim_loop         

    movl %edi, (%rdx)      
    addq $4, %rdx           
    incl %ecx              
    jmp .L_loop

.L_fim_loop:
    
    leaq -16(%rbp), %rdi   
    movl $4, %esi           
    call addl               

    leave
    ret
