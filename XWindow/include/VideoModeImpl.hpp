/*
 * ==========================================================================
 *
 *       Filename:  VideoModeImpl.hpp
 *
 *    Description:  VideoModeImpl declaration
 *    
 *
 *        Version:  1.0
 *        Created:  14/01/22 14:22:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __VIDEOMODEIMPL_HPP_
#define __VIDEOMODEIMPL_HPP_

///////////////////////////////////////
// Headers
///////////////////////////////////////
#include "VideoMode.hpp"

namespace xwc
{
    namespace priv
    {
        /////////////////////////////
        // brief  OS specific implementation of video mode functions
        /////////////////////////////
        
        class VideoModeImpl
        {
            public:
                /////////////////////
                // \brief Get the list of all the supported fullscreen videomode
                //
                // \return Array filled with full screen video modes
                ////////////////////
                static std::vector<VideoMode> getFullscreenModes();

                ///////////////////
                // \brief Get the current desktop video mode
                //
                // \return Current desktop video mode
                ///////////////////
                static VideoMode getDesktopMode ();
        };  // end of class declaration VideoModeImpl
    }  // end of namespace priv
}   // end of namespace xwc    

#endif
/* ----------------- Eof VideoModeImpl.hpp ---------------*/

