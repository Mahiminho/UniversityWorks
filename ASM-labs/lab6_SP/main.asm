.386
.model flat, stdcall
.stack 4096

GetStdHandle proto :dword
wsprintfA PROTO C :dword, :dword, :vararg
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
ReadConsoleA proto :dword, :dword, :dword, :dword, :dword
StrToIntA proto :dword
ExitProcess proto :dword

.data 
A dd 4
X dd -4, -3, -2, -1, 1, 2, 3, 4, 5, 6
N equ ($-X) / type X
SUM dd 0
MessageA db 'Input A:', 13, 10
NumberOfCharsA dd $-MessageA
MessageX db 'Input X:', 13, 10
NumberOfCharsX dd $-MessageX
Message db 'SUM =               ', 13, 10
NumberOfCharsMessage dd $-Message
NumberOfCharsWritten dd 0
format db '%d', 0
hConsoleInput dd 0
hConsoleOutput dd 0
NumberOfChars dd 0
ReadBuf db 32 dup(0)

.code
input proc
    push    ebp
    mov     ebp, esp

    ; Input A
    invoke GetStdHandle, -11
    mov hConsoleOutput, eax
    invoke WriteConsoleA, hConsoleOutput, addr MessageA, NumberOfCharsA, addr NumberOfCharsWritten, 0
    invoke GetStdHandle, -10
    mov hConsoleInput, eax
    invoke ReadConsoleA, hConsoleInput, addr ReadBuf, 32, addr NumberOfChars, 0
    invoke StrToIntA, addr ReadBuf
    mov dword ptr [A], eax

    ; Input X
    invoke GetStdHandle, -11
    mov hConsoleOutput, eax
    invoke WriteConsoleA, hConsoleOutput, addr MessageX, NumberOfCharsX, addr NumberOfChars, 0
    invoke GetStdHandle, -10
    mov hConsoleInput, eax
    mov ecx, dword ptr N
    lea ebx, X
    mov edi, 0
    L_input:
        push ecx
        invoke ReadConsoleA, hConsoleInput, addr ReadBuf, 32, addr NumberOfChars, 0
        invoke StrToIntA, addr ReadBuf
        pop ecx
        mov [ebx][edi], eax
        add edi, 4
    loop L_input

    pop     ebp
    ret     0
input endp

calculate proc
    push    ebp
    mov     ebp, esp

    mov     esi, 0  ;i in esi
    mov     edi, 0  ;sum in edi
    jmp     SHORT BODY
INCREMENT:
    add     esi, 1
BODY:
    cmp     esi, 10
    jge     SHORT FINISH
    mov     ecx, esi
    mov     edx, [X+ecx*4]
    cmp     edx, A
    jge     SHORT INCREMENT
    mov     ecx, esi
    mov     edx, [X+ecx*4]
    cmp     edx, 0
    jge     SHORT INCREMENT
    add     edi, [X+ecx*4]
    jmp     SHORT INCREMENT

FINISH:
    mov     dword ptr [SUM], edi
    pop     ebp
    ret     0
calculate endp

output proc
    push    ebp
    mov     ebp, esp

    ; result in SUM
    invoke wsprintfA, addr Message+6, addr format, SUM

    push -11
    call GetStdHandle
    mov hConsoleOutput, eax
    invoke WriteConsoleA, hConsoleOutput, addr Message, NumberOfCharsMessage, addr NumberOfChars, 0

    pop     ebp
    ret     0
output endp

main:
    call input
    call calculate
    call output
    push 0
    call ExitProcess
end main
