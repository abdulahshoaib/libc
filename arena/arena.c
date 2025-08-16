#include "arena.h"

/* ============================
    Initialization and Freeing
   ============================ */
arena
arena_alloc(u64 size)
{
  arena a;
  a.capacity = size;
  a.offset = 0;

  // mem alloc
  u8 MAP = 0, PROT_RWX = 0;
  PROT_RWX = PROT_EXEC | PROT_READ | PROT_WRITE;
  MAP = MAP_PRIVATE | MAP_ANON;
  int fd = -1; // don't need a fd to the memory

  a.base = mmap(0, size, PROT_RWX, MAP, fd, a.offset);
  if (a.base == MAP_FAILED)
  {
    perror("MMAP Failed");
  }

  return a;
}

void
arena_release(arena *a)
{
  int err = munmap(a->base, a->capacity);
}

/* ========================
    Getting Mem from arena
   ======================== */
void *
arena_push(arena *a, u64 size)
{
  if (a->offset + size > a->capacity)
  {
    return NULL; // arena over-run
  }
  void *ptr = a->base + a->offset;
  memset(ptr, 0, size);
  a->offset += size;
  return ptr;
}

/*
   =======================
    Poping Mem from arena
   =======================
   NOTE(abdullah): when ever you pop arena always set
   the pointer using that to 0
*/
void
arena_pop(arena *a, u64 size)
{
  if (size > a->offset)
    return;
  a->offset -= size;
}

/*
   ============================
    Get Allocated Mem of arena
   ============================
*/
u64
arena_pos(arena *a)
{
  return a->offset;
}
