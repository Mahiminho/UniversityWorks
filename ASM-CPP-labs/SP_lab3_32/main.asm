.686
.model flat, STDCALL

GetComputerNameA proto STDCALL, lpBuffer:DWORD, nSize:DWORD
MessageBoxA proto STDCALL, h:DWORD, lpText:DWORD, LPCSTR:DWORD, UINT:DWORD
lstrcatA proto STDCALL, dst:DWORD, src:DWORD
MoveFileA proto STDCALL, from:DWORD, to:DWORD
ExitProcess proto STDCALL, uExitCode:DWORD


.data
    str1 db 'C:\Users\Sager\Desktop\Test1\testasmfile.txt', 0
    str2 db 'C:\Users\Sager\Desktop\Test2\testasmfile.txt', 0
    buflen dd 256
    textmess1 db 'Файл було успішно переміщено з Test1 в Test2', 0
    user_name db 256 dup(0)

.code
Start:

    push offset buflen
    push offset user_name
    call GetComputerNameA

    push offset str2
    push offset str1
    call MoveFileA

    push 40h
    push offset user_name
    push offset textmess1
    push 0
    call MessageBoxA

    push 0
    call ExitProcess

end Start