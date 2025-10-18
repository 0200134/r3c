bits 64
default rel
section .text
global main
extern puts
extern ExitProcess

main:
    sub rsp, 40
    lea rcx, [rel msg]
    call puts
    xor rcx, rcx
    call ExitProcess

section .data
msg db 'R3 bootstrap success! (MinGW path)', 0
