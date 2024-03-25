.686
.model flat, c
.data
 const_1 dd 1.0
 const_2 dd 2.0
 const_4 dd 4.0
 const_24 dd 24.0
 const_28 dd 28.0
.code
fullprog PROC
 push ebp
 mov ebp, esp

 finit
 fld dword ptr[ebp+16]
 fcom dword ptr[ebp+20]
 fstsw ax
 sahf
 ja _d_L_c
 jmp _c_LE_d

 ; d < c
 _d_L_c:

 ; a
 fld qword ptr[ebp+8]

 ; c / d
 fld dword ptr[ebp+16]
 fdiv dword ptr[ebp+20]

 ; a + c / d
 fadd

 ; sqrt(28 * d)
 fld dword ptr[ebp+20]
 fmul const_28
 fsqrt

 ; a + c / d - sqrt(28 * d)
 fsub

 ; 4 * d * a + 1
 fld dword ptr[ebp+20]
 fmul const_4
 fmul qword ptr[ebp+8]
 fadd const_1

 ;чисельник/знаменник
 fdiv
 jmp _finish
 


; d => c
_c_LE_d:

  ; c / d
  fld dword ptr[ebp+16]
  fdiv dword ptr[ebp+20]

  ; sqrt(24 + d)
  fld dword ptr[ebp+20]
  fadd const_24
  fsqrt

  ; c / d - sqrt(24 + d)
  fsub

  ; c / d - sqrt(24 + d) + a
  fadd qword ptr[ebp+8]

  ; 2 * a * c - 4
  fld dword ptr[ebp+16]
  fmul const_2
  fmul qword ptr[ebp+8]
  fsub const_4

  ;чисельник/знаменник
  fdiv



_finish:
 pop ebp
 ret
fullprog ENDP
END