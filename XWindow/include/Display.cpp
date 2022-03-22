/*
 * ========================================================================
 *
 *       Filename:  Display.cpp
 *
 *    Description:  Class Display implementation file 
 *
 *        Version:  1.0
 *        Created:  07/01/22 14:36:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
//////////////////////////////////////////////
// Headers
/////////////////////////////////////////////
#include <X11/keysym.h>
#include <mutex>
#include <unordered_map>
#include <cassert>
#include <cstdlib>

#include "Display.hpp"
#include "Err.hpp"

namespace
{
    Display* sharedDisplay = nullptr;
    unsigned int referenceCount = 0;
    XIM sharedXIM = NULL;
    unsigned int referenceCountXIM = 0;
    std::recursive_mutex mutex;

    using AtomMap = std::unordered_map <std::string, Atom>;
    AtomMap atoms;
}

namespace xwc
{
    namespace priv
    {
        Display* OpenDisplay ()
        {
            std::scoped_lock lock (mutex);
            if (referenceCount == 0)
            {
                sharedDisplay = XOpenDisplay (nullptr);
                //Open display failed output the error message n Terminate
                if (!sharedDisplay) {
                    err () << "Failed to open X11 display. Make sure DISPLAY \
                                environment variable set correctly?" <<
                                std::endl;
                }
            } 
            referenceCount++;
            return sharedDisplay;
        }
        
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  CloseDisplay (Display* dpy)
         *  Description:  
         * ===================================================================
         */
        void
            CloseDisplay (Display* dpy) 
            {
                std::scoped_lock lock(mutex);
                assert (dpy == sharedDisplay);

                referenceCount--;
                if (referenceCount == 0)
                    XCloseDisplay (dpy);
            }/* -----  end of function CloseDisplay (Display* dpy)  ----- */
        
        /* 
         * ===  FUNCTION  ====================================================
         *         Name:  XIM OpenXIM ()
         *  Description:  
         * ===================================================================
         */
         XIM 
            OpenXIM ()
            {
                std::scoped_lock lock (mutex);
                assert (sharedDisplay != nullptr);

                if (referenceCountXIM == 0) {
                    // Create a new XIM instance

                    // we need the default environment locale and X locale for
                    // opeining the IM and properly receiving text
                    // First save the previous ones
                    const char *p;
                    std::string prevLoc ((p = setlocale(LC_ALL, nullptr)) 
                                                                ? p : "");
                    std::string prevXLoc ((p = XSetLocaleModifiers (nullptr))
                                                                ? p : "");
                    // set the locale from environment
                    setlocale (LC_ALL, "");
                    XSetLocaleModifiers ("");

                    // Create input context
                    sharedXIM = XOpenIM (sharedDisplay, 
                                    nullptr, nullptr, nullptr);
                    if (prevLoc.length () != 0)
                        setlocale (LC_ALL, prevLoc.c_str());

                    if (prevXLoc.length() != 0)
                        XSetLocaleModifiers (prevXLoc.c_str());
                }
                referenceCountXIM++;
                return sharedXIM;
            }/* -----  end of function XIM OpenXIM ()  ----- */

         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  CloseXIM (XIM xim)
          *  Description:  
          * ===================================================================
          */
         void
             CloseXIM (XIM xim)
             {
                std::scoped_lock lock (mutex);

                assert (xim == sharedXIM);

                referenceCountXIM--;

                if ((referenceCountXIM == 0) && (xim != nullptr))
                    XCloseIM (xim);
             }	/* -----  end of function CloseXIM (XIM xim)  ----- */

         /* 
          * ===  FUNCTION  ====================================================
          *         Name:  Atom getAtom (const std::string& name, 
          *                                 bool onlyIfExists)
          *  Description:  
          * ===================================================================
          */
         Atom 
             getAtom (const std::string& name, bool onlyIfExists)
             {
                 if (auto it = atoms.find (name); it != atoms.end())
                     return it->second;

                 Display* dpy = OpenDisplay ();
                 
                 Atom atom = XInternAtom (dpy, name.c_str(), 
                                        onlyIfExists ? True : False);

                 CloseDisplay (dpy);
                 atoms[name] = atom;

                 return atom;
             }	/* end of function Atom getAtom (const std::string& , bool)  */
    } // end of priv
}     // end of xwc

