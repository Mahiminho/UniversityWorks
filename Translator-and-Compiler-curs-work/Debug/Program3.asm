.386
.model flat, stdcall
option casemap :none
include masm32\include\windows.inc
include masm32\include\kernel32.inc
include masm32\include\masm32.inc
include masm32\include\user32.inc
include masm32\include\msvcrt.inc
includelib masm32\lib\kernel32.lib
includelib masm32\lib\masm32.lib
includelib masm32\lib\user32.lib
includelib masm32\lib\msvcrt.lib

.DATA
;===User Data==============
	A_	dw	00h
	A2_	dw	00h
	B_	dw	00h
	X_	dw	00h
	C1_	dw	00h
	C2_	dw	00h

;===Addition Data===========================================
	hConsoleInput	dd	?
	hConsoleOutput	dd	?
	ErrorMessage	db	"Error: division by zero", 0
	InputBuf	db	15 dup (?)
	InMessage	db	"get: ", 0
	OutMessage	db	"put: "," %d",0
	ResMessage	db	20 dup (?)
	NumberOfCharsRead	dd	?
	NumberOfCharsWrite	dd	?
	msg1310	dw	13,10
	buf	dd	0
	lb1	dd	?
	lb2	dd	?

.CODE
start:
invoke AllocConsole
invoke GetStdHandle, STD_INPUT_HANDLE
mov hConsoleInput, EAX
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov hConsoleOutput, EAX
finit
	call Input
	fild buf
	fistp A_
	call Input
	fild buf
	fistp B_
	fild A_
	fild B_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Endif_
	fild A_
	fistp A2_
Next_:
	fild A2_
	fild B_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Endif1_
	fild A2_
	fild A2_
	fmul
	fistp buf
	call Output
	fild A2_
	mov word ptr buf,1
	fild buf
	fadd
	fistp A2_
	jmp Next_
Endif1_:
	mov word ptr buf,0
	fild buf
	fistp X_
	mov word ptr buf,1
	fild buf
	fistp C1_
Next1_:
	fild C1_
	fild A_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Endif2_
	mov word ptr buf,1
	fild buf
	fistp C2_
Next2_:
	fild C2_
	fild B_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Endif3_
	fild X_
	mov word ptr buf,1
	fild buf
	fadd
	fistp X_
	fild C2_
	mov word ptr buf,1
	fild buf
	fadd
	fistp C2_
	jmp Next2_
Endif3_:
	fild C1_
	mov word ptr buf,1
	fild buf
	fadd
	fistp C1_
	jmp Next1_
Endif2_:
	fild X_
	fistp buf
	call Output
Endif_:
exit_label:
invoke WriteConsoleA,hConsoleOutput,ADDR msg1310,SIZEOF msg1310,ADDR NumberOfCharsWrite,0
invoke ReadConsoleA,hConsoleInput,ADDR InputBuf,1,ADDR NumberOfCharsRead,0
invoke ExitProcess, 0

;===Procedure Input==========================================================================
Input PROC
invoke WriteConsoleA,hConsoleOutput,ADDR msg1310,SIZEOF msg1310,ADDR NumberOfCharsWrite,0
invoke WriteConsoleA,hConsoleOutput,ADDR InMessage,SIZEOF InMessage,ADDR NumberOfCharsWrite,0
invoke ReadConsoleA,hConsoleInput,ADDR InputBuf,11,ADDR NumberOfCharsRead,0
invoke  crt_atoi, addr InputBuf
mov dword ptr buf, eax
ret
Input ENDP
;============================================================================================


;===Procedure Output=========================================================================
Output PROC
invoke WriteConsoleA,hConsoleOutput,ADDR msg1310,SIZEOF msg1310,ADDR NumberOfCharsWrite,0
invoke wsprintf, addr ResMessage, addr OutMessage, dword ptr buf
invoke WriteConsoleA,hConsoleOutput,ADDR ResMessage,eax,ADDR NumberOfCharsWrite,0
ret
Output ENDP
;============================================================================================


;===Procedure Mod=========================
Mod_ PROC

	fistp lb1
	fistp lb2
	fild lb1
	fild lb2
	fprem
	fistp lb1
	fistp lb2
	fild lb1
	ret
Mod_ ENDP
;=========================================


;===Procedure And=========================
And_ PROC
	push eax
	push edx
	pushf
	fistp lb1
	fistp lb2
	mov eax,lb1
	cmp eax,0
	jnz and_t1
	jz and_false
and_t1:
	mov eax,lb2
	cmp eax,0
	jnz and_true
and_false:
	fldz
	jmp and_fin
and_true:
	fld1
and_fin:

	popf
	pop edx
	pop eax

	ret
And_ ENDP
;=========================================


;===Procedure Or==========================
Or_ PROC
	push eax
	push edx
	pushf
	fistp lb1
	fistp lb2
	mov eax,lb1
	cmp eax,0
	jnz or_true
	mov eax,lb2
	cmp eax,0
	jnz or_true
	fldz
	jmp or_fin
or_true:
	fld1
or_fin:

	popf
	pop edx
	pop eax

	ret
Or_ ENDP
;=========================================


;===Procedure Not=========================
Not_ PROC
	push eax
	pushf
	fistp lb1
	mov eax,lb1
	cmp eax,0
	jne not_false
	fld1
	jmp not_fin
not_false:
	fldz
not_fin:

	popf
	pop eax

	ret
Not_ ENDP
;=========================================


;===Procedure Eq==========================
Eq_ PROC
	push eax
	push edx
	pushf
	fistp lb1
	fistp lb2
	mov eax,lb1
	mov edx,lb2
	cmp eax,edx
	jne not_eq
	fld1
	jmp eq_fin
not_eq:
	fldz
eq_fin:
	popf
	pop edx
	pop eax

	ret
Eq_ ENDP
;=========================================


;===Procedure Greate======================
Greate_ PROC
	push eax
	push edx
	pushf
	fistp lb1
	fistp lb2
	mov eax,lb1
	mov edx,lb2
	cmp edx,eax
	jle lov
	fld1
	jmp gr_fin
lov:
	fldz
gr_fin:
	popf
	pop edx
	pop eax

	ret
Greate_ ENDP
;=========================================


;===Procedure Less========================
Less_ PROC
	push eax
	push edx
	pushf
	fistp lb1
	fistp lb2
	mov eax, lb1
	mov edx, lb2
	cmp edx,eax
	jge gr
lo:
	fld1
	jmp less_fin
gr:
	fldz
less_fin:
	popf
	pop edx
	pop eax

	ret
Less_ ENDP
;=========================================


;===Procedure Check=======================
Check_ PROC
	push eax
	fldz
	fcomp
	fstsw ax
	sahf
	jne end_check
invoke WriteConsoleA,hConsoleOutput,ADDR msg1310,SIZEOF msg1310,ADDR NumberOfCharsWrite,0
	invoke WriteConsoleA, hConsoleOutput, ADDR ErrorMessage, SIZEOF ErrorMessage, ADDR NumberOfCharsWrite, 0
	jmp exit_label
end_check:
	pop eax
	ret
Check_ ENDP
;=========================================

end start
