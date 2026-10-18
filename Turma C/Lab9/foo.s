.text
.globl foo
foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rbx, -8(%rbp)   # Guarda %rbx na pilha (i)
    movq %r12, -16(%rbp)  # Guarda %r12 na pilha (s)

    movq %rdi, %r11       # %r11 = endereço base do array 'a'
    movl %esi, %r10d      # %r10d = 'n'
    movl $0, %ebx         # i = 0
    movl $0, %r12d        # s = 0

.L_loop:
    cmpl %r10d, %ebx      # if (i >= n) sai do loop
    jge .L_fim

    # Calcula endereço de a[i]: base + i * 4
    movslq %ebx, %rcx     # Converte 'i' para 64 bits
    movl (%r11,%rcx,4), %eax # %eax = a[i]

    addl %eax, %r12d      # s += a[i]

    cmpl $0, %eax         # if (a[i] == 0)
    jne .L_proximo
    movl %r12d, (%r11,%rcx,4) # a[i] = s
    movl $0, %r12d        # s = 0

.L_proximo:
    incl %ebx             # i++
    jmp .L_loop

.L_fim:
    movq -8(%rbp), %rbx   # Restaura registradores
    movq -16(%rbp), %r12
    leave
    ret
