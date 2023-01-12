:again
str>in.txt
C.cpp <in.txt>b.txt
D.cpp <in.txt>c.txt
fc b.txt c.txt
if not errorlevel 1 goto again
pause