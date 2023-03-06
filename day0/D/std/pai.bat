:loop
gen.exe
std.exe
bf.exe
fc apple.ans apple.out
if %errorlevel% == 0 goto loop
pause