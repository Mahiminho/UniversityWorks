printf proto c : vararg
EXTERN K : QWORD
.data
msg db 'Output from asm module is: %d', 0
.code
calc PROC
sub rsp, 20h
xor eax, eax

;Запис А в регістр і ділення його на 4
mov rax, rcx
sar rax, 2

;Додавання С до А
add rax, rdx

;Множення D на 2 та віднімання від результату
sal r8, 1
sub rax, r8

;Додавання К до результату
add rax, K

mov r12, rax
lea rcx, msg
mov rdx, rax
call printf
mov rax, r12
add rsp, 20h
ret
calc ENDP
END
