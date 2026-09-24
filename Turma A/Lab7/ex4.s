.data
.globl nums
.align 4
nums:
    .long 65            # int nums[0]
    .long -105          # int nums[1]
    .long 111           # int nums[2]
    .long 34            # int nums[3]

.section .rodata
Sfmt: .string "soma = %d\n"

.text
.globl main

main:
    movl $0, %eax        # int s = 0; (acumulador da soma)
    movq $0, %rcx        # int i = 0; (zerando os 64 bits de rcx)

L1:
    cmpl $4, %ecx        # Compara i com 4
    jge L2               # Se i >= 4, sai do loop (pula para L2)

    # s = s + nums[i];
    # Buscamos o valor na RAM multiplicando o índice %rcx por 4 bytes
    addl nums(, %rcx, 4), %eax  

    incl %ecx            # i++
    jmp L1               # Volta para o início do loop

L2:
    # Preparar e chamar o printf
    movq $Sfmt, %rdi     # 1º argumento: string de formato
    movl %eax, %esi      # 2º argumento: o valor da soma 's'
    movl $0, %eax        # printf sem ponto flutuante
    call printf          # printf("soma = %d\n", s);

    movl $0, %eax        # return 0;
    ret
