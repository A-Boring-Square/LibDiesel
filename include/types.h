#ifndef LIB_DIESEL_TYPES_H
#define LIB_DIESEL_TYPES_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief ASCII string type.
 * Null-terminated UTF-8 encoded string.
 */
typedef const char* string_t;

/**
 * @brief Wide string type.
 * UTF-16 or UTF-32 encoded string, depending on platform/compiler.
 */
typedef const wchar_t* wstring_t;

/**
 * @brief Generic error type for reporting errors with context.
 */
typedef struct {
    string_t error_msg;   ///< Detailed error message describing the error.
    string_t error_name;  ///< Symbolic error name (e.g., "EINVAL").
    string_t obj_name;    ///< Name of the causing object or function.
} error_t;

/**
 * @brief Enumeration of value kinds for tagged union.
 * Used to identify the type stored in a `value_t`.
 */
typedef enum {
    VALUE_NONE,        ///< No value.
    VALUE_BOOL,        ///< Boolean value.
    VALUE_CHAR,        ///< Single character.
    VALUE_INT,         ///< Signed 64-bit integer.
    VALUE_UINT,        ///< Unsigned 64-bit integer.
    VALUE_FLOAT,       ///< Double-precision floating point.
    VALUE_STRING,      ///< ASCII string (string_t).
    VALUE_WSTRING,     ///< Wide string (wstring_t).
    VALUE_VOID_PTR,    ///< Generic void pointer.
    VALUE_CHAR_PTR,    ///< Pointer to char.
    VALUE_INT_PTR,     ///< Pointer to int64_t.
    VALUE_FLOAT_PTR,   ///< Pointer to double.
    VALUE_CUSTOM_PTR,  ///< User-defined pointer.
    VALUE_ERROR        ///< Error object (error_t).
} value_kind_t;

/**
 * @brief Generic tagged value container.
 * Holds a value of various types tagged by `kind`.
 */
typedef struct {
    value_kind_t kind;  ///< Type tag indicating the stored value type.
    union {
        bool        b;          ///< Boolean value.
        char        c;          ///< Character value.
        int64_t     i;          ///< Signed integer value.
        uint64_t    u;          ///< Unsigned integer value.
        double      f;          ///< Floating-point value.
        string_t    s;          ///< ASCII string.
        wstring_t   ws;         ///< Wide string.
        void*       ptr;        ///< Void pointer.
        char*       cptr;       ///< Char pointer.
        int64_t*    iptr;       ///< Integer pointer.
        double*     fptr;       ///< Float pointer.
        void*       custom_ptr; ///< User-defined pointer.
        error_t     e;          ///< Error object.
    };
} value_t;

#endif // LIB_DIESEL_TYPES_H
