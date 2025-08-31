/*
 * ABOUT:
 *   LibDiesel is a C library designed to provide a more modern and complete
 *   environment for cross-platform, high-performance computing — without
 *   sacrificing access to the low-level internals that C developers rely on.
 *
 * COPYRIGHT:
 *   © A-Boring-Square & contributors, released under the MIT License.
 */

#ifndef LIBDIESEL_H
#define LIBDIESEL_H

/*
--------------------------------------------------------------------------
   VERSION INFORMATION
   Update these numbers whenever LibDiesel is released.
--------------------------------------------------------------------------
*/
#define LIBDIESEL_VERSION_STRING \
    "v" _LIBDIESEL_STRINGIFY(LIBDIESEL_VERSION_MAJOR) "." \
    _LIBDIESEL_STRINGIFY(LIBDIESEL_VERSION_MINOR) "." \
    _LIBDIESEL_STRINGIFY(LIBDIESEL_VERSION_PATCH)

#define LIBDIESEL_VERSION_MAJOR 1
#define LIBDIESEL_VERSION_MINOR 0
#define LIBDIESEL_VERSION_PATCH 0

#define _LIBDIESEL_STRINGIFY(x) #x




/* --------------------------------------------------------------------------
   CONFIGURATION
   Define LIBDIESEL_MIN_BUILD before including this header to exclude
   heavier modules for smaller builds.
-------------------------------------------------------------------------- */

#ifndef LIBDIESEL_MIN_BUILD

/* Full feature set */
#include "debug.h"      /* Core debugging utilities               */
#include "filesystem.h" /* Filesystem manipulation and paths      */
#include "memory.h"     /* Memory allocation, arenas, and pools   */
#include "platform.h"   /* Platform-specific abstractions         */
#include "time.h"       /* High-resolution timing utilities       */
#include "types.h"      /* Fundamental and extended types         */
#include "units.h"      /* Strongly-typed unit conversions        */
#include "threading.h"  /* Cross platform multi-threading         */

#else /* LIBDIESEL_MIN_BUILD */

/* Minimal feature set: just essentials */
#include "types.h"      /* Base type definitions                  */
#include "memory.h"     /* Core memory management                 */
#include "platform.h"   /* Platform-specific abstractions         */
#include "debug.h"      /* Core debugging utilities               */

#endif /* LIBDIESEL_MIN_BUILD */

COMP_MSG("Thank you for choosing LibDiesel!");

#endif /* LIBDIESEL_H */
