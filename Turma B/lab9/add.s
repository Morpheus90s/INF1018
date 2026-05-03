/*
int add (int a, int b, int c) {
  return a+b+c;
}
*/
.text
.globl add

add:
    pushq %rbp
    movq %rsp, %rbp

    movl %edi, %eax
    mov %esi, %eax
    mov %edx,%eax

leave
ret
