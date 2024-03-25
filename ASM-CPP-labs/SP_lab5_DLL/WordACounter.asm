.686
.model flat, c

MessageBoxA proto STDCALL, h:DWORD, lpText:DWORD, LPCSTR:DWORD, UINT:DWORD
ExitProcess proto STDCALL, uExitCode:DWORD

.data
    caption db "Lab5", 0          ; window name
    ;input db "Максим Максим Авто Антон Анураін Антон Антон Авто Панурір Анураін Пантон ", 0 ; input string
    output db 256 dup(0)           ; Output buffer
    outputSize dd 0               ;size of output
    wordSize dd 0             ; Variable to store the wordSize
.code
DllEntry PROC hInstDLL:DWORD, reason:DWORD, reserved:DWORD
mov eax, 1
ret
DllEntry ENDP

WordACounter PROC input:DWORD
    mov esi, input        ; Load the address of the string into ESI

main_loop:
    lodsb ; Load the next character into AL
    test al, al ; Check if AL is null terminator (end of string)
    jz end_main_loop ; If null terminator, jump to end_main_loop

    cmp al, ' ' ; Check if the character is a space
    je handle_space ; If equal, jump to handle_space

    inc wordSize
    jmp main_loop

handle_space:
    mov ecx, wordSize
    neg ecx
    dec ecx ; if not present skip first symbol 
    mov ah, byte ptr[esi + ecx]
    cmp ah, 'А' ;check first symbol
    jne next_main_loop_iteration
    mov edi, offset output
    jmp check_if_word_exist

check_if_word_exist:
    mov dh, byte ptr[esi + ecx]; word symbol
    mov dl, [edi] ;output symbol
    cmp dl, 0
    je add_word_to_output_before_loop
    cmp dl, dh
    je check_if_full_word_found
    mov ebx, 0 ;same symbols in a row found
    mov ecx, wordSize
    neg ecx
    dec ecx ; if not present skip first symbol 
    inc edi
    jmp check_if_word_exist

check_if_full_word_found:
    inc ebx ;same symbols in a row found
    cmp ebx, wordSize
    je word_found
    inc ecx ;inc to get next word symbol
    inc edi
    jmp check_if_word_exist

word_found: ;increase count value
    mov dh, [edi + 2]
    inc dh
    mov [edi + 2], dh
    jmp next_main_loop_iteration

add_word_to_output_before_loop:
    mov ecx, wordSize
    neg ecx
    dec ecx ; if not present skip first symbol 
    mov ebx, wordSize
    add ebx, outputSize ; inner loop limit
    jmp add_word_to_output_loop

add_word_to_output_loop:
    cmp ebx, outputSize
    je add_new_line
    mov edx, outputSize
    mov ah, byte ptr[esi + ecx]
    mov [output + edx], ah ; Copy the character to output
    inc outputSize ; Increment the destination index
    inc ecx
    jmp add_word_to_output_loop

next_main_loop_iteration:
    mov ebx, 0
    mov wordSize, 0
    jmp main_loop

add_new_line:
    mov edx, outputSize
    mov [output + edx], 32 ; Copy the character to output
    inc edx ; Increment the destination index
    mov [output + edx], 49 ; Copy the character to output
    inc edx ; Increment the destination index
    mov [output + edx], 10 ; Copy the character to output
    inc edx ; Increment the destination index
    mov outputSize, edx
    jmp next_main_loop_iteration

end_main_loop:
    push 40h
    push offset caption
    push offset output
    push 0
    call MessageBoxA

    push 0
    call ExitProcess

ret

WordACounter ENDP
END DllEntry