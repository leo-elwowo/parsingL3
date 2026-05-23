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
	movzx rax, byte [rsp]
	mov rsp, rbp
	pop rbp
	ret

putint:
	push rbp
	mov rbp, rsp
	sub rsp, 32
	mov rax, rdi
	lea rsi, [rsp+30]
	mov byte [rsp+31], 10
	xor rcx, rcx
	test rax, rax
	jns .putint_pos
	neg rax
.putint_pos:
	mov rbx, 10
.putint_loop:
	xor rdx, rdx
	cqo
	idiv rbx
	add dl, '0'
	mov [rsi], dl
	dec rsi
	inc rcx
	test rax, rax
	jnz .putint_loop
	test rdi, rdi
	jns .putint_write
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
	sub rsp, 8
	xor r12, r12
	xor r13, r13
	xor r14, r14
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	movzx rbx, byte [rsp]
	cmp rbx, '-'
	je .getint_minus
	cmp rbx, '+'
	je .getint_plus
	jmp .getint_check_digit
.getint_minus:
	mov r13, 1
	jmp .getint_next
.getint_plus:
	jmp .getint_next
.getint_check_digit:
	cmp rbx, '0'
	jl .getint_error
	cmp rbx, '9'
	jg .getint_error
	sub rbx, '0'
	imul r12, r12, 10
	add r12, rbx
	inc r14
.getint_next:
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	movzx rbx, byte [rsp]
	cmp rbx, 10
	je .getint_done
	cmp rbx, '0'
	jl .getint_error
	cmp rbx, '9'
	jg .getint_error
	sub rbx, '0'
	imul r12, r12, 10
	add r12, rbx
	inc r14
	jmp .getint_next
.getint_done:
	test r14, r14
	jz .getint_error
	mov rax, r12
	test r13, r13
	jz .getint_ret
	neg rax
.getint_ret:
	mov rsp, rbp
	pop rbp
	ret
.getint_error:
	mov rax, 60
	mov rdi, 5
	syscall

main:
	push rbp
	mov rbp, rsp
	;mise sur la pile du nombre '0'
	push 0
	pop rax
	mov rsp, rbp
	pop rbp
	ret
	mov rsp, rbp
	pop rbp
	ret

