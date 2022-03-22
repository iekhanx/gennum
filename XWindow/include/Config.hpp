/*
 * ==========================================================================
 *
 *       Filename:  Config.hpp
 *
 *    Description:  Global configuration file for OS specific 
 *
 *        Version:  1.0
 *        Created:  27/01/22 16:14:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef OS_CONFIG_HPP
#define OS_CONFIG_HPP


////////////////////////////////////////////////////////////
// Define the SFML version
////////////////////////////////////////////////////////////
#define OS_VERSION_MAJOR 3
#define OS_VERSION_MINOR 0
#define OS_VERSION_PATCH 0
#define OS_VERSION_IS_RELEASE false


////////////////////////////////////////////////////////////
// Identify the operating system
// see https://sourceforge.net/p/predef/wiki/Home/
////////////////////////////////////////////////////////////
#if defined(_WIN32)

    // Windows
    #define OS_SYSTEM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(__APPLE__) && defined(__MACH__)

    // Apple platform, see which one it is
    #include "TargetConditionals.h"

    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

        // iOS
        #define OS_SYSTEM_IOS

    #elif TARGET_OS_MAC

        // MacOS
        #define OS_SYSTEM_MACOS

    #else

        // Unsupported Apple system
        #error This Apple operating system is not supported by SFML library

    #endif

#elif defined(__unix__)

    // UNIX system, see which one it is
    #if defined(__ANDROID__)

        // Android
        #define OS_SYSTEM_ANDROID

    #elif defined(__linux__)

         // Linux
        #define OS_SYSTEM_LINUX

    #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

        // FreeBSD
        #define OS_SYSTEM_FREEBSD

    #elif defined(__OpenBSD__)

        // OpenBSD
        #define OS_SYSTEM_OPENBSD

    #elif defined(__NetBSD__)

        // NetBSD
        #define OS_SYSTEM_NETBSD

    #else

        // Unsupported UNIX system
        #error This UNIX operating system is not supported by SFML library

    #endif

#else

    // Unsupported system
    #error This operating system is not supported by SFML library

#endif


////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

    #define OS_DEBUG

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if !defined(OS_STATIC)

    #if defined(OS_SYSTEM_WINDOWS)

        // Windows compilers need specific (and different) keywords for export and import
        #define OS_API_EXPORT __declspec(dllexport)
        #define OS_API_IMPORT __declspec(dllimport)

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
        #ifdef _MSC_VER

            #pragma warning(disable: 4251)

        #endif

    #else // Linux, FreeBSD, Mac OS X

        #if __GNUC__ >= 4

            // GCC 4 has special keywords for showing/hidding symbols,
            // the same keyword is used for both importing and exporting
            #define OS_API_EXPORT __attribute__ ((__visibility__ ("default")))
            #define OS_API_IMPORT __attribute__ ((__visibility__ ("default")))

        #else

            // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
            #define OS_API_EXPORT
            #define OS_API_IMPORT

        #endif

    #endif

#else

    // Static build doesn't need import/export macros
    #define OS_API_EXPORT
    #define OS_API_IMPORT

#endif


////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
namespace xwc
{
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    using Int8 = signed char;
    using Uint8 = unsigned char;

    // 16 bits integer types
    using Int16 = short;
    using Uint16 = unsigned short;

    // 32 bits integer types
    using Int32 = int;
    using Uint32 = unsigned int;

    // 64 bits integer types
    #if defined(_MSC_VER)
        using Int64 = signed   __int64;
        using Uint64 = unsigned __int64;
    #else
        using Int64 = long long;
        using Uint64 = unsigned long long;
    #endif

} // namespace xwc


#endif // OS_CONFIG_HPP
