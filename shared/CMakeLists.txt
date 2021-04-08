set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_library(SharedMemory OBJECT Global.cpp memory/BufferAccess.cpp register/Register.cpp)

add_subdirectory(wrapper)