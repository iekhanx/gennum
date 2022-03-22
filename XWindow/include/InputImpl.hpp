/*
 * ==========================================================================
 *
 *       Filename:  InputImpl.hpp
 *
 *    Description: Class InputImpl.hpp definition 
 *
 *        Version:  1.0
 *        Created:  11/01/22 10:51:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef __INPUTIMPL_HPP__
#define __INPUTIMPL_HPP__

//////////////////////////////////////
// Headers
///////////////////////////////////////

namespace xwc
{
    namespace priv
    {
        class InputImpl
        {
            public:
                /////////////////////////////////
                // \brief Check if a key is pressed
                //
                // \param key Key to check
                //
                // \return True if the key is pressed, false otherwise
                ////////////////////////////////
                static bool isKeyPressed (Keyboard::Key key);

                //////////////////////////////
                // \brief Show or hide the virtual keyboard
                //
                // \param visible True to show or false to hide
                /////////////////////////////
                static void setVirtualKeyboardVisible (bool visible);

                /////////////////////////
                // \brief Check if mouse button is pressed
                //
                // \param button Button to check
                //
                // \return True if button pressed or false otherwise
                ////////////////////////
                static bool isMouseButtonPressed (Mouse::Button button);

                ///////////////////////
                // \brief Get the current position of mouse in desktop cooord
                //
                // The function return the current position of the mouse
                // cursor, in globle coordinates
                //
                // \return Current position of the mouse
                ////////////////////////
                static Vector2i getMousePosition ();

                ///////////////////////
                // \brief Get the current position of the mouse in window coord
                //
                // This function returns the current position of the mouse
                // cursor, relatives to the given window
                // If no window is used, it return desktop coord
                //
                // \param relativeTo Reference window
                //
                // \return Current position of the mouse
                //////////////////////
                static Vector2i getMousePosition (const WindowBase& relativeTo);

                ///////////////////////
                // \brief Set the current position of the mouse in desktop coord
                //
                // This function set the current position of the mouse
                // cursor in global desktop coordinates
                //
                // \param position New position of mouse
                //////////////////////
                static void setMousePosition (const Vector2i& pos);

                ///////////////////////
                // \brief Set the current position of the mouse in Window coord
                //
                // This function set the current position of the mouse
                // cursor, relatives to given window
                //
                // \param  position New Position
                // \param  relativeTo Reference window
                //////////////////////
                static void setMousePosition (const Vector2i& pos, 
                                              const WindowBase& relativeTo);

                //////////////////////
                // \brief Check if a touch event is currently down?
                //
                // \param Finger finger index
                //
                // \return True if \a finger is currently touching or false
                //////////////////////
                static bool isTouchDown (unsigned int finger);

                /////////////////////////
                // \brief Get the current position of touch in desktop coord
                //
                // This function returns the current touch position
                // in global desktop coord
                //
                // \param finger Finger index
                //
                // \return Current position of \a finger 
                ////////////////////////
                static Vector2i getTouchPosition (unsigned int finger);

                //////////////////////////
                // \brief Get the current position of a touch in window coord
                //
                // This function return the current touch position
                // in global desktop coord
                //
                // \param finger Finger Index
                // \param relativeTo References window
                //
                // \return Current position of \a finger
                /////////////////////////
                static Vector2i getTouchPosition (unsigned int finger,
                                                  const WindowBase& relativeTo);
        };  // end of class InputImpl {}
    }       // end of namespace priv
}           // end of namespace xwc

#endif
/* ---------------------Eof InputImpl.hpp -------------------------*/
