set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories( # A bit messy
    ${CMAKE_SOURCE_DIR}/client
    ${CMAKE_SOURCE_DIR}/shared
)

add_library(ClientCore OBJECT
    Global.cpp
    memory/BufferAccess.cpp
    register/Register.cpp
)

add_subdirectory(wrapper)