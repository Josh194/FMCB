include_directories(${CMAKE_SOURCE_DIR}/minparse/include)

# This should probably be improved, the core server could potentially become quite large
add_executable(Core Core.cpp registration/PipeServer.cpp registration/Register.cpp)
set_property(TARGET Core PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)