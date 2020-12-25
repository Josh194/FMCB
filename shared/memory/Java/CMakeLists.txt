#[[FindJNI is buggy as all hell and never finds the correct version.
"1.8 EXACT" might not even be doing anything, as FindJNI doesn't seem to set any version variable
The alternative is to use FindJava instead, and go backward through the path, but that seems error prone]]
find_package(JNI 1.8 EXACT REQUIRED)
include_directories(${JNI_INCLUDE_DIRS} ../)

add_library(JavaMemory SHARED Memory.cpp)

target_link_libraries(JavaMemory SharedMemory)