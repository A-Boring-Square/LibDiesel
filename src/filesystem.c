#include "filesystem.h"

DIESEL_API FILE* open_file(string_t path, bool read, bool write, bool append, bool create_if_not_exist) {
    _NORMALIZE_FILE_PATH(path);

    // Build mode string for fopen
    // Modes: r, w, a, r+, w+, a+
    string_t mode = "";

    if (append) {
        mode = write ? "a+" : "a";
    } else if (write) {
        mode = read ? "w+" : "w";
    } else if (read) {
        mode = "r";
    } else {
        // Default to read mode if nothing specified
        mode = "r";
    }

    // fopen doesn't create file if opened in "r" mode, so if create_if_not_exist is true and mode is read only, switch to "w+"
    if (create_if_not_exist && mode == "r") {
        mode = "w+";
    }

    FILE *f = fopen(path, mode);
    return f;
}

DIESEL_API void close_file(FILE* file_handle) {
    fclose(file_handle);
}

DIESEL_API string_t read_file_into_string_buffer(FILE* file_handle, char* buffer, size_t buffer_size) {
    if (!file_handle || !buffer || buffer_size == 0) return NULL;

    fseek(file_handle, 0, SEEK_END);
    long size = ftell(file_handle);
    if (size < 0 || (size_t)size >= buffer_size) return NULL;
    rewind(file_handle);

    char* heap_buffer = malloc(size + 1);
    if (!heap_buffer) return NULL;

    size_t read_size = fread(heap_buffer, 1, size, file_handle);
    if (read_size != (size_t)size) {
        free(heap_buffer);
        return NULL;
    }

    heap_buffer[size] = '\0';

    memcpy(buffer, heap_buffer, size + 1);
    free(heap_buffer);

    return buffer;
}