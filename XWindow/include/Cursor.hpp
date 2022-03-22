/*
 * ==========================================================================
 *
 *       Filename:  Cursor.hpp
 *
 *    Description: Cursor declaration  
 *
 *        Version:  1.0
 *        Created:  14/01/22 16:47:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __CURSOR_HPP__
#define __CURSOR_HPP__
/////////////////////////////////
// Headers
////////////////////////////////
#include "Vector2.hpp"
#include <cstdint>

namespace xwc
{
    namespace priv
    {
        class CursorImpl;
    }
    class Cursor
    {
    public:
        ///////////////////////////////////////
        // \brief Enumeration of the native system cursor types
        //
        // Refer to the following table to determinen which cursor
        // is available on which platform
        //
        // Type                                 | Linux | MacOSX | Windows |
        // ----------------------------------------------------------------|
        // xwc::Cursor::Arrow                   | yes   | yes    | yes     |
        // xwc::Cursor::ArrowWait               | no    | no     | yes     |
        // xwc::Cursor::Wait                    | yes   | no     | yes     |
        // xwc::Cursor::Text                    | yes   | yes    | yes     |
        // xwc::Cursor::Hand                    | yes   | yes    | yes     |
        // xwc::Cursor::SizeHorizontal          | yes   | yes    | yes     |
        // xwc::Cursor::SizeVertical            | yes   | yes    | yes     |
        // xwc::Cursor::SizeTopLeftBottomRight  | no    | yes*   | yes     |
        // xwc::Cursor::SizeBottomLeftTopRight  | no    | yes*   | yes     |
        // xwc::Cursor::SizeLeft                | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeTop                 | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeBottom              | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeTopLeft             | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeTopRight            | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeBottomLeft          | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeBottomRight         | yes   | yes**  | yes**   |
        // xwc::Cursor::SizeAll                 | yes   | no     | yes     |
        // xwc::Cursor::Cross                   | yes   | yes    | yes     |
        // xwc::Cursor::Help                    | yes   | yes*   | yes     |
        // xwc::NotAllowed                      | yes   | yes    | yes     |
        // -----------------------------------------------------------------
        //
        // * The cursor type are undocumented so may not 
        //   be available on all versions, but have been tested on 10.13
        //
        // ** On Windows and macOS, double-headed arrows are used
        ///////////////////////////////////////
        enum Type
        {
            Arrow,                      // Arrow cursor (default)
            ArrowWait,                  // Busy arrow cursor
            Wait,                       // Busy cursor
            Text,                       // I-Beam cursor for text to type
            Hand,                       // Pointing hand cursor
            SizeHorizontal,             // Horizontal double cursor
            SizeVertical,               // Vertical  double cursor
            SizeTopLeftBottomRight,     // Double arrow cursor top left to botm
            SizeBottomLeftToRight,      // Double arrow cursor bottom left to 
            SizeLeft,                   // Left arrow cursor on linux
            SizeRight,                  // Right arrow cursor on linux
            SizeTop,                    // Up arrow on linux
            SizeBottom,                 // Down arrow cursor on linux
            SizeTopLeft,                // Top-Left arrow cursor linux
            SizeBottomRight,            // Bottom-right arrow linux
            SizeBottomLeft,             // Bottom-Left arrow cursor linux
            SizeTopRight,               // Top-Right arrow cursor linux
            SizeAll,                    // SizeHorz SizeVert combination
            Cross,                      // CrossHair cursor
            Help,                       // Help cursor
            NotAllowed                  // Action not allowed cursor
        };
    public:
        ///////////////////////////////
        // \brief Default Constructor
        // This constructor doesn't actually create a cursor; until either
        // loadFromPixel() or loadFromSystem is called then successfully 
        // create a cursor
        /////////////////////////////
        Cursor ();

        ///////////////////////////
        // \brief Destructor default
        ///////////////////////////
        ~Cursor ();

        //////////////////////////
        // \brief Create a cursor with provided image
        //
        // \a pixel must be array of \a width by \a height pixels
        // in 32-bit RGBA format. If not, this will cause undefined behaviour.
        //
        // \warning On Unix platform which do not support colored
        //          cursor, the pixels are mapped into monochrome
        //          bitmap: pixels with an alpha channel to 0 are transformed
        // \param pixels  Array of pixels of the image
        // \param size    Width and height of the image
        // \param hotspot (x,y) location of the hotspot
        // \return true if the cursor was successfully loaded; false otherwise
        ///////////////////////
        [[nodiscard]] bool loadFromPixels (const uint8_t* pixels, 
                                            Vector2u size, Vector2u hotspot);

        /////////////////////
        // \brief Create a native system cursor
        //
        // \param  type Native system cursor type
        // \return true if corresponding cursor is natively supported by OS 
        //         or false otherwise
        ///////////////////
        [[nodiscard]] bool loadFromSystem (Type type);

    private:

        friend class WindowBase;

        /////////////////////
        // \brief Get access to underlaying implementation 
        //
        // \return a reference to the OS specific impl
        ////////////////////
        const priv::CursorImpl& getImpl () const;

        //////////////////////
        // Member data
        //////////////////////
        priv::CursorImpl* m_impl; // Platform specific implementation of cursor
    };
}
#endif     // CUSOR_HPP

////////////////////////////////////////////////////////////
/// \class xwc::Cursor
/// \ingroup window
///
/// \warning Features related to Cursor are not supported on
///          iOS and Android.
///
/// This class abstracts the operating system resources
/// associated with either a native system cursor or a custom
/// cursor.
///
/// After loading the cursor the graphical appearance
/// with either loadFromPixels() or loadFromSystem(), the
/// cursor can be changed with xwc::Window::setMouseCursor().
///
/// The behaviour is undefined if the cursor is destroyed while
/// in use by the window.
///
/// Usage example:
/// \code
/// xwc::Window window;
///
/// // ... create window as usual ...
///
/// xwc::Cursor cursor;
/// if (cursor.loadFromSystem(xwc::Cursor::Hand))
///     window.setMouseCursor(cursor);
/// \endcode
///
/// \see xwc::Window::setMouseCursor
///
////////////////////////////////////////////////////////////


