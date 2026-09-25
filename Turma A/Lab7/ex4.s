.data
.globl nums
.align 4
nums:
    .long 65            
    .long -105          
    .long 111           
    .long 34           

.section .rodata
Sfmt: .string "soma = %d\n"

.text
.globl main

main:
    movl $0, %eax        
    movq $0, %rcx        

L1:
    cmpl $4, %ecx        
    jge L2               

    addl nums(, %rcx, 4), %eax  

    incl %ecx            
    jmp L1              

L2:
    movq $Sfmt, %rdi     
    movl %eax, %esi      
    movl $0, %eax       
    call printf          

    movl $0, %eax        
    ret
