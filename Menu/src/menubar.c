/*
 * ========================================================================
 *
 *       Filename:  menubar.c
 *
 *    Description:  Menubar.c  
 *
 *        Version:  1.0
 *        Created:  06/11/20 21:23:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "funcs.h"
#include "menubar.h"


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  menubarConfigureNotify (Block *block, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
 static void
menubarConfigureNotify (Block *block, XEvent *ev)
{
    MenuBar   *self = &block->menubar;
    Button    *help = NULL;
    XConfigureEvent *xce = &ev->xconfigure;

    if (xce->width == self->width) return;
    self->width = xce->width;
    if (!self->helpButton) return;
    XFindContext (xce->display, self->helpButton, 
                  self->ctxt, (XPointer*)&help);
    if (!help) {
        printf ("Not found help button %p %p %x\n", 
                 (void*)self->helpButton, 
                 xce->display,
                 self->ctxt);
        return;
    }
    XMoveWindow (xce->display, self->helpButton, xce->width - help->width, 0);

    resizeBlock ((Block*)help, self->helpButton, help->width,
                               xce->height, ev);
} /*  end of function menubarConfigureNotify (Block *block, XEvent *ev)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newMenuBar (char *progname, Display *dpy, 
 *                                   Window parent, XrmDatabase db, 
 *                                   XContext ctxt, char *name, int x, 
 *                                   int y, int width, int height)
 *  Description:  
 * ===================================================================
 */
Window 
newMenuBar (char *progname, Display *dpy, Window parent, 
            XrmDatabase db, XContext ctxt, char *name, int x, 
            int y, int width, int height)
{
    Window  win;
    MenuBar *menubar;
    char    resourcename[256], classname[256];
    unsigned long background;

    menubar = calloc (sizeof (*menubar), 1);
    if (!menubar) {
        fprintf (stderr, "Unable loocate space for %s\n", name); exit (32); 
    }
    menubar->funcs = MenuBarFuncs;
    menubar->ctxt  = ctxt;

    sprintf (resourcename, "%s.%s.background", progname, name);
    sprintf (classname, "%s.background", progname);
    background = getColor (dpy, db, resourcename, classname, "conrnflowerblue");

    win = XCreateSimpleWindow (dpy,
                               parent,
                               x, y,
                               width, height,
                               0, 0,
                               background);
    XSelectInput (dpy, win, StructureNotifyMask);

    XSaveContext (dpy, win, ctxt, (XPointer)menubar);
    XMapWindow (dpy, win);

    return win;
} /* end of function Window newMenuBar (char *progname, Display *dpy, Window parent, XrmDatabase db, XContext ctxt, char *name, int x, int y, int width, int height)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window setHelpButton (Display *dpy, XContext ctxt, 
 *                                      Window win, Window helpButton, int x)
 *  Description:  
 * ===================================================================
 */
Window 
setHelpButton (Display *dpy, XContext ctxt, Window win, 
               Window helpButton, int x)
{
    MenuBar   *mb;
    Window    old;

    XFindContext (dpy, win, ctxt, (XPointer*)&mb);
    
    old = mb->helpButton;
    mb->helpButton = helpButton;
    XMoveWindow (dpy, mb->helpButton, x, 0);

    return old;
} /*  end of function Window setHelpButton (Display *dpy, XContext ctxt, Window win, Window helpButton, int x)  */

static struct Funcs _MenuBarFuncs = {
            menubarConfigureNotify,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
};
struct Funcs *MenuBarFuncs = &_MenuBarFuncs;

/* -------------------------------> end of menubar.c <----------------------*/
