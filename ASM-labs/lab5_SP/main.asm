.386
.model flat, stdcall
.stack 4096

GetStdHandle proto :dword
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
wsprintfA PROTO C :dword, :dword, :vararg
ExitProcess proto :dword

.data 
X dd -4, -3, -2, -1, 1, 2, 3, 4, 5, 6
A dd 4
Message db 'SUM =               ', 13, 10
NumberOfCharsToWrite dd $-Message
format db '%d', 0
hConsoleOutput dd 0
NumberOfCharsWritten dd 0

.code
main:
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
        ; result in edi
        push edi
        push offset format
        push offset [Message+6]
        call wsprintfA

        push -11
        call GetStdHandle
        mov hConsoleOutput, eax
        push 0
        push offset NumberOfCharsWritten
        push NumberOfCharsToWrite
        push offset Message
        push hConsoleOutput
        call WriteConsoleA
        push 0
        call ExitProcess
end main
