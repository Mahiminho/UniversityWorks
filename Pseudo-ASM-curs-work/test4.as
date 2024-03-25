	je 0 0 lb
    lw 0 7 x7
	halt
lb  lw 0 1 x1
	lw 0 2 x2
    bsr 1 3 0
    bsf 2 4 0
    halt    
x1 .fill 2
x2 .fill 4
x7 .fill 7