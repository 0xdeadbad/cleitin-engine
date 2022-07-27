#ifndef __CLEITIN_H__
#define __CLEITIN_H__

#include <luajit-2.1/lua.h>
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lualib.h>

typedef struct cleitin_ctx cleitin_ctx;

cleitin_ctx*
cleitin_init(int32_t argc, char **argv);
void
cleitin_destroy(cleitin_ctx *ctx);
int32_t
cleitin_mod_register(cleitin_ctx *ctx, const char *modname, const luaL_Reg *modfuncs);

#endif