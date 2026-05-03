.text
.globl fat

fat:
    # --- Prólogo ---
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp      # Abre espaço na pilha (alinhamento de 16 bytes)

    # --- if (n == 0) ---
    cmpl $0, %edi        # Compara n com 0
    jne  recursao        # Se não for zero, pula para o 'else' (recursão)

    movl $1, %eax        # Se for zero, prepara o retorno 1
    jmp  fim             # Vai para o fim

recursao:
    # --- else { return n * fat(n-1) } ---
    movl %edi, -4(%rbp)  # SALVA o n na pilha antes de chamar a função de novo
    
    decl %edi            # n = n - 1 (prepara o parâmetro para a próxima chamada)
    call fat             # Chama fat(n-1). O resultado volta no %eax

    # Agora recuperamos o 'n' que guardamos para multiplicar
    imull -4(%rbp), %eax # eax = eax * n (ou seja: resultado da chamada * n)

fim:
    # --- Epílogo ---
    leave
    ret
