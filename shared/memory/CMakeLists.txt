set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_library(SharedMemory OBJECT BufferAccess.cpp)

# Add language library directories here
add_subdirectory(Java)