#include "Memory.h"
#include "lauxlib.h"

static int iCube(lua_State *L) {
    int x = luaL_checknumber(L, 1);

    lua_pushnumber(L, x * x * x);

    return 1; // Number of return values
}

static const luaL_Reg fmcbReg[] = {
    {"int_cube", iCube},
    {NULL, NULL}
};

LUALIB_API int luaopen_libFMCBLua(lua_State *L) {
    luaL_newlib(L, fmcbReg); // ? Is this correct?

    return 1; // ? What does Lua expect here?
}