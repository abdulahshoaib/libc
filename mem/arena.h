#ifndef ARENA
#define ARENA

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

typedef struct Arena
{
  u8 *base; // only set once, no arithmetic EVER!
  u64 offset;
  u64 capacity;
} arena;

arena arena_alloc(u64);
void  arena_release(arena *);

void *arena_push(arena *, u64);

/* ===============
        MACROS
   =============== */
#define push(arena, type) (type *)arena_push(arena, sizeof(type))
#define push_arr(arena, type, length) (type *)arena_push(arena, sizeof(type) * len);

void arena_pop(arena *, u64);
u64  arena_pos(arena *);
void arena_clear(arena *);

#endif // ARENA
