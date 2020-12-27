@echo off

if "%2%" == "core" (
	set targets=core/all shared/memory/all
) else (
	set targets=
)

cd ../bin
call :%1%
cd ../build

goto :eof

:debug
ninja -v -f build-Debug.ninja %targets%
exit /b 0

:release
ninja -v -f build-Release.ninja %targets%
exit /b 0

:relwithdebinfo
ninja -v -f build-RelWithDebInfo.ninja %targets%
exit /b 0