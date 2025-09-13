#ifndef LIB_DIESEL_CONTAINERS_H
#define LIB_DIESEL_CONTAINERS_H

#include "memory.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------- Vector Definition Macro ------------------------ */
#define VECTOR_DEFINE(T, Name)                                                \
typedef struct {                                                              \
    T *data;                                                                   \
    size_t length;                                                             \
    size_t capacity;                                                           \
    allocator_t *alloc;                                                        \
} Name;                                                                        \
                                                                               \
static inline void Name##_init(Name *vec, allocator_t *alloc) {               \
    vec->data = NULL;                                                          \
    vec->length = 0;                                                           \
    vec->capacity = 0;                                                         \
    vec->alloc = alloc ? alloc : &default_allocator;                           \
}                                                                              \
                                                                               \
static inline void Name##_free(Name *vec) {                                    \
    if (vec->data) FREE(vec->alloc, vec->data);                                 \
    vec->data = NULL;                                                          \
    vec->length = 0;                                                           \
    vec->capacity = 0;                                                         \
}                                                                              \
                                                                               \
static inline bool Name##_push(Name *vec, T value) {                           \
    if (vec->length >= vec->capacity) {                                        \
        size_t new_capacity = vec->capacity ? vec->capacity * 2 : 4;           \
        T* new_data = REALLOC(vec->alloc, vec->data, vec->capacity * sizeof(T), new_capacity * sizeof(T)); \
        if (!new_data) return false;                                           \
        vec->data = new_data;                                                  \
        vec->capacity = new_capacity;                                          \
    }                                                                          \
    vec->data[vec->length++] = value;                                          \
    return true;                                                               \
}                                                                              \
                                                                               \
static inline bool Name##_pop(Name *vec, T *out) {                             \
    if (vec->length == 0) return false;                                        \
    if (out) *out = vec->data[vec->length - 1];                                \
    vec->length--;                                                             \
    return true;                                                               \
}                                                                              \
                                                                               \
static inline T* Name##_get(Name *vec, uint64_t index) {                       \
    if (index >= vec->length) return NULL;                                     \
    return &vec->data[index];                                                  \
}                                                                              \
                                                                               \
static inline void Name##_delete(Name *vec) {                                  \
    if (vec->alloc && vec->alloc->free_all) {                                  \
        FREE_ALL(vec->alloc);                                                  \
    } else if (vec->data) {                                                    \
        FREE(vec->alloc, vec->data);                                           \
    }                                                                          \
    vec->data = NULL;                                                          \
    vec->length = 0;                                                           \
    vec->capacity = 0;                                                         \
}

/* ------------------------ Singly-linked List Macro ------------------------- */
#define SL_LIST_DEFINE(T, Name)                                                \
typedef struct Name##_node {                                                   \
    T data;                                                                    \
    struct Name##_node *next;                                                  \
} Name##_node;                                                                 \
                                                                               \
typedef struct {                                                               \
    Name##_node *head;                                                         \
    Name##_node *tail;                                                         \
    size_t length;                                                             \
    allocator_t *alloc;                                                        \
} Name;                                                                        \
                                                                               \
static inline void Name##_init(Name *list, allocator_t *alloc) {               \
    list->head = NULL;                                                         \
    list->tail = NULL;                                                         \
    list->length = 0;                                                          \
    list->alloc = alloc ? alloc : &default_allocator;                           \
}                                                                              \
                                                                               \
static inline void Name##_free(Name *list) {                                   \
    Name##_node *curr = list->head;                                            \
    while (curr) {                                                             \
        Name##_node *next = curr->next;                                        \
        FREE(list->alloc, curr);                                               \
        curr = next;                                                           \
    }                                                                          \
    list->head = NULL;                                                         \
    list->tail = NULL;                                                         \
    list->length = 0;                                                          \
}                                                                              \
                                                                               \
static inline bool Name##_append(Name *list, T value) {                        \
    Name##_node *node = ALLOC(list->alloc, sizeof(Name##_node));               \
    if (!node) return false;                                                   \
    node->data = value;                                                        \
    node->next = NULL;                                                         \
    if (!list->head) {                                                         \
        list->head = node;                                                     \
        list->tail = node;                                                     \
    } else {                                                                   \
        list->tail->next = node;                                               \
        list->tail = node;                                                     \
    }                                                                          \
    list->length++;                                                            \
    return true;                                                               \
}                                                                              \
                                                                               \
static inline bool Name##_prepend(Name *list, T value) {                       \
    Name##_node *node = ALLOC(list->alloc, sizeof(Name##_node));               \
    if (!node) return false;                                                   \
    node->data = value;                                                        \
    node->next = list->head;                                                   \
    list->head = node;                                                         \
    if (!list->tail) list->tail = node;                                        \
    list->length++;                                                            \
    return true;                                                               \
}                                                                              \
                                                                               \
static inline bool Name##_pop_front(Name *list, T *out) {                      \
    if (!list->head) return false;                                             \
    Name##_node *node = list->head;                                            \
    if (out) *out = node->data;                                                \
    list->head = node->next;                                                   \
    if (!list->head) list->tail = NULL;                                        \
    FREE(list->alloc, node);                                                   \
    list->length--;                                                            \
    return true;                                                               \
}                                                                              \
                                                                               \
static inline void Name##_delete(Name *list) {                                  \
    if (list->alloc && list->alloc->free_all) {                                \
        FREE_ALL(list->alloc);                                                 \
    } else {                                                                   \
        Name##_node *curr = list->head;                                        \
        while (curr) {                                                         \
            Name##_node *next = curr->next;                                    \
            FREE(list->alloc, curr);                                           \
            curr = next;                                                       \
        }                                                                      \
    }                                                                          \
    list->head = NULL;                                                         \
    list->tail = NULL;                                                         \
    list->length = 0;                                                          \
}

#ifdef __cplusplus
}
#endif

#endif /* LIB_DIESEL_CONTAINERS_H */
