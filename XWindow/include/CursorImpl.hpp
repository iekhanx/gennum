/*
 * ==========================================================================
 *
 *       Filename:  CursorImpl.hpp
 *
 *    Description:  CursorImpl class declaration 
 *
 *        Version:  1.0
 *        Created:  29/01/22 15:51:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _CURSORIMPLUNIX_HPP
#define _CURSORIMPLUNIX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include "NonCopyable.hpp"
//#include "WindowStyle.hpp" // Prevent conflict with macro None 
#include "Cursor.hpp"
#include "Vector2.hpp"
#include <X11/Xlib.h>
#include <cstdint>

namespace xwc
{

namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Unix implementation of Cursor
///
////////////////////////////////////////////////////////////
class CursorImpl //: NonCopyable
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Refer to xwc::Cursor::Cursor().
    ///
    ////////////////////////////////////////////////////////////
    CursorImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Refer to xwc::Cursor::~Cursor().
    ///
    ////////////////////////////////////////////////////////////
    ~CursorImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Create a cursor with the provided image
    ///
    /// Refer to xwc::Cursor::loadFromPixels().
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromPixels(const uint8_t* pixels, Vector2u size, Vector2u hotspot);

    ////////////////////////////////////////////////////////////
    /// \brief Create a native system cursor
    ///
    /// Refer to xwc::Cursor::loadFromSystem().
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromSystem(Cursor::Type type);

private:

    friend class WindowImplX11;

    ////////////////////////////////////////////////////////////
    /// \brief Checks if colored cursors are supported for this display.
    ///
    ////////////////////////////////////////////////////////////
    bool isColorCursorSupported();

    ////////////////////////////////////////////////////////////
    /// \brief Create a cursor with the provided image (ARGB support)
    ///
    /// Refer to xwc::Cursor::loadFromPixels().
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromPixelsARGB(const uint8_t* pixels, Vector2u size, 
            Vector2u hotspot);

    ////////////////////////////////////////////////////////////
    /// \brief Create a cursor with the provided image (monochrome)
    ///
    /// Refer to xwc::Cursor::loadFromPixels().
    ///
    ////////////////////////////////////////////////////////////
    bool loadFromPixelsMonochrome(const uint8_t* pixels, Vector2u size, 
            Vector2u hotspot);

    ////////////////////////////////////////////////////////////
    /// \brief Release the cursor, if we have loaded one.
    ///
    ////////////////////////////////////////////////////////////
    void release();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ::Display* m_display;
    ::Cursor   m_cursor;
};

} // namespace priv

} // namespace xwc

#endif // _CUSROSIMPLUNIX_HPP
