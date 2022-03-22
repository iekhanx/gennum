/*
 * ========================================================================
 *
 *       Filename:  WindowImplX11.cpp
 *
 *    Description: Create Window  
 *
 *        Version:  1.0
 *        Created:  05/01/22 14:20:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
///////////////////////////////////////////////////
// Headers
// ////////////////////////////////////////////////
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/extensions/Xrandr.h>
#include <X11/Xlibint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <mutex>
#include <cstdint>
#include "WindowImplX11.hpp"
#include "ClipboardImpl.hpp"
#include "Display.hpp"
#include "InputImpl.hpp"
#include "String.hpp"
#include "Utf.hpp"
#include "Err.hpp"
#include "Sleep.hpp"

/////////////////////////////////////////////////
// Private data
// //////////////////////////////////////////////
namespace 
{
    namespace WindowsImplX11Impl
    {
        xwc::priv::WindowImplX11*     fullscreenWindow = nullptr;
        std::vector<xwc::priv::WindowImplX11*>  allWindows;
        std::recursive_mutex        allWindowMutex;
        xwc::String                 windowManagerName;
        xwc::String                 wmAbsPosGood[] = {"Enlight", "XWC", "13"};
        static const unsigned long  eventMask = 
                                  FocusChangeMask | ButtonPressMask  |
                                ButtonReleaseMask | ButtonMotionMask |
                                PointerMotionMask | KeyPressMask     |
                                KeyReleaseMask    | StructureNotifyMask |
                                EnterWindowMask   | LeaveWindowMask  |
                             VisibilityChangeMask | PropertyChangeMask;

        static const unsigned int     maxTrialsCount = 5;

        // Predicate we use to find key repeat events in processEvent
        struct KeyRepeatFinder
        {
            KeyRepeatFinder (unsigned int initialKeycode, Time initialTime) :
                            keycode (initialKeycode), time (initialTime) {}
            // Predicate operator that chech event type, 
            // keycode and timestamp
            bool operator () (const XEvent event) {
                return ((event.type == KeyPress) && 
                        (event.xkey.keycode == keycode) &&
                        (event.xkey.time - time < 2));
            }
            unsigned int keycode;
            Time time;
        };
        // Filter the event received by window (only allows those matching ev)
        Bool checkEvent (::Display*, XEvent* event, XPointer userData)
        {
            // Just check if the event matches the window
            // The input method sometimes sends ClientMessages with differentnID
            // our event loop has to process them for the IM to work
            return (event->xany.window == reinterpret_cast<::Window >(userData))
                || (event->type == ClientMessage);
        }
        // Find the name of the current executable
        std::string findExecutableName ()
        {
            // We use /proc/self/cmdline to get the command line
            // the user used to invoke this instance of the application
            int file = ::open("/proc/self/cmdline", O_RDONLY | O_NONBLOCK);

            if (file < 0)
                return "sfml";

            std::vector<char> buffer(256, 0);
            std::size_t offset = 0;
            ssize_t result = 0;

            while ((result = read(file, &buffer[offset], 256)) > 0)
            {
                buffer.resize(buffer.size() + 
                        static_cast<std::size_t>(result), 0);
                offset += static_cast<std::size_t>(result);
            }

            ::close(file);

            if (offset)
            {
                buffer[offset] = 0;

                // Remove the path to keep the executable name only
                return basename(buffer.data());
            }

            // Default fallback name
            return "xwc";
        }

        // Check if extended Window Manager Hints are supported?
        bool ewmhSupported ()
        {
            static bool checked = false;
            static bool ewmhSupported = false;

            if (checked)
                return ewmSupported;

            checked = true;

            Atom newSupportingWMcheck = xwc::priv::getAtom (
                    "_NET_SUPPORT_WM_CHECK", true);
            Atom netSupported = xwc::priv::getAtom ("_NET_SUPPORTED", true);

            if (!netSupportingWMcheck || netSupported)
                return false;

            ::Display* m_dpy = xwc::priv::OpenDisplay ();
            
            Atom actualType;
            int actualFormat;
            unsigned long numItems;
            unsigned long numBytes;
            unsigned char* data;

            int result = XGetWindowProperty (m_dpy,
                                             DefaultRootWindow (m_dpy),
                                             netWupportingWMcheck,
                                             0,
                                             1,
                                             False,
                                             XA_WINDOW,
                                             &actualType,
                                             &actualFormat,
                                             &numItems,
                                             &numBytes,
                                             &data);
            if (result != Success || actualType != XA_WINDOW || numItems != 1)
            {
                if (result == Success)
                    XFree (data);

                xwc::priv::CloseDisplay (m_dpy);
                return false;
            }
            ::Window rootWindow = *reinterpret_cast<::Window* > (data);

            XFree (data);

            if (!rootWindow) {
                xwc::priv::CloseDisplay (m_dpy);
            }
            result = XGetWindowProperty (m_dpy,
                                         rootWindow,
                                         netWupportingWMcheck,
                                         0,
                                         1,
                                         False,
                                         XA_WINDOW,
                                         &actualType,
                                         &actualFormat,
                                         &numItems,
                                         &numBytes,
                                         &data);
            if (result != Success || actualType != XA_WINDOW || numItems != 1)
            {
                if (result == Success)
                    XFree (data);

                xwc::priv::CloseDisplay (m_dpy);
                return false;
            }
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wcast-align"
            ::Window childWindow = *reinterpret_cast< ::Window* >(data);
            #pragma GCC diagnostic pop

            XFree(data);
            
            if (!childWindow) {
                xwc::priv::CloseDisplay (m_dpy);
                return false;
            }
            // Conforming window manager should return the same window
            if (rootWindow != childWindow) {
                xwc::priv::CloseDisplay (m_dpy);
                return false;
            }
            ewmhSupported = true;
            
            // We try to get the name of the window manager
            // for window manager specific workaround
            Atom netWMname = xwc::priv::getAtom ("_NET_WM_NAME", true);

            if (!netWMname) {
                xwc::priv::CloseDisplay (m_dpy);
                return true;
            }
            Atom utf8StringType = xwc::priv::getAtom ("UTF8_STRING");

            if (!utf8StringType)
                utf8StringType = XA_STRING;

            result = XGetWindowProperty (m_dpy,
                                         rootWindow,
                                         netWMname,
                                         0,
                                         0x7fffffff,
                                         False,
                                         utf8StringType,
                                         &actualType,
                                         &actualFormat,
                                         &numItems,
                                         &numBytes,
                                         &data);
            if (actualType && numItems) {
                // it seems the WM name string reply is not necessarity
                // null terminated. The work around is to get its actual
                // length to build a proper string.
                const char * begin = reinterpret_cast <const char*> (data);
                const char * end   = begin + numItems;
                windowManagerName = xwc::String::fromUtf8 (begin, end);
            }
            if (result == Success) 
                XFree (data);

            xwc::priv::CloseDisplay (m_dpy);

            return true;
        }
        // Get the parent window
        ::Window getParentWindow (::Display* dpy, ::Window win)
        {
            ::Window root, parent;
            ::Window childwin = nullptr;
            unsigned int numChildwin;

            XQueryTree (dpy, win, &root, &parent, &childwin, &numChildwin);

            // Child win information is not used so must be freed
            if (childwin != nullptr)
                XFree (childwin);

            return parent;
        }
        bool getEWMHFrameExtents (::Display *dpy, ::Window win, 
                long& xFrameExtent, long& yFrameExtent) 
        {
            if (!ewmhSupported ())
                return false;
            Atom frameExtents = xwc::priv::getAtom ("_NET_FRAME_EXTENTS", true);

            if (frameExtents == None)
                return false;

            bool gotFrameExtents = false;
            Atom actualType;
            int  actualFromat;
            unsigned long numItems;
            unsigned long numBytesLeft;
            unsigned char* data = nullptr;

            int result = XGetWindowProperty (dpy,
                                             win,
                                             frameExtents,
                                             0,
                                             4,
                                             False,
                                             XA_CARDINAL,
                                             &actualType,
                                             &actualFormat,
                                             &numItems,
                                             &numBytesLeft,
                                             &data);
            if ((result == success) && (actualType == XA_CARDINAL) &&
                    (actualFormat == 32) && (numItems == 4) && 
                    (numBytesLeft == 0) && (data != nullptr))
            {
                gotFrameExtents = true;
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wcast-align"
                long* extents = reinterpret_cast <long*> (data);
                #pragma GCC diagnostic pop

                xFrameExtent = extents[0];
                yFrameExtent = extents[2];
            } // Always free data
            if (data != nullptr)
                XFree (data);

            return gotFrameExtents;
        }
        // Check if the current WM is in the list of good WMs that provide
        // a correct absolute position for the window when queried
        bool isWMAbsolutePositionGood ()
        {
            // This can only work with EWMH to get the name
            if (!ewmhSupported ())
                return false;

            for (const xwc::String& name : wmAbsPosGood)
            {
                if (name == windowManagerName)
                    return true;
            }
            return false;
        }
        
        xwc::Keyboard::Key keysymToXW (KeySym symbol)
        {
            switch (symbol)
            {
                case XK_Shift_L:        return xwc::Keyboard::LShift;
                case XK_Shift_R:        return xwc::Keyboard::RShift;
                case XK_Control_L:      return xwc::Keyboard::LControl;
                case XK_Contrl_R:       return xwc::Keyboard::RControl;
                case XK_Alt_L:          return xwc::Keyboard::LAlt;
                case XK_Alt_R:          return xwc::Keyboard::RAlt;
                case XK_Super_L:        return xwc::Keyboard::LSystem;
                case XK_Super_R:        return xwc::Keyboard::RSystem;
                case XK_Menu:           return xwc::Keyboard::Menu;
                case XK_Escape:         return xwc::Keyboard::Escape;
                case XK_semicolon:      return xwc::Keyboard::Semicolon;
                case XK_slash:          return xwc::Keyboard::Slash;
                case XK_equal:          return xwc::Keyboard::Equal;
                case XK_minus:          return xwc::Keyboard::Hyphen;
                case XK_bracketleft:    return xwc::Keyboard::LBracket;
                case XK_bracketright:   return xwc::Keyboard::RBracket;
                case XK_comma:          return xwc::Keyboard::Comma;
                case XK_period:         return xwc::Keyboard::Period;
                case XK_apostrophe:     return xwc::Keyboard::Quote;
                case XK_backslash:      return xwc::Keyboard::Backslash;
                case XK_grave:          return xwc::Keyboard::Tilde;
                case XK_space:          return xwc::Keyboard::Space;
                case XK_Return:         return xwc::Keyboard::Enter;
                case XK_KP_Enter:       return xwc::Keyboard::Enter;
                case XK_BackSpace:      return xwc::Keyboard::BackSpace;
                case XK_Tab:            return xwc::Keyboard::Tab;
                case XK_Prior:          return xwc::Keyboard::PageUp;
                case XK_Next:           return xwc::Keyboard::PageDown;
                case XK_End:            return xwc::Keyboard::End;
                case XK_Home:           return xwc::Keyboard::Home;
                case XK_Insert:         return xwc::Keyboard::Insert;
                case XK_Delete:         return xwc::Keyboard::Delete;
                case XK_KP_Add:         return xwc::Keyboard::Add;
                case XK_KP_Subtract:    return xwc::Keyboard::Subtract;
                case XK_KP_Multiply:    return xwc::Keyboard::Multiply;
                case XK_KP_Divide:      return xwc::Keyboard::Divide;
                case XK_Pause:          return xwc::Keyboard::Pause;
                case XK_F1:             return xwc::Keyboard::F1;
                case XK_F2:             return xwc::Keyboard::F2;
                case XK_F3:             return xwc::Keyboard::F3;
                case XK_F4:             return xwc::Keyboard::F4;
                case XK_F5:             return xwc::Keyboard::F5;
                case XK_F6:             return xwc::Keyboard::F6;
                case XK_F7:             return xwc::Keyboard::F7;
                case XK_F8:             return xwc::Keyboard::F8;
                case XK_F9:             return xwc::Keyboard::F9;
                case XK_F10:            return xwc::Keyboard::F10;
                case XK_F11:            return xwc::Keyboard::F11;
                case XK_F12:            return xwc::Keyboard::F12;
                case XK_F13:            return xwc::Keyboard::F13;
                case XK_F14:            return xwc::Keyboard::F14;
                case XK_F15:            return xwc::Keyboard::F15;
                case XK_Left:           return xwc::Keyboard::Left;
                case XK_Right:          return xwc::Keyboard::Right;
                case XK_Up:             return xwc::Keyboard::Up;
                case XK_Down:           return xwc::Keyboard::Down;
                case XK_KP_Insert:      return xwc::Keyboard::Numpad0;
                case XK_KP_End:         return xwc::Keyboard::Numpad1;
                case XK_KP_Down:        return xwc::Keyboard::Numpad2;
                case XK_KP_Page_Down:   return xwc::Keyboard::Numpad3;
                case XK_KP_Left:        return xwc::Keyboard::Numpad4;
                case XK_KP_Begin:       return xwc::Keyboard::Numpad5;
                case XK_KP_Right:       return xwc::Keyboard::Numpad6;
                case XK_KP_Home:        return xwc::Keyboard::Numpad7;
                case XK_KP_Up:          return xwc::Keyboard::Numpad8;
                case XK_KP_Page_Up:     return xwc::Keyboard::Numpad9;
                case XK_a:              return xwc::Keyboard::A;
                case XK_b:              return xwc::Keyboard::B;
                case XK_c:              return xwc::Keyboard::C;
                case XK_d:              return xwc::Keyboard::D;
                case XK_e:              return xwc::Keyboard::E;
                case XK_f:              return xwc::Keyboard::F;
                case XK_g:              return xwc::Keyboard::G;
                case XK_h:              return xwc::Keyboard::H;
                case XK_i:              return xwc::Keyboard::I;
                case XK_j:              return xwc::Keyboard::J;
                case XK_k:              return xwc::Keyboard::K;
                case XK_l:              return xwc::Keyboard::L;
                case XK_m:              return xwc::Keyboard::M;
                case XK_n:              return xwc::Keyboard::N;
                case XK_o:              return xwc::Keyboard::O;
                case XK_p:              return xwc::Keyboard::P;
                case XK_q:              return xwc::Keyboard::Q;
                case XK_r:              return xwc::Keyboard::R;
                case XK_s:              return xwc::Keyboard::S;
                case XK_t:              return xwc::Keyboard::T;
                case XK_u:              return xwc::Keyboard::U;
                case XK_v:              return xwc::Keyboard::V;
                case XK_w:              return xwc::Keyboard::W;
                case XK_x:              return xwc::Keyboard::X;
                case XK_y:              return xwc::Keyboard::Y;
                case XK_z:              return xwc::Keyboard::Z;
                case XK_0:              return xwc::Keyboard::Num0;
                case XK_1:              return xwc::Keyboard::Num1;
                case XK_2:              return xwc::Keyboard::Num2;
                case XK_3:              return xwc::Keyboard::Num3;
                case XK_4:              return xwc::Keyboard::Num4;
                case XK_5:              return xwc::Keyboard::Num5;
                case XK_6:              return xwc::Keyboard::Num6;
                case XK_7:              return xwc::Keyboard::Num7;
                case XK_8:              return xwc::Keyboard::Num8;
                case XK_9:              return xwc::Keyboard::Num9;
            }
            return xwc::Keyboard::Unknown;
        }
    }
}
/////////////////////////////////////////////////////////////////////
// function section for namespace xwc
/////////////////////////////////////////////////////////////////////
namespace xwc
{
    namespace priv
    {
        WindowImplX11::WindowImplX11 (WindowHandle handle) :
            m_window        (0),
            m_scrn          (0),
            m_inputMethod   (nullptr),
            m_inputContext  (nullptr),
            m_isExternal    (true),
            m_oldVideoMode  (0),
            m_oldRRCrtc     (0),
            m_hiddenCursor  (0),
            m_lastCursor    (None),
            m_keyRepeat     (true),
            m_previousSize  (-1, -1),
            m_useSizeHints  (false),
            m_fullscreen    (false),
            m_cursorGrabbed (false),
            m_windowMapped  (false),
            m_iconPixmap    (0),
            m_iconMaskPixmap(0),
            m_lastInputTime (0)
        {
            using namespace WindowsImplX11Impl;

            // Open connection to X server
            m_dpy = OpenDisplay ();

            // Make sure  to check for EWMH support before we do anything?
            ewmhSupported ();

            m_scrn = DefaultScreen (m_dpy);

            // Save the window handle
            m_window = handle;

            if (m_window)
            {   
                // Make sure the windownis listening to all the required events
                XSetWindowAttributes attributes;
                attributes.event_mask = eventMask;

                XChangeWindowAttributes (m_dpy, m_window, 
                                          CWEventMask, &attributes);

                // Set the WM protocols
                setProtocols ();

                // Do some common initialisations
                initialize ();
            }
        }
    

        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  WindowImplX11::WindowImplX11 (VideoMode mode, 
         *         const String& title, unsigned long style, 
         *         const ContextSettings& settings)
         *  Description:  
         * ===================================================================
         */
         WindowImplX11::WindowImplX11 (VideoMode mode, const String& title, 
                 unsigned long style, const ContextSettings& settings) :
            m_window        (0),
            m_scrn          (0),
            m_inputMethod   (nullptr),
            m_inputContext  (nullptr),
            m_isExternal    (false),
            m_oldVideoMode  (0),
            m_oldRRCrtc     (0),
            m_hiddenCursor  (0),
            m_lastCursor    (None),
            m_keyRepeat     (true),
            m_previousSize  (-1, -1),
            m_useSizeHints  (false),
            m_fullscreen    ((style & Style::Fullscreen) != 0),
            m_cursorGrabbed (m_fullscreen),
            m_windowMapped  (false),
            m_iconPixmap    (0),
            m_iconMaskPixmap(0),
            m_lastInputTime (0)
            {
               using namespace WindowsImplX11Impl;
               // Open a connection with the X server
                m_dpy = OpenDisplay ();

                // Make sure to check for EWMH support before we do anything
                ewmhSupported ();

                m_scrn = DefaultScreen (m_dpy);

                // Compute position and size
                Vector2i windowPosition;
                if (m_fullscreen) {
                    windowPosition = getPrimaryMonitorPosition ();
                } else {
                    windowPosition = (DisplayWidth (m_dpy, m_scrn) -
                                      static_cast<int>(mode.width)) / 2;
                    windowPosition = (DisplayWidth (m_dpy, m_scrn) -
                                      static_cast<int>(mode.height)) / 2;
                }

                unsigned int width  = mode.width;
                unsigned int height = mode.height;

                Visual* visual = nullptr;
                int depth = 0;
                
                if (settings.attributeFlags == 0xFFFFFFFF) {
                    visual = DefaultVisual (m_dpy, m_scrn);
                    depth  = DefaultDepth (m_dpy, m_scrn);
                } else {
                    XVisualInfo visualInfo = ContextType::selectBestVisual (
                                                m_dpy, mode.bitsPerPixel,
                                                settings);
                    visual = visualInfo.visual;
                    depth  = visualInfo.depth;
                }
                // Define the window attributes
                XSetWindowAttributes attributes;
                attributes.colormap = XCreateColormap (m_dpy, 
                                                   DefaultRootWindow (m_dpy),
                                                   visual,
                                                   AllocNone);
                attributes.event_mask = eventMask;
                attributes.override_redirect = (m_fullscreen && 
                                             !ewmhSupported()) ? True : False;
                
                // create the our window
                m_window = XCreateWindow (m_dpy,
                                          DefaultRootWindow (m_dpy),
                                          windowPosition.x,
                                          windowPosition.y,
                                          width,
                                          height,
                                          0,
                                          depth,
                                          InputOutput,
                                          visual,
                                          CWEventMask | CWOverrideRedirect |
                                          CWColormap,
                                          &attributes);
                if (!m_window) {
                    err () << "Failed to create window" << std::endl;
                    return;
                }
                // set the WM protocols
                setProtocols ();

                // Set the WM initial stat to the normal state
                XWMHints*  xHints      = XAllocWMHints ();
                xHints->flags          = StateHint;
                xHints->initial_state  = NormalState;

                XSetWMHints (m_dpy, m_window, xHints);   // call XSetWMHints()
                
                XFree (xHints);

                // if not in fullscreen, set the wiindow style (tell the 
                // window manager to change our window's decorations and 
                // function according to the requeste style)
                if (!m_fullscreen) {
                    Atom WMHintsAtom getAtom ("_NOTIF_WM_HINTS", false);
                    if (WMHintsAtom) {
                        static const unsigned long MWM_HINTS_FUNCTIONS =1<<0;
                        static const unsigned long MWM_HINTS_DECORATIONS=1<<1;

                        // static const unsigned long MWM decor ALL
                        static const unsigned long MWM_DECOR_BORDER = 1<<1;
                        static const unsigned long MWM_DECOR_RESIZEH= 1<<2;
                        static const unsigned long MWM_DECOR_TITLE  = 1<<3;
                        static const unsigned long MWM_DECOR_MENU   = 1<<4;
                        static const unsigned long MWM_DECOR_MINIMIZE=1<<5;
                        static const unsigned long MWM_DECOR_MAXIMIZE=1<<6;

                        // static const unsigne long MWM_FUNC_ALL
                        static const unsigned long MWM_FUNC_RESIZE   = 1<<1;
                        static const unsigned long MWM_FUNC_MOVE     = 1<<2;
                        static const unsigned long MWM_FUNC_MINIMIZE = 1<<3;
                        static const unsigned long MWM_FUNC_MAXIMIZE = 1<<4;
                        static const unsigned long MWM_FUNC_CLOSE    = 1<<5;
                        
                        struct WMHints {
                            unsigned long flags;
                            unsigned long functions;
                            unsigned long decorations;
                            long          inputMode;
                            unsigned long state;
                        };

                        WMHints hints;
                        std::memset (&hints, 0, sizeof (hints));
                        hints.flags    = MWM_HINTS_FUNCTION | 
                                            MWM_HINTS_DECORATION;
                        hints.decorations = 0;
                        hints.functions   = 0;

                        if (style & Style::Titlebar) {
                            hints.decorations |= MWM_DECOR_BORDER  |
                                                 MWM_DECOR_TITLE   |
                                                 MWM_DECOR_MINIMIZE|
                                                 MWM_DECOR_MENU;
                            hints.functions   |= MWM_FUNC_MOVE | 
                                                 MWM_FUNC_MINIMIZE;
                        }
                        if (style & Style::Resize) {
                            hints.decorations |= MWM_DECOR_MAXIMIZE |
                                                 MWM_DECOR_RESIZEH;
                            hints.functions   |= MWM_FUNC_MAXIMIZE  |
                                                 MWM_FUNC_RESIZE;
                        }
                        if (style & Style::Close) {
                            hints.decorations |= 0;
                            hints.functions   |= MWM_FUNC_CLOSE;
                        }

                        XChangeProperty (m_dpy,
                                         m_window,
                                         WMHintsAtom,
                                         WMHintsAtom,
                                         32,
                                         PropModeReplace,
                                         reinterpret_cast<const unsigned char*>
                                         (&hints),
                                         5);

                    }
                }
                // This is a hack to force some window manager to disable
                // resizing
                if (!(style & Style::Resize)) {
                    m_useSizeHints = true;
                    XSizeHints* sizeHints = XAllcSizeHints ();
                    sizeHints->flags     = PMinSize | PMaxSize | USPosition;
                    sizeHints->min_width = sizeHints->max_width =
                                           static_cast<int>(width);
                    sizeHints->min_height= sizeHints->max_height =
                                           static_cast<int>(height);
                    sizeHints->x = windowPosition.x;
                    sizeHints->y = windowPosition.y;

                    XSetWMNormalHints (m_dpy, m_window, sizeHints);
                    XFree (sizeHints);
                }
                // Set the window's WM class (this can be used by window Mgr)
                XClassHint* hint = XAllocClassHint ();

                // The instance name should be someing unique to this invocation
                // of the application but rarely if ever used these days.
                // For simplicity, we retrieve it via the base executable name.
                std::string executableName = findExecutableName ();
                std::vector<char> windowInstance (executableName.size()+1,0);
                std::copy(executableName.begin(), executableName.end(),
                            windowInstance.begin());
                hint->res_name = windowInstance.data();

                // The class name identifies a class of window that 
                // "are of the same type". We simply use the initial window
                // name as the class name.
                std::string ansiTitle = title.toAnsiString ();
                std::vector<char> windowClass (ansiTitle.size() + 1, 0);
                std::copy (ansiTitle.begin(), ansiTitle.end(),
                            windowClass.begin());
                hint->res_class = windowClass.data();

                XSetClassHint (m_dpy, m_window, hint);

                XFree (hint);

                // Set the window's name
                setTitle (title);

                // Do some common initialization
                initialize ();

                // Set full screen video mode and switch fscreen
                if (m_fullscreen)
                {
                    // Disable hint for min and max size,
                    // otherwise some windows manager will not remove
                    // window decorations
                    XSizeHints *sizeHints = XAllocSizeHints ();
                    long flags = 0;
                    XGetWMNormalHints (m_dpy, m_window, sizeHints, &flags);
                    sizeHints->flags &= ~(PMinSize | PMaxSize);

                    XSetWMNormalHints (m_dpy, m_window, sizeHints);
                    XFree (sizeHints);

                    setVideoMode (mode);
                    switchToFullscreen ();
                }

            }/*  end of function WindowImplX11::WindowImplX11 ()  ----- */
            
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  WindowImplX11::~WindowImplX11()
          *  Description:  
          * ===================================================================
          */
         WindowImplX11::~WindowImplX11()
          {
            using namespace WindowImplX11;
            
            // Cleanup graphical resources
            cleanup ();

            // Destroy icon pixmap
            if (m_iconPixmap) {
                XFreePixmap (m_dpy, m_iconPixmap);
            }

            // Destroy icon mask pixmap
            if (m_iconMaskPixmap) {
                XFreePixmap (m_dpy, i_iconMaskPixmap);
            }

            // Destroy the cursor
            if (m_hiddenCursor) {
                XFreeCursor (m_dpy, m_hiddenCursor);
            }
            
            // Destroy the imput context
            if (m_iputContext) {
                XDestroyIC (m_inputContext);
            }
            
            // Destroy the window
            if (m_window && !m_isExternal) {
                DestroyWindow (m_dpy, m_window); XFlush (m_dpy);
            }

            // Close iput method
            if (m_inputMethod) {
                CloseXIM (m_inputMethod);
            }

            // Close the connection with X server
            CloseDisplay (m_dpy);

            // Remove this window from the global list of window
            // require for focus request
            std::scoped_lock lock (allWindowsMutex);
            allWindows.erase (std::find (allWindows.begin(), allWindows.end (),
                                this));
          }	/* -----  end of function WindowImplX11::~WindowImplX11()  ----- */

         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  XWindowHandle WindowImplX11::getSystemHandle ()
          *  Description:  
          * ===================================================================
          */
         XWindowHandle WindowImplX11::getSystemHandle () const
          {
                 return m_window;
          }	/* end of function XWindowHandle WindowImplX11::getSystemHandle () */
        
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  WindowImplX11::processEvents ()
          *  Description:  
          * ===================================================================
          */
         void
          WindowImplX11::processEvents ()
             {
                using namespace WindowImplX11;

                XEvent ev;

                // Pick out the events that are interesting for this window
                while (XCheckIfEvent (m_dpy, &ev, &checkEvent,
                            reinterpret_cast<XPointer>(m_window)))
                    m_event.push_back (ev);
                // Handle the events for this window that we just picked out
                while (!m_events.empty()) {
                    ev = m_events.front();
                    m_events.pop_front();
                    processEvent (ev);
                }
                // Process clipboard window events
                priv::processEvents ();    // remember add line here
                //priv::ClipboardImpl::processEvents();
             }/*----  end of function WindowImplX11::processEvents ()  ----- */
            
         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  Vector2i WindowImplX11::getPosition () const
          *  Description:  
          * ===================================================================
          */
          Vector2i WindowImplX11::getPosition () const 
          {   using namespace WindowImplX11;
              // Get absolute position of our window relative to root window.
              // This take into account all information that X11 has including
              // X11 border widths and any decorations. It corresponds to 
              // where actually is, but not necessarily to where we told it to
              // go using setPosition () and XMoveWindow(). To have the two
              // match as expected,we may have to substract decoration n border
              ::Window child;
              int xAbsRelToRoot, yAbsRelToRoot;

              XTranslateCoordinates (m_dpy, 
                                     m_window, 
                                     DefaultRootWindow (m_dpy),
                                     0, 0,
                                     &xAbsRelToRoot,
                                     &yAbsRelToRoot,
                                     &child);
              // CASE 1: some rare WMs actually put the window exactly where we
              // tell it to, even with decorations and such which get shifted
              // back. In these rare cases, we can use the absolute values.
              if (isWMAbsolutePositionGood ())
                  return Vector2i (xAbsRelToRoot, yAbsRelToRoot);
              // CASE 2: most modern WMs support EWMH and can define 
              // _NET_FRAME_EXTENTS with the exact frame size  to subtract, so
              // if present, we prefer it and query its first. 
              // According to spec, this already includes any borders.
              long xFrameExtent, yFrameExtent;

              if (getEWMHFrameExtents (m_dpy, m_window, 
                                        xFrameExtent,yFrameExtent) {
                      // Get final X/Y coordinates subtract EWMH frame extent
                      // from absolute window position
                    return Vector2i ((xAbsRelToRoot - 
                                static_cast<int>(xFrameExtent)),
                                (xAbsRelToRoot -
                                 static_cast<int>(yFrameExtent)));
                      }
                // CASE 3: EWMH frame extents were not available, use geometry
                // we climb back up to the window before the root and use its
                // geometry information to extract X/Y position. This because
                // re-parenting WMs may re-parent the window multiple times, so
                // we'd have to climb up to the furthest anscestor and sum the
                // relative differences and borders anyway; and doing that to
                // subtract those values from the absolute coordinates of the
                // windownis equivalent to going up the tree and asking the
                // furtherest ancestor that it's relative distnace to the root
                // is? So we use the that approach because it' simpler.
                // This approach assumes that any window between the root and
                // our window is part of decoration/border in some way. This
                // seems to hold true for most resonable WM implementations.
                ::Window ancestor = m_window;
                ::Window root     = DefaultRootWindow (m_dpy);

                while (getParentWindow (m_dpy, ancestor) != root)
                {
                    ancestor = getParentWindow (m_dpy, ancestor);
                }
                // Get final X/Y coordinate take the relative position to
                // the root of the furthest ancestor window.
                int xRelToRoot, yRelToRoot;
                unsigned int width, height, borderWidth, depth;
    
                XGetGeometry (m_dpy, 
                              ancestor, 
                              &root, 
                              &xRelToRoot,
                              &yRelToRoot,
                              &width,
                              &height,
                              &borderWidth,
                              &depth);
                 return Vector2i (xRelToRoot, yRelToRoot);
          }	/* end of function Vector2i WindowImplX11::getPosition () const */

          /* 
           * ===  FUNCTION  ====================================================
           *        Name:  WindowImplX11::setPosition (const Vector2i& position)
           *  Description:  
           * ===================================================================
           */
          void
            WindowImplX11::setPosition (const Vector2i& position)
            {
                XMoveWindow (m_dpy, m_window, position.x, position.y);
                XFlush (m_dpy);
            }	/*  end of function WindowImplX11::setPosition ()  ----- */

          /* 
           * ===  FUNCTION  ====================================================
           *      Name:  Vector2u WindowImplX11::setSize (const Vector2u& size)
           *  Description:  
           * ===================================================================
           */
           Vector2u WindowImplX11::getSize () const
           {
                XWindowAttributes attributes;
                XGetWindowAttributes (m_dpy, m_window, &attributes);
                return Vector2u (Vector2i (attributes.width, 
                            attributes.height));
           }/*  end of function Vector2u WindowImplX11::setSize ()  ----- */
           
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setSize (const Vector2u& size)
            *  Description:  
            * ==================================================================
            */
           void
             WindowImplX11::setSize (const Vector2u& size)
             {
                if (m_useSizeHints) {
                    XSizeHints* sizeHints = XAllocSizeHints ();
                    sizeHints->flags = PMinSize | PMaxSize;
                    sizeHints->min_width = sizeHints->max_width =
                                            static_cast<int>(size.x);
                    sizeHints->min_height = sizeHints->max_height =
                                            static_cast<int>(size.y);

                    XSetWMNormalHints (m_dpy, m_window, sizeHints);
                    XFree (sizeHints);
                }
                XResizeWindow (m_dpy, m_window, size.x, size.y);
                XFlush (m_dpy);
             }/* -----  end of function WindowImplX11::setSize ()  ----- */

           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setTitle (const String& title)
            *  Description:  
            * ==================================================================
            */
           void
             WindowImplX11::setTitle (const String& title)
             {
                // Bare X11 has no Unicode window title support.
                // There is however, an option to tell the WM your Unicode title
                // via hints

                 // Convert to UTF-8 encoding
                 std::basic_string<uint8_t> utf8Title;
                 Utf32::toUtf8 (title.begin (), title.end (),
                                std::back_insert_iterator (utf8Title));

                 Atom useUtf8 = getAtom ("UTF8_STRING", false);

                 // Set the _NET_WM_NAME atom which specifies  a UTF-8 encode
                 Atom wmName = getAtom ("_NET_WM_NAME", false);
                 XChangeProperty (m_dpy, 
                                  m_window, 
                                  wmName, 
                                  useUtf8, 8,
                                  PropModeReplace,
                                  utf8Title.c_str(),
                                  static_cast<int>(utf8Title.size()));
                 // Set the _NET_WM_ICON_NAME atom which spefied a UTF-8 encode
                 Atom wmIconName = getAtom ("_NET_WM_ICON_NAME", false);
                 XChangeProperty (m_dpy,
                                  m_window,
                                  wmIconName,
                                  useUtf8, 8,
                                  PropModeReplace,
                                  utf8Title.c_str(),
                                  static_cast<int>(utf8Title.c_str()));
                 // Set the non-Unicode title as fallback  for WM don't support

                 #ifdef X_HAVE_UTF8_STRING
                 Xutf8SetWMProperties (m_dpy,
                                       m_window,
                                       title.toAnsiString().c_str(),
                                       title.toAnsiString().c_str(),
                                       nullptr,
                                       0,
                                       nullptr,
                                       nullptr,
                                       nullptr);
                 #else
                 XmbSetWMProperties (m_dpy,
                                     m_window,
                                     title.toAnsiString().c_str(),
                                     title.toAnsiString().c_str(),
                                     nullptr,
                                     0,
                                     nullptr,
                                     nullptr,
                                     nullptr);
                 #endif
             }/* -----  end of function WindowImplX11::setTitle ()  ----- */

           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setIcon (unsigned int width, 
            *         unsigned int height, const Unit8* pixels)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setIcon (unsigned int width, unsigned int 
                       height, const Unit8* pixels)
               {
                   // X11 want BGRA pixels: swap red and blue channel
                   // Note: This memory will be freed by XDestroyImage()
                   auto *iconPixels = static_cast<uint8_t*>(std::malloc(
                                            width * height * 4));
                   for (std::size_t i=0; i<width*height; i++) {
                       iconPixels[i*4+0] = pixels[i*4+2];
                       iconPixels[i*4+1] = pixels[i*4+1];
                       iconPixels[i*4+2] = pixels[i*4+0];
                       iconPixels[i*4+3] = pixels[i*4+3];
                   }

                   //Create the icon pixma;
                   Visual*    defVisual = DefaultVisual (m_dpy, m_scrn);
                   auto defDepth = static_cast<unsigned int>(DefaultDepth (
                                        m_dpy, m_scrn));
                   XImage* iconImage = XCreateImage (m_dpy,
                                                     defVisual,
                                                     defDepth,
                                                     ZPixmap,
                                                     0,
                                                     reinterpret_cast<char*>(
                                                         iconPixels),
                                                     width,
                                                     height,
                                                     32,
                                                     0);
                   if (!iconImage) {
                        err () << "Failed to set the window's icon"<<std::endl;
                        return;
                   }
                   if (m_iconPixmap)
                       XFreePixmap (m_dpy, m_iconPixmap);
                   if (m_iconMaskPixmap)
                       XFreePixmap (m_dpy, m_iconMaskPixmap);

                   m_iconPixmap = XCreatePixmap (m_dpy,
                                                 RootWindow (m_dpy, m_scrn),
                                                 width,
                                                 height,
                                                 defDepth);
                   XGCValues values;
                   GC iconGC = XCreateGC (m_dpy, m_iconPixmap, 0, &values);
                   XPutImage (m_dpy, 
                              m_iconPixmap, 
                              iconGC, 
                              iconImage, 
                              0,0,0,0,
                              width,
                              height);
                   XFreeGC (m_dpy, iconGC);
                   XDestroyImage (iconImage);

                   // Create the mask pixmap (nust have 1 bit depth)
                   std::size_t pitch = (width+7)/8;
                   std::vector<uint8_t>maskPixels (pitch * height, 0);
                   for (std::size_t j=0; j<height; ++j) {
                        for (std::size_t i=0; i< pitch; ++i) {
                            for (std::size_t k=0; k<8; ++k) {
                                if (i*8+k < width) {
                                    uint8_t opacity = (pixels[(i*8+k+j*width) *
                                            4 + 3] > 0) ? 1 : 0;
                                    maskPixels[i+j*pitch] |=
                                        static_cast<uint8_t>(opacity << k);
                                }
                            }
                        }
                   }
                   m_iconMaskPixmap = XCreatePixmapFromBitmapData (m_dpy,
                                      m_window,
                                     reinterpret_cast<char*>(maskPixels.data()),
                                     width, height, 1, 0, 1);
                   // Send our new icon to the window through the WMHints
                   XWMHints* hints = XAllocWMHints ();
                   hints->flags       = IconPixmapHint | IconMaskHint;
                   hints->icon_pixmap = m_iconPixmap;
                   hints->icon_mask   = m_iconMaskPixmap;

                   XSetWMHints (m_dpy, m_window, hints);
                   XFree (hints);

                   // ICCCM want BGRA pixels: swap red and blue channel
                   // ICCCM also want the first 2 unsigned 32-bit values to be
                   // width and height
                   std::vector<unsigned long> icccmIconPixels (
                                            2 + width * height, 0);
                   unsigned long *ptr = icccmIconPixels.data();
                   #pragma GCC diagnostic push
                   #pragma GCC diagnostic ignored "-Wnull-dereference"
                   *ptr++ = width;
                   *ptr++ = height;
                   #pragma GCC diagnostic pop

                   for (std::size_t i=0; i<width * height; ++i) {
                      *ptr++ = static_cast<unsigned long>((pixels[i*4+2]<<0)|
                                                          (pixels[i*4+1]<<8)|
                                                          (pixels[i*4+0]<<16)|
                                                          (pixels[i*4+3]<<24));
                   }
                   Atom netWMIcon = getAtom ("_NET_WM_ICON");
                   XChageProperty (m_dpy,
                                   m_window,
                                   netWMIcon,
                                   XA_CARDINAL,
                                   32,
                                   PropModeReplace,
                                   reinterpret_cast<const unsigned char*>(
                                                    icccmIconPixels.data()),
                                   static_cast<int>(2 + width * height));
                   XFlush (m_dpy);                                              
               }/* -----  end of function WindowImplX11::setIcon ()  ----- */
            
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setVisible (bool visible)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setVisible (bool visible)
               {
                    if (visible) {
                        XMapWindow (m_dpy, m_window);
                        if (m_fullscreen)
                            switchToFullscreen ();

                        XFlush (m_dpy);

                        // Before continuing make sure the WM has
                        // internally marked the window as viewable
                        while (!m_windowMapped && !m_isExternal)
                            processEvents ();
                    } else {
                        UNmapWindow (m_dpy, m_window);
                        XFlush (m_dpy);

                        // Before continuing make sure the WM has
                        // internally marked the window as unviewable
                        while (m_windowMapped && !m_isExternal)
                            processEvents ();
                    }
               } /* -----  end of function WindowImplX11::setVisible ()  ----- */

           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setMouseCursorVisible (bool visible)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setMouseCursorVisible (bool visible)
               {
                    XDefineCusor (m_dpy, m_window, visible ? m_lastCursor :
                                                        m_hiddenCursor);
                    XFlush (m_dpy);
               }/*  end of function WindowImplX11::setMouseCursorVisible ()  */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setMouseCursor (const 
            *                       CursorImpl& cursor)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setMouseCursor (const CursorImpl& cursor)
               {
                    m_lastCursor = cursor.m_cursor;
                    XDefineCursor (m_dpy, m_window, m_lastCursor);
                    XFlush (m_dpy);
               }/* end of function WindowImplX11::setMouseCursor ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setMouseCursorGrabbed (bool grabbed)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setMouseCursorGrabbed (bool grabbed)
               {
                    using namespace WindowImplX11;
                    // This has no effect in fullscreen mode
                    if (m_fullscreen || (m_cusorGrabbed == grabbed))
                        return;
                    if (grabbed) {
                        // Try multiple time to grab the cursor
                      for (unsigned int trial=0; trial < maxTrialCount; ++Trial)
                      {
                          int result = XGrabPointer (m_dpy,
                                                     m_window,
                                                     True,
                                                     None,
                                                     GrabModeAsync,
                                                     GrabModeAsync,
                                                     m_window,
                                                     None,
                                                     CurrentTime);
                          if (result == GrabSuccess) {
                              m_cursorGrabbed = true; break;
                          }
                          xwc::sleep (xwc::milliseconds (50));
                      }
                      if (!m_cursorGrabbed)
                          err () "Failed to grab mouse cursor" << std::endl;
                    } else {
                        // Release the cursor from the window and disable cursor
                        XUngrabPointer (m_dpy, CurrentTime);
                        m_cursorGrabbed = false;
                    }
               }/* end of function WindowImplX11::setMouseCursorGrabbed () */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setKeyRepeatEnabled (bool enabled)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setKeyRepeatEnabled (bool enabled)
               {
                   m_keyRepeat = enabled;
               }/* end of function WindowImplX11::setKeyRepeatEnabled () */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::requestFocus ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::requestFocus ()
               {
                using namespace WindowImplX11;

                // focus is only stolen among WindowImplX11 not between appltion
                // Check the global list of window to find out whether an
                // window has the focus.
                // note: can't handle console and other non window belong  to
                // the application
                bool xwcWindowFocused = false;

                {
                    std::scoped_lock lock (allWindowMutex);
                    for (xwc::priv::WindowImplX11* windowPtr : allWindows)
                    {
                        if (windowPtr->hasFocus ()) {
                            xwcWindowFocused = true; break;
                        }
                    }
                }
                // check if window is viewable?
                // TODO: Check also if minimized?
                XWindowAttributes attributes;
                if (XGetWindowAttributes (m_dpy, m_window, &attributes) == 0) {
                    xwc::err () "Failed to check if windown viewable for Focus"
                             << std::endl;
                    return; 
                }
                bool windowViewable = (attributes.map_state = IsViewable);
                if (xwcWindowFocused && windowViewable) {
                    // steal focus
                    grabFocus ();
                } else {
                    // Otherwise display urgency hint 
                    // Ensure WM hints exist, allocate if necessary
                    XWMHints *hints = XGetWMHints (m_dpy, m_window);
                    if (hints == nullptr)
                        hints = XAllocWMHints();

                    // Add urgency nonotification flag to hints
                    hints->flags |= XUigencyHint;
                    XSetWMHints (m_dpy, m_window, hints);
                    XFree (hints);
                }
               }/*  end of function WindowImplX11::requestFocus ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::hasFocus () const
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::hasFocus () const
               {
                   ::Window focusedWindow = 0;
                   int revertToReturn = 0;
                   XGetInputFocus (m_dpy, &focusedWindow, &revertToReturn);

                   return (m_window == focusedWindow);
               }/* ---  end of function WindowImplX11::hasFocus () const  --- */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::grabFocus ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::grabFocus ()
               {
                    using namespace WindowImplX11;

                    Atom netAcitveWindow = None;

                    if (ewmhSupported ())
                        netActiveWindow = getAtom ("_NET_ACTIVE_WINDOW");

                    // Only try to grab focus if the window is mapped
                    XWindowAttributes attr;
                    XGetWindowAttributes (m_dpy, m_window, &attr);

                    if (attr.map_state == IsUnmapped ) return;

                    if (netActiveWindow) {
                        XEvent ev;
                        std::memset (&ev, 0, sizeof (ev));

                        ev.type   = ClientMessage;
                        ev.xclient.window = m_window;
                        ev.xclient.format = 32;
                        ev.xclient.message_type = netActiveWindow;
                        ev.xclient.data.l[0]=1; // normal application
                        ev.xclient.data.l[1]=static_cast<long>(m_lastInputTime);
                        ev.xclient.data.;[2]=0; // we don't cur active window

                        int result = XSendEvent (m_dpy,
                                                 DefaultWindow (m_dpy),
                                                 False,
                                                 SubstrctureNotifyMask |
                                                    SubstructureRedirectMask,
                                                &ev);
                        XFlush (m_dpy);

                        if (!result)
                            err << "Setting fullscreen failed could not send \
                                  \"_NET_ACTIVE_WINDOW\" event" << std::endl;
                    } else {
                        XRaiseWindow (m_dpy, m_window);
                        XSetInputFocus (m_dpy, m_window, RevertToPointerRoot,
                                         CurrentTime);
                        XFlush (m_dpy);
                    }
               }/* -----  end of function WindowImplX11::grabFocus ()  ----- */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setVideoMode (const VideoMode &mode)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setVideoMode (const VideoMode &mode)
               {
                   using namespace WindowImplX11;

                   // skip mode switching if the new mode is equal to desktop
                   // mode
                   if (mode == VideoMode::getDesktopMode())
                       return;

                   // Check if the XRandR extension is present
                   int xRandRMajor, xRandRMinor;
                   if (!checkXRandR (xRandRMajor, xRandRMinor)) {
                       // XRandR extension is not supported; no Fullscreen
                       err () << "Fullscreen is not supported. \
                               switching to window mode" << std::endl;
                       return;
                   }
                   ::Window rootWindow = RootWindow (m_dpy, m_scrn);

                   // get the screen resources
                   XRRScreenResources* res = XRRGetScreenResources (
                                                    m_dpy, rootWindow);
                   if (!res) {
                       err () << "Failed to get the current screen \
                           resources for fullscreen mode switching window mode"
                           << std::endl; 
                       return;
                   }
                   RROutput output = getOutputPrimary (rootWindow,
                                                       res,
                                                       xRandRMajor,
                                                       xRandRMinor);

                   // get output info from output
                   XRROutputInfo *outputInfo = XRRGetOutputInfo (
                                                m_dpy, res, output);
                   if (!outputInfo || outputInfo->connection == RR_Disconnected)
                   {
                       XRRFreeScreenResources (res);

                       // if outputInfo->connectionn==RR_Disconnected free
                       // output info
                       if (outputInfo)
                           XRRFreeOutputInfo (outputInfo);
                       err () << "Failed to get output info for fullscreen \
                            mode. Switching to window mode" << std::endl;
                       return;
                   }
                   // Retrieve current RRMode, screen position and rotation
                   XRRCrtcInfo* crtcInfo = XRRGetCrtcInfo (m_dpy,
                                                res, outputInfo->crtc);
                   if (!crtcInfo) {
                       XRRFreeScreenResources (res);
                       XRRFreeOutputInfo (outputInfo);
                       err () << "Failed to get CRTC info for fullscreen mode\
                           switching window mode" << std::endl;
                       return;
                   }
                   bool modeFound = false;
                   RRMode xRandMode;

                   for (int i=0; (i<res->nmode) && !modeFound; i++) {
                       if (crtcInfo->rotation == RR_Rotate_90 ||
                               crtcInfo->rotation == RR_Rotate_270)
                           std::swap(res->modes[i].height, res->modes[i].width);

                       // Check if screen size match
                       if ((res->modes[i].width == mode.width) &&
                           (res->modes[i].height== mode.height)) {
                           xRandMode = res->modes[i].id;
                           modeFound = true;
                       }
                   }
                   if (!modeFound) {
                       XRRFreeScreenResources (res);
                       XRRFreeOutputInfo (outputInfo);
                       err () << "Failed to find a matching RRMode for \
                           fullscreen mode, switching window mode" << std::endl;
                       return;
                   }
                   // save the current video mode before switch to fullscreen
                   m_oldVideoMode = crtcInfo->mode;
                   m_oldRRCrtc = outputInfo->crtc;

                   // Switch to fullscreen mode
                   XRRSetCrtcConfig (m_dpy,
                                     res,
                                     outputInfo->crtc,
                                     CurrentTime,
                                     crtcInfo->x,
                                     crtcInfo->y,
                                     xRandMode,
                                     crtcInfo->rotation,
                                     &output,
                                     1);
                   // Set "this" as the current fullscreen window
                   fullscreenWindow = this;

                   XRRFreeScreenResources (res);
                   XRRFreeOutputInfo (outputInfo);
                   XRRFreeCrtcInfo (crtcInfo);
               }/*  end of function WindowImplX11::setVideoMode ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::resetVideoMode ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::resetVideoMode ()
               {
                   using namespace WindowImplX11;

                   if (fullscreenWindow == this)
                   {
                       // Try to set old configuration
                       // Check if the XRandR extension
                       int xRandRMajor, xRandRMinor;
                       if (checkXRandR (xRandRMajor, xRandRMinor))
                       {
                           XRRScreenResources* res = XRRGetScreenResources (
                                                        m_dpy,
                                                        DefaultRootWindow (
                                                            m_dpy));
                           if (!res) {
                               err () << "Failed to get current screen \
                                   resources to rest the video mode" << 
                                   std::endl; return;
                           }
                           XRRCrtcInfo *crtcInfo = XRRGetCrtcInfo (m_dpy,
                                                            res,
                                                            m_oldRRCrtc);
                           if (!crtcInfo) {
                                XRRFreeScreenResources (res);
                                err () << "Failed to get crtc info to reset \
                                    the video mode" << std::endl;
                                return;
                           }
                           RROutput output;

                           // if version >= 1.3 get the primary screen else
                           // tak the first screen
                           if ((xRandRMajor == 1 && xRandRMinor >=3) ||
                                        xRandRMajor > 1) {
                               output = XRRGetOutputPrimary (m_dpy,
                                                   DefaultRootWindow (m_dpy));
                               // Check if returned output is valid?
                               if (output == None)
                                   output = res->outputs[0];
                           } else {
                               output = res->outputs[0];
                           }
                           XRRSetCrtcConfig (m_dpy,
                                             res,
                                             m_oldRRCrtc,
                                             CurrentTime,
                                             crtcInfo->x,
                                             crtcInfo->y,
                                             m_oldVideoMode,
                                             crtcInfo->rotation,
                                             &output,
                                             1);
                            XRRFreeCrtcInfo (crtcInfo);
                            XRRFreeScreenResources (res);
                       }
                       fullscreenWindow = nullptr;
                   }
               }/*  end of function WindowImplX11::resetVideoMode ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::switchToFullscreen()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::switchToFullscreen()
               {
                   using namespace WindowImplX11;

                   grabFocus ();

                   if (ewmhSupported ())
                   {
                       Atom netWMbypassCompositor = getAtom (
                               "_NET_WM_BYPASS_COMPOSITOR");
                       if (netWMbypassCompositor)
                       {
                           static const unsigned long bypassCompositor = 1;
                           XChangeProperty (m_dpy,
                                            m_window,
                                            netWMbypassCompositor,
                                            XA_CARDINAL,
                                            32,
                                            PropModeReplace,
                                            reinterpret_cast<const unsigned
                                            char*>(&bypassCompositor),
                                            1);
                       }
                       Atom netWMstate = getAtom ("_NET_WM_STATE", true);
                       Atom netWMstateFullscreen =
                            getAtom ("_NET_WM_STAT_FULLSCREEN", true);
                       if (!netWMstat || !netWMstateFullscreen)
                       {
                            err () << "Setting full screen failed, \
                                could not get required Atoms"<< std::endl;
                            return;
                       }
                       XEvent ev;
                       std::memset (&ev, 0, sizeof (ev));

                       ev.type = ClientMessage;
                       ev.xclient.window = m_window;
                       ev.xclient.format = 32;
                       ev.xclient.message_type = netWMstate;
                       ev.xclient.data.l[0] = 1; // _NET_WM_STATE_ADD
                       ev.xclient.data.l[1] = 
                           static_cast<long>(netWMstateFullscreen);
                       ev.xclient.data.l[2] = 0; // No second property
                       ev.xclient.data.l[3] = 1; // Normal Window

                       int result = XSendEvent (m_dpy,
                                        DefaultRootWindow (m_dpy),
                                        False,
                                        SubstructureNotifyMask |
                                            SubstructureRedirectMask,
                                        &ev);
                       if (!result)
                           err () << "Setting full screen failed. \
                               could not send \"_NET_WM_STATE\" event"
                               << std::endl;
                   }

               }/*  end of function WindowImplX11::switchToFullscreen()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::setProtocols ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::setProtocols ()
               {
                    using namespace WindowImplX11;

                    Atom wmProtocols = getAtom ("WM_PROTOCOLS");
                    Atom wmDeleteWindow = getAtom ("WM_DELETE_WINDOW");

                    if (wmProtocols) {
                        err () << "Failed to request WM_PROTOCOLS atom"
                                << std::endl; return;
                    }
                    std::vector<Atom> atoms;
                    
                    if (wmDeleteWindow) {
                        atoms.push_back( (wmDeleteWindow);
                    } else {
                        err() << "Failed to request WM_DELETE_WINDOW atom"
                              << std::endl;
                    }
                    Atom netWMping = None;
                    Atom netWMPid   = None;

                    if (ewmhSupported ()) {
                        netWMping = getAtom ("_NET_WM_PING", true);
                        netWMPid  = getAtom ("_NET_WM_PID", true);
                    }
                    if (netWMping && netWMPid) {
                        const long pid = getpid ();
                        XChangeProperty (m_dpy,
                                         m_window,
                                         netWMPid,
                                         XA_CARDINAL,
                                         32,
                                         PropModeReplace,
                                         reinterpret_cast<const unsigned char*>
                                          (&pid),
                                          1);
                        atoms.push_back(netWMping);
                    }
                    if (!atoms.empty()) {
                        XChangeProperty (m_dpy,
                                         m_window,
                                         wmProtocols,
                                         XA_ATOM,
                                         32,
                                         PropModeReplace,
                                         reinterpret_cast<const unsigned char*>
                                            (atoms.data()),
                                         static_cast<int>(atoms.size()));
                    } else {
                        err () << "Didn't set any window protocols"<< std::endl;
                    }
               }/* -----  end of function WindowImplX11::setProtocols ()  --- */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::initialize ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::initialize ()
               {
                   using namespace WindowImplX11;

                   // Create input context
                   m_inputMethod = OpenXIM ();

                   if (m_inputMethod) {
                       m_inputContext = XCreateIC (m_inputMethod,
                                                   XNClientWindow,
                                                   m_window,
                                                   XNFocusWindow,
                                                   m_window,
                                                   XNInputStyle,
                                                   XNMPreeditNothing |
                                                        XIMStatusnothing,
                                                   nullptr);
                   } else {
                       m_inputContext = nullptr;
                   }

                   if (!m_inputContext)
                       err () << "Failed to create input Context for window \
                           Textentered event wont be able to return \
                           unicode" << std::endl;

                   Atom wmWindowType = getAtom ("_NET_WM_WINDOW_TYPE", false);
                   Atom wmWinTypeNormal = getAtom ("_NET_WM_WINDOW_TYPE_NORMA,",
                                                        false);
                   if (wmWindowType && wmWinTypeNormal) {
                       XChangeProperty (m_dpy,
                                        m_window,
                                        wmWindowType,
                                        XA_ATOM,
                                        32,
                                        PropModeReplace,
                                        reinterpret_cast<const unsigned char*>
                                            (&wmWinTypeNormal),
                                        1);
                   }

                   // Show the window
                   setVisible (true);

                   // Raise the window and grab input focus
                   grabFocus ();

                   // Create Hidden Cursor
                   createHiddenCursor ();

                   // Flush the commands queue
                   XFlush (m_dpy);

                   // Add this window to the global list of window
                   // requre for focus request
                   std::scoped_lock (allWindowsMutex);
                   allWindows.push_back (this);
               }/* ----  end of function WindowImplX11::initialize ()  ---- */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::updateLastTime (::Time time)
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::updateLastTime (::Time time)
               {
                   if (time && (time != m_lastInputTime)) {
                       Atom netWMuserTime = getAtom ("_NET_WM_USER_TIME", true);

                       if (netWMuserTime) {
                           XChangeProperty (m_dpy,
                                            m_window,
                                            netWMuserTime,
                                            XA_CARDINAL,
                                            32,
                                            PropModeReplace,
                              reinterpret_cast<const unsigned char*>(&time),
                                            1);
                       }
                       m_lastInputTime = time;
                   }
               }/* end of function WindowImplX11::updateLastTime ()  */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::createHiddenCursor ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::createHiddenCursor ()
               {
                   // Create the cursor pixmap 1x1 pixel
                   Pixmap cursorPixmap = XCreatePixmap (m_dpy, m_window, 1,1,);
                   GC gc = XCreateGC (m_dpy, cursorPixmap, 0, nullptr);
                   XDrawPoint (m_dpy, cursorPixmap, gc, 0, 0);
                   XFreeGC (m_dpy, gc);

                   // Create the cursor using pixmap as both the shape and
                   // the mask of the cursor
                   XColor  color;
                   color.flags = DoRed | DoGreen | DoBlue;
                   color.red = color.blue = color.green = 0;

                   m_hiddenCursor = XCreatePixmapCursor (m_dpy,
                                                         cursorPixmap,
                                                         cursorPixmap,
                                                         &color,
                                                         &color,
                                                         0, 0);
                   XFreePixmap (m_dpy, cusorPixmap);
               }/* end of function WindowImplX11::createHiddenCursor ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::Cleanup ()
            *  Description:  
            * ==================================================================
            */
           void
               WindowImplX11::Cleanup ()
               {
                   // Restore the previous video mode 
                   resetVideMode ();

                   // Unhide the mouse cursor
                   setMouseCursorVisible (true);
               }/* -----  end of function WindowImplX11::Cleanup ()  ----- */                /* 
            * ===  FUNCTION  ===================================================
            *         Name:  WindowImplX11::processEvent (XEvent& ev)
            *  Description:  
            * ==================================================================
            */
           bool
               WindowImplX11::processEvent (XEvent& ev)
               {
                   using namespace WindowImplX11;

                   // This function implements a workaround to properly discard
                   // reperated key events when necessary. The problem is that
                   // system's key events policy doesn't match to one Xserver
                   // will generate both repeated keyPress and KeyRelease 
                   // events when maintaining a key down while
                   
                   // discard the duplicated keyrelease events when 
                   // KeyRepeatEnabled is true
                   // Discard both duplicate KeyPress and KeyRelease event
                   // when KeyRepeatEnabled is false

                   // Detect repeated key events
                   if (ev.type == KeyRelease) {
                        // find the next keypress event with matching keycode
                        // and time
                        auto it = std::find_if(
                                    m_events.begin(),
                                    m_events.end(),
                                    KeyRepeatFinder (ev.xkey.keycode,
                                                     ev.xkey.time) );
                        if (it != m_events.end()) {
                            // if we don't want repeated events remove
                            // the next KeyPress from queue
                            if (!m_keyRepeat)
                                m_events.erase(it);
                            // This KeyRelease is a repeated event
                            return false;
                        }
                   }

                   // Covert the X11 event to a xwc:event
                    switch (ev.type)
                    {
                        case DestroyNotify:
                            {
                                // The window about to destroyed so cleanup
                                cleanup ();
                                break;
                            }
                        case FocusIn:
                            {
                                // Update input contex
                                if (m_InputContext)
                                    XSetICFocus (m_InputContext);
                                // Grab cursor
                                if (m_cursorGrabbed) {
                                    // Tru multiple time to grab the cursor
                                    for (unsigned int trial=0; 
                                            trial < maxTrialCount; ++trial)
                                    {
                                        int result = XGrabPointer (m_dpy,
                                                      m_window,
                                                      True,
                                                      None,
                                                      GrabModeAsync,
                                                      GrabModeAsync,
                                                      m_window,
                                                      None,
                                                      CurrentTime);
                                        if (result == GrabSuccess) {
                                            m_cursorGrabbed = true;
                                            break;
                                        }
                                        xwc::sleep (xwc::milliseconds (50));
                                    }
                                    if (!m_cursorGrabbed)
                                        err () << "Failed to grab mouse cursor"
                                               << std::endl;
                                }
                                Event event;
                                event.type = Event::GainedFocus;
                                pushEvent (event);

                                // If the window has been previously marked 
                                // urgent notification as result of a focus
                                // request undo that
                                XWMHints* hints = XGetWMHints (m_dpy, m_window);
                                if (hints != nullptr) {
                                    // remove urgency flag from hints
                                    hints->flags &= ~XUrgencyHint;
                                    XSetWMHints (m_dpy, m_window, hints);
                                    XFree (hints);
                                }
                                break;
                            }
                            // Lost focus event
                        case FocusOut:
                            {
                                // Update the input context
                                if (m_inputContext)
                                    XUnsetICFocus (m_inputContext);
                                // Release cursor
                                if (m_cursorGrabbed)
                                    XUngrabPointer (m_dpy, CurrentTime);

                                Event event;
                                event.type = Event::LostFocus;
                                pushEvent (event);
                                break;
                            }
                        case ConfigureNotify:
                            {
                                // Configurenotify can be triggered for other
                                // reason check if the size has actually change
                                if ((ev.xconfigure.width != m_previousSize.x) ||
                                    (ev.xconfigure.height != m_previousSize.y))
                                {
                                    Event event;
                                    event.type   = Event::Resized;
                                    event.size.width = static_cast<unsigned int>
                                        (ev.xconfigure.width);
                                   event.size.height = static_cast<unsigned int>
                                       (ev.xconfigure.height);
                                   pushEvent (event);
                                   m_previousSize.x = ev.xconfigure.width;
                                   m_previousSize.y = ev.xconfigure.height;
                                }
                                break;
                            }
                        case ClientMessage:
                            {
                                // Input method might want random ClientMessage
                                if (!XFilerEvent (&ev, None))
                                {
                                    static Atom wmProtocols = getAtom (
                                            "WM_PROTOCOLS");
                                    // Handle WM protocol messages we support
                                    if (ev.xclient.message_type == wmProtocols)
                                    {
                                        static Atom wmDeleteWindow =
                                            getAtom ("WM_DELETE_WINDOW");
                                        static Atom netWMPing = 
                                              ewmhSupported () ? getAtom (
                                                 "_NET_WM_PING", true) : None;
                                        if ((ev.xclient.format == 32) &&
                                            (ev.xclient.data.l[0]) ==
                                            static_cast<long>(wmDeleteWindow))
                                        {   // handle WM_DELETE_WINDOW msg
                                            Event event;
                                            event.type = Event::Closed;
                                            pushEvent (event);
                                        } else if (netWMPing &&
                                                (ev.xclient.format == 32) &&
                                               (ev.xclient.data.l[0]) ==
                                              static_cast<long>(netWMPing))
                                        {
                                            // handle _NET_WM_PING send pong
                                            ev.xclient.window = 
                                                DefaultRootWindow (m_dpy);
                                            XSendEvent (m_dpy, 
                                                DefaultRootWindow (m_dpy),
                                                False,
                                                SubstructureNotify |
                                                     SubstructureRedirectMask,
                                                &ev);
                                        }
                                    }
                                }
                                break;
                            }
                        case KeyPress:    // Key down event
                            {
                                Keyboard::Key key = Keyboard::Unknown;
                                // Try each KeySym index (modifier group) 
                                // until we get a match
                                for (int i=0; i<4; ++i) {
                                    key = keysymToXW (XLookupKeysym 
                                                      (&ev.xkey,1));
                                    if (key != Keyboard::Unknown)
                                        break;
                                }
                                // Fill the event parameterw
                                // If modifiers are wrong, use XGetModifier -
                                // Mapping to retrieve actual modifier mapping
                                Event  event;
                                event.type   = Event::KeyPressed;
                                event.key.code = key;
                                event.key.alt  = ev.xkey.state & Mod1Mask;
                                event.key.control = ev.xkey.state & ControlMask;
                                event.key.shift = ev.xkey.state & ShiftMask;
                                event.key.system = ev.xkey.state & Mod4Mask;
                                pushEvent (event);

                                // Generate a Text Entered event
                                if (!XFilterEvent (&ev, None)) {
                                    #ifdef X_HAVE_UTF8_STRING
                                    if (m_inputContext) {
                                        Status status;
                                        uint8_t keyBuffer[64];

                                        int length = Xutf8LookupString (
                                                        m_inputContext,
                                                        &ev.xkey,
                                                        reinterpret_cast<char*>
                                                            (keyBuffer),
                                                        sizeof (keyBuffer),
                                                        nullptr,
                                                        &status);
                                        if (status == XBufferOverflow)
                                            err () << "A text Entered event \
                                                      has more than 64 bytes \
                                                      of UTF-8 input. You have \
                                                      typed more than 20 chars"
                                                      << std::endl;
                                        else if (status == XLookupChars) {
                                            // There might be more than 1 char
                                            // in this event so we must iterate
                                            uint32_t unicode = 0;
                                            uint8_t* iter = keyBuffer;
                                            while (iter < keyBuffer + length) {
                                                iter = Utf8::decode (iter,
                                                                 keyBuffer +
                                                                 length,
                                                                 unicode,
                                                                 0);
                                                if (unicode != 0) {
                                                    Event tEvent;
                                                    tEvent.type  = 
                                                             Event::TextEntered;
                                                    tEvent.text.unicode =
                                                            unicode;
                                                    pushEvent (tEvent);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    #endif
                                    {
                                        static XComposeStatus status;
                                        char keyBuffer [16];

                                        if (XLookupString (&ev.xkey, 
                                                           keyBuffer,
                                                           sizeof (keyBuffer),
                                                           nullptr,
                                                           &status)) {
                                            Event tevent;
                                            tevent.type = Event::TextEntered;
                                            tevent.text.unicode =
                                                static_cast<uint32_t>(
                                                        keyBuffer[0]);
                                            pushEvent (tevent);
                                        }
                                    }
                                }
                                updateLastInputTime (ev.xkey.time);
                                break;
                            }
                        case KeyRelease:   // Key up event
                            {
                                Keyboard::Key key = Keyboard::Unknown;

                                // Try each keySym index until we get a match
                                for (int i=0; i<4; ++i) {
                                    key = keysymToXW (XLookupKeysym (
                                                    &ev.xkey, i));
                                    if (key != Keyboard::Unknown)
                                        break;
                                }
                                // Fill the event parameters
                                Event  event;
                                event.type   = Event::KeyReleased;
                                event.key.code = key;
                                event.key.alt  = ev.xkey.state & Mod1Mask;
                                event.control  = ev.xkey.state & ControlMask;
                                event.key.shift= ev.xkey.state & ShiftMask;
                                event.key.system=ev.xkey.state & Mod4Mask;
                                pushEvent (event);

                                break;
                            }
                        case ButtonPress:
                            {
                                // Why button 8 and 9?
                                // Because 4 n 5 are vertical wheel and 6 n 7
                                // are horizontal wheel
                                unsigned int button = ev.xbutton.button;
                                if ((button == Button1) ||
                                    (button == Button2) ||
                                    (button == Button3) ||
                                    (button == 8)       ||
                                    (button == 9)) {
                                    Event ve;
                                    ve.type     = Event::MouseButtonPressed;
                                    ve.mouseButton.x = ev.xbutton.x;
                                    ve.mouseButton.y = ev.xbutton.y;
                                    switch (button) {
                                        case Button1: 
                                            ve.mouseButton.button =
                                                Mouse::Left; break;
                                        case Button2:
                                            ve.mouseButton.button =
                                                Mouse::Middle; break;
                                        case Button3:
                                            ve.mouseButton.button =
                                                Mouse::Right; break;
                                        case 8:
                                            ve.mouseButton.button =
                                                Mouse::XButton1; break;
                                        case 9:
                                            ve.mouseButton.button =
                                                Mouse::XButton2; break;
                                    }
                                    pushEvent (ve);
                                }
                                updateLastInputTime (ev.xbutton.time);
                                break;
                            }
                        case ButtonRelease:   // Mouse button released
                            {
                                unsigned int button = ev.xbutton.button;
                                if ((button == Button1) ||
                                    (button == Button2) ||
                                    (button == Button3) ||
                                    (button == 8)       ||
                                    (button == 9)) {
                                    Event ve;
                                    ve.type     = Event::MouseButtonPressed;
                                    ve.mouseButton.x = ev.xbutton.x;
                                    ve.mouseButton.y = ev.xbutton.y;
                                    switch (button) {
                                        case Button1: 
                                            ve.mouseButton.button =
                                                Mouse::Left; break;
                                        case Button2:
                                            ve.mouseButton.button =
                                                Mouse::Middle; break;
                                        case Button3:
                                            ve.mouseButton.button =
                                                Mouse::Right; break;
                                        case 8:
                                            ve.mouseButton.button =
                                                Mouse::XButton1; break;
                                        case 9:
                                            ve.mouseButton.button =
                                                Mouse::XButton2; break;
                                    }
                                    pushEvent (ve);
                                }
                                else if ((button == Button4) || 
                                         (button == Button5)) {
                                    Event ve;

                                    ve.type     = Event::MouseWheelScrolled;
                                    ve.mouseWheelScroll.wheel = 
                                                   Mouse::VerticalWheel;
                                    ve.mouseWheelScroll.delta = 
                                                (button == Button)?1:-1;
                                    ve.mouseWheelScroll.x =
                                                ev.xbutton.x;
                                    ve.mouseWheelScroll.y =
                                                ev.xbutton.y;
                                    pushEvent (ve);
                                } else if ((button == 6)||(button == 7)) {
                                    Event ve;
                                    ve.type       = Event::MouseWheelScrolled;
                                    ve.mouseWheelScroll.wheel =
                                            Mouse::HorizontalWheel;
                                    ve.mouseWheelScroll.delta =
                                           (button == 6) ? 1 : -1;
                                    ve.mouseWheelScroll.x = ev.xbutton.x;
                                    ve.mouseWheelScroll.y = ev.xbutton.y;
                                    pushEvent (ve);
                                }
                                break;
                            }
                        case MotionNotify:    // mouse moved
                            {
                                Event ve;
                                ve.type     = Event::MouseMoved;
                                ve.mouseMove.x = ev.xmotion.x;
                                ve.mouseMove.y = ev.xmotion.y;
                                pushEvent (ve);

                                break;
                            }
                        case EnterNotify:   // Mouse entered
                            {
                                if (ev.xcrossing.mode == NotifyNormal) {
                                    Event ve;
                                    ve.type = Event::MouseEntered;
                                    pushEvent (ve);
                                }
                                break;
                            }
                        case LeaveNotify:   // mouse left
                            {
                                if (ev.xcrossing.mode == NotifyNormal) {
                                    Event ve;
                                    ve.type   = Event::MouseLeft;
                                    pushEvent (ve);
                                }
                                break;
                            }
                        case UnmapNotify:   // Window unmapped
                            {
                                if (ev.xunmap.window == m_window)
                                    m_windowMapped = false;

                                break;
                            }
                        case VisibilityNotify:    // Window visibility change
                            {
                                // We prefer using visibility Nofify over 
                                // mapNotify because some window managers
                                // like awesome don't internally flag a window
                                // as viewable even after it is mapped but
                                // before it is visible leading to certian 
                                // function call failing with an unviewable
                                // error if called before visibilityNotify
                                // arrives
                                // Emprical testing on most widely used window
                                // managers shows that mapping a window will
                                // always lead to a visibilityNotify event
                                // that is not VisibilityFullyObscured
                                if (ev.xvisibility.window == m_window) {
                                    if (ev.xvisibility.state !=
                                            VisibilityFullyObscured)
                                        m_windowMapped = true;
                                }
                                break;
                            }
                        case PropertyNotify:   // Window property change
                            {
                                if (m_lastInputTime)
                                    m_lastInputTime = ev.xproperty.time;

                                break;
                            }
                    }
                    return true;
               }/*  end of function WindowImplX11::processEvent (XEvent& ev)  */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  bool WindowImplX11::checkXRandR 
            *         (int& xRandRMajor, int& xRandRMinor)
            *  Description:  
            * ==================================================================
            */
           void
             bool WindowImplX11::checkXRandR (int& xRandRMajor, int& xRandRMinor)
            {
                int version;  // Check if XrandR extension is present
                if (!XQueryExtension (m_dpy, "RANDR", 
                                      &version, &version, &version)) {
                    err () << "XRandR extension is not supported" << std::endl;
                    return false;
                }
                // Check XRandR version 1.2 required
                if (!XRRQueryVersion (m_dpy, &xRandRMajor, &xRandRMinor) ||
                     xRandRMajor < 1 || (xRandRMajor == 1 && xRandRMinor <2)) {
                    err () << "XRandR is too old" << std::endl;
                    return false;
                }
                return true;
            }/* end of function bool WindowImplX11::checkXRandR ()   */
           /* 
            * ===  FUNCTION  ===================================================
            *         Name:  RROutput WindowImplX11::getOutputPrimary (::Window& 
            *         rootWindow, XRRScreenResources* res, int xRandRMajor, 
            *         int xRandRMinor)
            *  Description:  
            * ==================================================================
            */
           RROutput WindowImplX11::getOutputPrimary (::Window& rootWindow, 
                     XRRScreenResources* res, int xRandRMajor, int xRandRMinor) 
               {
                    // if xRandR version >= 1.3 get primary screen
                  if ((xRandRMajor == 1 && xRandRMinor >= 3) || xRandRMajor >1){
                      RROutput output = XRRGetOutputPrimary (m_dpy,
                                                    rootWindow);
                      // Check if requred output is valid?
                      if (output == None)
                          return res->outputs[0];
                      else
                          return output;
                  }
                  // xRandR version can't get the primary screen
                  return res->outputs[0];
               }/* end of function RROutput WindowImplX11::getOutputPrimary () */            /* 
            * ===  FUNCTION  ===================================================
            *         Name:  Vector2i WindowImplX11::getPrimaryMonitorPosition ()
            *  Description:  
            * ==================================================================
            */
           Vector2i WindowImplX11::getPrimaryMonitorPosition ()
               {
                   Vector2i mPosition;
                   // get root window
                   ::Window rootWindow = RootWindow (m_dpy, m_scrn);

                   // get the screen resources
                   XRRScreenResources* res = XRRGetScreenResources (m_dpy,
                                                rootWindow);
                   if (!res) {
                       err () << "Failed to get current screen resources for \
                                  primary monitor" << std::endl;
                       return mPosition;
                   }
                   // Get xRandR version
                   int xRandRMajor, xRandRMinor;
                   if (!checkXRandR (xRandRMajor, xRandRMinor))
                       xRandRMajor = xRandRMinor = 0;
                   RROutput output = getOutputPrimary (rootWindow, res,
                                        xRandRMajor, xRandRMinor);
                   // get output info from output
                   XRROutputInfo* outputInfo = XRRGetOutputInfo (m_dpy,
                                                    res, output);
                   if (!outputInfo || outputInfo->connection == RR_Disconnected)
                    {
                        XRRFreeScreenResources (res);

                        // if outputInfo->connection == RR_Disconnected? Free
                        if (outputInfo)
                            XRRFreeOutputInfo (outputInfo);

                        err () << "Failed to get output info for primary mon \
                                    monitor position" << std::endl;
                        return mPosition;
                    }
                   // Retrieve current RRMode screen positon and rotation
                   XRRCrtcInfo* crtcinfo = XRRGetCrtcInfo (m_dpy, res,
                                                        outputInfo->crtc);
                   if (!crtcInfo) {
                        XRRFreeScreenResources (res);
                        XRRFreeOutputInfo (outputInfo);
                        err () << "Failed to get CRTC info for primary monitor \
                                        system" << std::endl;
                        return mPosition;
                   }

                   mPosition.x = crtcInfo->x;
                   mPosition.y = crtcInfo->y;

                   XRRFreeCrtcInfo (crtcInfo);
                   XRRFreeOutputInfo (outputInfo);
                   XRRFreeScreenResources (res);

                   return mPosition;
               }/* Vector2i WindowImplX11::getPrimaryMonitorPosition ()*/
    }   // end of namespace priv
}       // end of namespace xwc

/* ----------------------------- Eof WindowImplX11.cpp -------------------*/
