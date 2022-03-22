/*
 * ==========================================================================
 *
 *       Filename:  GlxContext.hpp
 *
 *    Description:  GlxContext class declaration 
 *
 *        Version:  1.0
 *        Created:  06/02/22 18:33:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _GLXCONTEXT_HPP
#define _GLXCONTEXT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//#include "GlContext.hpp"
//#include <glad/glx.h>

#include <GL/glx.h>
#include <X11/Xlib.h>


namespace xwc
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Linux (GLX) implementation of OpenGL contexts
///
////////////////////////////////////////////////////////////
class GlxContext : public GlContext
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Create a new default context
    ///
    /// \param shared Context to share the new one with (can be a null pointer)
    ///
    ////////////////////////////////////////////////////////////
    GlxContext(GlxContext* shared);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new context attached to a window
    ///
    /// \param shared       Context to share the new one with
    /// \param settings     Creation parameters
    /// \param owner        Pointer to the owner window
    /// \param bitsPerPixel Pixel depth, in bits per pixel
    ///
    ////////////////////////////////////////////////////////////
    GlxContext(GlxContext* shared, const ContextSettings& settings, 
            const WindowImpl& owner, unsigned int bitsPerPixel);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new context that embeds its own rendering target
    ///
    /// \param shared   Context to share the new one with
    /// \param settings Creation parameters
    /// \param width    Back buffer width, in pixels
    /// \param height   Back buffer height, in pixels
    ///
    ////////////////////////////////////////////////////////////
    GlxContext(GlxContext* shared, const ContextSettings& settings, 
            unsigned int width, unsigned int height);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~GlxContext();

    ////////////////////////////////////////////////////////////
    /// \brief Get the address of an OpenGL function
    ///
    /// \param name Name of the function to get the address of
    ///
    /// \return Address of the OpenGL function, 0 on failure
    ///
    ////////////////////////////////////////////////////////////
    static GlFunctionPointer getFunction(const char* name);

    ////////////////////////////////////////////////////////////
    /// \brief Activate the context as the current target for rendering
    ///
    /// \param current Whether to make the context current or no longer current
    ///
    /// \return True on success, false if any error happened
    ///
    ////////////////////////////////////////////////////////////
    bool makeCurrent(bool current) override;

    ////////////////////////////////////////////////////////////
    /// \brief Display what has been rendered to the context so far
    ///
    ////////////////////////////////////////////////////////////
    void display() override;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable vertical synchronization
    ///
    /// Activating vertical synchronization will limit the number
    /// of frames displayed to the refresh rate of the monitor.
    /// This can avoid some visual artifacts, and limit the framerate
    /// to a good value (but not constant across different computers).
    ///
    /// \param enabled True to enable v-sync, false to deactivate
    ///
    ////////////////////////////////////////////////////////////
    void setVerticalSyncEnabled(bool enabled) override;

    ////////////////////////////////////////////////////////////
    /// \brief Select the best GLX visual for a given set of settings
    ///
    /// \param display      X display
    /// \param bitsPerPixel Pixel depth, in bits per pixel
    /// \param settings     Requested context settings
    ///
    /// \return The best visual
    ///
    ////////////////////////////////////////////////////////////
    static XVisualInfo selectBestVisual(::Display* display, 
            unsigned int bitsPerPixel, const ContextSettings& settings);

private:

    ////////////////////////////////////////////////////////////
    /// \brief Update the context visual settings from XVisualInfo
    ///
    /// \param visualInfo XVisualInfo to update settings from
    ///
    ////////////////////////////////////////////////////////////
    void updateSettingsFromVisualInfo(XVisualInfo* visualInfo);

    ////////////////////////////////////////////////////////////
    /// \brief Update the context visual settings from the window
    ///
    ////////////////////////////////////////////////////////////
    void updateSettingsFromWindow();

    ////////////////////////////////////////////////////////////
    /// \brief Create the context's drawing surface
    ///
    /// \param shared       Context to share the new one with 
    ///                     (can be a null pointer)
    /// \param width        Back buffer width, in pixels
    /// \param height       Back buffer height, in pixels
    /// \param bitsPerPixel Pixel depth, in bits per pixel
    ///
    ////////////////////////////////////////////////////////////
    void createSurface(GlxContext* shared, unsigned int width, 
            unsigned int height, unsigned int bitsPerPixel);

    ////////////////////////////////////////////////////////////
    /// \brief Create the context's drawing surface from an existing window
    ///
    /// \param window Window ID of the owning window
    ///
    ////////////////////////////////////////////////////////////
    void createSurface(::Window window);

    ////////////////////////////////////////////////////////////
    /// \brief Create the context
    ///
    /// \param shared Context to share the new one with (can be a null pointer)
    ///
    ////////////////////////////////////////////////////////////
    void createContext(GlxContext* shared);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ::Display*        m_display;    ///< Connection to the X server
    ::Window          m_window;     ///< Window to which the context is attached
    GLXContext        m_context;    ///< OpenGL context
    GLXPbuffer        m_pbuffer;    ///< GLX pbuffer ID if one was created
    bool              m_ownsWindow; ///< Do we own the window associated to the context?
};

} // namespace priv

} // namespace xwc

#endif // _GLXCONTEXT_HPP
