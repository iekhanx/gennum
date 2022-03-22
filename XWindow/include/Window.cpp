/*
 * ========================================================================
 *
 *       Filename:  Window.cpp
 *
 *    Description:  Window class implementation 
 *
 *        Version:  1.0
 *        Created:  29/01/22 02:28:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Window.hpp"
#include "GlContext.hpp"
#include "WindowImpl.hpp"
#include "Sleep.hpp"
#include "Err.hpp"
#include <cstdint>

namespace xwc
{
////////////////////////////////////////////////////////////
Window::Window() :
m_context       (nullptr),
m_frameTimeLimit(Time::Zero)
{

}


////////////////////////////////////////////////////////////
Window::Window(VideoMode mode, const String& title, uint32_t style, 
                const ContextSettings& settings) :
m_context       (nullptr),
m_frameTimeLimit(Time::Zero)
{
    Window::create(mode, title, style, settings);
}


////////////////////////////////////////////////////////////
Window::Window(WindowHandle handle, const ContextSettings& settings) :
m_context       (nullptr),
m_frameTimeLimit(Time::Zero)
{
    Window::create(handle, settings);
}


////////////////////////////////////////////////////////////
Window::~Window()
{
    close();
}


////////////////////////////////////////////////////////////
void Window::create(VideoMode mode, const String& title, uint32_t style)
{
    Window::create(mode, title, style, ContextSettings());
}


////////////////////////////////////////////////////////////
void Window::create(VideoMode mode, const String& title, uint32_t style, 
                        const ContextSettings& settings)
{
    // Destroy the previous window implementation
    close();

    // Fullscreen style requires some tests
    if (style & Style::Fullscreen)
    {
        // Make sure there's not already a fullscreen 
        // window (only one is allowed)
        if (getFullscreenWindow())
        {
            err() << "Creating two fullscreen windows is not allowed, \
                switching to windowed mode" << std::endl;
            style &= ~static_cast<uint32_t>(Style::Fullscreen);
        }
        else
        {
            // Make sure that the chosen video mode is compatible
            if (!mode.isValid())
            {
                err() << "The requested video mode is not available, \
                    switching to a valid mode" << std::endl;
                mode = VideoMode::getFullscreenModes()[0];
            }

            // Update the fullscreen window
            setFullscreenWindow(this);
        }
    }

    // Check validity of style according to the underlying platform
    #if defined(SFML_SYSTEM_IOS) || defined(SFML_SYSTEM_ANDROID)
        if (style & Style::Fullscreen)
            style &= ~static_cast<uint32_t>(Style::Titlebar);
        else
            style |= Style::Titlebar;
    #else
        if ((style & Style::Close) || (style & Style::Resize))
            style |= Style::Titlebar;
    #endif

    // Recreate the window implementation
    m_impl = priv::WindowImpl::create(mode, title, style, settings);

    // Recreate the context
    m_context = priv::GlContext::create(settings, m_impl, mode.bitsPerPixel);

    // Perform common initializations
    initialize();
}


////////////////////////////////////////////////////////////
void Window::create(WindowHandle handle)
{
    Window::create(handle, ContextSettings());
}


////////////////////////////////////////////////////////////
void Window::create(WindowHandle handle, const ContextSettings& settings)
{
    // Destroy the previous window implementation
    close();

    // Recreate the window implementation
    WindowBase::create(handle);

    // Recreate the context
    m_context = priv::GlContext::create(settings, m_impl, 
                        VideoMode::getDesktopMode().bitsPerPixel);

    // Perform common initializations
    initialize();
}


////////////////////////////////////////////////////////////
void Window::close()
{
    // Delete the context
    delete m_context;
    m_context = nullptr;

    // Close the base window
    WindowBase::close();
}


////////////////////////////////////////////////////////////
const ContextSettings& Window::getSettings() const
{
    static const ContextSettings empty(0, 0, 0);

    return m_context ? m_context->getSettings() : empty;
}


////////////////////////////////////////////////////////////
void Window::setVerticalSyncEnabled(bool enabled)
{
    if (setActive())
        m_context->setVerticalSyncEnabled(enabled);
}


////////////////////////////////////////////////////////////
void Window::setFramerateLimit(unsigned int limit)
{
    if (limit > 0)
        m_frameTimeLimit = seconds(1.f / static_cast<float>(limit));
    else
        m_frameTimeLimit = Time::Zero;
}


////////////////////////////////////////////////////////////
bool Window::setActive(bool active) const
{
    if (m_context)
    {
        if (m_context->setActive(active))
        {
            return true;
        }
        else
        {
            err() << "Failed to activate the window's context" << std::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////
void Window::display()
{
    // Display the backbuffer on screen
    if (setActive())
        m_context->display();

    // Limit the framerate if needed
    if (m_frameTimeLimit != Time::Zero)
    {
        sleep(m_frameTimeLimit - m_clock.getElapsedTime());
        m_clock.restart();
    }
}


////////////////////////////////////////////////////////////
void Window::initialize()
{
    // Setup default behaviors 
    // (to get a consistent behavior across different implementations)
    setVerticalSyncEnabled(false);
    setFramerateLimit(0);

    // Reset frame time
    m_clock.restart();

    // Activate the window
    if (!setActive())
    {
        err() << "Failed to set window as active during \
            initialization" << std::endl;
    }

    WindowBase::initialize();
}

} // namespace xwc

