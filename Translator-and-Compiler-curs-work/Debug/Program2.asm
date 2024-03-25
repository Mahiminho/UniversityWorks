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
	B_	dw	00h
	C_	dw	00h

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
	call Input
	fild buf
	fistp C_
	fild A_
	fild B_
	call Less_
	fistp buf
	cmp word ptr buf, 1
	je Else1_
	fild A_
	fild C_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Else2_
	fild C_
	fistp buf
	call Output
	jmp Endif2_
Else2_:
	fild A_
	fistp buf
	call Output
Endif2_:
	jmp Endif1_
Else1_:
	fild B_
	fild C_
	call Greate_
	fistp buf
	cmp word ptr buf, 1
	je Else3_
	fild C_
	fistp buf
	call Output
	jmp Endif3_
Else3_:
	fild B_
	fistp buf
	call Output
Endif3_:
Endif1_:
	fild A_
	fild B_
	call Eq_
	fild A_
	fild C_
	call Eq_
	call And_
	fild B_
	fild C_
	call Eq_
	call And_
	fistp buf
	cmp word ptr buf, 1
	je Else4_
	mov word ptr buf,0
	fild buf
	fistp buf
	call Output
	jmp Endif4_
Else4_:
	mov word ptr buf,1
	fild buf
	fistp buf
	call Output
Endif4_:
	fild A_
	mov word ptr buf,0
	fild buf
	call Less_
	fild B_
	mov word ptr buf,0
	fild buf
	call Less_
	call Or_
	fild C_
	mov word ptr buf,0
	fild buf
	call Less_
	call Or_
	fistp buf
	cmp word ptr buf, 1
	je Else5_
	mov word ptr buf,0
	fild buf
	fistp buf
	call Output
	jmp Endif5_
Else5_:
	mov word ptr buf,1
	fild buf
	FLDZ
	FSUBR
	fistp buf
	call Output
Endif5_:
	fild A_
	fild B_
	fild C_
	fadd
	call Less_
	call Not_
	fistp buf
	cmp word ptr buf, 1
	je Else6_
	mov word ptr buf,0
	fild buf
	fistp buf
	call Output
	jmp Endif6_
Else6_:
	mov word ptr buf,10
	fild buf
	fistp buf
	call Output
Endif6_:
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
