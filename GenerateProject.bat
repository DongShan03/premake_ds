@echo off
call premake5 gmake2
cd build
make config=release_win64
cd Debug
Main.exe
