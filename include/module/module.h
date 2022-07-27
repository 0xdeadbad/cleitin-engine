#ifndef __MODULE_H__
#define __MODULE_H__

#include <stdint.h>
#include <raylib.h>

#include <luajit-2.1/lua.h>
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lualib.h>

int32_t
ecs_module_register(lua_State *L);
int32_t
draw_module_register(lua_State *L);
int32_t
draw_module_draw(lua_State *L);

#endif