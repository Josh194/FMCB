set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_library(SharedMemory OBJECT memory/BufferAccess.cpp)

add_subdirectory(wrapper)