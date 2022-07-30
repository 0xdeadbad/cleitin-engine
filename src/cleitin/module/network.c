#include <stdint.h>
#include <stdbool.h>
#include <enet.h>
#include "module.h"


static int32_t
network_lua_initialize(lua_State *L)
{
    if(enet_initialize() != 0)
    {
        luaL_error(L, "Error: %s", "An error occurred while initializing ENet.");
        return 1;
    }
    return 0;
}

static const luaL_Reg network_lua_funcs[] = 
{
    {"init_window", network_lua_initialize},
    {NULL, NULL}
};

int32_t
network_module_register(lua_State *L)
{
     lua_newtable(L);
     luaL_register(L, NULL, network_lua_funcs);
     lua_setglobal(L, "network");
}