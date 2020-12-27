cmake_minimum_required(VERSION 3.19)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "")

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG  "-g")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")

project(FMCB)

# Add any (internal) directories containing a CMakeLists.txt that should be built here
add_subdirectory(shared/memory)

# Add subsystem directories containing a CMakeLists.txt here
# This will need to modularized later
add_subdirectory(Minecraft)