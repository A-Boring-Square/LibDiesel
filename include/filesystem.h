#ifndef LIB_DIESEL_FILESYSTEM_H
#define LIB_DIESEL_FILESYSTEM_H

#include "platform.h"
#include "types.h"
#include "_export.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef DISTRO_WIN32

/**
 * @brief Normalize a file path by converting all '/' characters to '\\\' on Windows.
 * This macro modifies the input string in place.
 *
 * @param path The file path string to normalize.
 */
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

/**
 * @brief Normalize a file path by converting all '\\' characters to '/' on POSIX systems.
 * This macro modifies the input string in place.
 *
 * @param path The file path string to normalize.
 */
#define _NORMALIZE_FILE_PATH(path)                   \
    do {                                            \
        char* __p = (path);                         \
        while (*__p) {                              \
            if (*__p == '\\') *__p = '/';           \
            ++__p;                                  \
        }                                           \
    } while (0)

#endif

/**
 * @brief Open a file with specified access modes.
 *
 * @param path The path to the file to open.
 * @param read Whether to open for reading.
 * @param write Whether to open for writing.
 * @param append Whether to open in append mode (writes go to end).
 * @param create_if_not_exist Whether to create the file if it does not exist.
 * @return FILE* A file handle on success, or NULL on failure.
 */
DIESEL_API FILE* open_file(string_t path, bool read, bool write, bool append, bool create_if_not_exist);

/**
 * @brief Close an opened file handle.
 *
 * @param file_handle The FILE pointer to close.
 */
DIESEL_API void close_file(FILE* file_handle);

/**
 * @brief Read contents of a file into a provided buffer.
 * Reads up to buffer_size bytes or until EOF.
 *
 * @param file_handle The open FILE pointer to read from.
 * @param buffer The buffer to store read data into.
 * @param buffer_size The maximum number of bytes to read.
 * @return string_t Pointer to the buffer containing file contents.
 */
DIESEL_API string_t read_file_into_string_buffer(FILE* file_handle, char* buffer, size_t buffer_size);

#endif // LIB_DIESEL_FILESYSTEM_H
