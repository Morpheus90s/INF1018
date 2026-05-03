.globl add2
add2:
    pushq %rbp              
    movq %rsp, %rbp         
    
    cmpq $0, %rdi           # if (x == NULL)
    jne recurse
    movl $0, %eax           
    jmp end_add2

recurse:
    pushq %rbx              
    subq $8, %rsp           
    
    movl (%rdi), %ebx       # x->val em %ebx
    movq 8(%rdi), %rdi      #  x->next
    call add2               # add2(x->next)
    
    addl %ebx, %eax         
    
    addq $8, %rsp           
    popq %rbx               

end_add2:
    leave                   
    ret