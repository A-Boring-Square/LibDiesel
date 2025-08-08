#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



static FILE *log_file_handle = NULL;
static log_level_t min_log_level = LOG_DEBUG; // default: show all

// ======================== STACK TRACE ========================
#if defined(DISTRO_WIN32)  // ----- Windows -----
    #include <windows.h>
    #include <dbghelp.h>
    #pragma comment(lib, "dbghelp.lib")

    DIESEL_API void print_stacktrace() {
        void *stack[64];
        HANDLE process = GetCurrentProcess();
        SymInitialize(process, NULL, TRUE);

        USHORT frames = CaptureStackBackTrace(0, 64, stack, NULL);
        SYMBOL_INFO *symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + 256);
        if (!symbol) {
            fprintf(stderr, "Failed to allocate symbol buffer\n");
            return;
        }

        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

        fprintf(stderr, "Stack trace (%u frames):\n", frames);
        for (USHORT i = 0; i < frames; i++) {
            SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
            fprintf(stderr, "  %u: %s - 0x%0llX\n", i, symbol->Name, symbol->Address);
        }

        free(symbol);
    }

#elif defined(PLAT_LINUX) || defined(PLAT_BSD) || defined(PLAT_DARWIN) || defined(DISTRO_CYGWIN)  // ----- Unix-like -----
    #include <execinfo.h>

    DIESEL_API void print_stacktrace() {
        void *buffer[64];
        int nptrs = backtrace(buffer, 64);
        char **symbols = backtrace_symbols(buffer, nptrs);

        if (!symbols) {
            perror("backtrace_symbols");
            return;
        }

        fprintf(stderr, "Stack trace (%d frames):\n", nptrs);
        for (int i = 0; i < nptrs; i++) {
            fprintf(stderr, "  %s\n", symbols[i]);
        }
        free(symbols);
    }

#else  // ----- Unsupported -----
    DIESEL_API void print_stacktrace() {
        fprintf(stderr, "Stack trace printing is not supported on this platform.\n");
    }
#endif

// ======================== LOGGING ========================
static void log_message(log_level_t level, string_t msg) {
    if (level > min_log_level) return;

    const char *level_str[] = { "ERROR", "WARN", "INFO", "DEBUG" };
    FILE *out = log_file_handle ? log_file_handle : stderr;

    fprintf(out, "[%s] %s\n", level_str[level], msg);
    fflush(out);
}

// Public api
DIESEL_API void log_error(string_t msg) { log_message(LOG_ERROR, msg); }
DIESEL_API void log_warn(string_t msg)  { log_message(LOG_WARN,  msg); }
DIESEL_API void log_info(string_t msg)  { log_message(LOG_INFO,  msg); }
DIESEL_API void log_debug(string_t msg) { log_message(LOG_DEBUG, msg); }

DIESEL_API void set_log_level(log_level_t level) { min_log_level = level; }
DIESEL_API void set_log_file(FILE *f) { log_file_handle = f; }

