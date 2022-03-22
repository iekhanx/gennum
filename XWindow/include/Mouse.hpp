/*
 * ==========================================================================
 *
 *       Filename:  Mouse.hpp
 *
 *    Description:  Mouse class declaration 
 *
 *        Version:  1.0
 *        Created:  15/01/22 01:04:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

///////////////////////////////
// Headers
///////////////////////////////
#include "Vector2.hpp"

namespace xwc
{
    class WindowBase;

    class Mouse
    {
        public:
            
            ////////////////////
            // \brief Mouse buttons
            //
            ///////////////////
            enum Button
            {
                left,                   // < Left mouse button
                Right,                  // < Right mouse button
                Middle,                 // < Middle wheel button
                XButton1,               // < First extra mouse button
                XButton2,               // < Second extra mouse button

                ButtonCount             // < Total number of mouse button
            };

            //////////////////////
            // \brief Mouse wheel
            //////////////////////
            enum Wheel
            {
                VerticalWheel,          // < vertical mouse wheel
                HorizontalWheel         // > Horizontal mouse wheel
            };

            /////////////////////
            // \brief Check if mouse button is pressed
            //
            // \param button Button to check
            // \return True if the button is pressed false otherwise
            /////////////////////
            static bool isButtonPressed (Button button);

            ////////////////////
            // \brief Get the current position of mouse in desktop coord
            // \return Current position of the mouse
            ////////////////////
            static Vector2i getPosition ();

            ////////////////////
            // \brief Get the current position of the mouse in window coord
            // \param relativeTo reference window
            // \return Current position of the mouse
            ////////////////////
            static Vector2i getPosition (const WindowBase& relativeTo);

            //////////////////
            // \brief Set the current position of the mouse desktop coord
            // \param position New position of the mouse
            //////////////////
            static void setPosition (const Vector2i& pos);

            /////////////////
            // \brief set current pos of mouse in window coord
            // \param position New position of mouse in window
            // \param relateTo reference window
            /////////////////
            static void setPosition (const Vector2i& pos, 
                                     const WindowBase& relTo);
    }; // end of class mouse
}   // end of namespace xwc
#endif

////////////////////////////////////////////////////////////
/// \class xwc::Mouse
/// \ingroup window
///
/// xwc::Mouse provides an interface to the state of the
/// mouse. It only contains static functions (a single
/// mouse is assumed), so it's not meant to be instantiated.
///
/// This class allows users to query the mouse state at any
/// time and directly, without having to deal with a window and
/// its events. Compared to the MouseMoved, MouseButtonPressed
/// and MouseButtonReleased events, xwc::Mouse can retrieve the
/// state of the cursor and the buttons at any time
/// (you don't need to store and update a boolean on your side
/// in order to know if a button is pressed or released), and you
/// always get the real state of the mouse, even if it is
/// moved, pressed or released when your window is out of focus
/// and no event is triggered.
///
/// The setPosition and getPosition functions can be used to change
/// or retrieve the current position of the mouse pointer. There are
/// two versions: one that operates in global coordinates (relative
/// to the desktop) and one that operates in window coordinates
/// (relative to a specific window).
///
/// Usage example:
/// \code
/// if (xwc::Mouse::isButtonPressed(xwc::Mouse::Left))
/// {
///     // left click...
/// }
///
/// // get global mouse position
/// xwc::Vector2i position = xwc::Mouse::getPosition();
///
/// // set mouse position relative to a window
/// xwc::Mouse::setPosition(xwc::Vector2i(100, 200), window);
/// \endcode
///
/// \see xwc::Joystick, xwc::Keyboard, xwc::Touch
///
////////////////////////////////////////////////////////////

