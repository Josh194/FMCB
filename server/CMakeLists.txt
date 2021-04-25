set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

configure_file(Info.h.in Info.h)

include_directories( # A bit messy
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/server
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_SOURCE_DIR}/minparse/include
)

# This should probably be improved, the core server could potentially become quite large
add_executable(Server
    Server.cpp
    Status.cpp
    data/Database.cpp
    registration/PipeServer.cpp
    registration/Register.cpp
    processing/CScheduler.cpp
    processing/modules/translate/Translate.cpp
)