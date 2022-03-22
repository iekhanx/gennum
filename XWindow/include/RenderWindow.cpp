/*
 * ========================================================================
 *
 *       Filename:  RenderWindow.cpp
 *
 *    Description:  RenderWindow class implementation
 *
 *        Version:  1.0
 *        Created:  16/01/22 00:47:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
/////////////////////////////
// Header
// //////////////////////////
#include "RenderWindow.hpp"

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  RenderWindow::RenderWindow () :
     *  Description:  
     * ===================================================================
     */
    RenderWindow::RenderWindow () :
        m_defaultFrameBuffer (0)
    {
        // nothing more to do
    }/* -----  end of function RenderWindow::RenderWindow () :  ----- */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  RenderWindow::RenderWindow (VideMode mode, 
     *         const String& title,uint32_t style, 
     *         const ContextSettings& settings) 
     *  Description:  
     * ===================================================================
     */
    RenderWindow::RenderWindow (VideMode mode, const String& title,
            uint32_t style, const ContextSettings& settings) :
        m_defaultFrameBuffer (0);
    { 
        Window::create (mode, title, style, settings);
    }/* end of function RenderWindow::RenderWindow () :  */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  RenderWindow::RenderWindow (WindowHandle handle, 
     *                  const ContextSettings& settings) 
     *  Description:  
     * ===================================================================
     */
     RenderWindow::RenderWindow (WindowHandle handle, 
             const ContextSettings& settings) :
         m_defaultFrameBuffer (0)
    {
        Window::create (handle, settings);
    }/* end of function RenderWindow::RenderWindow () :  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  RenderWindow::~RenderWindow ()
      *  Description:  
      * ===================================================================
      */
    RenderWindow::~RenderWindow ()
    {
             // Nothing to do
    }	/*  end of function RenderWindow::~RenderWindow ()  */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  Vector2u RenderWindow::getSize () const
     *  Description:  
     * ===================================================================
     */
    Vector2u RenderWindow::getSize () const
    {
            return Window::getSize();
    }/* end of function Vector2u RenderWindow::getSize () const */
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  bool RenderWindow::isSrgb () const
     *  Description:  
     * ===================================================================
     */
     bool RenderWindow::isSrgb () const 
     {
            return getSettings().sRgbCapable;
     }/* end of function bool RenderWindow::isSrgb () const   */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  bool RenderWindow::setAcive (bool active)
      *  Description:  
      * ===================================================================
      */
     bool RenderWindow::setAcive (bool active)
     {  
         bool result = Window::setActive (active);

         // Update RenderTarget tracking
         if (result)
             result = RenderTarget::setActive (active);

         // If FBOs are available, make sure none are bound when we tru to
         // draw the default framebuffer of renderWindow
         return result;
     }	/*  end of function bool RenderWindow::setAcive ()  */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  RenderWindow::onCreate ()
      *  Description:  
      * ===================================================================
      */
     void
         RenderWindow::onCreate ()
         {
            RenderWindow::initialize ();
         }	/* -----  end of function RenderWindow::onCreate ()  ----- */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  RenderWindow::onResize ()
      *  Description:  
      * ===================================================================
      */
     void
         RenderWindow::onResize ()
         {
             // Update current view
             setView (getView ());
         }	/* -----  end of function RenderWindow::onResize ()  ----- */
}
/* ------------------- Eof RenderWindow.cpp ----------------------*/
