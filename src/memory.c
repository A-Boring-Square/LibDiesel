#include "memory.h"


// Internal: create a new block of at least min_size bytes or default block size
static _arena_block* _arena_block_create(size_t min_size, size_t default_block_size) {
    size_t size = (min_size > default_block_size) ? min_size : default_block_size;
    _arena_block* block = malloc(sizeof(_arena_block));
    if (!block) return NULL;

    block->data = malloc(size);
    if (!block->data) {
        free(block);
        return NULL;
    }

    block->size = size;
    block->used = 0;
    block->next = NULL;
    return block;
}

DIESEL_API void arena_init(arena_t* arena, size_t block_size) {
    arena->block_size = block_size ? block_size : LIB_DIESEL_MEMORY_ARENA_DEFAULT_BLOCK_SIZE;
    arena->root_block = NULL;
}

DIESEL_API void arena_destroy(arena_t* arena) {
    _arena_block* block = arena->root_block;
    while (block) {
        _arena_block* next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    arena->root_block = NULL;
}

DIESEL_API void arena_reset(arena_t* arena) {
    _arena_block* block = arena->root_block;
    while (block) {
        block->used = 0;
        block = block->next;
    }
}


DIESEL_API void* arena_malloc(arena_t* arena, size_t size) {
    if (!arena || size == 0) return NULL;

    _arena_block* block = arena->root_block;

    // Try to find space in existing blocks
    while (block) {
        if (block->size - block->used >= size) {
            void* ptr = (char*)block->data + block->used;
            block->used += size;
            return ptr;
        }
        block = block->next;
    }

    // No block found, create new one
    _arena_block* new_block = _arena_block_create(size, arena->block_size);
    if (!new_block) return NULL;

    new_block->used = size;
    new_block->next = arena->root_block;
    arena->root_block = new_block;

    return new_block->data;
}