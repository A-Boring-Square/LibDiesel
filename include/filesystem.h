#ifndef LIB_DIESEL_FILESYSTEM_H
#define LIB_DIESEL_FILESYSTEM_H

#include "platform.h"
#include "types.h"
#include "_export.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef DISTRO_WIN32


#define _NORMALIZE_FILE_PATH(path)                   \
    do {                                            \
        char* __p = (path);                         \
        while (*__p) {                              \
            if (*__p == '/') *__p = '\\';           \
            ++__p;                                  \
        }                                           \
    } while (0)
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define _NORMALIZE_FILE_PATH(path)                   \
    do {                                            \
        char* __p = (path);                         \
        while (*__p) {                              \
            if (*__p == '\\') *__p = '/';           \
            ++__p;                                  \
        }                                           \
    } while (0)
#endif

DIESEL_API FILE* open_file(string_t path, bool read, bool write, bool append, bool create_if_not_exist);

DIESEL_API void close_file(FILE* file_handle);

DIESEL_API string_t read_file_into_string_buffer(FILE* file_handle, char* buffer, size_t buffer_size);


#endif // LIB_DIESEL_FILESYSTEM_H
