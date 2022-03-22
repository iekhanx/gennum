/*
 * ========================================================================
 *
 *       Filename:  CursorImpl.cpp
 *
 *    Description:  CursorImpl class implementation 
 *
 *        Version:  1.0
 *        Created:  29/01/22 15:55:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CursorImpl.hpp"
#include "Display.hpp"

#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/Xcursor/Xcursor.h>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <cstdint>

namespace xwc
{
namespace priv
{

////////////////////////////////////////////////////////////
CursorImpl::CursorImpl() :
m_display(OpenDisplay()),
m_cursor(None)
{
    // That's it.
}


////////////////////////////////////////////////////////////
CursorImpl::~CursorImpl()
{
    release();

    CloseDisplay(m_display);
}


////////////////////////////////////////////////////////////
bool CursorImpl::loadFromPixels(const uint8_t* pixels, Vector2u size, 
                                                     Vector2u hotspot)
{
    release();

    if (isColorCursorSupported())
        return loadFromPixelsARGB(pixels, size, hotspot);
    else
        return loadFromPixelsMonochrome(pixels, size, hotspot);
}


////////////////////////////////////////////////////////////
bool CursorImpl::loadFromPixelsARGB(const uint8_t* pixels, 
                    Vector2u size, Vector2u hotspot)
{
    // Create cursor image, convert from RGBA to ARGB.
    XcursorImage* cursorImage = XcursorImageCreate(static_cast<int>(size.x), 
                                                   static_cast<int>(size.y));
    cursorImage->xhot = hotspot.x;
    cursorImage->yhot = hotspot.y;

    const std::size_t numPixels = size.x * size.y;
    for (std::size_t pixelIndex = 0; pixelIndex < numPixels; ++pixelIndex)
    {
        cursorImage->pixels[pixelIndex] = 
            static_cast<uint8_t>(pixels[pixelIndex * 4 + 2] +
                      (pixels[pixelIndex * 4 + 1] << 8) +
                      (pixels[pixelIndex * 4 + 0] << 16) +
                      (pixels[pixelIndex * 4 + 3] << 24));
    }

    // Create the cursor.
    m_cursor = XcursorImageLoadCursor(m_display, cursorImage);

    // Free the resources
    XcursorImageDestroy(cursorImage);

    // We assume everything went fine...
    return true;
}


////////////////////////////////////////////////////////////
bool CursorImpl::loadFromPixelsMonochrome(const uint8_t* pixels, 
                Vector2u size, Vector2u hotspot)
{
    // Convert the image into a bitmap (monochrome!).
    // The bit data is stored packed into bytes. If the number of 
    // pixels on each row of the image
    // does not fit exactly into (width/8) bytes, one extra byte 
    // is allocated at the end of each
    // row to store the extra pixels.
    std::size_t packedWidth = (size.x + 7) / 8;
    std::size_t bytes = packedWidth * size.y;
    std::vector<uint8_t> mask(bytes, 0); 
    // Defines which pixel is opaque (1) or transparent (0).
    std::vector<uint8_t> data(bytes, 0); 
    // Defines which pixel is white (1) or black (0).

    for (std::size_t j = 0; j < size.y; ++j)
    {
        for (std::size_t i = 0; i < size.x; ++i)
        {
            std::size_t pixelIndex = i + j * size.x;
            std::size_t byteIndex  = i / 8 + j * packedWidth;
            std::size_t bitIndex   = i % 8;

            // Turn on pixel that are not transparent
            uint8_t opacity = pixels[pixelIndex * 4 + 3] > 0 ? 1 : 0;
            mask[byteIndex] |= static_cast<uint8_t>(opacity << bitIndex);

            // Choose between black/background & white/foreground 
            // color for each pixel,
            // based on the pixel color intensity: on average, 
            // if a channel is "active"
            // at 50%, the bit is white.
            int intensity = (pixels[pixelIndex * 4 + 0] + 
                    pixels[pixelIndex * 4 + 1] + 
                    pixels[pixelIndex * 4 + 2]) / 3;
            uint8_t bit = intensity > 128 ? 1 : 0;
            data[byteIndex] |= static_cast<uint8_t>(bit << bitIndex);
        }
    }

    Pixmap maskPixmap = XCreateBitmapFromData(m_display, 
            XDefaultRootWindow(m_display),
            reinterpret_cast<char*>(mask.data()), size.x, size.y);
    Pixmap dataPixmap = XCreateBitmapFromData(m_display, 
            XDefaultRootWindow(m_display),
            reinterpret_cast<char*>(data.data()), size.x, size.y);

    // Define the foreground color as white and the background as black.
    XColor fg, bg;
    fg.red   = 0xFFFF;
    fg.blue  = 0xFFFF;
    fg.green = 0xFFFF;
    bg.red   = 0x0000;
    bg.blue  = 0x0000;
    bg.green = 0x0000;

    // Create the monochrome cursor.
    m_cursor = XCreatePixmapCursor(m_display,
                                   dataPixmap, maskPixmap,
                                   &fg, &bg,
                                   hotspot.x, hotspot.y);

    // Free the resources
    XFreePixmap(m_display, dataPixmap);
    XFreePixmap(m_display, maskPixmap);

    // We assume everything went fine...
    return true;
}


////////////////////////////////////////////////////////////
bool CursorImpl::loadFromSystem(Cursor::Type type)
{
    release();

    unsigned int shape;
    switch (type)
    {
        default: return false;

        case Cursor::Arrow:           shape = XC_arrow;               break;
        case Cursor::Wait:            shape = XC_watch;               break;
        case Cursor::Text:            shape = XC_xterm;               break;
        case Cursor::Hand:            shape = XC_hand1;               break;
        case Cursor::SizeHorizontal:  shape = XC_sb_h_double_arrow;   break;
        case Cursor::SizeVertical:    shape = XC_sb_v_double_arrow;   break;
        case Cursor::SizeLeft:        shape = XC_left_side;           break;
        case Cursor::SizeRight:       shape = XC_right_side;          break;
        case Cursor::SizeTop:         shape = XC_top_side;            break;
        case Cursor::SizeBottom:      shape = XC_bottom_side;         break;
        case Cursor::SizeTopLeft:     shape = XC_top_left_corner;     break;
        case Cursor::SizeBottomRight: shape = XC_bottom_right_corner; break;
        case Cursor::SizeBottomLeft:  shape = XC_bottom_left_corner;  break;
        case Cursor::SizeTopRight:    shape = XC_top_right_corner;    break;
        case Cursor::SizeAll:         shape = XC_fleur;               break;
        case Cursor::Cross:           shape = XC_crosshair;           break;
        case Cursor::Help:            shape = XC_question_arrow;      break;
        case Cursor::NotAllowed:      shape = XC_X_cursor;            break;
    }

    m_cursor = XCreateFontCursor(m_display, shape);
    return true;
}


////////////////////////////////////////////////////////////
bool CursorImpl::isColorCursorSupported()
{
    return XcursorSupportsARGB(m_display);
}


////////////////////////////////////////////////////////////
void CursorImpl::release()
{
    if (m_cursor != None)
    {
        XFreeCursor(m_display, m_cursor);
        m_cursor = None;
    }
}


} // namespace priv

} // namespace xwc


