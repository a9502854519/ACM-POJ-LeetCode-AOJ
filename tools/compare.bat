@echo off
set var= 0
:again
set /a var+=1
1912.exe <./dwarfs/dwarfs/dwarfs.in%var% >output.txt
fc output.txt ./dwarfs/dwarfs/dwarfs.out%var%
if a==10 goto finish
if not errorlevel 1 goto again
pause
:finish