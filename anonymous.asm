section .text
global _start
_start:
	mov rax, [i]
	push rax
	;mise sur la pile du nombre '4'
	push 4
	mov rax, [somme]
	push rax
	;mise sur la pile du nombre '0'
	push 0
	mov rax, [somme]
	push rax
	mov rax, [somme]
	push rax
	;mise sur la pile du nombre '10'
	push 10
	pop rbx
	pop rax
	add rax, rbx
	push rax
	mov rax, [i]
	push rax
	mov rax, [i]
	push rax
	;mise sur la pile du nombre '1'
	push 1
	pop rbx
	pop rax
	sub rax, rbx
	push rax
	;mise sur la pile du nombre '4'
	push 4
	pop rax
	mov [i], rax
	;mise sur la pile du nombre '0'
	push 0
	pop rax
	mov [somme], rax
.L1:
	mov rax, [i]
	push rax
	pop rax
	cmp rax, 0
	je .L2
	mov rax, [somme]
	push rax
	;mise sur la pile du nombre '10'
	push 10
	pop rbx
	pop rax
	add rax, rbx
	push rax
	pop rax
	mov [somme], rax
	mov rax, [i]
	push rax
	;mise sur la pile du nombre '1'
	push 1
	pop rbx
	pop rax
	sub rax, rbx
	push rax
	pop rax
	mov [i], rax
	jmp .L1
.L2:
	mov rax, [somme]
	push rax
	pop rax
	mov rdi, rax
	mov rax, 60
	syscall
mov rax, 60
mov rdi, 0
syscall
section .bss
	somme: resq 1
	i: resq 1

