EXTERN GetStdHandle : PROC
EXTERN WriteFile    : PROC
EXTERN ExitProcess  : PROC

.DATA?
    hFile           QWORD ?
    BytesWritten    DWORD ?

.DATA
    hello byte "Popov", 10, 13
    byte "           __", 10, 13
    byte ".-.__      \ .-.  ___  __", 10, 13
    byte "|_|  '--.-.-(   \/\;;\_\.-._______.-.", 10, 13
    byte "(-)___     \ \ .-\ \;;\(   \       \ \", 10, 13
    byte " Y    '---._\_((Q)) \;;\\ .-\     __(_)", 10, 13
    byte " I           __'-' / .--.((Q))---'    \,", 10, 13
    byte " I     ___.-:    \|  |   \'-'_          \", 10, 13
    byte " A  .-'      \ .-.\   \   \ \ '--.__     '\", 10, 13
    byte " |  |____.----((Q))\   \__|--\_      \     '", 10, 13
    byte "    ( )        '-'  \_  :  \-' '--.___\", 10, 13
    byte "     Y                \  \  \       \(_)", 10, 13
    byte "     I                 \  \  \         \,", 10, 13
    byte "     I                  \  \  \          \", 10, 13
    byte "     A                   \  \  \          '\", 10, 13
    byte "     |                    \  \__|           '", 10, 13
    byte "                           \_:.  \", 10, 13
    byte "                             \ \  \", 10, 13
    byte "                              \ \  \", 10, 13
    byte "                               \_\_|", 10, 13, 10, 13
    byte 10, 10, 179, 32, 179, 32, 179, 32, 10, 192, 196, 193, 196, 217, 10

    helloLen = $-hello

.CODE
main PROC

    sub rsp, 40                 ; Shadow space (4 * 8) & 1 parameter (8 bytes)
    
    and spl, -16                ; Align to 16

    
    mov ecx, -11                ; DWORD         nStdHandle = STD_OUTPUT_HANDLE
    call GetStdHandle           ; Call WinApi
    mov hFile, rax              ; Save returned handle

    
    mov rcx, hFile              ; HANDLE        hFile (here: Stdout)
    lea rdx, hello              ; LPCVOID       lpBuffer
    lea r9, BytesWritten        ; LPDWORD       lpNumberOfBytesWritten
    mov r8d, helloLen     ; DWORD         nNumberOfBytesToWrite
    mov qword ptr [rsp+32], 0   ; LPOVERLAPPED  lpOverlapped = NULL
    call WriteFile              ; Call WinAPI

exit:
    
    xor ecx, ecx                ; Set RCX to null for return value
    call ExitProcess            ; Call WinAPI to exit
main ENDP

end





