#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <flecs.h>

#include "module.h"
#include "cleitin.h"

struct cleitin_ctx 
{
    ecs_world_t *ecs_world;
    lua_State *lua_state;
};

static void
cleitin_load_modules(cleitin_ctx *ctx);

cleitin_ctx*
cleitin_init(int32_t argc, char **argv)
{
    cleitin_ctx *ctx;

    if((ctx = (cleitin_ctx*)malloc(sizeof(cleitin_ctx))) == NULL)
        return NULL;

    ctx->ecs_world = ecs_init_w_args(argc, argv);
    if((ctx->lua_state = luaL_newstate()) == NULL)
    {
        ecs_fini(ctx->ecs_world);
        free(ctx);
        return NULL;
    }

    luaL_openlibs(ctx->lua_state);
    
    cleitin_load_modules(ctx);

    if(luaL_dofile(ctx->lua_state, "./main.lua") != 0)
    {
        const char *err = lua_tostring(ctx->lua_state, -1);
        fprintf(stderr, "Error: %s\n", err);
        ecs_fini(ctx->ecs_world);
        free(ctx);
        return NULL;
    }

    return ctx; 
}

void
cleitin_destroy(cleitin_ctx *ctx)
{
    ecs_fini(ctx->ecs_world);
    lua_close(ctx->lua_state);
    free(ctx);
}

lua_State*
cleitin_get_luaState(cleitin_ctx *ctx)
{
    return ctx->lua_state;
}

static int32_t
cleitin_print(lua_State *L)
{
    if(!lua_isstring(L, -1))
    {
        luaL_error(L, "Error: %s", "Argument to print is not a string");
        return 1;
    }
    const char *str = luaL_checkstring(L, 1);
    printf("%s", str);
    return 0;
}

static void
cleitin_load_modules(cleitin_ctx *ctx)
{
    lua_register(ctx->lua_state, "cleitin_print", cleitin_print);
    draw_module_register(ctx->lua_state);
    ecs_module_register(ctx->lua_state);
    window_module_register(ctx->lua_state);
    network_module_register(ctx->lua_state);
}

