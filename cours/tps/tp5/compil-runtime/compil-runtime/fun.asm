; default code;
; use make and edit fun.asm

section .text
global my_getchar
global my_putchar
global my_getint
global my_putint

my_getchar:
my_putchar:
    push rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    pop rdi
    ret
my_getint:
my_putint:
    ret