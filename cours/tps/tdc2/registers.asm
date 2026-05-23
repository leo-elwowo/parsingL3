; registers.asm
; registres, chevauchements
section .text
global _start
extern show_registers
_start:
	mov rbx, 2
	mov r12, 10
	mov r13, 0
	mov r14, 0
	; après initialisation
	add rbx, r12
	; après addition sur 64 bits
	add bl, 2
	; après addition sur 8 bits
	mov ebx, 256
	; après copie sur 32 bits
    mov rax, 0
	mov al,  bh
	mov r13, rax
	; après copie sur 8 bits
	add bh, 1
	; après addition sur 8 bits
	mov rax, 60
	mov rdi, 0
	syscall
