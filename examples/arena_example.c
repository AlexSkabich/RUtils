#include <stdio.h>
#define ARENA_IMPLEMENTATION
#include "../arena.h"


int main(void)
{
  Arena my_arena;
  u64 *p = arena_alloc_(&my_arena, 128);
  arena_free_(p);
  return(0);
}
