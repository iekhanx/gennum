/*
 * ==========================================================================
 *
 *       Filename:  windowImpl.hpp
 *
 *    Description:  Pure virual class for XWindowImpl 
 *
 *        Version:  1.0
 *        Created:  11/01/22 01:03:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _WINDOWIMPL_HPP_
#define _WINDOWIMPL_HPP_

///////////////////////////////
// Headers
//////////////////////////////
#include "String.hpp"
#include "ContextSettings.hpp"
#include "CursorImpl.hpp"
#include "Event.hpp"
#include "Joystick.hpp"
#include "Sensor.hpp"
#include "VideoMode.hpp"
#include "WindowHandle.hpp"
#include <cstdint>
#include <queue>
#include <set>

namespace xwc
{
    namespace priv
    {
        class WindowImpl
        {
            public:
                ///////////////////////////////
                // \brief Create a new Window depending on the current OS
                //
                // \param mode Vieo mode to use
                // \param title Title of the window
                // \param style Window style
                // \param setting Additional setting 
                //
                // \return Pointer to the created window
                ////////////////////////////////
                static WindowImpl* create (VideoMode mode, const String& title,
                                           uint32_t style,
                                           const ContextSettings &setting);

                /////////////////////////////
                // \brief Create new window depend on the current OS
                //
                // \param handle platform-specific handle
                //
                // \return Pointer to the created window
                /////////////////////////////
                static WindowImpl* create (WindowHandle handle);

                /////////////////////////////
                // \brief Destructor
                //
                ////////////////////////////
                virtual ~WindowImpl ();

                ////////////////////////////
                // \brief Return the next window event available
                //
                // If there is no event available, this function call the
                // window internal event procesing function
                //
                // \param event Event to be returned
                // \param block Use true to block the thread until an event
                ////////////////////////////
                bool popEvent (Event &event, bool block);

                ////////////////////////////
                // \brief Get the OS-specific handle of the window
                //
                // \return Handle of the window
                ///////////////////////////
                virtual WindowHandle getSystemHandle () const = 0;

                //////////////////////////
                // \brief get the position of the window
                //
                // \return Position  of the window
                ///////////////////////////
                virtual Vector2i getPosition () const = 0;

                //////////////////////////
                // \brief Change the position of the window
                //
                // \return position new Position
                /////////////////////////
                virtual void setPosition (const Vector2i& position) = 0;

                ////////////////////////
                // \brief Get the client size of the window
                //
                // \retur Size of the window in pixel
                ///////////////////////
                virtual Vector2u getSize () const = 0;

                ///////////////////////
                // \brief Change the size of the rendering region of the win
                //
                // \param size new Size in pixel
                ///////////////////////
                virtual void setSize (const Vector2u& size) = 0;

                ///////////////////////
                // \brief Change title of the window
                //
                // \param title New Title
                //////////////////////
                virtual void setTitle (const String& title) = 0;

                //////////////////////
                // \brief Change the window Icon
                //
                // \param width Icon width in pixels
                // \param height 
                // \param pixel Pointer to the pixel in memory RGBA 32 bits
                /////////////////////
                virtual void setIcon (unsigned int width, unsigned int height,
                                        const uint8_t* pixels) = 0;
                /////////////////////
                // \brief Show or hide the window
                //
                // \param Visible True to show false to hide
                /////////////////////
                virtual void setVisible (bool visible) = 0;

                ///////////////////////
                // \brief show or hide mouse cursor
                //
                // \param visible true to show false to hide
                //////////////////////
                virtual void setMouseCursorVisible (bool visible) = 0;

                //////////////////////
                // \brief Grab or release the mouse cursor n keep it from leavin
                //
                // \param grabbed True to enable, false to disable
                /////////////////////
                virtual void setMouseCursorGrabbed (bool grabbed) = 0;

                /////////////////////////
                // \brief set the displayed cursor to native system cursor
                //
                // \param cursor native system cursor
                /////////////////////////
                virtual void setMouseCursor (const CursorImpl& cursor) = 0;

                ////////////////////////
                // \brief Enable or disable automatic key repeat
                //
                // \param enable True to disable false
                ///////////////////////
                virtual void setKeyRepeatEnabled (bool enable) = 0;

                ////////////////////////
                // \brief Request the current window to active
                //
                ///////////////////////
                virtual void requestFocus () = 0;

                /////////////////////////
                // \brief  Check whether the window has a input focus?
                //
                // \return True if has or false no focus
                ////////////////////////
                virtual bool hasFocus () const = 0;

                //////////////////////////
                // \brief Default constructor
                //////////////////////////
                WindowImpl ();

                //////////////////////////////
                // \brief Push new event int the event queue
                //
                // This function isto be used by derived class, to
                // notify the XWC window that anew event was triggerd
                // by the system
                // 
                // \param event Event to push
                //////////////////////////////
                void pushEvent (const Event& event);

                //////////////////////////////
                // \brief Process incoming event from OS system
                //
                ///////////////////////////////
                virtual void processEvents () = 0;
        }; // end of class definition WindowImpl {}
    }      // end of namespace priv
}          // end of namespace xwc

#endif    // _WINDOWIMPL_HPP
/* ------------------------ End of windowImpl.hpp -------------------*/
