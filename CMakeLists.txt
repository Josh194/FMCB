cmake_minimum_required(VERSION 3.19)

project(FMCB)

include(CheckIPOSupported)
check_ipo_supported()

# maybe error check to insure version was found
file(READ info.json INFO_JSON)
string(JSON VERSION GET "${INFO_JSON}" version)

message("Server version is ${VERSION}")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -mno-ms-bitfields is only needed to make -Wpadded work correctly, this could cause problems down the line. A gnu bugzilla report has been filed under the id: 100058
set(CMAKE_CXX_FLAGS "-std=c++17 -mno-ms-bitfields -fdiagnostics-color=always -fno-rtti")

set(CXX_WARNINGS "-Wall -Wextra -Wdisabled-optimization -Wold-style-cast -Wshadow -Wdouble-promotion -Wundef -Wconversion -Wcast-align=strict -Wpadded")

set(CMAKE_CXX_FLAGS_DEBUG  "-g ${CXX_WARNINGS}")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-g -O3 -DNDEBUG")

# Is this correct? Either way, it does seem to slow compilation to a slightly annoying degree, is cmake/ninja recompiling files that don't need to be?
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")

# Add any (internal) directories containing a CMakeLists.txt that should be built here
add_subdirectory(core)
add_subdirectory(shared)

add_subdirectory(tests)