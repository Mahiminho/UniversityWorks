; �������������������������������������������������������������������������

    .486                      ; force 32 bit code
    .model flat, stdcall      ; memory model & calling convention
    option casemap :none      ; case sensitive

    PUBLIC decade

  .data
    align 16
    decade \
      dd 0,1,2,3,4,5,6,7,8,9
      dd 0,10,20,30,40,50,60,70,80,90
      dd 0,100,200,300,400,500,600,700,800,900
      dd 0,1000,2000,3000,4000,5000,6000,7000,8000,9000
      dd 0,10000,20000,30000,40000,50000,60000,70000,80000,90000
      dd 0,100000,200000,300000,400000,500000,600000,700000,800000,900000
      dd 0,1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000
      dd 0,10000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000
      dd 0,100000000,200000000,300000000,400000000,500000000,600000000,700000000,800000000,900000000
      dd 0,1000000000,2000000000,3000000000,4000000000,0,0,0,0,0

    end

; �������������������������������������������������������������������������