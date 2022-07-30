#include <stdint.h>
#include <stdbool.h>
#include <raylib.h>
#include "module.h"

static int32_t
window_lua_set_fps(lua_State *L)
{
    if(!lua_isnumber(L, -1))
    {
        luaL_error(L, "Error: %s", "FPS value should be a valid number!");
        return 1;
    }

    const int32_t fps = lua_tointeger(L, -1);
    SetTargetFPS(fps);

    return 0;
}

static int32_t
window_lua_init_window(lua_State *L)
{
    if(!lua_isnumber(L, -1))
    {
        luaL_error(L, "Error: %s", "Window height should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -2))
    {
        luaL_error(L, "Error: %s", "Window width should be a valid number!");
        return 1;
    }
    if(!lua_isstring(L, -3))
    {
        luaL_error(L, "Error: %s", "Window title should be a valid string!");
        return 1;
    }

    const char *title = lua_tostring(L, -3);
    const int32_t screenWidth = lua_tointeger(L, -2);
    const int32_t screenHeight = lua_tointeger(L, -1);

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

static const luaL_Reg window_lua_window_funcs[] = 
{
    {"init_window", window_lua_init_window},
    {"set_fps", window_lua_set_fps},
    {NULL, NULL}
};

int32_t
window_module_register(lua_State *L)
{
    lua_newtable(L);
    lua_pushstring(L, "window");
    lua_newtable(L);
    luaL_register(L, NULL, window_lua_window_funcs);
    lua_rawset(L, -3);
    lua_setglobal(L, "window");
}

bool
window_module_should_close()
{
    return WindowShouldClose();
}