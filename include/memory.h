#ifndef LIB_DIESEL_MEMORY_H
#define LIB_DIESEL_MEMORY_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------------------------------------------------------- */
/* Arena types                                                                 */
/* -------------------------------------------------------------------------- */
typedef struct _arena_block {
    void* data;
    size_t size;
    size_t used;
    struct _arena_block* next;
} _arena_block;

typedef struct {
    _arena_block* root_block;
    size_t block_size;
} arena_t;

/* -------------------------------------------------------------------------- */
/* Allocator type                                                              */
/* -------------------------------------------------------------------------- */
typedef void* (*alloc_fn)(void* ctx, size_t size);
typedef void  (*free_fn)(void* ctx, void* ptr);
typedef void  (*free_all_fn)(void* ctx);
typedef void* (*realloc_fn)(void* ctx, void* ptr, size_t old_size, size_t new_size);

typedef struct {
    alloc_fn alloc;
    free_fn free;
    free_all_fn free_all;
    realloc_fn realloc;
    void* ctx;
} allocator_t;

/* -------------------------------------------------------------------------- */
/* Helper macros                                                               */
/* -------------------------------------------------------------------------- */
#define ALLOC(a, size) ((a)->alloc((a)->ctx, (size)))
#define FREE(a, ptr)   ((a)->free((a)->ctx, (ptr)))
#define FREE_ALL(a)    ((a)->free_all ? (a)->free_all((a)->ctx) : (void)0)
#define REALLOC(a, ptr, old_size, new_size) \
    ((a)->realloc ? (a)->realloc((a)->ctx, (ptr), (old_size), (new_size)) : _default_realloc((a), (ptr), (old_size), (new_size)))

void* _default_realloc(allocator_t* a, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Arena API                                                                   */
/* -------------------------------------------------------------------------- */
void arena_init(arena_t* arena, size_t block_size);
void arena_destroy(arena_t* arena);
void arena_reset(arena_t* arena);
void* arena_malloc(arena_t* arena, size_t size);
void arena_free_all_fn(void* ctx);
void* arena_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Default allocator functions                                                 */
/* -------------------------------------------------------------------------- */
void* malloc_alloc(void* ctx, size_t size);
void malloc_free(void* ctx, void* ptr);
void* malloc_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Global allocators                                                           */
/* -------------------------------------------------------------------------- */
extern allocator_t default_allocator;
extern allocator_t default_temp_allocator;

/* -------------------------------------------------------------------------- */
/* Allocator control                                                           */
/* -------------------------------------------------------------------------- */
void set_allocator(allocator_t* target,
                   alloc_fn alloc,
                   free_fn free,
                   free_all_fn free_all,
                   realloc_fn realloc,
                   void* ctx);

#ifdef __cplusplus
}
#endif

#endif /* LIB_DIESEL_MEMORY_H */
