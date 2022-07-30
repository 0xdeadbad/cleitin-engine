#ifndef __CLEITIN_H__
#define __CLEITIN_H__

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

typedef struct cleitin_ctx cleitin_ctx;

cleitin_ctx*
cleitin_init(int32_t argc, char **argv);
void
cleitin_destroy(cleitin_ctx *ctx);
int32_t
cleitin_mod_register(cleitin_ctx *ctx, const char *modname, const luaL_Reg *modfuncs);
lua_State*
cleitin_get_luaState(cleitin_ctx *ctx);

#endif