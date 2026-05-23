section .text
global _start
_start:
	call main
	mov rdi, rax
	mov rax, 60
	syscall

main:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	;mise sur la pile du nombre '10'
	push 10
	;mise sur la pile du nombre '20'
	push 20
	;mise sur la pile du nombre '0'
	push 0
	pop rax
	mov rsp, rbp
	pop rbp
	ret
	mov rsp, rbp
	pop rbp
	ret

section .bss
	p1: resq 1

