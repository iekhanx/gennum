/*
 * ========================================================================
 *
 *       Filename:  Mouse.cpp
 *
 *    Description:  Mouse class implementation  
 *
 *        Version:  1.0
 *        Created:  15/01/22 01:27:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
///////////////////////////////
// Headers
//////////////////////////////
#include "Mouse.hpp"
#include "Window.hpp"
#include "InputImpl.hpp"

namespace xwc
{
    /* 
     * ===  FUNCTION  ====================================================
     *         Name:  bool Mouse::isButtonPressed (Button button)
     *  Description:  
     * ===================================================================
     */
     bool Mouse::isButtonPressed (Button button)
     {
            return priv::InputImpl::isMouseButtonPressed (button);
     }/*  end of function bool Mouse::isButtonPressed ()   */
     /* 
      * ===  FUNCTION  ====================================================
      *         Name:  Vector2i Mouse::getPosition()
      *  Description:  
      * ===================================================================
      */
      Vector2i Mouse::getPosition() 
      {
             return priv::InputImpl::getMousePosition ();
      }/* end of function Vector2i Mouse::getPosition() */
      /* 
       * ===  FUNCTION  ====================================================
       *         Name:  Vector2i Mouse::getPosition(const Vector2i& pos)
       *  Description:  
       * ===================================================================
       */
       Vector2i Mouse::getPosition(const Vector2i& pos)
       {
              return priv::InputImpl::getMousePosition (pos);
       }/* end of function Vector2i Mouse::getPosition()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  Mouse::setPosition (const Vector2i& pos)
        *  Description:  
        * ===================================================================
        */
       void
           Mouse::setPosition (const Vector2i& pos)
           {
               return priv::InputImpl::setMousePosition (pos);
           }/* end of function Mouse::setPosition ()  */
       /* 
        * ===  FUNCTION  ====================================================
        *         Name:  Mouse::setPosition (const Vector2i& pos, 
        *                                    const WindowBase& relTo)
        *  Description:  
        * ===================================================================
        */
       void
           Mouse::setPosition (const Vector2i& pos, const WindowBase& relTo)
           {
               priv::ImputImpl::setmousePosition (pos, relTo);
           }/*  end of function Mouse::setPosition ()  */
}   // end of namespace xwc

/* ------------------ Eof Mouse.cpp ----------------------*/

