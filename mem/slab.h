#ifndef SLAB
#define SLAB

#include "arena.h"
#include "errors/errors.h"
#include <stdlib.h>

typedef struct
{
  void *mem;
  void *free_list;
  u64   object_size;
  u64   capacity;
  u64   used;
} slab;

int   slab_create(slab *, u64, u64);
void  slab_destroy(slab *);

void *slab_alloc(slab *);
void  slab_free(slab *, void *);

u64   slab_used(slab *s);

#endif // !SLAB
