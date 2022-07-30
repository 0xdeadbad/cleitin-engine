#include <stdint.h>
#include <raylib.h>
#include "module.h"

static int32_t
draw_lua_funcs_draw_text(lua_State *L)
{
    if(!lua_isnumber(L, -1))
    {
        luaL_error(L, "Error: %s", "Text font size should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -2))
    {
        luaL_error(L, "Error: %s", "Text y position should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -3))
    {
        luaL_error(L, "Error: %s", "Text x position should be a valid number!");
        return 1;
    }
    if(!lua_isstring(L, -4))
    {
        luaL_error(L, "Error: %s", "Text 'text' should be a valid string!");
        return 1;
    }

    const char *text = lua_tostring(L, -4);
    const int32_t x = lua_tointeger(L, -3);
    const int32_t y = lua_tointeger(L, -2);
    const int32_t fontsize = lua_tointeger(L, -1);
    
    DrawText(text, x, y, fontsize, WHITE);

    return 0;
}

static int32_t
draw_lua_funcs_draw_rectangle(lua_State *L)
{
    if(!lua_isnumber(L, -1))
    {
        luaL_error(L, "Error: %s\n", "Ractangle height should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -2))
    {
        luaL_error(L, "Error: %s\n", "Ractangle width should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -3))
    {
        luaL_error(L, "Error: %s\n", "Ractangle y position should be a valid number!");
        return 1;
    }
    if(!lua_isnumber(L, -4))
    {
        luaL_error(L, "Error: %s\n", "Ractangle x position should be a valid number!");
        return 1;
    }

    const int32_t x = lua_tointeger(L, -4);
    const int32_t y = lua_tointeger(L, -3);
    const int32_t w = lua_tointeger(L, -2);
    const int32_t h = lua_tointeger(L, -1);

    DrawRectangle(x, y, w, h, MAROON);

    return 0;
}

static const luaL_Reg draw_lua_funcs_draw_funcs[] = 
{
    {"draw_rectangle", draw_lua_funcs_draw_rectangle},
    {"draw_text", draw_lua_funcs_draw_text},
    {NULL, NULL}
};

static void
map_colours(lua_State *L)
{
    lua_pushstring(L, "color");
    lua_newtable(L);
}

int32_t
draw_module_register(lua_State *L)
{
    lua_newtable(L);
    map_colours(L);
    lua_pushstring(L, "funcs");
    lua_newtable(L);
    luaL_register(L, NULL, draw_lua_funcs_draw_funcs);
    lua_rawset(L, -3);
    lua_pushstring(L, "draw");
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_setglobal(L, "draw");
}

int32_t
draw_module_draw(lua_State *L)
{
    lua_getglobal(L, "draw");
    lua_pushstring(L, "draw");
    lua_rawget(L, -2);

    if(lua_isnil(L, -1))
    {
        luaL_error(L, "Error: %s", "Draw function is nil!");
        return -1;
    }

    BeginDrawing();
        ClearBackground(BLACK);
        lua_pushnumber(L, GetFrameTime());
        if(lua_pcall(L, 1, 0, 0) != 0)
        {
            const char *err = lua_tostring(L, -1);
            DrawText(err, 20, 20, 20, WHITE);
        }
    EndDrawing();

    lua_settop(L, 0);

    return 0;
}