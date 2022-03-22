/*
 * ==========================================================================
 *
 *       Filename:  WindowBase.hpp
 *
 *    Description: Window Base class declaration 
 *
 *        Version:  1.0
 *        Created:  11/01/22 14:11:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _WINDOWBASE_HPP_
#define _WINDOWBASE_HPP_

//////////////////////////////////////
// Headers
//////////////////////////////////////
#include "Vector2.hpp"
#include "WindowImpl.hpp"
#include "WindowStyle.hpp"

namespace xwc
{
    namespace priv
    {
        class WindowImpl;
    }

    class Event;

    /////////////////////////////////
    // \brief Window that serves as a base for other windows
    //
    /////////////////////////////////

    class WindowBase
    {
        public:

            //////////////////////////////
            // \brief Default constructor
            //
            // This constructor doesn't create the window
            // use the other constructor  or call create () to do so
            WindowBase ();

            ////////////////////////////
            // \brief Construct a new Window
            //
            // This constructor create the window with the size and pixel
            // depth defined in  \q mode. An optional style can be passed to
            // customise the look and behavior of the window (border,
            // title bar resizeable, closeable etc) if a style contains
            // Style::Fullscreen, then a mode must be a valid video mode.
            //
            // \param mode Video to use width,height, depth etc
            // \param title for window
            // \param style Window style bitwise or combination
            ///////////////////////////
            WindowBase (VideoMode mode, const String& title, uint32_t style =
                    Style::Default);

            //////////////////////////
            // \brief Construct the window from an existing control
            //
            // \param handle Platform specific handle of the control
            ///////////////////////////
            explicit WindowBase (WindowHandle handle);

            ///////////////////////////
            // \brief Destructor 
            // 
            // Close the window and free all the resources attached to it
            ////////////////////////////
            virtual ~WindowBase ();

            ///////////////////////////
            // \brief Create the window
            //
            // If the window was already created, it close it first
            // If \a style contain Style::Fullscreen, then \a mode
            // must be a valid video mode.
            //
            // \param mode Video mode 
            // \param title for window
            // \param style window style
            ///////////////////////////
            virtual void create (VideoMode mode, const String& title,
                    uint32_t style = Style::Default);

            //////////////////////////
            // \brief Create or recreate the window from an existing control
            //
            // \param handle Platform specific handle
            //////////////////////////
            virtual void create (WindowHandle handle);

            /////////////////////////
            // \brief Close the window and destroy all the attached resources
            //
            // After calling this function the xwc::Window instance reamain
            // valid and your can call create() to recreate the window
            // All other function such as pollEvent or disp;ay *( will
            // still work, You don't have to test isOpen every time
            // and will have no effect on closed windows.
            virtual void close ();

            ////////////////////////
            // \brief Tell whether or not the window is open?
            //
            // This function return whether or not the window exists
            //
            // \return True if the window is open false if it closed
            ///////////////////////
            bool isOpen () const;

            //////////////////////
            // \brief Pop the event on top of the event queue if any?
            //
            // This functioin is not blocking if there is no pending events
            // then it will return false and leave \a event unmodified
            // thus you should always call this function in a loop
            // to make sure that your process every pending event
            // \code
            // xwc::Event event;
            // while (window.pollEvent (event) {
            // // process the events
            // }
            // \encode
            //
            // \param event Event to be returned
            // 
            // \return True if an event was returned
            //
            // \see waitEvent
            //////////////////////
            [[nodiscard]] bool pollEvent (Event& event);

            //////////////////////////
            // \brief Wait for an event and return it
            //
            // This function isblocking if there is no pending event then
            // it will wait untile an event is received
            // This function must run under loop
            // \code
            // \encode
            //
            // \param Event event
            //
            // \return False if any error
            //
            // \see pollEvent
            //////////////////////////
            [[nodiscard]] bool waitEvent (Event& event);

            /////////////////////////
            // \brief Get the position of window
            //
            // \return Position of the window in pixel
            //
            // \see getPosition
            ////////////////////////
            void getPostion () const;

            ////////////////////////
            // \brief change the position of window on the screen window
            //
            // This function only works for top-lelvel window          
            //
            // \param position New position in pixels
            //
            // \see getPosition
            ///////////////////////
            void setPosition (const Vector2i& pos);

            ///////////////////////
            // \brief Getthe size of the rendering region or the window
            //
            // The size doesn't include titlebar and borders
            //
            // \return Size in pixels
            //
            // \see setSize
            //////////////////////
            Vector2u getSize () const;

            ////////////////////////
            // \brief Change size of the rendering region of window
            //
            // \param size new Size pixels
            //
            // \see setIcon
            ///////////////////////
            void setSize (const Vector2u& size);

            ////////////////////////
            // \brief Change the title of window
            //
            // \param Title title 
            //
            // \see setIcon
            ///////////////////////
            void setTitle (const String& title);

            //////////////////////////
            // \brief Change Window Icon
            //
            // \a pixels must be an array oof \a width x \a height pixels
            // in 32 bits RGBA format
            // The OS default icon is used by default
            // \param width
            // \param height
            // \param pixels
            // \see setTitle
            //////////////////////////
            void setIcon (unsigned int width, unsigned int height,
                    const uint8_t* pixels);

            //////////////////////////
            // \brief Show or hide the window
            //
            // The window is show by default
            //
            // \param visible True to show
            /////////////////////////
            void setVisible (bool visible);

            ////////////////////////
            // \brief Show or hide the mouse cursor
            //
            // The mouse cursor is visiable by default
            //
            // \param visible True
            ////////////////////////
            void setMouseCursorVisible (bool visible);

            ////////////////////////
            // \brief grab or release the mouse cursor
            //
            // If set, grab the mouse cursor inside this window client area
            // \param grabbed True to enabled
            ////////////////////////
            void setMouseCursorGrabbed (bool grabbed);

            ///////////////////////
            // \brief Set the displayed cursor to a native system cursor
            // Upon windown creation the arrow cursor is used by default
            // \warning  The cursor not be destroyed while in use by window
            // \warning  Feature related to Cursor  are not suppored On iOS
            // \param cursor Native system cursor type to display
            // \see xwc::Cursor::loadFromSystem
            // \see xwc::Cursor::loadFromPixels
            ///////////////////////
            void setMouseCursor (const Cursor& cursor);

            ///////////////////
            // \brief Enable or disable automatic key-repeat
            //
            // You get single event when the key is pressed
            //
            // Key repeat is enable by default
            // \param  enabled True 
            ////////////////////
            void setKeyRepeatEnabled (bool enabled);

            ///////////////////
            // \brief Chnage the joystick threshold
            //
            // The hoistick event will generated
            // \param Threshold  New threshold
            ///////////////////
            void setJoystickThreshold (float threshold);

            ///////////////////
            // \brief Request the curren window to be made active
            //
            // \see hasFocus
            //////////////////
            void requestFocus ();

            ///////////////////
            // \brief Check whether the window has the input focus
            // \return True if window has focus
            // \see requestFocus
            ///////////////////
            bool hasFocus () const;

            ////////////////////
            // \brief Get the OS specific handle of the window
            // The type of the returned handle is xwc::WindowHandle,
            // which is a typen alias to the handle type defined by the OS
            // you shouldn't need to use this function, unless you have
            // very specific stuff to implement that xwc doen't support.
            //
            // \return System handle of the window
            ////////////////////
            WindowHandle getSystemHandle () const;

            /////////////////////
            // \brief Function called after the window  has been created
            //
            // This function is called so that derived classes can
            // perform their own specific intialization as soon as the 
            // window created.
            ////////////////////
            virtual void onCreate ();

            ////////////////////
            // \brief Function called after the window has been resized
            ////////////////////
            virtual void onResize ();

        private:
            /////////////////////
            // \brief Perform some common internal initilization    
            //
            ////////////////////
            void initialization ();

            ///////////////////
            // \brief Get the fullscreen window
            //
            // \return The fullscreen window or a null pointer if there is none
            ///////////////////
            const WindowBase* getFullscreenWindow ();

            /////////////////
            // \brief  Set a window as the fullscreen window
            //
            // \param window window to set as fullscreen window
            ////////////////
            void setFullscreenWindow (const WindowBase* window);

            ///////////////////
            //Member data
            ///////////////////
            priv::WindowImpl* m_impl;
            Vector2u          m_size;        
    };    
}   // end of namespace xwc
#endif


////////////////////////////////////////////////////////////
/// \class xwc::WindowBase
/// \ingroup window
///
/// xwc::WindowBase serves as the base class for all Windows.
///
/// A xwc::WindowBase can create its own new window, or be embedded into
/// an already existing control using the create(handle) function.
///
/// The xwc::WindowBase class provides a simple interface for manipulating
/// the window: move, resize, show/hide, control mouse cursor, etc.
/// It also provides event handling through its pollEvent() and waitEvent()
/// functions.
///
/// Usage example:
/// \code
/// // Declare and create a new window
/// xwc::WindowBase window(xwc::VideoMode(800, 600), "SFML window");
///
/// // The main loop - ends as soon as the window is closed
/// while (window.isOpen())
/// {
///    // Event processing
///    xwc::Event event;
///    while (window.pollEvent(event))
///    {
///        // Request for closing the window
///        if (event.type == xwc::Event::Closed)
///            window.close();
///    }
///
///    // Do things with the window here...
/// }
/// \endcode
///
////////////////////////////////////////////////////////////

/* --------------- EoF WindowBase.hpp ----------------*/
