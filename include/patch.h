#ifndef LIB_DIESEL_PATCH_H
#define LIB_DIESEL_PATCH_H

#include <stddef.h>
#include "platform.h"
#include "_export.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DISTRO_WIN32)
#include <windows.h>
#endif

/**
 * @struct Patch
 * @brief Represents a dynamically loaded patch/shared library.
 */
typedef struct {
#if defined(_WIN32)
    HMODULE handle;      /**< Handle to the loaded DLL (Windows) */
#else
    void *handle;        /**< Handle to the loaded shared library (Unix) */
#endif
    char **symbols;      /**< Array of symbol names requested */
    void **funcs;        /**< Array of function pointers corresponding to symbols */
    size_t count;        /**< Number of symbols/functions */
} Patch;


#ifndef PATCH_FOLDER
/**
 * @brief Default folder to load patches from.
 * Empty string "" means use current working directory.
 */
#define PATCH_FOLDER ""
#endif

/**
 * @brief Load a single shared library (patch) and fetch user-defined symbols.
 *
 * @param path Path to the shared library file (.dll on Windows, .so on Unix)
 * @param symbol_names Array of symbol names to fetch
 * @param symbol_count Number of symbols in symbol_names
 * @return A Patch struct containing the loaded library and function pointers
 */
DIESEL_API Patch load_patch(const char *path, const char **symbol_names, size_t symbol_count, allocator_t *alloc);


/**
 * @brief Unload a previously loaded patch and free its resources.
 *
 * @param p Pointer to the Patch struct to unload
 */
DIESEL_API void unload_patch(Patch *p, allocator_t *alloc);

/**
 * @brief Load all shared libraries from the patch folder.
 *
 * This scans the folder (PATCH_FOLDER or current working directory if empty)
 * for all shared libraries and loads them with the specified symbols.
 *
 * @param symbol_names Array of symbol names to fetch from each library
 * @param symbol_count Number of symbols in symbol_names
 * @param out_count Pointer to size_t to store the number of loaded patches
 * @return Dynamically allocated array of Patch structs
 */
DIESEL_API Patch* load_all_patches(const char **symbol_names, size_t symbol_count, size_t *out_count, allocator_t *alloc);

#ifdef __cplusplus
}
#endif

#endif // LIB_DIESEL_PATCH_H
