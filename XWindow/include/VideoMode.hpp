/*
 * ==========================================================================
 *
 *       Filename:  VideMode.hpp
 *
 *    Description:  VideoMode class definition file 
 *
 *        Version:  1.0
 *        Created:  11/01/22 21:31:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _VIDEOMODE_HPP_
#define _VIDEOMODE_HPP_

//////////////////////////////////
// Headers
//////////////////////////////////
#include <vector>

namespace xwc
{
    class VideoMode
    {
        public:
            ////////////////////
            // \brief Default constructor
            //
            // This constructor initialize all members to 0
            ////////////////////
            VideoMode ();

            ///////////////////
            // \brief Constructor the vidwo mode with attributes
            //
            // \param modeWidth   width in pixels
            // \param modeHeight  height in pixels
            // \param modeBitsperPixel   pixels depth in bits per pixels
            //////////////////
            VideoMode (unsigned int modeWidth, unsigned int modeHeight, 
                       unsigned int BitsPerPixels = 32);

            ////////////////
            // \brief Get the current desktop video mode
            //
            // \return Current desktop video nmode
            ////////////////
            static VideoMode getDesktopMode ();
            
            ////////////////////////////
            // \brief Retrive all the video mode supported in fullscreen mode
            //
            // when creating a fullscreen window. the vide mode is restricted
            // to be compatible with what the graphic driver and monitor
            // support. This function return the complete list of all video
            // modes that can be used in fullscreen mode.
            // The return array sorted from best to worst, so that the first
            // element will always give the best mode (hight width, height
            // and bits-per-pixels)
            //
            // \return Array containing all the supported fullscreen modes
            ////////////////////////
            static const std::vector<VideoMode> & getFullscreenModes ();

            ///////////////////////
            // \brief Tell whther or not the video mode is valid
            //
            // The validity of video modes is only relevant when using
            // fullscreen window; otherwise any video mode can be used
            // with no restriction.
            //
            // \return True if the video mode is valid for fullscreen mode
            /////////////////////////
            bool isValid () const;

            ////////////////////////
            // \Member data
            ////////////////////////
            unsigned int width;        //< Video mode width in pixels
            unsigned int height;       //<  
            unsigned int bitsPerPixel; //<
    };

    /////////////////////
    // \brie VideoMode overload of == operator to compare two video modes
    //
    // \param left  Left operand 
    // \param right Right operand
    //
    // \return True  if mode are equal
    ///////////////////
      bool operator == (const VideoMode& left, const VideoMode& right);

    ////////////////////////
    // \brief Overload of != operator to compare two video modes
    //
    // \param left  Left
    // \param right Right
    //
    // \return  True if modes are diffrent
    /////////////////////
     bool operator != (const VideoMode& left, const VideoMode& right);

    ///////////////////
    // \brief Overload of < operator to compare video mode
    //
    // \param  left Left
    // \param  right Right operand
    //
    // \return True if \a left is lesser tha \a right
    /////////////////
     bool operator < (const VideoMode& left, const VideoMode& right);

    /////////////////
    // \relates Video Mode
    // \brief Overload > operator to compare video Mode
    //
    // \param  left  Left
    // \param  right Right
    //
    // \return True is \a left is greater than \a right
    ////////////////
     bool operator > (const VideoMode& left, const VideoMode& right);

    ///////////////////////
    // \relates VideoMode
    // \brief Overload of >= operator to compare video mode
    //
    // \param left  Left
    // \param right Right
    //
    // \return True if \a left is greater than or equal to \a right
    ////////////////////
     bool operator >= (const VideoMode& left, const VideoMode& right);

    ////////////////////////
    // \relates VideoMode
    // \brief Overload of <= operator to compare video mode
    //
    // \param left  Left
    // \param right Right
    //
    // \return True if \a left is greater than or equal to right
    /////////////////////
     bool operator <= (const VideoMode& left, const VideoMode& right);
}   // end of namespace xwc

#endif  
/* ----------------------- Eof VideoMode.hpp --------------------*/

////////////////////////////////////////////////////////////
/// \class xwc::VideoMode
/// \ingroup window
///
/// A video mode is defined by a width and a height (in pixels)
/// and a depth (in bits per pixel). Video modes are used to
/// setup windows (xwc::Window) at creation time.
///
/// The main usage of video modes is for fullscreen mode:
/// indeed you must use one of the valid video modes
/// allowed by the OS (which are defined by what the monitor
/// and the graphics card support), otherwise your window
/// creation will just fail.
///
/// xwc::VideoMode provides a static function for retrieving
/// the list of all the video modes supported by the system:
/// getFullscreenModes().
///
/// A custom video mode can also be checked directly for
/// fullscreen compatibility with its isValid() function.
///
/// Additionally, xwc::VideoMode provides a static function
/// to get the mode currently used by the desktop: getDesktopMode().
/// This allows to build windows with the same size or pixel
/// depth as the current resolution.
///
/// Usage example:
/// \code
/// // Display the list of all the video modes available for fullscreen
/// std::vector<xwc::VideoMode> modes = xwc::VideoMode::getFullscreenModes();
/// for (std::size_t i = 0; i < modes.size(); ++i)
/// {
///     xwc::VideoMode mode = modes[i];
///     std::cout << "Mode #" << i << ": "
///               << mode.width << "x" << mode.height << " - "
///               << mode.bitsPerPixel << " bpp" << std::endl;
/// }
///
/// // Create a window with the same pixel depth as the desktop
/// xwc::VideoMode desktop = xwc::VideoMode::getDesktopMode();
/// window.create(xwc::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML window");
/// \endcode
///
////////////////////////////////////////////////////////////
