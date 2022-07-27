#include <stdint.h>
#include <raylib.h>
#include "module.h"

int32_t
window_module_register(lua_State *L)
{
    lua_newtable(L);
    lua_pushstring(L, "2d");
    lua_setglobal(L, "window");
}