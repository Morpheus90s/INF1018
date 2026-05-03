.globl map2
map2:
    # --- Prólogo ---
    pushq %rbp              
    movq %rsp, %rbp         
    
    # Salva registradores
    pushq %rbx              
    pushq %r12              
    pushq %r13              
    pushq %r14              

    movq %rdi, %rbx         
    movq %rsi, %r12         
    movl %edx, %r13d        
    movl $0, %r14d         

loop_map2:
    cmpl %r13d, %r14d       
    jge end_map2            

    movl (%rbx, %r14, 4), %edi # 1º parâmetro de f 
    call f                  # f(*(um + i)) 
    
    movl %eax, (%r12, %r14, 4) # Retorno de f está em %eax 

    incl %r14d              # i++
    jmp loop_map2

end_map2:
    # --- Epílogo ---
    popq %r14              
    popq %r13
    popq %r12
    popq %rbx
    leave                  
    ret