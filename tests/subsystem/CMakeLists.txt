include_directories(
    ${CMAKE_SOURCE_DIR}/client
    ${CMAKE_SOURCE_DIR}/shared
)

add_executable(Test_Subsystem Run.cpp)

target_link_libraries(Test_Subsystem ClientCore)