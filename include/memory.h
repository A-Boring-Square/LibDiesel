#ifndef LIB_DIESEL_MEMORY_H
#define LIB_DIESEL_MEMORY_H

#include "types.h"
#include "_export.h"
#include "platform.h"

// In bytes
#ifndef LIB_DIESEL_MEMORY_ARENA_DEFAULT_BLOCK_SIZE
#define LIB_DIESEL_MEMORY_ARENA_DEFAULT_BLOCK_SIZE KB(1)
#endif

#ifndef KB
#define KB(x) ((size_t)(x) * 1024)
#endif
#ifndef MB
#define MB(x) ((size_t)(x) * 1024 * 1024)
#endif
#ifndef GB
#define GB(x) ((size_t)(x) * 1024 * 1024 * 1024)
#endif

typedef struct _arena_block {
    void* data;
    size_t size;
    size_t used;
    struct _arena_block* next;
} _arena_block;

typedef struct {
    _arena_block* root_block;
    size_t block_size;         // default block size for new allocations
} arena_t;

void arena_init(arena_t* arena, size_t block_size);

void* arena_malloc(arena_t* arena, size_t size);

void arena_free(arena_t* arena, void* obj);

#endif