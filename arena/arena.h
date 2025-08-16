#ifndef ARENA
#define ARENA

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

typedef struct Arena
{
  u8 *base;
  u64 offset;
  u64 capacity;
} arena;

arena arena_alloc(u64);

void arena_release(arena *);

void *arena_push(arena *, u64);

/* ===============
        MACROS
   =============== */
#define push(arena, type) arena_push

void arena_pop(arena *, u64);
u64 arena_pos(arena *);

#endif // ARENA
