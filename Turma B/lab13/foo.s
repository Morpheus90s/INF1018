/*
    .text
    .globl foo

    foo:
        pushq %rbp              # Salva a base do Registro de Ativação anterior 
        movq %rsp, %rbp         # Estabelece a nova base do nosso RA
        
        # O argumento 'x' chega pelo primeiro registrador de inteiros: %edi
        movl %edi, %eax         # Copia o valor de x para %eax (onde guardamos o retorno)
        incl %eax               # Incrementa %eax em 1 (x + 1)
        
        popq %rbp               # Restaura a base do RA do chamador 
        ret                     # Retorna o controle
*/

.text
.globl foo

foo:
    pushq %rbp 
    movq %rsp, %rbp 
    
    # O x chega em %edi. Deixamos ele lá porque add(x) também espera receber o argumento em %rdi!
    call add                # Chama a função add 
    
    popq %rbp 
    ret 