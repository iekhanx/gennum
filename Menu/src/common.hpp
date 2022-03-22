/*
 * ==========================================================================
 *
 *       Filename:  common.hpp
 *
 *    Description:  Common class declaration 
 *
 *        Version:  1.0
 *        Created:  07/03/22 17:57:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  © Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _COMMON_HPP_
#define _COMMON_HPP_
///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <X11/Xlib.h>     /* xlib  */
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/Xatom.h>
#include <X11/xpm.h>
#include <X11/Xos.h>
#include <sys/utsname.h>
#include <sys/stat.h>

#include <cstdio>       /* C++ runtime libs */
#include <cstdlib>
#include <string>


#define DefGC(dpy) DefaultGC(dpy, DefaultScreen(dpy)) 
#define NUM_FONTS   30
#define MAX_IMAGES 100

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#pragma GCC diagnostic ignored "-Wstringop-overflow="
#pragma GCC diagnostic ignored "-Wpointer-sign"

namespace xlib
{
namespace priv
{
class common
{
  public:

  ////////////////////////////////////////////////
  // Stricture 
  ////////////////////////////////////////////////
      typedef struct {
          Font fs;
          char *name;
      } FontCache;

      static struct Image {
          int           used;
          XpmAttributes xAtt;
          Pixmap        pixmap;
          Pixmap        clipmask;
          Pixmap        saved;
          int           x, y;
      } Images[MAX_IMAGES];

      typedef union Block Block;

      /////////////////////////////////////////////////////////////
      /// \brief set up XrmDatabase
      /// \return  Read command line to access database
      /////////////////////////////////////////////////////////////
      XrmDatabase setupDB (Display *dpy, XrmOptionDescRec *xrmTable, 
              int nCommandLineResources, const char *progname,
              int *argc, char **argv);

      /////////////////////////////////////////////////////////////
      /// \brief Read sources from local database file
      /// \param Display
      /////////////////////////////////////////////////////////////
      char *getResource (Display *dpy, XrmDatabase db, char *name, 
              char *cl, char *def);

      /////////////////////////////////////////////////////////////
      /// \brief Get Color setting from local database
      /////////////////////////////////////////////////////////////
      unsigned long getColor (Display *dpy, XrmDatabase db, char *name,
              char *cl, char *def);

      /////////////////////////////////////////////////////////////
      /// \brief Get Font to be used in apps 
      /////////////////////////////////////////////////////////////
      XFontStruct *getFont (Display *dpy, XrmDatabase db, char *name,
              char *cl, char *def);

      /////////////////////////////////////////////////////////////
      /// \brief Convert char to binary length
      ////////////////////////////////////////////////////////////
      int XChar2bLen (XChar2b *str);

      ///////////////////////////////////////////////////////////
      /// \brief Convert utf8 to XChar2b utility function
      ///////////////////////////////////////////////////////////
      int utf8toXChar2b (XChar2b *ourput_r, int outsize, 
              const char *input, int inlen);

      ///////////////////////////////////////////////////////////
      /// \brief ResizeBlock 
      ///////////////////////////////////////////////////////////
      void resizeBlock (Block *block, Window win, int width, 
              int height, XEvent *ev);
      ///////////////////////////////////////////////////////////
      /// \brief Convert char value
      ///////////////////////////////////////////////////////////
      char *get_var (char *p);

    }; // end of class common
} // end of namespace priv
} // end of namespace xlib
#endif   // _COMMON_HPP_
