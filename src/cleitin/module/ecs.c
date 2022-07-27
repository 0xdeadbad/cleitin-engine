#include <stdint.h>
#include <flecs.h>
#include "module.h"

static int32_t
ecs_lua_component_register(lua_State *L)
{
    
}

static const luaL_Reg ecs_lua_entity_funcs[] = 
{
    {NULL, NULL}
};

static const luaL_Reg ecs_lua_component_funcs[] = 
{
    {"register", ecs_lua_component_register},
    {NULL, NULL}
};

static const luaL_Reg ecs_lua_system_funcs[] = 
{
    {NULL, NULL}
};

static const luaL_Reg ecs_lua_world_funcs[] = 
{
    {NULL, NULL}
};

int32_t
ecs_module_register(lua_State *L)
{
    lua_newtable(L);
    lua_pushstring(L, "entity");
    lua_newtable(L);
    luaL_register(L, NULL, ecs_lua_entity_funcs);
    lua_rawset(L, -3);
    lua_pushstring(L, "component");
    lua_newtable(L);
    luaL_register(L, NULL, ecs_lua_component_funcs);
    lua_rawset(L, -3);
    lua_pushstring(L, "system");
    lua_newtable(L);
    luaL_register(L, NULL, ecs_lua_system_funcs);
    lua_rawset(L, -3);
    lua_pushstring(L, "world");
    lua_newtable(L);
    luaL_register(L, NULL, ecs_lua_world_funcs);
    lua_rawset(L, -3);
    lua_setglobal(L, "ecs");
    
    return 0;
}