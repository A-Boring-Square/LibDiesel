#ifndef LIB_DIESEL_DEBUG_H
#define LIB_DIESEL_DEBUG_H

#include "platform.h"
#include "_export.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Platform-specific macro to trigger a debugger breakpoint.
 * On Windows, calls __debugbreak().
 * On GCC/Clang, uses __builtin_trap().
 * Otherwise, sends SIGTRAP signal to the process.
 */
#if defined(DISTRO_WIN32) || defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define DEBUG_BREAK() __builtin_trap()
#else
    #include <signal.h>
    #define DEBUG_BREAK() raise(SIGTRAP)
#endif

/**
 * @brief Macro to log an error message, print a stacktrace, and then trigger a debug break.
 * This is useful for fatal errors that require immediate debugging intervention.
 * 
 * @param msg The error message to log before breaking.
 */
#define DEBUG_CRASH(msg) do { \
    log_error(msg);           \
    print_stacktrace();       \
    DEBUG_BREAK();            \
} while (0)

/**
 * @brief Print the current call stack to the log output.
 * Implementation is platform dependent and helps trace the source of errors.
 */
DIESEL_API void print_stacktrace();

/**
 * @brief Enumeration of log severity levels.
 * Messages below the set log level will be ignored.
 */
typedef enum {
    LOG_ERROR, ///< Error messages, usually fatal or severe problems.
    LOG_WARN,  ///< Warning messages, non-fatal but notable issues.
    LOG_INFO,  ///< Informational messages about normal operation.
    LOG_DEBUG  ///< Debugging messages with detailed internal state.
} log_level_t;

/**
 * @brief Set an optional file handle to write logs to.
 * If set to NULL, logs will be directed only to stdout or stderr.
 *
 * @param fp Pointer to a FILE stream for logging output.
 */
DIESEL_API void set_log_file(FILE *fp);

/**
 * @brief Set the minimum log level for messages to be output.
 * Messages with a severity below this level will be ignored.
 *
 * @param level The minimum log level to allow.
 */
DIESEL_API void set_log_level(log_level_t level);

/**
 * @brief Log an error-level message.
 *
 * @param msg The message to log.
 */
DIESEL_API void log_error(string_t msg);

/**
 * @brief Log a warning-level message.
 *
 * @param msg The message to log.
 */
DIESEL_API void log_warn(string_t msg);

/**
 * @brief Log an informational message.
 *
 * @param msg The message to log.
 */
DIESEL_API void log_info(string_t msg);

/**
 * @brief Log a debug-level message.
 *
 * @param msg The message to log.
 */
DIESEL_API void log_debug(string_t msg);

#ifdef __cplusplus
}
#endif

#endif
