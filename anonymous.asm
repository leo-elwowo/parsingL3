global _start
section .text
start:
	push 12
	push 24
	push 24
	push 12
mov rax, 60
mov rdi, 0
syscall
