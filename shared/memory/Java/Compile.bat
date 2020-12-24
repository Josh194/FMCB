set FLAGS=-std=c++17 -O3
g++ %FLAGS% -c -I"C:\Program Files\Java\jdk1.8.0_231\include" -I"C:\Program Files\Java\jdk1.8.0_231\include\win32" -I"D:\Eclipse\FMCB\FMCB\Shared" MemoryUtils.cpp -o MemoryUtils.o
g++ %FLAGS% -shared MemoryUtils.o -o memAssist.dll -Wl,--add-stdcall-alias
pause