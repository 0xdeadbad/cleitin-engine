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

  while (!WindowShouldClose())
  {
    
  }

  cleitin_destroy(ctx);

  return EXIT_SUCCESS;
}