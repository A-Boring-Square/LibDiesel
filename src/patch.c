#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patch.h"
#include "memory.h"
#include "filesystem.h"

#if !defined(DISTRO_WIN32)
#include <dlfcn.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#endif

/* -------------------------------------------------------------------------- */
/* Cross-platform dynamic library helpers                                      */
/* -------------------------------------------------------------------------- */
void* load_library(const char *path) {
#if defined(_WIN32)
    return (void*)LoadLibraryA(path);
#else
    return dlopen(path, RTLD_NOW);
#endif
}

void* get_symbol(void *handle, const char *name) {
#if defined(_WIN32)
    return (void*)GetProcAddress((HMODULE)handle, name);
#else
    return dlsym(handle, name);
#endif
}

void close_library(void *handle) {
    if (!handle) return;
#if defined(_WIN32)
    FreeLibrary((HMODULE)handle);
#else
    dlclose(handle);
#endif
}

/* -------------------------------------------------------------------------- */
/* Load a single patch                                                         */
/* -------------------------------------------------------------------------- */
DIESEL_API Patch load_patch(const char *path, const char **symbol_names, size_t symbol_count, allocator_t *alloc) {
    alloc = alloc ? alloc : &default_allocator;

    Patch p = {0};
    p.handle = load_library(path);
    if (!p.handle) {
        fprintf(stderr, "Failed to load %s\n", path);
        return p;
    }

    p.symbols = ALLOC(alloc, sizeof(char*) * symbol_count);
    p.funcs   = ALLOC(alloc, sizeof(void*) * symbol_count);
    p.count   = symbol_count;

    for (size_t i = 0; i < symbol_count; i++) {
        p.symbols[i] = REALLOC_STRDUP(alloc, symbol_names[i]);
        p.funcs[i] = get_symbol(p.handle, symbol_names[i]);
        if (!p.funcs[i]) {
            fprintf(stderr, "Symbol %s not found in %s\n", symbol_names[i], path);
        }
    }

    return p;
}

/* -------------------------------------------------------------------------- */
/* Unload a patch and free memory                                              */
/* -------------------------------------------------------------------------- */
DIESEL_API void unload_patch(Patch *p, allocator_t *alloc) {
    if (!p || !p->handle) return;
    alloc = alloc ? alloc : &default_allocator;

    for (size_t i = 0; i < p->count; i++) {
        if (p->symbols[i]) FREE(alloc, p->symbols[i]);
    }
    FREE(alloc, p->symbols);
    FREE(alloc, p->funcs);

    close_library(p->handle);
    p->handle = NULL;
}

/* -------------------------------------------------------------------------- */
/* Load all patches in PATCH_FOLDER                                            */
/* -------------------------------------------------------------------------- */
DIESEL_API Patch* load_all_patches(const char **symbol_names, size_t symbol_count, size_t *out_count, allocator_t *alloc) {
    alloc = alloc ? alloc : &default_allocator;

    size_t capacity = 8;
    size_t n = 0;
    Patch *patches = ALLOC(alloc, sizeof(Patch) * capacity);

#if defined(_WIN32)
    WIN32_FIND_DATAA ffd;
    char search_path[512];
    snprintf(search_path, sizeof(search_path), "%s\\*.dll",
             PATCH_FOLDER[0] != '\0' ? PATCH_FOLDER : ".");
    _NORMALIZE_FILE_PATH(search_path);

    HANDLE hFind = FindFirstFileA(search_path, &ffd);
    if (hFind == INVALID_HANDLE_VALUE) {
        *out_count = 0;
        return patches;
    }
    do {
        if (n >= capacity) {
            capacity *= 2;
            patches = REALLOC(alloc, patches, sizeof(Patch) * (capacity / 2), sizeof(Patch) * capacity);
        }
        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s\\%s",
                 PATCH_FOLDER[0] != '\0' ? PATCH_FOLDER : ".", ffd.cFileName);
        _NORMALIZE_FILE_PATH(fullpath);
        patches[n++] = load_patch(fullpath, symbol_names, symbol_count, alloc);
    } while (FindNextFileA(hFind, &ffd) != 0);
    FindClose(hFind);
#else
    DIR *dir = opendir(PATCH_FOLDER[0] != '\0' ? PATCH_FOLDER : ".");
    if (!dir) {
        *out_count = 0;
        return patches;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (entry->d_type != DT_REG) continue;
        const char *ext = strrchr(entry->d_name, '.');
        if (!ext || strcmp(ext, ".so") != 0) continue;

        if (n >= capacity) {
            capacity *= 2;
            patches = REALLOC(alloc, patches, sizeof(Patch) * (capacity / 2), sizeof(Patch) * capacity);
        }

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s",
                 PATCH_FOLDER[0] != '\0' ? PATCH_FOLDER : ".", entry->d_name);
        patches[n++] = load_patch(fullpath, symbol_names, symbol_count, alloc);
    }

    closedir(dir);
#endif

    *out_count = n;
    return patches;
}
