/*
 * ==========================================================================
 *
 *       Filename:  menu.h
 *
 *    Description:  menu.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:52:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _MENU_H_
#define _MENU_H_

typedef struct Menu Menu;
struct Menu {
        struct Funcs   *funcs;
        int            width, nsubws;
        XContext       ctxt;
        Window         *subws;
};

extern struct Funcs *MenuFuncs;
extern struct Funcs *PieMenuFuncs;

Window newMenu (char *progname, Display *dpy, XrmDatabase db,
                XContext ctxt, char *name);

Window newPieMenu (char *progname, Display *dpy, XrmDatabase db,
                   XContext ctxt, char *name);

Window *menuSetSubWins (Display *dpy, XContext ctxt, Window menu,
                        Window *subws, int nsubws);

void pieMenuMap (Window piemenuwin, XEvent *ev, XContext ctxt);

#endif
/* ----------------------------> end of menu.h <-----------------------*/
