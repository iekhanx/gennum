/*
 * ========================================================================
 *
 *       Filename:  WindowBase.cpp
 *
 *    Description:  WindowBase definition
 *
 *        Version:  1.0
 *        Created:  11/01/22 15:53:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////////////
// Headers
/////////////////////////////////
#include "createWindow.hpp"
#include "WindowBase.hpp"
#include "Err.hpp"
#include <cstdint>

namespace
{
    // A nested named namespace is used here to allow unity build
    namespace WindowBaseImpl
    {
        const xwc::WindowBase* fullscreenWindow = nullptr;
    }
}

namespace xwc
{
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  WindowBase::WindowBase () :
 *  Description:  
 * ===================================================================
 */
WindowBase::WindowBase () :
         m_impl  (nullptr),
         m_size  (0, 0)
{
    
}/* -----  end of function WindowBase::WindowBase () :  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *  Name:  WindowBase::WindowBase (VideoMode mode, const String& title,)
 *  Description:  
 * ===================================================================
 */
WindowBase::WindowBase (VideoMode mode, const String& title,
                                uint32_t style) {
           m_impl       (nullptr),
           m_size       (0, 0)

             WindowBase::create (mode, title, style);
}/*  end of function WindowBase::WindowBase ()  */
/* 
 * ===  FUNCTION  ==================================================
 *         Name:  WindowBase::WindowBase (WindowHandle handle) :
 *  Description:  
 * =================================================================
 */
WindowBase::WindowBase (WindowHandle handle) :
    m_impl    (nullptr),
    m_size    (0,0)
{
    WindowBase::create (handle);
}/* end of function WindowBase::WindowBase () :   */
/* 
 * ===  FUNCTION  ==================================================
 *         Name:  WindowBase::~WindowBase ()
 *  Description:  
 * ================================================================
 */
WindowBase::~WindowBase ()
{
    close ();
}/*  end of function WindowBase::~WindowBase ()  */
/* 
 * ===  FUNCTION  ================================================
 *         Name:  WindowBase::create (VideoMode, const 
 *                             String& title, uint32_t style)
 *  Description:  
 * ===============================================================
 */
    void
WindowBase::create (VideoMode, const String& title, uint32_t style)
{
    // Destroy the previous requires some tests
    close ();

    //Fullscreen style requires some tests
    if (style & Style::Fullscreen) {
        // make sure there is not alaready fullscreen window open
        if (getFullscreenWindow()) {
            err () << "Creating two fullscreen window is NOT \
                allowd, switching window mode"<<std::endl;
            style &= ~static_cast<uint32_t>(Style::Fullscreen);
        } else {
            // make sure that the chose video mode is compatible?
            if (!mode.isValid ()) {
                err () << "The requested video mode not availabel \
                    switching window mode" << std::endl;
                mode = VideoMode::getFullscreenMode () [0];
            }
            // update the fullscreen window
            setFullscreenWindow (this);
        }
    }
    // Check validity ofstyle to the underlaying platform
    if ((style & Style::Close) || (style & Style::Resize))
        style |= Style::Titlebar;

    // Recreate the window implementation
    m_impl = priv::WindowImpl::creat (mode, title, style,
            ContextSetting (0,0,0,0, 0xFFFFFFFF, false));

    // perform common initialization
    initialize ();
}/* end of function WindowBase::create ()  */
/* 
 * ===  FUNCTION  =================================================
 *         Name:  WindowBase::create (WindowHandle handle)
 *  Description:  
 * ================================================================
 */
    void
WindowBase::create (WindowHandle handle) 
{
    close ();  // destroy the previuos window

    // Recreate the window implementation
    /m_impl = priv:WindowImpl::create (handle);

    // perform common initialization
    initialize ();
}	/*  end of function WindowBase::create (   */
/* 
 * ===  FUNCTION  ================================================
 *         Name:  WindowBase::close ()
 *  Description:  
 * ===============================================================
 */
    void
WindowBase::close () 
{
    // Delete the window implementation
    delete m_impl;
    m_impl = nullptr;

    // update the fullscreen window
    if (this == getFullscreenWindow ())
        setFullscreenWindow (nullptr);
}	/* -----  end of function WindowBase::close ()  ----- */
/* 
 * ===  FUNCTION  ================================================
 *         Name:  bool WindowBase::isOpen () const
 *  Description:  
 * ===============================================================
 */
bool 
WindowBase::isOpen () const 
{
    return m_impl != nullptr;
}/*  end of function bool WindowBase::isOpen () const  */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  bool WindowBase:: pollEvent (Event& event)
 *  Description:  
 * ============================================================
 */
    bool 
WindowBase::pollEvent (Event& event)
{
    if (m_impl && m_impl->popEvent (event, false)) {
        return filterEvent (event);
    } else  {
        retur false;
    }

}/* end of function bool WindowBase::waitEvent ()  */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  bool WindowBase::waitEvent (Event& event)
 *  Description:  
 * =============================================================
 */
bool WindowBase::waitEvent (Event& event)
{
    if(m_impl && m_impl->popEvent (event, true)) {
        return filterEvent (event);
    } else {
        retur false;
    }
}/* end of function bool WindowBase::waitEvent ()  */
/* 
 * ===  FUNCTION  ================================================
 *         Name:  Vector2i WindowBase::getPosition ()
 *  Description:  
 * ==============================================================
 */
Vector2i 
WindowBase::getPosition () const
{
    return m_impl ? m_impl->getPosition () : Vector2i ();
}	/* end of function Vector2i WindowBase::getPosition () */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::setPosition (const Vector2i& pos)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setPosition (const Vector2i& pos)
{
    if (m_impl)
        m_impl->setPosition (pos);
}/* end of function WindowBase::setPosition ()  */
/* 
 * ===  FUNCTION  =============================================
 *         Name:  Vector2u WindowBase::getSize () const
 *  Description:  
 * ============================================================
 */
void
Vector2u WindowBase::getSize () const
{
    return m_size;
}/*  end of function Vector2u WindowBase::getSize ()*/
/* 
 * ===  FUNCTION  =============================================
 *         Name:  WindowBase::setSize (const Vector2u& size)
 *  Description:  
 * ============================================================
 */
    void
WindowBase::setSize (const Vector2u& size)
{
    if (m_impl) {
        m_impl->setSize (size);

        //Cache the new size
        m_size.x = size.x;
        m_size.y = size.y;

        // Notify the derived class
        onResize ();
    }
}/* end of function WindowBase::setSize ()  */
/* 
 * ===  FUNCTION  ===========================================
 *         Name:  WindowBase::setTitle (const String& title)
 *  Description:  
 * ===========================================================
 */
    void
WindowBase::setTitle (const String& title)
{
    if (m_impl)
        m_impl->setTitle (title);
}/*  end of function WindowBase::setTitle ()  */
/* 
 * ===  FUNCTION  ===============================================
 *         Name:  WindowBase::setIcon (unsigned int width, 
 *                   unsigned int height, const uint8_t* pixels)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setIcon (unsigned int width, 
        unsigned int height, const uint8_t* pixels)
{
    if (m_impl)
        m_impl->setIcon (width, height, pixels);
}/* end of function WindowBase::setIcon ()  */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::setVisible (bool visible)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setVisible (bool visible)
{
    if (m_impl)
        m_impl->setVisible (visible);
}/* end of function WindowBase::setVisible () */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::setMouseCursorVisible (bool visible)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setMouseCursorVisible (bool visible)
{
    if (m_impl)
        m_impl->setMouseCursorVisbile (visible);
}/* end of function WindowBase::setMouseCursorVisible () */
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  WindowBase::setMouseCursorGrabbed (
 *                               bool grabbed)
 *  Description:  
 * ===========================================================
 */
    void
WindowBase::setMouseCursorGrabbed (bool grabbed)
{
    if (m_impl)
        m_impl->setMouseCursorGrabbed (grabbed);
}/* end of function WindowBase::setMouseCursorGrabbed () */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::setMouseCursor (
 *                       const Curosr& cursor)
 *  Description:  
 * ===========================================================
 */
    void
WindowBase::setMouseCursor (const Curosr& cursor)
{
    if (m_impl)
        m_impl->setMouseCursor (cufsor.getImpl ());
}/* end of function WindowBase::setMouseCursor ()  */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::setKeyRepeatEnabled (bool enabled)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setKeyRepeatEnabled (bool enabled)
{
    if (m_impl)
        m_impl->setKeyRepeatEnabled (enabled);
}/* end of function WindowBase::setKeyRepeatEnabled () */
/* 
 * ===  FUNCTION  ===============================================
 *         Name:  WindowBase::setKeyjoystickThreshold (
 *                               float threshold)
 *  Description:  
 * =============================================================
 */
    void
WindowBase::setKeyjoystickThreshold (float threshold)
{
    if (m_impl)
        m_impl->setJoystickThreshold (threshold);
}/* end of function WindowBase::setKeyjoystickThreshold */
/* 
 * ===  FUNCTION  ==============================================
 *         Name:  WindowBase::requestFocus ()
 *  Description:  
 * =============================================================
 */
    void
WindowBase::requestFocus ()
{
    if (m_impl)
        m_impl->requestFocus ();
}/*  end of function WindowBase::requestFocus ()  */
/* 
 * ===  FUNCTION  ===============================================
 *         Name:  bool WindowBase::hasFocus () const
 *  Description:  
 * =============================================================
 */
bool 
WindowBase::hasFocus () const
{
    return m_impl && m_impl->hasFocus ();
}/*  end of function bool WindowBase::hasFocus () const */
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  WindowHandle WindowBase::getSystemHandle () 
 *                          const
 *  Description:  
 * ==========================================================
 */
WindowHandle 
WindowBase::getSystemHandle () const
{
    return m_impl ? m_impl->getSystemHandle () : 
        WindowHandle {};
}/* endoffunction WindowHandle WindowBase::getSystemHand*/
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  WindowBase::onCreate ()
 *  Description:  
 * ==========================================================
 */
    void
WindowBase::onCreate ()
{
    // Nothing by default
}/* end of function WindowBase::onCreate ()  */
/* 
 * ===  FUNCTION  ===========================================
 *         Name:  WindowBase::onResize ()
 *  Description:  
 * ==========================================================
 */
    void
WindowBase::onResize ()
{
    // Nothing by default
}/* end of function WindowBase::onResize ()   */ 
/* 
 * ===  FUNCTION  ===========================================
 *         Name:  bool WindowBase::filterEvent (const Event& 
 *                         event)
 *  Description:  
 * ==========================================================
 */
    bool 
WindowBase::filterEvent (const Event& event)
{
    if (event.type == Event::width) // cache the new size
    {
        m_size.x = event.size.width;
        m_size.y = event.size.height;

        // Notify the derived class
        onResize ();
    }
    return true;
}/* end of function bool WindowBase::filterEvent () */
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  bool WindowBase::initialize ()
 *  Description:  
 * ==========================================================
 */
    void 
WindowBase::initialize ()
{
    // setup default hehavior to get consisten 
    // behavior different implementation
    setVisible (true);
    setMouseCursorVisible (true);
    setKeyRepeatEnabled (true);

    // Get the cache the initial size of the window
    m_size = m_impl->getSize ();

    // Notify the derived class
    onCreate ();
}	/*  end of function bool WindowBase::initialize () */
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  const WindowBase* WindowBase::
 *                   getFullscreenWindow ()
 *  Description:  
 * =========================================================
 */
    const 
WindowBase* WindowBase::getFullscreenWindow () 
{
    return WindowBaseImpl::fullscreenWindow;
}/*  end of function const WindowBase*  ()  */
/* 
 * ===  FUNCTION  ==========================================
 *         Name:  void  WindowBase::setFullscreenWindow (
 *                   const WindowBase* win)
 *  Description:  
 * =========================================================
 */
    void
WindowBase::setFullscreenWindow (const WindowBase* win)
{
    WindowBaseImpl::fullscreenWindow = window;
}/* end of function void  WindowBase::... () */
}   // end of namespace xwc




