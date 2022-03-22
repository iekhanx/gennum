/*
 * ==========================================================================
 *
 *       Filename:  menubar.h
 *
 *    Description:  menubar.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:46:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _MENUBAR_H_
#define _MENUBAR_H_

typedef struct MenuBar MenuBar;
struct MenuBar {
    struct Funcs   *funcs;
    Window         helpButton; /* kepp at far right  */
    int            width;
    XContext       ctxt;
};

extern struct Funcs *MenuBarFuncs;

Window newMenuBar (char *progname, Display *dpy, Window parent,
                   XrmDatabase db, XContext ctxt, char *name, 
                   int x, int y, int width, int height);

Window setHelpButton (Display *dpy, XContext ctxt, Window mb, 
                     Window helpButton, int x);

#endif
/* ------------------------> end of menubar.h <-------------------------*/
