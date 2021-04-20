#[[FindJNI is buggy as all hell and never finds the correct version.
"1.8 EXACT" might not even do anything , as FindJNI doesn't seem to set any version variable
The alternative is to use FindJava instead, and go backward through the path, but this seems error prone]]
# Note that the original command used -Wl,--add-stdcall-alias, it may be needed
include_directories($ENV{JAVA_HOME}/include $ENV{JAVA_HOME}/include/win32)

add_library(FMCBJava SHARED fmcb_Memory.cpp fmcb_Register.cpp)

target_link_libraries(FMCBJava SharedMemory)