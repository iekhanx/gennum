/*
 * ==========================================================================
 *
 *       Filename:  createWindow.hpp
 *
 *    Description:  Hpp file for creating XWindows 
 *
 *        Version:  1.0
 *        Created:  05/01/22 14:20:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */

#ifndef _CREATE_WINDOW_HPP_
#define _CREATE_WINDOW_HPP_

/////////////////////////////////////////////////////////
// Headers
// //////////////////////////////////////////////////////
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <deque>

#include "WindowImpl.hpp"
#include "Event.hpp"
#include "WindowStyle.hpp" // Prevent conflict with macro None from Xlib

namespace xwc
{
namespace priv
{
////////////////////////////////////////////
/// \brief Linux (X11) implementation of Window Impl
///
/////////////////////////////////////////////
class WindowImplX11   :public WindowImpl
    {
    public:
        ////////////////////////////////////
        /// \brief Construct the window implementation from existing control
        ///
        /// \param handle Platform-specific handle of the control
        ///
        ///////////////////////////////////
        WindowImplX11 (WindowHandle handle);

        ///////////////////////////////////
        /// \brief  Create the window implementation
        /// \param mode    Video Mode to use
        /// \param title   Title of Window
        /// \param style   Window style (resizable, fix, or full screen)
        /// \param setting Addtional setting for the underlaying OpenGL  contex
        ///
        ///////////////////////////////////
        WindowImplX11 (VideoMode mode, const String& title, 
                        unsigned long style, const ContextSettings& setting);
        
        ///////////////////////////////////
        /// \brief Destructor
        ///
        ///////////////////////////////////
        ~WindowImplX11 ();
        
        ///////////////////////////////////
        /// \brief Get the OS specific handle of the window
        ///
        /// \return  Handle of the Window
        ///////////////////////////////////
        WindowHandle getSystemHandle () const override;

        ///////////////////////////////////
        /// \brief Change the position of Window
        ///
        /// \param position new position in pixels
        Vector2i getPosition () const override;

        /////////////////////////////////
        /// \brief Change the position of the Window on screen
        /// 
        /// \param position New position of the window
        /////////////////////////////////
        void setPosition (const Vector2i& position) override;

        /////////////////////////////////
        /// \brief Get the client size of window
        /// 
        /// \return  Size of the window in pixel
        /////////////////////////////////
        Vector2u getSize () const override;

        //////////////////////////////////
        /// \brief Change the size of rendering region of the window
        ///
        /// \param Size new size in pixels
        //////////////////////////////////
        void setSize (const Vector2u& size) override;

        //////////////////////////////////
        /// \brief  Change the title of the window
        ///
        /// \param  title new title
        //////////////////////////////////
        void setTitle (const String& title) override;

        /////////////////////////////////
        /// \brief Change the Window's Icon
        ///
        /// \param width    Icon's width in pixels
        /// \param height   Icon's height in pixels
        /// \pixels Pointer to the pixel to the pixel in memory format must be
        ///                 RGBA 32 bits
        ///
        //////////////////////////////////
        void setIcon (unsigned int width, unsigned int height, 
                      const uint8_t* pixels) override;

        //////////////////////////////////
        /// \brief Show or hide the new Window
        ///
        /// \param visible True  to show, false to hide
        ///////////////////////////////////
        void setVisible (bool visible) override;

        //////////////////////////////////
        /// \brief Show or hide the mouse cursor
        /// 
        /// \param visible True to show, false to hide
        //////////////////////////////////
        void setMouseCursorVisible (bool visible) override;

        //////////////////////////////////
        /// \brief Grab or release mouse cursor
        ///
        /// \param grabbed True to enable false to disable
        //////////////////////////////////
        void setMouseCursorGrabbed (bool grabbed) override;

        //////////////////////////////////
        /// \brief set the displayed cursor to native system cursor
        /// 
        /// \param cursor Native system cursor
        //////////////////////////////////
        void setMouseCursor (const CursorImpl& cursor) override;

        //////////////////////////////////
        /// \brief Enable or disable automatic key-repeat
        ///
        /// \param enable True to false disable
        //////////////////////////////////
        void setKeyRepeatEnabled (bool enabled) override;

        /////////////////////////////////
        /// \brief Request the current window to be made active
        /// foreground window
        ///
        ////////////////////////////////
        void requestFocus () override;

        /////////////////////////////////
        /// \brief Check whether the window has the input focus
        ///
        /// \retur True if window has the focus
        /////////////////////////////////
        bool hasFocus () const override;

    protected:
        ////////////////////////////////
        /// \brief Process incoming events from the OS systems
        ///
        ////////////////////////////////
        void processEvents () override;

    private:
        ///////////////////////////////////
        /// \brief Request the WM to make the current window active
        ///
        ///////////////////////////////////
        void grabFocus ();

        ///////////////////////////////////
        /// \brief Set fullscreen video mode
        ///
        /// \param Mode video mode to switch to
        void setVideoMode (const VideoMode& mode);

        /////////////////////////////////////
        /// \brief Rest to desktop video mode
        ///
        /////////////////////////////////////
        void resetVideoMode ();

        /////////////////////////////////////
        /// \brief Switch to full screen mode
        ///
        /////////////////////////////////////
        void switchToFullscreen ();

        //////////////////////////////////////
        /// \brief Set the WM protocols we support
        ///
        ////////////////////////////////////////
        void setProtocols ();

        ///////////////////////////////////////
        /// \brief  Update the last time we received user input
        /// 
        /// \param time last time we received user input
        ///////////////////////////////////////
        void updateLastInputTime (::Time time);

        ///////////////////////////////////////
        /// \brief Do some common initilisation after window created
        ///
        ///////////////////////////////////////
        void initialize ();

        //////////////////////////////////////
        /// \brief Create transparent mouse cursor
        ///
        //////////////////////////////////////
        void createHiddenCursor ();

        //////////////////////////////////////
        /// \brief Cleanup  graphical resource attached to the window
        ///
        //////////////////////////////////////
        void Cleanup ();

        ///////////////////////////////////////
        /// \brief Process an incoming event from window
        ///
        /// \param WindowEvent Event which has been received
        ///
        /// \return True if the event was processed, false if discarded
        ///////////////////////////////////////
        bool processEvent (XEvent& windowEvent);

        ///////////////////////////////////////
        /// \brief Check if a valid version of XRandR extension is present
        ///
        /// \param xRandRMajor XRandR major version
        /// \param xRandRMinor XRandR minor version
        ///
        /// \return True if a valid XRandR version found, false otherwise
        ///////////////////////////////////////
        bool chechXRandR (int &xRandRMajor, int& xRandRMinor);

        ///////////////////////////////////////
        /// \brief Get the RROutput or the primary monitor
        ///
        /// \param rootWindow the root window
        /// \param res screen resources
        /// \param xRandRMajor XRandR major version
        /// \param xRandRMinor XrandR minor version
        ///
        /// \return RROutput of the primary monitor
        /////////////////////////////////////////
        RROutput getOutputPrimary (::Window& rootWindow, 
                                    XRRScreenResources* res,
                                   int xRandRMajor, int xRandRMinor);

        /////////////////////////////////////////
        /// \brief Get coordinate of the primary monitor
        ///
        /// \return Position or the primary monitor
        /////////////////////////////////////////
        Vector2i getPrimaryMonitorPosition ();

        ///////////////////////////////////////////
        /// Members data
        ///////////////////////////////////////////
        ::Window        m_win;          ///< X identifier defining our win
        ::Display       *m_dpy;         ///< Pointer to the display
        int             m_scrn;         ///< Screen Identifier
        XIM             m_inputMethod;  ///< Input Method linked to X display
        XIC             m_inputContext; ///< Input context used to get unicode
        std::deque<XEvent> m_event;     ///< Queue we used to store events
        bool            m_isExternal;   ///< Tell whether created internally
        RRMode          m_oldVideoMode; ///< Video mode to switch fullscreen
        RRCrtc          m_oldRRCrtc;    ///< RRCrtc in use before switch fscrn
        ::Cursor        m_hiddenCursor; ///< X11 cursor hiding
        ::Cursor        m_lastCursor;   ///< Last cursor
        bool            m_keyRepeat;    ///< Is key repeate feature enable?
        Vector2i        m_previousSize; ///< Previous size of the window
        bool            m_useSizeHint;  ///< Is size of Window fixed with Shint?
        bool            m_fullscreen;   ///< Is window full screen?
        bool            m_windowMapped; ///< Has window been mapped by WM?
        Pixmap          m_iconPixmap;   ///< The current icon pixmap if in use?
        Pixmap          m_iconMaskPixmap;//< The current Icon mask pixmap if use
        ::Time          m_lastInputTime;///< Last Input time received user input
    };

}   // end of prev

}   // end of XWidnow_create

#endif
