find_package(Lua)
include_directories(${LUA_INCLUDE_DIR})

add_library(LuaWrapperDef SHARED Memory.c)

target_link_libraries(LuaWrapperDef ClientCore ${LUA_LIBRARIES})

set_target_properties(LuaWrapperDef PROPERTIES OUTPUT_NAME "FMCBLua") # Can this be placed in add_library?

install(TARGETS LuaWrapperDef)

# Should we create some kind of lua archive?