.text
.globl foo3
foo3:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp           

    movq    %rbx, -8(%rbp)     
    movq    %r12, -16(%rbp)     

    movq    %rdi, %rbx          
    movl    %esi, %r12d        

    xorpd   %xmm0, %xmm0        
    movsd   %xmm0, -24(%rbp)   

LOOP:
    cmpl    $0, %r12d          
    jle     FIM                 

    movsd   (%rbx), %xmm0      
    call    sin               

    addsd   -24(%rbp), %xmm0   
    movsd   %xmm0, -24(%rbp)    
   
    addq    $8, %rbx            
    decl    %r12d               
    jmp     LOOP

FIM:
  
    movsd   -24(%rbp), %xmm0

    movq    -8(%rbp), %rbx
    movq    -16(%rbp), %r12

    leave
    ret
