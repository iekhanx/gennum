/*
 * ========================================================================
 *
 *       Filename:  WindowHandle.cpp
 *
 *    Description:  WindowHandle class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 16:05:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#ifndef OS_WINDOWHANDLE_HPP
#define OS_WINDOWHANDLE_HPP

#define OS_SYSTEM_LINUX

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Config.hpp"

// Windows' HWND is a type alias for struct HWND__*
#if defined(OS_SYSTEM_WINDOWS)
    struct HWND__;
#endif

namespace xwc
{
#if defined(OS_SYSTEM_WINDOWS)

    // Window handle is HWND (HWND__*) on Windows
    using WindowHandle = HWND__ *;

#elif defined(OS_SYSTEM_LINUX) || defined(OS_SYSTEM_FREEBSD) || defined(OS_SYSTEM_OPENBSD) || defined(OS_SYSTEM_NETBSD)

    // Window handle is Window (unsigned long) on Unix - X11
    using WindowHandle = unsigned long;

#elif defined(OS_SYSTEM_MACOS)

    // Window handle is NSWindow or NSView (void*) on Mac OS X - Cocoa
    using WindowHandle = void*;

#elif defined(OS_SYSTEM_IOS)

    // Window handle is UIWindow (void*) on iOS - UIKit
    using WindowHandle = void*;

#elif defined(OS_SYSTEM_ANDROID)

    // Window handle is ANativeWindow* (void*) on Android
    using WindowHandle = void*;

#elif defined(OS_DOXYGEN)

    // Define type alias symbol so that Doxygen can attach some documentation to it
    using WindowHandle = "platform-specific";

#endif

} // namespace xwc


#endif // OS_WINDOWHANDLE_HPP

////////////////////////////////////////////////////////////
/// \typedef xwc::WindowHandle
/// \ingroup window
///
/// Define a low-level window handle type, specific to
/// each platform.
///
/// Platform        | Type
/// ----------------|------------------------------------------------------------
/// Windows         | \p HWND
/// Linux/FreeBSD   | \p %Window
/// Mac OS X        | either \p NSWindow* or \p NSView*, disguised as \p void*
/// iOS             | \p UIWindow*
/// Android         | \p ANativeWindow*
///
/// \par Mac OS X Specification
///
/// On Mac OS X, a xwc::Window can be created either from an
/// existing \p NSWindow* or an \p NSView*. When the window
/// is created from a window, SFML will use its content view
/// as the OpenGL area. xwc::Window::getSystemHandle() will
/// return the handle that was used to create the window,
/// which is a \p NSWindow* by default.
///
////////////////////////////////////////////////////////////
