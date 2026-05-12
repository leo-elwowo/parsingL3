global _start
section .text
_start:
	push 12
	push 24
	push 24
	push 12
mov rax, 60
mov rdi, 0
syscall
section .bss
	somme: resq 1
	reste: resq 1
	letter: resq 1
	difference: resq 1
	punct: resq 1
	quotient: resq 1
	produit: resq 1
	digit: resq 1
	uppercase: resq 1

