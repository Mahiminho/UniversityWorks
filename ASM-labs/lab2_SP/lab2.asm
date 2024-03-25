.386
.model flat, stdcall
.stack 4096

GetStdHandle proto :dword
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
ExitProcess proto :dword

.data 
A dq 104421464212531473610Q, 1122334455667788h, 1234605616436508552
B dd 11223344h
Cc dt 3.14e8
LBL LABEL BYTE
D dt 112233445566778899AAh
E db 11h
F dq 1122334455667788h
K equ 18932020h
HelloMessage db 'Maxim Popov', 13, 10
NumberOfCharsToWrite dd $-HelloMessage
hConsoleOutput dd 0
NumberOfCharsWritten dd 0

.code
main:
push -11
call GetStdHandle
mov hConsoleOutput, eax
push 0
push offset NumberOfCharsWritten
push NumberOfCharsToWrite
push offset HelloMessage
push hConsoleOutput
call WriteConsoleA
push 0
call ExitProcess
end main