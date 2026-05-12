section .text
global _start
_start:
	push 2
	push 5
	pop rbx
	pop rax
	imul rax, rbx
	push rax
	pop rax
	mov [glob], rax
mov rax, 60
mov rdi, 0
syscall
section .bss
	glob: resq 1

