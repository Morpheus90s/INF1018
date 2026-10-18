/*
#include <stdio.h>

int main(void){
    int i = 1;

    while (i <= 10 ){
       int quadrado = i*i;
       printf("%d\n", quadrado);
       i++;
    }
    return 0;
}

*/

.data

.section .rodata        
Sf: .string "%d\n"       

.text
.globl main

main:
    pushq %rbx        

    movl $1, %ebx      

WHILE:
    cmpl $10, %ebx       
    jg FORA                

    movl %ebx, %eax     
    imull %eax, %eax     

    movq $Sf, %rdi       
    movl %eax, %esi     
    movl $0, %eax        
    call printf          

    incl %ebx            
    jmp WHILE            

FORA:
    movl $0, %eax       
    popq %rbx            
    ret                  
