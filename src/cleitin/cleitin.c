#include <malloc.h>
#include <stdint.h>
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

    cleitin_load_modules(ctx);

    return ctx; 
}

void
cleitin_destroy(cleitin_ctx *ctx)
{
    ecs_fini(ctx->ecs_world);
    lua_close(ctx->lua_state);
    free(ctx);
}

static void
cleitin_load_modules(cleitin_ctx *ctx)
{
    draw_module_register(ctx->lua_state);
    ecs_module_register(ctx->lua_state);
}