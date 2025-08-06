#ifndef LIB_DIESEL_TYPES_H
#define LIB_DIESEL_TYPES_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// ASCII string type
typedef const char* string_t;

// UTF-16 or UTF-32 string type (platform/compiler-dependent)
typedef const wchar_t* wstring_t;

// Generic error type
typedef struct {
    string_t error_msg;   // Detailed error message
    string_t error_name;  // Symbolic error name (e.g., "EINVAL")
    string_t obj_name;    // Causing object/function name
} error_t;

// Kind tags for union
typedef enum {
    VALUE_NONE,
    VALUE_BOOL,
    VALUE_CHAR,
    VALUE_INT,
    VALUE_UINT,
    VALUE_FLOAT,
    VALUE_STRING,
    VALUE_WSTRING,
    VALUE_VOID_PTR,
    VALUE_CHAR_PTR,
    VALUE_INT_PTR,
    VALUE_FLOAT_PTR,
    VALUE_CUSTOM_PTR,
    VALUE_ERROR
} value_kind_t;

// Generic tagged value container
typedef struct {
    value_kind_t kind;
    union {
        bool        b;    // Boolean
        char        c;    // Character
        int64_t     i;    // Signed integer
        uint64_t    u;    // Unsigned integer
        double      f;    // Floating-point number
        string_t    s;    // ASCII string
        wstring_t   ws;   // Wide string
        void*       ptr;  // Void pointer
        char*       cptr; // Char pointer
        int64_t*    iptr; // Integer pointer
        double*     fptr; // Float pointer
        void*       custom_ptr; // User-defined pointer
        error_t     e;    // Error object
    };
} value_t;

#endif // LIB_DIESEL_TYPES_H
