#include "slab.h"

int
slab_create(slab *s, u64 obj_size, u64 cap)
{
  s->object_size = (obj_size < sizeof(void *)) ? sizeof(void *) : obj_size;
  s->capacity = cap;
  u64 size = s->object_size * cap;

  s->mem = malloc(size);
  if (!s->mem)
    return SLAB_NOT_CREATED;

  s->free_list = s->mem;
  u8 *ptr = (u8 *)s->mem;

  for (u64 i = 0; i < cap - 1; ++i)
  {
    void *next = ptr + s->object_size;
    *(void **)ptr = next; // NOTE(abdullah): this marks the starting 8
                          // bytes of the 64 bytes to point to the next
    ptr += s->object_size;
  }

  *(void **)ptr = NULL;

  return 0;
};

void
slab_destroy(slab *s)
{
  free(s);
  s->mem = NULL;
  s->free_list = NULL;
}

void *
slab_alloc(slab *s)
{
  if (!s->free_list)
    return NULL;
  void *slot = s->free_list;
  // NOTE(abdullah): this just moves the ref to the free_list
  // to the next available object space so that the next alloc
  // is next to the current and head keeps moving
  s->free_list = *(void **)s->free_list;
  s->used++;
  return slot;
}

void
slab_free(slab *s, void *slot)
{
  // NOTE(abdullah): This would just add the next slot's address
  // and set the free_list to point to it'self
  *(void **)slot = s->free_list;
  s->used--;
  s->free_list = slot;
}

u64
slab_used(slab* s) {
  return s->used;
}
