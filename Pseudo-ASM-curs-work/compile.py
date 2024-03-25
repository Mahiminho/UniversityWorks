import os

os.system('cmd /c "gcc -c asol.c"')
os.system('cmd /c "gcc -o asol asol.o"')

os.system('cmd /c "gcc -c ssol.c"')
os.system('cmd /c "gcc -o ssol ssol.o"')

os.system('cmd /c "asol.exe test.as test.mc"')
os.system('cmd /c "ssol.exe test.mc>result.txt"')