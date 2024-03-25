	lw 0 1 x1
	lw 0 2 x2
    jmae 1 2 l1
    halt
l1  lw 0 3 x3
    jmna 2 1 l2
    halt
l2  lw 0 4 x4 
	halt
x1 .fill 7
x2 .fill 3
x3 .fill 2
x4 .fill 1