#ifndef LIB_DIESEL_PLATFORM_H
#define LIB_DIESEL_PLATFORM_H

/**
 * @file platform.h
 * @brief Detects the target operating system platform and distribution at compile time.
 *
 * This header defines platform-specific macros to enable conditional compilation
 * depending on the OS and environment. It distinguishes major platforms such as
 * Windows, Linux, BSD variants, macOS/Darwin, Solaris, Amiga, Haiku, and others.
 *
 * Macros defined:
 * - PLAT_WINDOWS: Windows OS family
 * - PLAT_LINUX: Linux OS family
 * - PLAT_BSD: BSD variants
 * - PLAT_DARWIN: Apple macOS / Darwin
 * - PLAT_UNIX: Unix System V variants (Solaris)
 * - PLAT_AMIGA: Amiga OS
 * - PLAT_HAIKU: Haiku OS
 *
 * Additionally, distribution-specific macros are defined to differentiate
 * specific environments or distros within these platforms:
 * - DISTRO_WIN32, DISTRO_CYGWIN (Windows)
 * - DISTRO_LINUX, DISTRO_ANDROID (Linux)
 * - DISTRO_FREEBSD, DISTRO_NETBSD, DISTRO_OPENBSD, DISTRO_BSDI, DISTRO_DRAGONFLY (BSD)
 * - DISTRO_MACOS (macOS)
 * - DISTRO_SOLARIS (Solaris)
 * - DISTRO_AMIGA (Amiga)
 * - DISTRO_HAIKU (Haiku)
 *
 * If the platform cannot be determined, a preprocessor error is triggered.
 */



#if defined(__clang__) || defined(__GNUC__)
/**
 * @brief Prints a message to the terminal during compilation (GCC/Clang).
 * @param msg The message to print.
 */
    #define COMP_MSG(msg) _Pragma(_LIBDIESEL_STRINGIFY(message msg))

#elif defined(_MSC_VER)
/**
 * @brief Prints a message to the terminal during compilation (MSVC).
 * @param msg The message to print.
 */
    #define COMP_MSG(msg) __pragma(message(msg))

#else
/**
 * @brief Fallback when compiler message pragmas aren't supported.
 * @param msg The message to print.
 */
    #define COMP_MSG(msg)
#endif




// Windows platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define PLAT_WINDOWS
    #if defined(__CYGWIN__)
        #define DISTRO_CYGWIN
    #else
        #define DISTRO_WIN32
    #endif

// Linux platform detection
#elif defined(__gnu_linux__) || defined(__linux__)
    #define PLAT_LINUX
    #if defined(__ANDROID__)
        #define DISTRO_ANDROID
    #else
        #define DISTRO_LINUX
    #endif

// BSD variants detection
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #define PLAT_BSD
    #if defined(__FreeBSD__)
        #define DISTRO_FREEBSD
    #elif defined(__NetBSD__)
        #define DISTRO_NETBSD
    #elif defined(__OpenBSD__)
        #define DISTRO_OPENBSD
    #elif defined(__bsdi__)
        #define DISTRO_BSDI
    #elif defined(__DragonFly__)
        #define DISTRO_DRAGONFLY
    #endif

// macOS / Darwin detection
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLAT_DARWIN
    #define DISTRO_MACOS

// Solaris / Illumos detection
#elif defined(__sun) && defined(__SVR4)
    #define PLAT_UNIX
    #define DISTRO_SOLARIS

// Amiga detection
#elif defined(AMIGA)
    #define PLAT_AMIGA
    #define DISTRO_AMIGA

// Haiku detection
#elif defined(__HAIKU__)
    #define PLAT_HAIKU
    #define DISTRO_HAIKU

// Unknown platform fallback
#else
    #error "Unknown platform: please make a pull request and define PLAT and DISTRO for this target"
#endif

#endif // LIB_DIESEL_PLATFORM_H
