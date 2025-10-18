default rel
extern ExitProcess
extern GetStdHandle
extern WriteConsoleA
extern Sleep
extern GetFileAttributesA
section .data
msg_0: db "Start",0Dh,0Ah,0
msg_1: db "Equal",0Dh,0Ah,0
msg_2: db "Not equal",0Dh,0Ah,0
msg_3: db "For Loop",0Dh,0Ah,0
msg_4: db "While Loop",0Dh,0Ah,0
section .bss
section .text
fn_main:
    push rbp
    mov rbp,rsp
    sub rsp,48
    mov rax,2
    mov [rbp-8],rax
    mov rax,4
    mov [rbp-16],rax
    mov rcx,-11
    call GetStdHandle
    mov rcx,rax
    lea rdx,[rel msg_0]
    mov r8d,7
    xor r9d,r9d
    sub rsp,40
    call WriteConsoleA
    add rsp,40
    mov rax,[rbp-8]
    cmp rax,[rbp-16]
    jne L_else_0
    mov rcx,-11
    call GetStdHandle
    mov rcx,rax
    lea rdx,[rel msg_1]
    mov r8d,7
    xor r9d,r9d
    sub rsp,40
    call WriteConsoleA
    add rsp,40
    jmp L_endif_0
L_else_0:
    mov rcx,-11
    call GetStdHandle
    mov rcx,rax
    lea rdx,[rel msg_2]
    mov r8d,11
    xor r9d,r9d
    sub rsp,40
    call WriteConsoleA
    add rsp,40
L_endif_0:
    mov rax,0
    mov [rbp-24],rax
L_for_cond_0:
    mov rax,[rbp-24]
    cmp rax,3
    jge L_for_end_0
    mov rcx,-11
    call GetStdHandle
    mov rcx,rax
    lea rdx,[rel msg_3]
    mov r8d,10
    xor r9d,r9d
    sub rsp,40
    call WriteConsoleA
    add rsp,40
    mov rax,[rbp-24]
    add rax,1
    mov [rbp-24],rax
    jmp L_for_cond_0
L_for_end_0:
    mov rax,0
    mov [rbp-32],rax
L_while_cond_0:
    mov rax,[rbp-32]
    cmp rax,[rbp-16]
    jge L_while_end_0
    mov rcx,-11
    call GetStdHandle
    mov rcx,rax
    lea rdx,[rel msg_4]
    mov r8d,12
    xor r9d,r9d
    sub rsp,40
    call WriteConsoleA
    add rsp,40
    mov rax,0
    add rsp,48
    pop rbp
    ret
    jmp L_while_cond_0
L_while_end_0:
    add rsp,48
    pop rbp
    ret
global main
main:
    push rbp
    mov rbp,rsp
    call fn_main
    mov ecx,0
    call ExitProcess
