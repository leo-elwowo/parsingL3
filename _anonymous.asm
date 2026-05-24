section .text
global _start
_start:
	call main
	mov rdi, rax
	mov rax, 60
	syscall

; --- fonctions d'E/S built-in ---
putchar:
	push rbp
	mov rbp, rsp
	push rdi
	mov rax, 1
	mov rdi, 1
	mov rsi, rsp
	mov rdx, 1
	syscall
	pop rdi
	mov rsp, rbp
	pop rbp
	ret

getchar:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	xor rax, rax
	mov al, byte [rsp]
	mov rsp, rbp
	pop rbp
	ret

putint:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rax, rdi
	mov rsi, rsp
	add rsi, 30
	mov byte [rsp+31], 10
	xor rcx, rcx
	cmp rax, 0
	jge .putint_pos
	neg rax
.putint_pos:
	mov r10, 10
.putint_loop:
	xor rdx, rdx
	idiv r10
	add rdx, '0'
	mov byte [rsi], dl
	dec rsi
	inc rcx
	cmp rax, 0
	jne .putint_loop
	cmp rdi, 0
	jge .putint_write
	mov byte [rsi], '-'
	dec rsi
	inc rcx
.putint_write:
	inc rsi
	add rcx, 1
	mov rax, 1
	mov rdi, 1
	mov rdx, rcx
	syscall
	mov rsp, rbp
	pop rbp
	ret

getint:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	sub rsp, 8
	xor r12, r12
	xor r13, r13
	xor r14, r14
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	xor r10, r10
	mov r10b, byte [rsp]
	cmp r10, '-'
	je .getint_minus
	cmp r10, '+'
	je .getint_next
	jmp .getint_check_digit
.getint_minus:
	mov r13, 1
	jmp .getint_next
.getint_check_digit:
	cmp r10, '0'
	jl .getint_error
	cmp r10, '9'
	jg .getint_error
	sub r10, '0'
	mov rax, 10
	imul r12, rax
	add r12, r10
	inc r14
.getint_next:
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	xor r10, r10
	mov r10b, byte [rsp]
	cmp r10, 10
	je .getint_done
	cmp r10, '0'
	jl .getint_error
	cmp r10, '9'
	jg .getint_error
	sub r10, '0'
	mov rax, 10
	imul r12, rax
	add r12, r10
	inc r14
	jmp .getint_next
.getint_done:
	cmp r14, 0
	je .getint_error
	mov rax, r12
	cmp r13, 0
	je .getint_ret
	neg rax
.getint_ret:
	add rsp, 8
	pop r14
	pop r13
	pop r12
	pop rbp
	ret
.getint_error:
	mov rax, 60
	mov rdi, 5
	syscall

main:
	push rbp
	mov rbp, rsp
	sub rsp, 8
	mov rax, [p + 0]
	push rax
	pop r10
	pop rax
	add rax, r10
	push rax
	pop rax
	mov [rbp-8], rax
	mov rax, [rbp-8]
	push rax
	pop rax
	mov rsp, rbp
	pop rbp
	ret
	mov rsp, rbp
	pop rbp
	ret

section .bss
	p: resq 1

