:loop
mkdt.exe
std.exe < data.in > std.out
i.exe < data.in > I.out
fc log.txt log2.txt
if %errorlevel% == 0 goto loop
pause
