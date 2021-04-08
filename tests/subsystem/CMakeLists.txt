include_directories(${CMAKE_SOURCE_DIR}/shared/memory ${CMAKE_SOURCE_DIR}/shared/register)

add_executable(Test_Subsystem Run.cpp)

target_link_libraries(Test_Subsystem SharedMemory)