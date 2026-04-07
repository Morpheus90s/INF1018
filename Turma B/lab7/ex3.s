.data
    Sf: .string "%d\n"

.text
.globl main
.extern printf

main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    %rbx, -8(%rbp)
    movq    %r12, -16(%rbp)

    movq    $1, %r12          # Inicializa contador em 1

loop:
    cmpq    $11, %r12         # Compara com 11
    je      end               # Sai se for 11

    movq    %r12, %rax        # Copia o valor atual
    imulq   %rax, %rax        # Calcula o quadrado (rax = rax * rax)

    movq    $Sf, %rdi         # String de formatação
    movq    %rax, %rsi        # Valor a imprimir
    movl    $0, %eax
    call    printf            # Chama printf

    addq    $1, %r12          # Incrementa contador
    jmp     loop              # Repete

end:
    movq    $0, %rax
    movq    -16(%rbp), %r12
    movq    -8(%rbp), %rbx
    leave
    ret   