@echo off

cd bin
call :%1%
cd ../

goto :eof

:debug
ninja -v -f build-Debug.ninja
exit /b 0

:release
ninja -v -f build-Release.ninja
exit /b 0

:relwithdebinfo
ninja -v -f build-RelWithDebInfo.ninja
exit /b 0

:clean
echo Cleaning Debug, Release, and RelWithDebInfo
ninja clean -f build-Debug.ninja
ninja clean -f build-Release.ninja
ninja clean -f build-RelWithDebInfo.ninja
exit /b 0