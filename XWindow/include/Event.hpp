/*
 * ==========================================================================
 *
 *       Filename:  Event.hpp
 *
 *    Description:  Event class definition 
 *
 *        Version:  1.0
 *        Created:  11/01/22 02:15:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _EVENT_HPP_
#define _EVENT_HPP_
//////////////////////////////////
// Headers include
////////////////////////////////////
#include <cstdint>
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Joystick.hpp"
#include "Sensor.hpp"

namespace xwc
{
    class Event
    {
        public:
            //////////////////////////////////
            // \brief size event parameter 
            //
            //////////////////////////////////
            struct SizeEvent {
                unsigned int width;    // New width in pixels
                unsigned int height;   // New height in pixels
            };

            /////////////////////////////////
            // \brief Keyboard event parameter
            //
            ////////////////////////////////
            struct KeyEvent {
                Keyboard::Key code;  // Code of the key that has pressed
                bool    alt;         // it the Alt key pressed
                bool    control;     // is the control key pressed
                bool    shift;       // is the shift key pressed
                bool    system;      // is the System key pressed
            };

            ///////////////////////////////
            // \brief Text event paramters
            //
            //////////////////////////////
            struct TextEvent {
                uint32_t unicode;     // UTF-32 Unicode value of the character
            };

            ////////////////////////////
            // \brief Mouse move event parameter (MouseMove)
            //
            ///////////////////////////
            struct MouseMoveEvent {
                int x;  //< X position of the mouse pointer
                int y;  //< Y position of the mouse pointer
            };

            /////////////////////////////
            // \brief Mouse button event parameters
            //
            ////////////////////////////
            struct MouseButtonEvent {
                Mouse::Button button;   // Copy of button that has pressed
                int x;                  // X position
                int y;                  // Y Position
            };

            /////////////////////////////////
            // \brief Mouse wheel event parameters
            //
            ///////////////////////////////
            struct MouseWheelScrollEvent {
                Mouse::Wheel  wheel;    // Which wheel pressed
                float   delta;          // Wheel offset up/left  down/right
                int     x;              // X position
                int     y;              // Y position
            };

            ////////////////////////////////
            // \brief Joystick connection event parameters
            //
            ////////////////////////////////
            struct JoystickConnectEvent {
                unsigned int joysticId;     // joystick range id joystick count
            };

            //////////////////////////////
            // \brief Joystick axis move event
            //
            /////////////////////////////
            struct JoystickMoveEvent {
                unsigned int joystickId;    // joystick id
                Joystick::Axis  axis;       // Is joystick move
                float       pos;            // New position
            };

            ///////////////////////////
            // \brief joystick button event
            //
            //////////////////////////
            struct JoystickButtonEvent {
                unsigned int joystickId;    // joystick id
                unsigned int button;        // index of button
            };

            //////////////////////////////
            // \brief Touch event parameters
            //
            ////////////////////////////
            struct TouchEvent {
                unsigned int finger;        // index of finger
                int         x;              // X Pos
                int         y;              // Y pos
            };

            /////////////////////////
            // \brief Sensor event parameter
            //
            /////////////////////////
            struct SensorEvent {
                Sensor::Type  type;     // Type of the sensor
                float   x;              // X Axis
                float   y;              // Y Axis
                float   z;              // Z Axis
            };

            ///////////////////////////
            // \brief Enumeration of the different types of events
            //
            ///////////////////////////
            enum EventType
            {
                Close,              // close or close requested
                Resized,            // resized
                LostFocus,          // lost focus
                GainedFocus,        //
                TextEntered,
                KeyPressed,
                KeyReleased,
                MouseWheelScrolled,
                MouseButtonPressed,
                MouseButtonReleased,
                MouseMove,
                MouseEntered,
                MouseLeft,
                JoystickButtonPressed,
                joystickButtonReleased,
                joystickMoved,
                JoystickConnected,
                JoystickDisconnected,
                TouchBegin,
                TouchMoved,
                TouchEnded,
                SensorChanged,

                Count
            };

            /////////////////////////////////
            // Member data
            /////////////////////////////////
            EventType type;         // Type of the events

            union
            {
                SizeEvent               size;           // size event parameter
                KeyEvent                key;            // Key event
                TextEvent               text;           // Text
                MouseMoveEvent          mouseMove;      // Mouse Move
                MouseButtonEvent        mouseButton;    
                MouseWheelScrollEvent   mouseWheelScroll;
                JoystickMoveEvent       joystickMove;
                JoystickButtonEvent     joystickButton;
                JoystickConnectEvent    joystickConnect;
                TouchEvent              touch;
                SensorEvent             sensor;
            };
    };  // end of class Event
}       // end of xwc namespace
#endif
/* -------------------- Eof Event.hpp ----------------------*/

////////////////////////////////////////////////////////////
/// \class xwc::Event
/// \ingroup window
///
/// xwc::Event holds all the informations about a system event
/// that just happened. Events are retrieved using the
/// xwc::Window::pollEvent and xwc::Window::waitEvent functions.
///
/// A xwc::Event instance contains the type of the event
/// (mouse moved, key pressed, window closed, ...) as well
/// as the details about this particular event. Please note that
/// the event parameters are defined in a union, which means that
/// only the member matching the type of the event will be properly
/// filled; all other members will have undefined values and must not
/// be read if the type of the event doesn't match. For example,
/// if you received a KeyPressed event, then you must read the
/// event.key member, all other members such as event.mouseMove
/// or event.text will have undefined values.
///
/// Usage example:
/// \code
/// xwc::Event event;
/// while (window.pollEvent(event))
/// {
///     // Request for closing the window
///     if (event.type == xwc::Event::Closed)
///         window.close();
///
///     // The escape key was pressed
///     if ((event.type == xwc::Event::KeyPressed) &&
///             (event.key.code == xwc::Keyboard::Escape))
///         window.close();
///
///     // The window was resized
///     if (event.type == xwc::Event::Resized)
///         doSomethingWithTheNewSize(event.size.width, event.size.height);
///
///     // etc ...
/// }
/// \endcode
///
////////////////////////////////////////////////////////////


