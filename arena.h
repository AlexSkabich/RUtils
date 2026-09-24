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
  size_t cur_block;
};
typedef struct Arena Arena;

// TODO(RT): fix allocaation issues (probably rewrite)
// TODO(RT): implement arena_realloc
// TODO(RT): implement arena_memcpy
// TODO(RT): implement arena_strcmp
// TODO(RT): get rid of c runtime garbage
// TODO(RT): add support of multiple backends


void arena_init_(Arena *base);
void* arena_alloc_(Arena *base, size_t size);
void arena_destroy_(Arena *base);
void arena_realloc_(Arena *base, size_t Qu);



#if defined(ARENA_IMPLEMENTATION)

Region new_region()
{
  Region temp;
  temp.data = calloc(DEFAULT_REGION_CAPACITY, sizeof(char));
  temp.capacity = DEFAULT_REGION_CAPACITY;
  temp.cur = 0;
  return temp;
}


void arena_init_(Arena *base)
{

  base->flag = INIT;
  base->blocks = (Region *)calloc(DEFAULT_REGIONS_QUANTITY, sizeof(Region));
  base->cur_block = 0;
  if(!base->blocks)
    {
      perror("Allocation issue\n");
    }
}


void* arena_alloc_(Arena *base, size_t size)
{
  if(base->flag == UNINIT) arena_init_(base);
  // if [want to allocate] >= [empty space of region]
  // do it in the new_region()
  // but if [want to allocate] >= [region_capacity * all empty regions we have in arena]
  // do realloc()
  // TODO(RT): fix conditions mistake
  if(size >= (base->blocks->capacity - base->blocks->cur))
    {
      if(size >= DEFAULT_REGIONS_CAPACITY * (arena->capacity - base->cur_block))
	{
	  arena_realloc_(base, (base->cur_block * 2));
	}

      base->blocks[base->cur_block] = new_region();
      base->cur_block++;
    }

  base->blocks->cur += size;
  return base->blocks->data + size - base->blocks->cur;
}

void arena_destroy_(Arena *base)
{

  while(base->cur_block)
    {
      free(base->blocks[base->cur_block].data);
      base->cur_block--;
    }
  free(base->blocks);
  return;
}

void arena_realloc_(Arena *base, size_t Qu)
{
  Region* pointer = base->blocks;
  base->blocks = (Region *)realloc(base->blocks, (sizeof(Region) * Qu));
  pointer += base->cur_block;
  pointer = calloc((Qu - base->cur_block), sizeof(Region));

}


#endif
#endif
