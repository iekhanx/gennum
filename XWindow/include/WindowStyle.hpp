/*
 * ==========================================================================
 *
 *       Filename:  WindowStyle.hpp
 *
 *    Description: WindowStyle class declaration 
 *
 *        Version:  1.0
 *        Created:  27/01/22 16:30:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _WINDOWSTYLE_HPP
#define _WINDOWSTYLE_HPP


namespace xwc
{
namespace Style
{
    ////////////////////////////////////////////////////////////
    /// \ingroup window
    /// \brief Enumeration of the window styles
    ///
    ////////////////////////////////////////////////////////////
    enum
    {
        //None     = nullptr,   //!< No border / title bar (this flag and all 
                                //!< others are mutually exclusive)
        Titlebar   = 1 << 0, //!< Title bar + fixed border
        Resize     = 1 << 1, //!< Title bar + resizable border + maximize button
        Close      = 1 << 2, //!< Title bar + close button
        Fullscreen = 1 << 3, //!< Fullscreen mode (this flag and all 
                             //!< others are mutually exclusive)

        Default = Titlebar | Resize | Close //!< Default window style
    };
}

} // namespace xwc


#endif // _WINDOWSTYLE_HPP
