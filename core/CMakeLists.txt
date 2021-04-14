configure_file(Info.h.in Info.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/minparse/include) # A bit messy

# This should probably be improved, the core server could potentially become quite large
add_executable(Core Core.cpp data/Database.cpp registration/PipeServer.cpp registration/Register.cpp)
set_property(TARGET Core PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)