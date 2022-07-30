#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cleitin.h"
#include "module.h"

int32_t
main(int32_t argc, char **argv)
{
  cleitin_ctx *ctx;

  if((ctx = cleitin_init(argc, argv)) == NULL)
    return EXIT_FAILURE;

  lua_State *L = cleitin_get_luaState(ctx);

  while(!window_module_should_close())
  {
    if(draw_module_draw(L) != 0) {
      break;
    }
  }

  cleitin_destroy(ctx);

  return EXIT_SUCCESS;
}