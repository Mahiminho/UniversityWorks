	lw 0 1 x1
	lw 0 2 x2
    lw 0 4 x4
	lw 0 5 x5
    xsub 1 2 3
    sw 0 3 x3
    inc 5 0 0
    sub 4 5 6
    sw 0 6 x6
	halt
x1 .fill 7
x2 .fill 3
x3 .fill 0
x4 .fill 6
x5 .fill 4
x6 .fill 0