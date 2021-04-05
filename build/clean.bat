@echo off

cd ../bin
call :%1%
cd ../build

goto :eof

:debug
ninja clean -f build-Debug.ninja
exit /b 0

:release
ninja clean -f build-Release.ninja
exit /b 0

:relwithdebinfo
ninja clean -f build-RelWithDebInfo.ninja
exit /b 0

:all
call :debug
call :release
call :relwithdebinfo
exit /b 0