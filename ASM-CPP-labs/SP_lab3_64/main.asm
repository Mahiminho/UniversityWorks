GetComputerNameA proto
MessageBoxA proto
lstrcatA proto
MoveFileA proto
ExitProcess proto


.data 
    str1 db 'C:\Users\Sager\Desktop\Test1\testasmfile.txt', 0
    str2 db 'C:\Users\Sager\Desktop\Test2\testasmfile.txt', 0
    buflen dd 256
    textmess1 db 'Файл було успішно переміщено з Test1 в Test2', 0
    user_name db 256 dup(0)

.code 
mainCRTStartup proc
    sub rsp, 28h

    lea rdx, buflen
    lea rcx, user_name
    call GetComputerNameA

    lea rdx, str2
    lea rcx, str1
    call MoveFileA

    mov r9, 40h
    lea r8, user_name
    lea rdx, textmess1
    mov rcx, 0
    call MessageBoxA

    add rsp, 28h
    ret

mainCRTStartup endp 
end 