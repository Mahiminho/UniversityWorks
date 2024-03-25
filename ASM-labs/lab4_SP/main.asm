.386
.model flat, stdcall
.stack 4096

GetStdHandle proto :dword
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
wsprintfA PROTO C :dword, :dword, :vararg
ExitProcess proto :dword

.data 
A db 0
B db 1
MessageSuccess db 'X =                  ', 13, 10
NumberOfCharsToWriteSuccess dd $-MessageSuccess
MessageError db 'ERROR!', 13, 10
NumberOfCharsToWriteError dd $-MessageError
format db '%d', 0
hConsoleOutput dd 0
NumberOfCharsWritten dd 0

.code
main:
; if A != B, goto A_NE_B
    movsx   eax, A
    movsx   ecx, B
    cmp     eax, ecx
    jne     SHORT A_NE_B

; here, A == B
; set result to 3 and goto EXIT_SUCCESS, result in eax
    mov     eax, 3
    jmp     SHORT EXIT_SUCCESS

; here, A != B
; if A <= B, goto A_LE_B
A_NE_B:
    movsx   edx, A
    movsx   eax, B
    cmp     edx, eax
    jle     SHORT A_LE_B

; here, A > B
; if B != 0, goto B_NOT_ZERO
    movsx   ecx, B
    test    ecx, ecx
    jne     SHORT B_NOT_ZERO

; here, A > B and B == 0
    jmp     SHORT EXIT_ERROR

; here, A > B and B != 0
; calculate 6 * A / B - 37 and goto EXIT_SUCCESS, result in eax
B_NOT_ZERO:
    movsx   edx, A
    imul    eax, edx, 6
    movsx   ecx, B
    cdq
    idiv    ecx
    add     eax, -37
    jmp     SHORT EXIT_SUCCESS

; here, A <= B; since A == B was already checked, here A < B
; if A != 0, goto a_NOT_ZERO
A_LE_B:
    movsx   edx, A
    test    edx, edx
    jne     SHORT A_NOT_ZERO

; here, A < B and A == 0
    jmp     SHORT EXIT_ERROR

; here, A < B and A != 0
; calculate (A - B) / A and goto EXIT_SUCCESS, result in eax
A_NOT_ZERO:
    movsx   eax, A
    movsx   ecx, B
    sub     eax, ecx
    movsx   ecx, A
    cdq
    idiv    ecx

EXIT_SUCCESS:
    ; result in eax
    push eax
    push offset format
    push offset [MessageSuccess+4]
    call wsprintfA

    push -11
    call GetStdHandle
    mov hConsoleOutput, eax
    push 0
    push offset NumberOfCharsWritten
    push NumberOfCharsToWriteSuccess
    push offset MessageSuccess
    push hConsoleOutput
    call WriteConsoleA

    jmp     SHORT EXIT

EXIT_ERROR:
    push -11
    call GetStdHandle
    mov hConsoleOutput, eax
    push 0
    push offset NumberOfCharsWritten
    push NumberOfCharsToWriteError
    push offset MessageError
    push hConsoleOutput
    call WriteConsoleA

EXIT:
    push 0
    call ExitProcess
end main
