section .data
fmt db "The result is: %d", 10, 0
section .text
extern printf
global main
main:
mov rax, 5
add rax, 5
add rax, 4
mov rdi, fmt
mov rsi, rax
mov rax, 0
call printf
mov rax, 60
mov rdx, 0
syscall