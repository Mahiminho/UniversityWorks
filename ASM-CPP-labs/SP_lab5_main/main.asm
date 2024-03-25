.686
.model flat, stdcall
option casemap:none

include windows.inc
include kernel32.inc
include user32.inc

.data
LibName db "lab5_SP_DLL.dll",0
FunctionName db "WordACounter",0
DllNotFound db "Cannot load library",0
AppName db "Load explisit Library",0
NotFound db "WordACounter function not found",0
msg db "Максим Максим Авто Антон Анураін Антон Антон Авто Панурір Анураін Пантон ",0

.data?
hLib dd ?
TestFunctionAddr dd ?

.code
start:
invoke LoadLibrary,addr LibName ; завантаження бібліотеки

.if eax == NULL ; якщо завантаження не вдалося
invoke MessageBoxA,NULL,addr DllNotFound,addr AppName,MB_OK
.else
mov hLib,eax ; збереження заголовку бібліотеки
; визначення адреси функції
invoke GetProcAddress,hLib,addr FunctionName
.if eax == NULL ; якщо не вдалося взяти адресу
invoke MessageBoxA,NULL,addr NotFound,addr AppName,MB_OK
.else
push offset msg
mov TestFunctionAddr,eax
call [TestFunctionAddr] ; виклик функції
.endif
invoke FreeLibrary,hLib ; вивантаження бібліотеки
.endif
invoke ExitProcess,NULL
end start