.text
.globl fat
fat:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp     

    cmpl $0, %edi       
    jne .L_recursao
    movl $1, %eax       
    jmp .L_fim

.L_recursao:
    movl %edi, -4(%rbp) 
    decl %edi           
    call fat           
    imull -4(%rbp), %eax 

.L_fim:
    leave
    ret
