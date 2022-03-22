/*
 * ========================================================================
 *
 *       Filename:  InputImpl.cpp
 *
 *    Description:  Class InputImpl definition 
 *
 *        Version:  1.0
 *        Created:  11/01/22 11:20:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
///////////////////////////////////////////////
// Headers
///////////////////////////////////////////////
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "InputImpl.hpp"
#include "Display.hpp"
#include "Window.hpp"

namespace xwc
{
    namespace priv
    {
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  bool InputImpl::isKeyPressed (Keyboard::Key key)
         *  Description:  
         * ===================================================================
         */
         bool InputImpl::isKeyPressed (Keyboard::Key key)
         {
            // Get the corresponding X11 keysym
            KeySym keysym = 0;
            switch (key)
            {
               case Keyboard::LShift:     keysym = XK_Shift_L;      break;
               case Keyboard::RShift:     keysym = XK_Shift_R;      break;
               case Keyboard::LControl:   keysym = XK_Control_L;    break;
               case Keyboard::RControl:   keysym = XK_Control_R;    break;
               case Keyboard::LAlt:       keysym = XK_Alt_L;        break;
               case Keyboard::RAlt:       keysym = XK_Alt_R;        break;
               case Keyboard::LSystem:    keysym = XK_Super_L;      break;
               case Keyboard::RSystem:    keysym = XK_Super_R;      break;
               case Keyboard::Menu:       keysym = XK_Menu;         break;
               case Keyboard::Escape:     keysym = XK_Escape;       break;
               case Keyboard::Semicolon:  keysym = XK_semicolon;    break;
               case Keyboard::Slash:      keysym = XK_slash;        break;
               case Keyboard::Equal:      keysym = XK_equal;        break;
               case Keyboard::Hyphen:     keysym = XK_minus;        break;
               case Keyboard::LBracket:   keysym = XK_bracketleft;  break;
               case Keyboard::RBracket:   keysym = XK_bracketright; break;
               case Keyboard::Comma:      keysym = XK_comma;        break;
               case Keyboard::Period:     keysym = XK_period;       break;
               case Keyboard::Quote:      keysym = XK_apostrophe;   break;
               case Keyboard::Backslash:  keysym = XK_backslash;    break;
               case Keyboard::Tilde:      keysym = XK_grave;        break;
               case Keyboard::Space:      keysym = XK_space;        break;
               case Keyboard::Enter:      keysym = XK_Return;       break;
               case Keyboard::Backspace:  keysym = XK_BackSpace;    break;
               case Keyboard::Tab:        keysym = XK_Tab;          break;
               case Keyboard::PageUp:     keysym = XK_Prior;        break;
               case Keyboard::PageDown:   keysym = XK_Next;         break;
               case Keyboard::End:        keysym = XK_End;          break;
               case Keyboard::Home:       keysym = XK_Home;         break;
               case Keyboard::Insert:     keysym = XK_Insert;       break;
               case Keyboard::Delete:     keysym = XK_Delete;       break;
               case Keyboard::Add:        keysym = XK_KP_Add;       break;
               case Keyboard::Subtract:   keysym = XK_KP_Subtract;  break;
               case Keyboard::Multiply:   keysym = XK_KP_Multiply;  break;
               case Keyboard::Divide:     keysym = XK_KP_Divide;    break;
               case Keyboard::Pause:      keysym = XK_Pause;        break;
               case Keyboard::F1:         keysym = XK_F1;           break;
               case Keyboard::F2:         keysym = XK_F2;           break;
               case Keyboard::F3:         keysym = XK_F3;           break;
               case Keyboard::F4:         keysym = XK_F4;           break;
               case Keyboard::F5:         keysym = XK_F5;           break;
               case Keyboard::F6:         keysym = XK_F6;           break;
               case Keyboard::F7:         keysym = XK_F7;           break;
               case Keyboard::F8:         keysym = XK_F8;           break;
               case Keyboard::F9:         keysym = XK_F9;           break;
               case Keyboard::F10:        keysym = XK_F10;          break;
               case Keyboard::F11:        keysym = XK_F11;          break;
               case Keyboard::F12:        keysym = XK_F12;          break;
               case Keyboard::F13:        keysym = XK_F13;          break;
               case Keyboard::F14:        keysym = XK_F14;          break;
               case Keyboard::F15:        keysym = XK_F15;          break;
               case Keyboard::Left:       keysym = XK_Left;         break;
               case Keyboard::Right:      keysym = XK_Right;        break;
               case Keyboard::Up:         keysym = XK_Up;           break;
               case Keyboard::Down:       keysym = XK_Down;         break;
               case Keyboard::Numpad0:    keysym = XK_KP_Insert;    break;
               case Keyboard::Numpad1:    keysym = XK_KP_End;       break;
               case Keyboard::Numpad2:    keysym = XK_KP_Down;      break;
               case Keyboard::Numpad3:    keysym = XK_KP_Page_Down; break;
               case Keyboard::Numpad4:    keysym = XK_KP_Left;      break;
               case Keyboard::Numpad5:    keysym = XK_KP_Begin;     break;
               case Keyboard::Numpad6:    keysym = XK_KP_Right;     break;
               case Keyboard::Numpad7:    keysym = XK_KP_Home;      break;
               case Keyboard::Numpad8:    keysym = XK_KP_Up;        break;
               case Keyboard::Numpad9:    keysym = XK_KP_Page_Up;   break;
               case Keyboard::A:          keysym = XK_a;            break;
               case Keyboard::B:          keysym = XK_b;            break;
               case Keyboard::C:          keysym = XK_c;            break;
               case Keyboard::D:          keysym = XK_d;            break;
               case Keyboard::E:          keysym = XK_e;            break;
               case Keyboard::F:          keysym = XK_f;            break;
               case Keyboard::G:          keysym = XK_g;            break;
               case Keyboard::H:          keysym = XK_h;            break;
               case Keyboard::I:          keysym = XK_i;            break;
               case Keyboard::J:          keysym = XK_j;            break;
               case Keyboard::K:          keysym = XK_k;            break;
               case Keyboard::L:          keysym = XK_l;            break;
               case Keyboard::M:          keysym = XK_m;            break;
               case Keyboard::N:          keysym = XK_n;            break;
               case Keyboard::O:          keysym = XK_o;            break;
               case Keyboard::P:          keysym = XK_p;            break;
               case Keyboard::Q:          keysym = XK_q;            break;
               case Keyboard::R:          keysym = XK_r;            break;
               case Keyboard::S:          keysym = XK_s;            break;
               case Keyboard::T:          keysym = XK_t;            break;
               case Keyboard::U:          keysym = XK_u;            break;
               case Keyboard::V:          keysym = XK_v;            break;
               case Keyboard::W:          keysym = XK_w;            break;
               case Keyboard::X:          keysym = XK_x;            break;
               case Keyboard::Y:          keysym = XK_y;            break;
               case Keyboard::Z:          keysym = XK_z;            break;
               case Keyboard::Num0:       keysym = XK_0;            break;
               case Keyboard::Num1:       keysym = XK_1;            break;
               case Keyboard::Num2:       keysym = XK_2;            break;
               case Keyboard::Num3:       keysym = XK_3;            break;
               case Keyboard::Num4:       keysym = XK_4;            break;
               case Keyboard::Num5:       keysym = XK_5;            break;
               case Keyboard::Num6:       keysym = XK_6;            break;
               case Keyboard::Num7:       keysym = XK_7;            break;
               case Keyboard::Num8:       keysym = XK_8;            break;
               case Keyboard::Num9:       keysym = XK_9;            break;
               default:                   keysym = 0;               break;
            }
            // Sanity checks
            if (key < 0 || key >= xwc::Keyboard::KeyCount)
                return false;

            // Open a connection with the X server
            Display *dpy = OpenDisplay ();

            // convert to keycode
            KeyCode keycode = XKeysymToKeycode (dpy, keysym);
            if (keycode != 0) {
                // Get the whole keyboard state
                char keys[32];
                XQueryKeymap (dpy, keys);
                
                // close the connection with the X server
                CloseDisplay (dpy);

                // Check our keycode
                return (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
            } else {
                // Close the connection with X server
                CloseDisplay (dpy);

                return false;
            }            
        } /* end of InputImpl::isKeyPressed () */ 
        /* 
         * ===  FUNCTION  ===================================================
         *         Name:  InputImpl::setVirtualKeyboardVisible (
         *                      Mouse::Button button)
         *  Description:  
         * ===================================================================
         */
        void
         InputImpl::setVirtualKeyboardVisible (bool)
         {
               // not applicable
         }/* end of function InputImpl::setVirtualKeyboardVisible ()  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  bool InputImpl::isMouseButtonPressed (
         *                      Mouse::Button button)
         *  Description:  
         * ===================================================================
         */
        void
         bool InputImpl::isMouseButtonPressed (Mouse::Button button)
         {
            // Open a connection with the X server
            Display *dpy = OpenDisplay ();

            // we don't care about these but they are requred
            ::Window root, child;
            int wx, wy;
            int gx, gy;
            unsigned int buttons = 0;

            XQueryPointer (dpy, DefaultRootWindow (dpy), &root, &child,
                                &gx, &gy, &wx, &wy, &buttons);
            // Close the connection with X server
            CloseDisplay (dpy);

            switch (button) {
                case Mouse::Left:            return button & Button1Mask;
                case Mouse::Right:           return button & Button3Mask;
                case Mouse::Middle:          return button & Button2Mask;
                case Mouse::XButton1:        return false; // not supprted X
                case Mouse::XButton2:        return false;
                default:                     return false;
            }
            return false;
         }/* end of function bool InputImpl::isMouseButtonPressed ()  */
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  bool InputImpl::getMousePosition ()
         *  Description:  
         * ===================================================================
         */
         Vector2i InputImpl::getMousePosition ()
         {
             // Open Display connection to X server
             Display *dpy;

             // Required
             ::Window root, child;
             int x, y, gx=0, gy=0;
             unsigned int buttons;

             XQueryPointer (dpy, DefaultRootWindow (dpy), &root, &child, &gx,
                            &gy, &x, &y, &button);
             // Close the connection with X server
             CloseDisplay (dpy);

             return Vector2i (gx, gy);
         }/* end of function bool InputImpl::getMousePosition ()  */
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  Vector2i InputImpl::getMousePosition (
          *                             const WindowBase& relt)
          *  Description:  
          * ===================================================================
          */
          Vector2i InputImpl::getMousePosition (const WindowBase& relt)
          {
              WindowHandle handl = relt.getSystemHandle ();
              if (handle) {
                  Display *dpy = OpenDisplay ();

                  ::Window root, child;
                  int gx, gy, x=0, y=0;
                  unsigned int buttons;

                  XQueryPointer (dpy, handle, &root, &child, &gx, &gy,
                                    &x, &y, &buttons);
                  CloseDisplay (dpy);
                  return Vector2i (x, y);
              } else {
                  return Vector2i ();
              }              
          }/* end of function Vector2i InputImpl::getMousePosition ()  */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  InputImpl::setMousePosition (const Vector2i& pos)
           *  Description:  
           * ===================================================================
           */
          void
           InputImpl::setMousePosition (const Vector2i& pos)
            {
                Display *dpy = OpenDisplay ();

                XWarpPointer (dpy, None, DefaultRootWindow (dpy),
                                0,0,0,0, pos.x, pos.y);
                XFlush (dpy);

                CloseDisplay (dpy); // close connection to X server
            }/* end of function InputImpl::setMousePosition ()   */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  InputImpl::setMousePosition (const Vector2i& pos, 
           *                                            const WindowBase& relt)
           *  Description:  
           * ===================================================================
           */
          void
           InputImpl::setMousePosition (const Vector2i& pos, 
                                        const WindowBase& relt)
           {
                Display* dpy = OpenDisplay ();

                WindowHandle handle = relt.getSystemHandle ();
                if (handle) {
                    XWarpPointer (dpy, None, handle, 0,0,0,0, pos.x, pos.y);
                    XFlush (dpy);
                }
                CloseDisplay (dpy);
           }/* end of function InputImpl::setMousePosition ()   */
          /* 
           * ===  FUNCTION  ====================================================
           *         Name:  bool InputImpl::isTouchDown (unsigned int)
           *  Description:  
           * ===================================================================
           */
           bool InputImpl::isTouchDown (unsigned int) 
           {
                  return false;
           }/* end of function bool InputImpl::isTouchDown (unsigned int) */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  Vector2i InputImpl::getTouchPosition (unsigned int)
            *  Description:  
            * ==================================================================
            */
            Vector2i InputImpl::getTouchPosition (unsigned int)
            {
                   return Vector2i ();
            }/*  end of function Vector2i InputImpl::getTouchPosition () */
            /* 
             * ===  FUNCTION  =================================================
             *         Name:  Vector2i InputImpl::getTouchPosition (
             *                              unsigned int, const WindowBase&)
             *  Description:  
             * ================================================================
             */
             Vector2i InputImpl::getTouchPosition (unsigned int, 
                                                    const WindowBase&)
             {
                    return Vector2i ();
             }/* end of function Vector2i InputImpl::getTouchPosition () */
    } // end of namespace priv
}     // end of namespace xwc










