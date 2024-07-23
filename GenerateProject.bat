@echo off
call premake5 gmake2
cd build
make
cd Debug
Main.exe
