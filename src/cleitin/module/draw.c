#include <stdint.h>
#include <raylib.h>
#include "module.h"

static int32_t
draw_lua_2d_draw(lua_State *L)
{
    int32_t h = lua_tointeger(L, -1);
    int32_t w = lua_tointeger(L, -2);
    int32_t y = lua_tointeger(L, -3);
    int32_t x = lua_tointeger(L, -4);
    DrawRectangle(x, y, w, h, MAROON);
}

static const luaL_Reg draw_lua_2d_draw_funcs[] = 
{
    {"draw_rectangle", draw_lua_2d_draw},
    {NULL, NULL}
};

int32_t
draw_module_register(lua_State *L)
{
    lua_newtable(L);
    lua_pushstring(L, "2d");
    lua_newtable(L);
    lua_pushstring(L, "draw");
    lua_pushnil(L);
    lua_rawset(L, -3);
    luaL_register(L, NULL, draw_lua_2d_draw_funcs);
    lua_rawset(L, -3);
    lua_setglobal(L, "draw");
}

int32_t
draw_module_draw(lua_State *L)
{
    lua_getglobal(L, "draw");
    lua_pushstring(L, "2d");
    lua_rawget(L, -2);
    lua_pushstring(L, "draw");
    lua_rawgeti(L, -2, -1);

    BeginDrawing();
        ClearBackground(BLACK);
        if(lua_pcall(L, 0, 0, 0) != 0)
            return -1;
    EndDrawing();
}