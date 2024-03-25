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
msg db "������ ������ ���� ����� ������ ����� ����� ���� ������ ������ ������ ",0

.data?
hLib dd ?
TestFunctionAddr dd ?

.code
start:
invoke LoadLibrary,addr LibName ; ������������ ��������

.if eax == NULL ; ���� ������������ �� �������
invoke MessageBoxA,NULL,addr DllNotFound,addr AppName,MB_OK
.else
mov hLib,eax ; ���������� ��������� ��������
; ���������� ������ �������
invoke GetProcAddress,hLib,addr FunctionName
.if eax == NULL ; ���� �� ������� ����� ������
invoke MessageBoxA,NULL,addr NotFound,addr AppName,MB_OK
.else
push offset msg
mov TestFunctionAddr,eax
call [TestFunctionAddr] ; ������ �������
.endif
invoke FreeLibrary,hLib ; ������������ ��������
.endif
invoke ExitProcess,NULL
end start