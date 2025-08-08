#ifndef LIB_DIESEL_DEBUG_H
#define LIB_DIESEL_DEBUG_H
#include "platform.h"
#include "_export.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(DISTRO_WIN32)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define DEBUG_BREAK() __builtin_trap()
#else
    #include <signal.h>
    #define DEBUG_BREAK() raise(SIGTRAP)
#endif

#define DEBUG_CRASH(msg) do { \
    log_error(msg);        \
    print_stacktrace();    \
    DEBUG_BREAK();      \
} while (0)

DIESEL_API void print_stacktrace();


typedef enum {
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
} log_level_t;

/**
 * @brief Set an optional log file handle.
 * If NULL, logs will only go to stdout/stderr.
 */
DIESEL_API void set_log_file(FILE *fp);

/**
 * @brief Set the minimum log level (messages below this are ignored).
 */
DIESEL_API void set_log_level(log_level_t level);

DIESEL_API void log_error(string_t msg);
DIESEL_API void log_warn(string_t msg);
DIESEL_API void log_info(string_t msg);
DIESEL_API void log_debug(string_t msg);



#endif