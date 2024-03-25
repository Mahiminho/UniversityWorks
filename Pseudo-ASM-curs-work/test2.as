	lw 0 1 x1
	lw 0 2 x2
    and 1 2 3
    sw 0 3 x3
    xor 1 2 4
    sw 0 4 x4
    cmpg 1 2 5
    sw 0 5 x5
	halt
x1 .fill 7
x2 .fill 3
x3 .fill 0
x4 .fill 0
x5 .fill 0