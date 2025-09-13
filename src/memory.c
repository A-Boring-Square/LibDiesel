#include "memory.h"
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/* Cross-platform constructor/destructor macros                                */
/* -------------------------------------------------------------------------- */
#if defined(__clang__) || defined(__GNUC__)
    #define MEM_CONSTRUCTOR __attribute__((constructor))
    #define MEM_DESTRUCTOR  __attribute__((destructor))
#elif defined(_MSC_VER)
    #define MEM_CONSTRUCTOR \
        __pragma(section(".CRT$XCU",read)) \
        static void __cdecl _mem_init(void); \
        __declspec(allocate(".CRT$XCU")) void (*_mem_init_ptr)(void) = _mem_init;
    #define MEM_DESTRUCTOR \
        static void _mem_shutdown(void); \
        static void _mem_shutdown_register(void) { atexit(_mem_shutdown); } \
        __pragma(section(".CRT$XCU",read)) \
        __declspec(allocate(".CRT$XCU")) void (*_mem_shutdown_ptr)(void) = _mem_shutdown_register;
#else
    #warning "Constructor/Destructor macros not defined; manual init required"
    #define MEM_CONSTRUCTOR
    #define MEM_DESTRUCTOR
#endif


/* ------------------------------ Forward Declarations ---------------------- */
void* arena_alloc(void* ctx, size_t size);
void arena_free(void* ctx, void* ptr);
void* arena_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size);
void arena_free_all_fn(void* ctx);

/* ------------------------------ Arena Implementation ---------------------- */
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

void arena_init(arena_t* arena, size_t block_size) {
    arena->block_size = block_size ? block_size : 1024;
    arena->root_block = NULL;
}

void arena_destroy(arena_t* arena) {
    _arena_block* block = arena->root_block;
    while (block) {
        _arena_block* next = block->next;
        free(block->data);
        free(block);
        block = next;
    }
    arena->root_block = NULL;
}

void arena_reset(arena_t* arena) {
    _arena_block* block = arena->root_block;
    while (block) {
        block->used = 0;
        block = block->next;
    }
}

void* arena_malloc(arena_t* arena, size_t size) {
    if (!arena || size == 0) return NULL;
    _arena_block* block = arena->root_block;

    while (block) {
        if (block->size - block->used >= size) {
            void* ptr = (char*)block->data + block->used;
            block->used += size;
            return ptr;
        }
        block = block->next;
    }

    _arena_block* new_block = _arena_block_create(size, arena->block_size);
    if (!new_block) return NULL;
    new_block->used = size;
    new_block->next = arena->root_block;
    arena->root_block = new_block;
    return new_block->data;
}

/* Arena allocator functions */
void* arena_alloc(void* ctx, size_t size) {
    return arena_malloc((arena_t*)ctx, size);
}

void arena_free(void* ctx, void* ptr) {
    (void)ctx;
    (void)ptr;
    /* no-op for arena */
}

void arena_free_all_fn(void* ctx) {
    arena_reset((arena_t*)ctx);
}

void* arena_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size) {
    void* new_ptr = arena_malloc((arena_t*)ctx, new_size);
    if (ptr && new_ptr && old_size) memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    return new_ptr;
}

/* ------------------------------ Allocator Functions ---------------------- */
void* malloc_alloc(void* ctx, size_t size) { (void)ctx; return malloc(size); }
void malloc_free(void* ctx, void* ptr) { (void)ctx; free(ptr); }

void* malloc_realloc(void* ctx, void* ptr, size_t old_size, size_t new_size) {
    (void)ctx; (void)old_size;
    return realloc(ptr, new_size);
}

void* _default_realloc(allocator_t* a, void* ptr, size_t old_size, size_t new_size) {
    if (!new_size) {
        if (ptr) FREE(a, ptr);
        return NULL;
    }
    void* new_ptr = ALLOC(a, new_size);
    if (!new_ptr) return NULL;
    if (ptr && old_size) memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    if (ptr) FREE(a, ptr);
    return new_ptr;
}

/* ------------------------------ Global Allocators ------------------------ */
static arena_t _temp_arena;

allocator_t default_allocator = {
    .alloc = malloc_alloc,
    .free = malloc_free,
    .free_all = NULL,
    .realloc = malloc_realloc,
    .ctx = NULL
};

allocator_t default_temp_allocator = {
    .alloc = arena_alloc,
    .free = arena_free,
    .free_all = arena_free_all_fn,
    .realloc = arena_realloc,
    .ctx = &_temp_arena
};

/* ------------------------------ Allocator Control ------------------------ */
void set_allocator(allocator_t* target,
                   alloc_fn alloc,
                   free_fn free,
                   free_all_fn free_all,
                   realloc_fn realloc,
                   void* ctx)
{
    if (!target) return;
    target->alloc = alloc;
    target->free = free;
    target->free_all = free_all;
    target->realloc = realloc;
    target->ctx = ctx;
}

/* ------------------------------ Auto init / destroy ---------------------- */
MEM_CONSTRUCTOR static void _init_temp_allocator(void) {
    arena_init(&_temp_arena, 1024);
}

MEM_DESTRUCTOR static void _destroy_temp_allocator(void) {
    arena_destroy(&_temp_arena);
}
