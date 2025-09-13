#include "filesystem.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/* File Open/Close Functions                                                   */
/* -------------------------------------------------------------------------- */
DIESEL_API FILE* open_file(string_t path, bool read, bool write, bool append, bool create_if_not_exist) {
    _NORMALIZE_FILE_PATH(path);

    // Build mode string
    string_t mode = "";

    if (append) {
        mode = write ? "a+" : "a";
    } else if (write) {
        mode = read ? "w+" : "w";
    } else if (read) {
        mode = "r";
    } else {
        mode = "r";
    }

    // fopen doesn't create file if opened in "r" mode
    if (create_if_not_exist && strcmp(mode, "r") == 0) {
        mode = "w+";
    }

    return fopen(path, mode);
}

DIESEL_API void close_file(FILE* file_handle) {
    if (file_handle) fclose(file_handle);
}

/* -------------------------------------------------------------------------- */
/* Read File into String Using Allocator                                       */
/* -------------------------------------------------------------------------- */
DIESEL_API string_t read_file_into_string_buffer(FILE* file_handle, char* buffer, size_t buffer_size, allocator_t* alloc) {
    if (!file_handle || !buffer || buffer_size == 0) return NULL;

    alloc = alloc ? alloc : &default_allocator;

    if (fseek(file_handle, 0, SEEK_END) != 0) return NULL;
    long size = ftell(file_handle);
    if (size < 0 || (size_t)size >= buffer_size) return NULL;
    rewind(file_handle);

    char* heap_buffer = ALLOC(alloc, size + 1);
    if (!heap_buffer) return NULL;

    size_t read_size = fread(heap_buffer, 1, size, file_handle);
    if (read_size != (size_t)size) {
        FREE(alloc, heap_buffer);
        return NULL;
    }

    heap_buffer[size] = '\0';
    memcpy(buffer, heap_buffer, size + 1);
    FREE(alloc, heap_buffer);

    return buffer;
}

/* -------------------------------------------------------------------------- */
/* Read Entire File into Allocator-Managed Heap (Optional)                     */
/* Returns pointer allocated from allocator; caller must free with allocator  */
/* -------------------------------------------------------------------------- */
DIESEL_API char* read_file_to_heap(FILE* file_handle, allocator_t* alloc) {
    if (!file_handle) return NULL;

    alloc = alloc ? alloc : &default_allocator;

    if (fseek(file_handle, 0, SEEK_END) != 0) return NULL;
    long size = ftell(file_handle);
    if (size < 0) return NULL;
    rewind(file_handle);

    char* heap_buffer = ALLOC(alloc, size + 1);
    if (!heap_buffer) return NULL;

    size_t read_size = fread(heap_buffer, 1, size, file_handle);
    if (read_size != (size_t)size) {
        FREE(alloc, heap_buffer);
        return NULL;
    }

    heap_buffer[size] = '\0';
    return heap_buffer;
}
