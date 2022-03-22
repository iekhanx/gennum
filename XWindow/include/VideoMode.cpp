/*
 * ========================================================================
 *
 *       Filename:  VideoMode.cpp
 *
 *    Description:  
 *                 \class sf::VideoMode
 *
 *                  \ingroup window
 *                  
 *                  A video mode is defined by a width and a height (in pixels)
 *                   and a depth (in bits per pixel). Video modes are used to
 *                   setup windows (sf::Window) at creation time.
 *                   
 *                   The main usage of video modes is for fullscreen mode:
 *                      indeed you must use one of the valid video modes
 *                      allowed by the OS (which are defined by what the monitor
 *                      and the graphics card support), otherwise your window
 *                      creation will just fail.
 *                      
 *                       sf::VideoMode provides a static function for 
 *                       retrieving
 *                       the list of all the video modes supported by 
 *                       the system:
 *                       getFullscreenModes().
 *
 *                        A custom video mode can also be checked directly 
 *                        for fullscreen compatibility with its isValid() 
 *                        function.
 *                        Additionally, sf::VideoMode provides a static 
 *                        function to get the mode currently used by the 
 *                        desktop: getDesktopMode().
 *                        This allows to build windows with the same size or 
 *                        pixel depth as the current resolution.
 *                  Usage example:
 *
 *                   \code
 *                    Display the list of all the video modes available 
 *                    for fullscreen
 *
 *                    std::vector<sf::VideoMode> modes = 
 *                         xwc::VideoMode::getFullscreenModes();
 *
 *                     for (std::size_t i = 0; i < modes.size(); ++i)
 *                      { 
 *                          xwc::VideoMode mode = modes[i];
 *                          std::cout << "Mode #" << i << ": "
 *                          << mode.width << "x" << mode.height << " - "
 *                          << mode.bitsPerPixel << " bpp" << std::endl;
 *                      }
 *                      
 *                      Create a window with the same pixel depth as 
 *                      the desktop
 *
 *                      xwc::VideoMode desktop = xwc::VideoMode::
 *                         getDesktopMode();
 *
 *                      window.create(xwc::VideoMode(1024, 768, 
 *                          desktop.bitsPerPixel), "XWC window");
 *
 *                      \endcode
 *
 *
 *        Version:  1.0
 *        Created:  14/01/22 13:38:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
 /////////////////////////////////
 // Headers
 /////////////////////////////////
#include "VideoMode.hpp"
#include "VideoModeImpl.hpp"
#include <algorithm>
#include <functional>

namespace xwc
{
    VideoMode::VideoMode () :
        width       (0),
        height      (0),
        bitsPerPixel(0)
    {
    }

    VideoMode::VideoMode (unsigned int modeWidth, unsigned int modeHeight,
                            unsigned int modeBitsPerPixel) :
        width           (modeWidth),
        height          (modeHeight),
        bitsPerPixel    (modeBitsPerPixel)
        {
        }

    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  VideoMode VideoMode::getDesktopMode ()
     *  Description:  
     * ===================================================================
     */
    VideoMode VideoMode::getDesktopMode ()
    {
            return priv::VideoModeImpl::getDesktopMode ();
    }/*  end of function VideoMode VideoMode::getDesktopMode ()  */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  const std::vector<VideoMode>& VideoMode::getFullscreen()
     *  Description:  
     * ===================================================================
     */
     const std::vector<VideoMode>& VideoMode::getFullscreenModes()
     {  
         static std::vector<VideoMode> modes;

         // Populate the array on first call
         if (modes.empty()) {
            modes = priv::VideoModeImpl::getFullscreenModes ();
            std::sort(modes.begin(), modes.end(), std::greater<VideoMode>());
         }
         return modes;
     }/* end of function const std::vector<VideoMode>& ::getFullscreen()*/
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool VideoMode::isValid () const
      *  Description:  
      * ===================================================================
      */
     bool VideoMode::isValid () const
     {  const std::vector<VideoMode>& modes = getFullscreenModes ();
        return std::find(modes.begin(), modes.end(), *this) != modes.end();
     }/*  end of function bool VideoMode::isValid () const  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool operator ==(const VideoMode left, 
      *                                 const VideoMode right)
      *  Description:  
      * ===================================================================
      */
      bool operator ==(const VideoMode& left, const VideoMode& right)
      {
             return (left.width             == right.width)      &&
                    (left.height            == right.height)     &&
                    (left.bitsPerPixel      == right.bitsPerPixel);
      }	/*  end of function bool operator ==()  */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  bool operator !=(const VideoMode left, 
       *                                 const VideoMode right)
       *  Description:  
       * ===================================================================
       */
      bool operator !=(const VideoMode& left, const VideoMode& right)
      {
           return !(left == right);
      }/* end of function bool operator !=()   */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  bool operator < (const VideoMode left, 
       *                                 const VideoMode right)
       *  Description:  
       * ===================================================================
       */
       bool operator < (const VideoMode& left, const VideoMode& right)
       {
           if (left.bitsPerPixel == right.bitsPerPixel) {
               if (left.width  == right.width) {
                   return left.height < right.height;
               } else {
                   return left.width < right.width;
               }
           }else {
               return left.bitsPerPixel < right.bitsPerPixel;
           }
       }/*  end of function bool operator < ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool operator > (const VideoMode left, 
        *                                 const VideoMode right)
        *  Description:  
        * ===================================================================
        */
       bool operator > (const VideoMode& left, const VideoMode& right)
       {
               return right < left;
       }/* end of function bool operator > ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool operator <= (const VideoMode left, 
        *                                  const VideoMode right)
        *  Description:  
        * ===================================================================
        */
       bool operator <= (const VideoMode& left, const VideoMode& right)
       {
               return !(right < left);
       }/*  end of function bool operator <= ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  bool operator >= (const VideoMode left, 
        *                                  const VideoMode right)
        *  Description:  
        * ===================================================================
        */
       bool operator >= (const VideoMode& left, const VideoMode& right)
       {
               return !(left < right);
       }/* end of function bool operator >= ()   */
}   // end of namespace xwc 

/* -------------------------- Eof VideoMode.cpp ----------------------*/















