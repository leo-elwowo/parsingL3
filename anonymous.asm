section .text
global _start
_start:
	;mise sur la pile du nombre '11'
	push 11
	pop rax
	mov [th_level], rax
	;mise sur la pile du nombre '1111'
	push 1111
	pop rax
	mov [a_assez_or], rax
	mov rax, [th_level]
	push rax
	;mise sur la pile du nombre '10'
	push 10
	pop rbx
	pop rax
	cmp rax, rbx
	jmp .L2
.L3:
	mov rax, [a_assez_or]
	push rax
	pop rax
	cmp rax, 0
	jne .L1
	jmp .L2
.L1:
	;mise sur la pile du nombre '1'
	push 1
	pop rax
	mov [peut_ameliorer], rax
	jmp .L4
.L2:
	;mise sur la pile du nombre '0'
	push 0
	pop rax
	mov [peut_ameliorer], rax
.L4:
	mov rax, [peut_ameliorer]
	push rax
	pop rax
	mov rdi, rax
	mov rax, 60
	syscall
mov rax, 60
mov rdi, 0
syscall
section .bss
	th_level: resq 1
	peut_ameliorer: resq 1
	a_assez_or: resq 1

