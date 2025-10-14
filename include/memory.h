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

/**
 * @brief A single memory block within an arena.
 */
typedef struct _arena_block {
    void* data;                /**< Pointer to the memory block */
    size_t size;               /**< Total size of the block */
    size_t used;               /**< Bytes used in this block */
    struct _arena_block* next; /**< Next block in the arena */
} _arena_block;

/**
 * @brief Arena allocator structure.
 *
 * Manages a linked list of memory blocks for fast allocation and reset.
 */
typedef struct {
    _arena_block* root_block; /**< First block in the arena */
    size_t block_size;        /**< Default block size for new allocations */
} arena_t;

/* -------------------------------------------------------------------------- */
/* Allocator type                                                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Function pointer type for allocation.
 *
 * @param ctx User-defined context
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory
 */
typedef void* (*alloc_fn)(void* ctx, size_t size);

/**
 * @brief Function pointer type for freeing a single allocation.
 *
 * @param ctx User-defined context
 * @param ptr Pointer to memory to free
 */
typedef void  (*free_fn)(void* ctx, void* ptr);

/**
 * @brief Function pointer type for freeing all allocations.
 *
 * @param ctx User-defined context
 */
typedef void  (*free_all_fn)(void* ctx);

/**
 * @brief Function pointer type for reallocating memory.
 *
 * @param ctx User-defined context
 * @param ptr Pointer to existing memory
 * @param old_size Original size of memory
 * @param new_size New requested size
 * @return Pointer to resized memory
 */
typedef void* (*realloc_fn)(void* ctx, void* ptr, size_t old_size, size_t new_size);

/**
 * @brief Generic allocator structure.
 */
typedef struct {
    alloc_fn alloc;       /**< Allocation function */
    free_fn free;         /**< Free function */
    free_all_fn free_all; /**< Optional bulk-free function */
    realloc_fn realloc;   /**< Optional realloc function */
    void* ctx;            /**< User-defined context passed to functions */
} allocator_t;

/* -------------------------------------------------------------------------- */
/* Helper macros                                                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocate memory using an allocator.
 */
#define ALLOC(a, size) ((a)->alloc((a)->ctx, (size)))

/**
 * @brief Free memory using an allocator.
 */
#define FREE(a, ptr)   ((a)->free((a)->ctx, (ptr)))

/**
 * @brief Free all memory using an allocator, if supported.
 */
#define FREE_ALL(a)    ((a)->free_all ? (a)->free_all((a)->ctx) : (void)0)

/**
 * @brief Reallocate memory using an allocator, or fallback to default.
 */
#define REALLOC(a, ptr, old_size, new_size) \
    ((a)->realloc ? (a)->realloc((a)->ctx, (ptr), (old_size), (new_size)) : _default_realloc((a), (ptr), (old_size), (new_size)))

/**
 * @brief Default realloc fallback if allocator does not provide one.
 *
 * @param a Allocator
 * @param ptr Existing memory pointer
 * @param old_size Old memory size
 * @param new_size New memory size
 * @return Pointer to resized memory
 */
void* _default_realloc(allocator_t* a, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Arena API                                                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize an arena.
 *
 * @param arena Pointer to arena to initialize
 * @param block_size Default block size for allocations
 */
void arena_init(arena_t* arena, size_t block_size);

/**
 * @brief Destroy an arena and free all memory.
 *
 * @param arena Pointer to arena to destroy
 */
void arena_destroy(arena_t* arena);

/**
 * @brief Reset an arena to reuse all memory.
 *
 * @param arena Pointer to arena to reset
 */
void arena_reset(arena_t* arena);

/**
 * @brief Allocate memory from an arena.
 *
 * @param arena Arena to allocate from
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory
 */
void* arena_malloc(arena_t* arena, size_t size);

/**
 * @brief Free all memory allocated from an arena (used as a free_all_fn).
 *
 * @param ctx Pointer to arena_t
 */
void arena_free_all_fn(void* ctx);

/**
 * @brief Reallocate memory in an arena.
 *
 * @param ctx Pointer to arena_t
 * @param ptr Existing memory pointer
 * @param old_size Original size of memory
 * @param new_size New requested size
 * @return Pointer to resized memory
 */
void* arena_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Default allocator functions                                                */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocate memory using malloc.
 *
 * @param ctx Ignored
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory
 */
void* malloc_alloc(void* ctx, size_t size);

/**
 * @brief Free memory using free.
 *
 * @param ctx Ignored
 * @param ptr Pointer to memory to free
 */
void malloc_free(void* ctx, void* ptr);

/**
 * @brief Reallocate memory using realloc.
 *
 * @param ctx Ignored
 * @param ptr Pointer to existing memory
 * @param old_size Ignored
 * @param new_size Number of bytes to reallocate
 * @return Pointer to resized memory
 */
void* malloc_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size);

/* -------------------------------------------------------------------------- */
/* Global allocators                                                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Default general-purpose allocator.
 */
extern allocator_t default_allocator;

/**
 * @brief Temporary allocator for short-lived allocations.
 */
extern allocator_t default_temp_allocator;

/* -------------------------------------------------------------------------- */
/* Allocator control                                                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Configure an allocator with custom functions.
 *
 * @param target Allocator to configure
 * @param alloc Allocation function
 * @param free Free function
 * @param free_all Optional bulk-free function
 * @param realloc Optional realloc function
 * @param ctx User-defined context
 */
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
