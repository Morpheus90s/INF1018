.text
.globl bemboba
bemboba:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp        

    pushq %rbx             
    movl  %edi, %ebx      

    movl  $0, %ecx         # i = 0
    leaq  -16(%rbp), %rdx  # a = &local[0]

L1:
    cmpl  $4, %ecx         
    je    L2               

    movl  %ebx, (%rdx)    
    addq  $4, %rdx         
    addl  $1, %ecx        
    jmp   L1

L2:

    leaq  -16(%rbp), %rdi  
    movl  $4, %esi         
    call  addl             

    popq  %rbx             
    leave
    ret
