#ifndef LIB_DIESEL_MEMORY_H
#define LIB_DIESEL_MEMORY_H

#include "types.h"
#include "_export.h"
#include "platform.h"

/**
 * @brief Default block size for memory arena allocations, in bytes.
 * If not defined elsewhere, defaults to 1 KB.
 */
#ifndef LIB_DIESEL_MEMORY_ARENA_DEFAULT_BLOCK_SIZE
#define LIB_DIESEL_MEMORY_ARENA_DEFAULT_BLOCK_SIZE KB(1)
#endif

/**
 * @brief Convert kilobytes to bytes.
 */
#ifndef KB
#define KB(x) ((size_t)(x) * 1024)
#endif

/**
 * @brief Convert megabytes to bytes.
 */
#ifndef MB
#define MB(x) ((size_t)(x) * 1024 * 1024)
#endif

/**
 * @brief Convert gigabytes to bytes.
 */
#ifndef GB
#define GB(x) ((size_t)(x) * 1024 * 1024 * 1024)
#endif

/**
 * @brief A block of memory managed by the arena allocator.
 */
typedef struct _arena_block {
    void* data;                ///< Pointer to the memory block.
    size_t size;               ///< Total size of the block in bytes.
    size_t used;               ///< Number of bytes allocated in this block.
    struct _arena_block* next; ///< Pointer to the next block in the linked list.
} _arena_block;

/**
 * @brief Memory arena for efficient linear allocations.
 * Manages a linked list of blocks.
 */
typedef struct {
    _arena_block* root_block;  ///< First block in the arena.
    size_t block_size;         ///< Default block size for new allocations.
} arena_t;

/**
 * @brief Initialize the memory arena.
 * Allocates initial block with the given block size or default size if zero.
 *
 * @param arena Pointer to the arena structure to initialize.
 * @param block_size Size of blocks to allocate in bytes.
 */
DIESEL_API void arena_init(arena_t* arena, size_t block_size);

/**
 * @brief Allocate memory from the arena.
 * Allocates `size` bytes from current block or creates a new block if necessary.
 *
 * @param arena Pointer to the arena to allocate from.
 * @param size Number of bytes to allocate.
 * @return Pointer to allocated memory.
 */
DIESEL_API void* arena_malloc(arena_t* arena, size_t size);

/**
 * @brief Free all memory blocks and reset the arena to empty.
 * Releases all allocated memory owned by the arena.
 *
 * @param arena Pointer to the arena to destroy.
 */
DIESEL_API void arena_destroy(arena_t* arena);

/**
 * @brief Reset the arena for reuse without freeing memory.
 * Resets the used counters so allocations can start over.
 *
 * @param arena Pointer to the arena to reset.
 */
DIESEL_API void arena_reset(arena_t* arena);

#endif
