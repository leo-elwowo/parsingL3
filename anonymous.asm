global _start
section .text
start:
mov rax, 60
mov rdi, 0
syscall
	push 8
	push 5
    pop rbx
    pop rax
    sub rax, rbx
    push rax
