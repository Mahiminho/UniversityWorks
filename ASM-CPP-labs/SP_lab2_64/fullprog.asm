.data
 const_1 dd 1.0
 const_2 dd 2.0
 const_4 dd 4.0
 const_24 dd 24.0
 const_28 dd 28.0
.code
fullprog PROC

 movsd qword ptr [rsp+8], xmm0
 movss dword ptr [rsp+16], xmm1
 movss dword ptr [rsp+24], xmm2

 push rbp
 mov rbp, rsp

 finit
 fld dword ptr[rsp+24]
 fcom dword ptr[rsp+32]
 fstsw ax
 sahf
 ja _d_L_c
 jmp _c_LE_d

 ; d < c
 _d_L_c:

 ; a
 fld qword ptr[rsp+16]

 ; c / d
 fld dword ptr[rsp+24]
 fdiv dword ptr[rsp+32]

 ; a + c / d
 fadd

 ; sqrt(28 * d)
 fld dword ptr[rsp+32]
 fmul const_28
 fsqrt

 ; a + c / d - sqrt(28 * d)
 fsub

 ; 4 * d * a + 1
 fld dword ptr[rsp+32]
 fmul const_4
 fmul qword ptr[rsp+16]
 fadd const_1

 ;чисельник/знаменник
 fdiv
 jmp _finish
 


; d => c
_c_LE_d:

  ; c / d
  fld dword ptr[rsp+24]
  fdiv dword ptr[rsp+32]

  ; sqrt(24 + d)
  fld dword ptr[rsp+32]
  fadd const_24
  fsqrt

  ; c / d - sqrt(24 + d)
  fsub

  ; c / d - sqrt(24 + d) + a
  fadd qword ptr[rsp+16]

  ; 2 * a * c - 4
  fld dword ptr[rsp+24]
  fmul const_2
  fmul qword ptr[rsp+16]
  fsub const_4

  ;чисельник/знаменник
  fdiv



_finish:
 pop rbp
 fstp qword ptr [rsp+8]
 movsd xmm0, qword ptr [rsp+8]
 ret
fullprog ENDP
END