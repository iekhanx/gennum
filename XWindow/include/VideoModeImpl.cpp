/*
 * ========================================================================
 *
 *       Filename:  VideoModeImpl.cpp
 *
 *    Description:  VideoModeImpl definition proc 
 *
 *        Version:  1.0
 *        Created:  14/01/22 14:30:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////////////////////
// Headers
//////////////////////////////////////
#include "VideoModeImpl.hpp"
#include "Display.hpp"
#include "Err.hpp"
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <algorithm>

namespace xwc
{
    namespace priv
    {
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  std::vector<VideoMode> VideoMode::getFullscreenModes()
         *  Description:  
         * ===================================================================
         */
         std::vector<VideoMode> VideoModeImpl::getFullscreenModes ()
         {
            std::vector <VideoMode> modes;

            // Open a connection to X server
            Display *dpy = OpenDisplay ();
            if (dpy) {
                
                // retrieve the default screen number
                int scrn = DefaultScreen (dpy);
                // Check the Xrandr extension is present
                int version;
                if (XQueryExtension (dpy, "RANDR", &version, &version,
                                        &version)) {
                    // Get the current configuration of display
                    XRRScreenConfiguration *config = 
                            XRRGetScreenInfo (dpy, RootWindow (dpy, scrn));
                    if (config) {
                        // Get the list of available screen sizes
                        int nbSizes;
                        XRRScreenSize * sizes = 
                                XRRConfigSizes (config, &nbSizes);
                        if (sizes && (nbSizes > 0)) {
                            // Get the list of supported depths
                            int nbDepths = 0;
                            int *depths = XListDepths (dpy, scrn, &nbDepths);
                            if (depths && (nbDepths > 0)) {
                                // Combine depths n sizes to fill the array
                                // of supported mode
                                for (int i=0; i<nbDepths; ++i) {
                                    for (int j=0; j<nbSizes; ++j) {
                                        // Convert to Video mode
                                        VideoMode mode (static_cast
                                          <unsigned int>(sizes[j].width),
                                          static_cast <unsigned int>
                                          (sizes[j].height),
                                          static_cast <unsigned int>
                                                (depths[i]));
                                        Rotation curRot;
                                        XRRConfigRotations (config, &curRot);
                                        if (curRot == RR_Rotate_90 ||
                                                curRot == RR_Rotate_270)
                                            std::swap(mode.width, mode.height);
                                        // Add it only if it is not already in 
                                        // array
                                        if (std::find (modes.begin(),
                                                       modes.end(), mode) ==
                                                modes.end())
                                            modes.push_back(mode);
                                    }
                                } // Free the array of depths
                                XFree (depths);
                            }
                        } // Free the configuration instance
                        XRRFreeScreenConfigInfo (config);
                    } else {
                        // Failed to get the screen configuration
                        err () << "Failed to retrieve screen configuration"
                               << std::endl;
                    }
                } else {
                    // XRandr exenstion is NOT supported videomode not availabl
                    err () << "Failed to use XRandR extension.NOT available"
                           << std::endl;
                }
                // Close the connection to X server
                CloseDisplay (dpy);
            } else {
                // We couldn't connect to the X server
                err () << "Failed to connect X server, NO supported Video Mode"
                       << std::endl;
            }
            return modes;
        } /* End of function getVideoMode() */
/* 
* ===  FUNCTION  ====================================================
*         Name:  VideoMode VidoeModeImpl::getDesktopMode ()
*  Description:  
* ===================================================================
*/
VideoMode VideoModeImpl::getDesktopMode ()
{
    VideoMode desktopMode;

    // Open connection to X server
    Display *dpy = OpenDisplay ();
    if (dpy) {
        // Retrieve the default screen number
        int scrn = DefaultScreen (dpy);

        // Check if XRandR extension is present
        int version;
        if (XQueryExtension (dpy, "RANDR", &version, &version, 
                    &version)) {
            // Get the current configuration info
            XRRScreenConfiguration *config = 
                XRRGetScreenInfo (dpy, RootWindow (dpy, scrn));
            if (config) {
                // Get the current video Mode
                Rotation curRot;
                int curMode = XRRConfigCurrentConfiguration (config, &curRot);
                // Get the available  screen sizes
                int nbSizes;
                XRRScreenSize* sizes = XRRConfigSizes (config, &nbSizes);
                if (sizes && (nbSizes >0)) {
                    desktopMode = VideoMode (
                            static_cast<unsigned int>
                            (sizes[curMode].width),
                            static_cast<unsigned int>
                            (sizes[curMode].height),
                            static_cast<unsigned int>
                            (DefaultDepth (dpy, scrn)));
                    Rotation mRot;
                    XRRConfigRotations (config, &mRot);
                    if (mRot == RR_Rotate_90 ||
                            mRot == RR_Rotate_270)
                        std::swap(desktopMode.width, 
                                desktopMode.height);
                }
                // Free the configuration instance
                XRRFreeScreenConfigInfo (config);
            } else {
                // Failed to get the screen configuration
                err () << "Failed to get screen configuration"
                    << std::endl;
            }
        } else {
            // XRandR extension is not supported cannot get videomode
            err () << "Failed to use XRandR extension, no videomode"
                << std::endl;
        }
        // Close the connection to the X server
        CloseDisplay (dpy);
    } else {
        // we couln't open connction to X server
        err () << "Failed to connect X server for videomode"
            << std::endl;
    }
    return desktopMode;
}/*  end of function VideoMode VidoeModeImpl::getDesktopMode ()  */
/////////////////////////////////////////////////////////////////////
} // end of namespace priv
} // end of namespace xwc
/* --------------------- Eof VideModeImpl.cpp --------------------*/
