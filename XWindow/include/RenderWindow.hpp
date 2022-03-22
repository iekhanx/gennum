/*
 * ==========================================================================
 *
 *       Filename:  RenderWindow.hpp
 *
 *    Description:  Render Window class declaration  
 *
 *        Version:  1.0
 *        Created:  15/01/22 18:46:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

/////////////////////////////
// Headers
/////////////////////////////
#include "RenderTarget.hpp"
#include "Image.hpp"
#include "Window.hpp"
#include <string>
#include <cstdint>

namespace xwc
{
    class RenderWindow : public Window, public RenderTarget
    {
        public:

            /////////////////////////
            // \brief Default constructor
            /////////////////////////
            RenderWindow ();
            
            ///////////////////////
            // \brief Construct a new Window
            // \param mode Video mode to use
            // \param title Title the window
            // \param style window style a bitwise enumerator
            // \param settings 
            //////////////////////
            RenderWindow (VideoMode mode, const String& title, 
                          uint32_t style = Style::Default, 
                          const ContextSettings& settings = ContextSettings());

            /////////////////////
            // \brief Construct the window from existing control
            // \param handle platform specific
            // \param setting  additional setting 
            ////////////////////
            explicit RenderWindow (WindowHandle handle, 
                                   const ContextSettings& settings =
                                   ContextSettings ());

            ////////////////////
            // \brief Destructor
            ////////////////////
            ~RenderWindow () override;

            /////////////////////
            // \brief Get the size of the rendering window
            //
            // \return True if the window use sRGB encoding
            ////////////////////
            bool isSrgb () const override;

            //////////////////
            // \brief Activate or deactivate the window
            // \param active true
            // \return True
            //////////////////
            [[nodiscard]] bool setActive (bool active = true) override;

        protected:
            /////////////////
            // \brief Function call after window create
            // This function is called so that derived classes can perform
            // their own specific initialization as soon as the window
            // is created
            /////////////////
            void onCreate () override;

            //////////////////
            // \brief Function called after the window resized
            // This function is called so the derived class can
            // perform custom action.
            /////////////////
            void onResized () override;

        private:
            ////////////////////////
            // Member data
            ////////////////////////
            unsigned int m_defaultFrameBuffer; //< to bind targeting this wind
    };  // end of class RenderWindow
} // end of namespace xwc
#endif
/* ---------------------- Eof RenderWindow.hpp ----------------------*/
////////////////////////////////////////////////////////////
/// \class xwc::RenderWindow
/// \ingroup graphics
///
/// xwc::RenderWindow is the main class of the Graphics module.
/// It defines an OS window that can be painted using the other
/// classes of the graphics module.
///
/// xwc::RenderWindow is derived from xwc::Window, thus it inherits
/// all its features: events, window management, OpenGL rendering,
/// etc. See the documentation of xwc::Window for a more complete
/// description of all these features, as well as code examples.
///
/// On top of that, xwc::RenderWindow adds more features related to
/// 2D drawing with the graphics module (see its base class
/// xwc::RenderTarget for more details).
/// Here is a typical rendering and event loop with a xwc::RenderWindow:
///
/// \code
/// // Declare and create a new render-window
/// xwc::RenderWindow window(xwc::VideoMode(800, 600), "SFML window");
///
/// // Limit the framerate to 60 frames per second (this step is optional)
/// window.setFramerateLimit(60);
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
///    // Clear the whole window before rendering a new frame
///    window.clear();
///
///    // Draw some graphical entities
///    window.draw(sprite);
///    window.draw(circle);
///    window.draw(text);
///
///    // End the current frame and display its contents on screen
///    window.display();
/// }
/// \endcode
///
/// Like xwc::Window, xwc::RenderWindow is still able to render direct
/// OpenGL stuff. It is even possible to mix together OpenGL calls
/// and regular SFML drawing commands.
///
/// \code
/// // Create the render window
/// xwc::RenderWindow window(xwc::VideoMode(800, 600), "SFML OpenGL");
///
/// // Create a sprite and a text to display
/// xwc::Sprite sprite;
/// xwc::Text text;
/// ...
///
/// // Perform OpenGL initializations
/// glMatrixMode(GL_PROJECTION);
/// ...
///
/// // Start the rendering loop
/// while (window.isOpen())
/// {
///     // Process events
///     ...
///
///     // Draw a background sprite
///     window.pushGLStates();
///     window.draw(sprite);
///     window.popGLStates();
///
///     // Draw a 3D object using OpenGL
///     glBegin(GL_TRIANGLES);
///         glVertex3f(...);
///         ...
///     glEnd();
///
///     // Draw text on top of the 3D object
///     window.pushGLStates();
///     window.draw(text);
///     window.popGLStates();
///
///     // Finally, display the rendered frame on screen
///     window.display();
/// }
/// \endcode
///
/// \see xwc::Window, xwc::RenderTarget, xwc::RenderTexture, xwc::View
///
////////////////////////////////////////////////////////////
