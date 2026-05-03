.globl add
add:
    movl $0, %eax           # int a = 0
loop_add:
    cmpq $0, %rdi           # x == NULL?
    je end_add
    addl (%rdi), %eax       # a += x->val
    movq 8(%rdi), %rdi      # x = x->next 
    jmp loop_add
end_add:
    ret