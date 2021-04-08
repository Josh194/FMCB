cmake_minimum_required(VERSION 3.19)

project(FMCB)

include(CheckIPOSupported)
check_ipo_supported()

# maybe error check to insure version was found
file(READ info.json INFO_JSON)
string(JSON VERSION GET "${INFO_JSON}" version)

message("Server version is ${VERSION}")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "")

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG  "-g")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")

# Is this correct? Either way, it does seem to slow compilation to a slightly annoying degree, is cmake/ninja recompiling files that don't need to be?
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")

# Add any (internal) directories containing a CMakeLists.txt that should be built here
add_subdirectory(core)
add_subdirectory(shared)

add_subdirectory(tests)