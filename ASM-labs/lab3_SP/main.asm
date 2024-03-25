.386
.model flat, stdcall
.stack 4096

GetStdHandle proto :dword
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
wsprintfA PROTO C :dword, :dword, :vararg
ExitProcess proto :dword

.data 
K EQU 18932020h ;412295200
B dd 1DCD6500h ;500000000
Cc dw 1388h ;5000
D db 37h ;55
E db 54h ;84
F dw 1020h ;4128
Message db 'X = K + B/C - D*F -E =              ', 13, 10
NumberOfCharsToWrite dd $-Message
format db '%d', 0
hConsoleOutput dd 0
NumberOfCharsWritten dd 0


.code
main:
;K + B/C - D*F -E

;B/C-->eax
movsx   esi, Cc
mov     eax, B
cdq
idiv    esi

;edx+eax-->edx(K+B/C)
mov     ecx, eax
mov     eax, K
add     ecx,eax 

;D*F-->eax
movsx   edx, D
movsx   eax, F
imul    eax, edx

;ecx-eax-->ecx(K+B/C-D*F)
sub     ecx, eax

;edx-eax-->edx(X)
mov     edx, ecx
movsx   eax, E
sub     edx, eax

push edx
push offset format
push offset [Message+28]
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