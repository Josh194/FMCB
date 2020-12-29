@echo off

set group=%2%

call :%1%

goto :eof

:debug
call clean debug
echo Done
call build debug %group%
exit /b 0

:release
call clean release
echo Done
call build release %group%
exit /b 0

:relwithdebinfo
call clean relwithdebinfo
echo Done
call build relwithdebinfo %group%
exit /b 0