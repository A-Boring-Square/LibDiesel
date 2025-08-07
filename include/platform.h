#ifndef LIB_DIESEL_PLATFORM_H
#define LIB_DIESEL_PLATFORM_H

// Windows
#if defined(_WIN32) || defined(_WIN64)
    #define PLAT_WINDOWS
    #if defined(__CYGWIN__)
        #define DISTRO_CYGWIN
    #else
        #define DISTRO_WIN32
    #endif

// Linux
#elif defined(__gnu_linux__) || defined(__linux__)
    #define PLAT_LINUX
    #if defined(__ANDROID__)
        #define DISTRO_ANDROID
    #else
        #define DISTRO_LINUX
    #endif

// BSD
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

// macOS / Darwin
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLAT_DARWIN
    #define DISTRO_MACOS

// Solaris / Illumos
#elif defined(__sun) && defined(__SVR4)
    #define PLAT_UNIX
    #define DISTRO_SOLARIS

// Amiga
#elif defined(AMIGA)
    #define PLAT_AMIGA
    #define DISTRO_AMIGA

// Haiku
#elif defined(__HAIKU__)
    #define PLAT_HAIKU
    #define DISTRO_HAIKU

// Unknown
#else
    #error "Unknown platform: please define PLAT and DISTRO for this target"
#endif

#endif // LIB_DIESEL_PLATFORM_H
