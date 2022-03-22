/*
 * ==========================================================================
 *
 *       Filename:  app.h
 *
 *    Description:  App.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:07:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _APP_H_
#define _APP_H_

typedef struct App App;
struct App {
    struct Funcs  *funcs;
    Window        menubar;
    Window        contextmenu;
    XContext      ctxt;
    int           menubarHeight, width, height;
    unsigned long border, background, foreground;
};

extern struct Funcs *AppFuncs;

Window newApp (char *progname, Display *dpy, XrmDatabase db, XContext ctxt,
                int width, int height, int argc, char **argv);

Window setAppMenuBar (Display *dpy, XContext ctxt, Window w, Window menubar,
                 int width, int menubarHeight);

Window setAppContextMenu (Display *dpy, XContext ctxt, Window w,
                          Window contextmenu);

#endif

/* ---------------------> end of app.h <----------------------------- */
