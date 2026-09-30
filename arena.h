#ifndef _ARENA_ALLOCATOR_H_
#define _ARENA_ALLOCATOR_H_

#include <stdlib.h>
#include "misc.h"
#include <errno.h>
#include <string.h>



#ifndef DEFAULT_REGIONS_QUANTITY
#define DEFAULT_REGIONS_QUANTITY 64
#endif

#ifndef DEFAULT_REGION_CAPACITY
#define DEFAULT_REGION_CAPACITY 256
#endif

typedef enum
  {
    UNINIT,
    INIT
  } ARENA_STATUS;

struct Region
{
  void* data;
  size_t cur;
  size_t capacity;
};
typedef struct Region Region;


struct Arena
{
  ARENA_STATUS flag;
  Region *blocks;
  u32 cur_pointer;
  struct Arena *next;
};
typedef struct Arena Arena;

// TODO(RT): implement arena_memcpy
// TODO(RT): implement arena_strcmp
// TODO(RT): get rid of c runtime garbage
// TODO(RT): add support of multiple backends


internal void arena_init_(Arena *base);
void *arena_alloc_(Arena *base, size_t size);
void arena_free_(Arena *base);
void arena_realloc_(Arena *base, size_t Qu);
// @Cleanup: do we really need realloc_ function?


#if defined(ARENA_IMPLEMENTATION)

#define ALLOC malloc
#define FREE  free
// @Cleanup: not so perfect decision, have to rewrite later


Region new_region()
{
  Region temp;
  temp.data = ALLOC(DEFAULT_REGION_CAPACITY * sizeof(char));
  temp.capacity = DEFAULT_REGION_CAPACITY;
  temp.cur = 0;
  return temp;
}


internal void arena_init_(Arena *base)
{

  base->flag = INIT;
  base->blocks = (Region *)calloc(DEFAULT_REGIONS_QUANTITY, sizeof(Region));
  base->cur_block = 0;
  if(!base->blocks)
    {
      printf("Allocation issue: %s\n", strerror);
      exit(1);
    }
}


void* arena_alloc_(Arena *base, size_t size)
{

}

void arena_destroy_(Arena *base)
{

}

void arena_realloc_(Arena *base, size_t Qu)
{

}


#endif
#endif
