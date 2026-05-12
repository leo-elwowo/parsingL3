section .text
global _start
_start:
	mov rax, [th_level]
	push rax
	;mise sur la pile du nombre '11'
	push 11
	mov rax, [electro_dragon_unlocked]
	push rax
	;mise sur la pile du nombre '1'
	push 1
	mov rax, [electro_dragon_unlocked]
	push rax
	;mise sur la pile du nombre '0'
	push 0
	;mise sur la pile du nombre '11'
	push 11
	pop rax
	mov [th_level], rax
	;mise sur la pile du nombre '1'
	push 1
	pop rax
	mov [electro_dragon_unlocked], rax
	mov rax, [th_level]
	push rax
	;mise sur la pile du nombre '11'
	push 11
	pop rbx
	pop rax
	sub rax, rbx
	push rax
	pop rax
	cmp rax, 0
	je .L1
	;mise sur la pile du nombre '0'
	push 0
	pop rax
	mov [electro_dragon_unlocked], rax
.L1:
mov rax, 60
mov rdi, 0
syscall
section .bss
	th_level: resq 1
	electro_dragon_unlocked: resq 1

