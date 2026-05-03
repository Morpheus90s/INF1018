.globl boo
boo:
    pushq %rbp
    movq %rsp, %rbp
    pushq %r12              
    pushq %r13              
    pushq %r14              
    subq $8, %rsp           # Alinhamento de 16 bytes

    movq %rdi, %r12
    movl %esi, %r13d
    movl %edx, %r14d

loop_boo:
    testl %r13d, %r13d      # n == 0?
    jz end_boo
    
    movl (%r12), %edi       # px->val1
    movl %r14d, %esi        # val
    call f
    
    movl %eax, 4(%r12)      # px->val2 = f(...)
    addq $8, %r12           # px++ (próxima struct de 8 bytes)
    decl %r13d              # n--
    jmp loop_boo

end_boo:
    addq $8, %rsp
    popq %r14
    popq %r13
    popq %r12
    leave
    ret