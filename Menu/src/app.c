/*
 * ========================================================================
 *
 *       Filename:  app.c
 *
 *    Description:  App.c implementation file 
 *
 *        Version:  1.0
 *        Created:  06/11/20 18:42:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 * =========================================================================
 * I had the same problem. Using XSetClassHint solves the problem:
 *
 *   XClassHint *class_hint = XAllocClassHint();
 *   
 *   if (class_hint)
 *   {
 *       class_hint->res_name = class_hint->res_class = (char *)argv[0]
 *       XSetClassHint(display, window, class_hint);
 *       XFree(class_hint);
 *   }
 *
 * =========================================================================
 */
#include <X11/xpm.h>

#include "funcs.h"
#include "app.h"
#include "rose.h"
#include "myMacro.h"

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newApp (char *progname, Display *dpy, 
 *                               XrmDatabase db, XContext ctxt, int width, 
 *                               int height, int argc, char **argv)
 *  Description:  return Window
 * ===================================================================
 */
Window 
newApp (char *progname, Display *dpy, XrmDatabase db, XContext ctxt, 
        int width, int height, int argc, char **argv)
{
    App            *mainwindow;
    char           resourcename[256], *tmp;
    Window         win;

    char           *win_name  = "Xtut15_MenuSystem";
    char           *icon_name = "Xtut15";
    XTextProperty  winName, iconName;

    XSizeHints     *size_hints;    /* Window Manager hits provide to  */
    XWMHints       *wm_hints;      /* window properties */
    XClassHint     *class_hints;

    Pixmap         icon_pixmap;

    UNUSED (height);
    UNUSED (width);

    mainwindow = calloc (sizeof (*mainwindow), 1);
    if (!mainwindow) {
        fprintf (stderr, "Unable to allocate main window\n"); exit (3);
    }
    mainwindow->funcs = AppFuncs;

    /* Read the default data from xtut15.resources file if exist? */
    sprintf (resourcename, "%s.background", progname);
    mainwindow->background = getColor (dpy, db, resourcename, 
                                       resourcename, "DargGree");

    sprintf (resourcename, "%s.border", progname);
    mainwindow->border = getColor (dpy, db, resourcename, 
                                         resourcename, "LightGreen");

    sprintf (resourcename, "%s.width", progname);
    tmp = getResource (dpy, db, resourcename, resourcename, "400");

    mainwindow->width = 400;
    free (tmp);
    sprintf (resourcename, "%s,height", progname);
    tmp = getResource (dpy, db, resourcename, resourcename, "400");
    mainwindow->height = 400;
    free (tmp);

    if (!(size_hints = XAllocSizeHints())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocSizeHints'\n",
                argv[0]); exit (31);
    }
    if (!(wm_hints = XAllocWMHints())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocateWMHint'\n",
                argv[0]); exit (31); 
    }
    if (!(class_hints = XAllocClassHint())) {
        fprintf (stderr, "%s: failed to allocate 'XAllocateClassHint'\n",
                argv[0]); exit (311);
    }

    size_hints->flags = PPosition | PSize | PMinSize;
    size_hints->min_width = 400;
    size_hints->min_height= 400;
    size_hints->max_width = DisplayWidth (dpy, DefaultScreen (dpy));
    size_hints->max_height= DisplayHeight (dpy, DefaultScreen (dpy));

    /*  Disabled currently
    mainwindow->width = size_hints->max_width;
    mainwindow->height = size_hints->max_height;     */

    class_hints->res_name = argv[0];
    class_hints->res_class= "Project:Xtut15";

    if (XStringListToTextProperty (&win_name, 1, &winName) == 0) {
        fprintf (stderr, "%s: structure allocation for winName failed\n",
                argv[0]); exit (31);
    }
    if (XStringListToTextProperty (&icon_name , 1, &iconName) == 0) {
        fprintf (stderr,"%s: Structure allocation to iconName failed\n",
                argv[0]); exit (31);
    }                                                                          

    win = XCreateSimpleWindow (dpy,
                               DefaultRootWindow (dpy),
                               0, 0,
                               mainwindow->width,
                               mainwindow->height,
                               0,
                               mainwindow->border,
                               mainwindow->background);

    icon_pixmap = XCreateBitmapFromData (dpy, 
                                         win,
                                         Penguin_bits,
                                         Penguin_width,
                                         Penguin_height);  
    wm_hints->initial_state = NormalState;
    wm_hints->input = True;
    wm_hints->icon_pixmap = icon_pixmap;
    wm_hints->flags = StateHint | IconPixmapHint | InputHint;
                                        
    XSelectInput (dpy, win, 
                  ButtonPressMask     |
                  ButtonReleaseMask   |
                  StructureNotifyMask |
                  ExposureMask);

    XSetWMProperties (dpy,
                      win,
                      &winName,
                      &iconName,
                      argv,
                      argc,
                      size_hints,
                      wm_hints,
                      class_hints);

    Atom wmDeleteMsg = XInternAtom (dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (dpy, win, &wmDeleteMsg, 1);

    Atom win_icon = XInternAtom (dpy, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom (dpy, "CARDINAL", False);

    int length = 2 + 16 * 16 + 2 + 32 * 32;
    XChangeProperty (dpy,
                     win,
                     win_icon,
                     cardinal, 32,
                     PropModeReplace,
                     (const unsigned char *) buffer, length);

    XSetWMIconName (dpy, win, &iconName);
    mainwindow->ctxt = ctxt;
    XSaveContext (dpy, win, ctxt,  (XPointer)mainwindow);

    Xutf8SetWMProperties (dpy, win, progname, progname, argv, argc,
                          NULL, NULL, NULL);
    return win; 
} /*              end of function Window newApp ()  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  appConfigureNotify (Block *block, XEvent *cv)
 *  Description:  
 * ===================================================================
 */
static void
appConfigureNotify (Block *block, XEvent *ev)
{
    App              *self = &block->app;
    XConfigureEvent  *xce  = &ev->xconfigure;
    MenuBar          *menubar;

    if (self->height != xce->height) {
        self->height = xce->height;
    }
    if (self->width == xce->width)  return;
    self->width = xce->width;

    if (!self->menubar) return;
    if (XFindContext (xce->display, self->menubar, self->ctxt,
                      (XPointer*)&menubar))
        return;
    resizeBlock ((Block*)menubar, self->menubar, self->width,
                         self->menubarHeight, ev);
} /*  end of function appConfigureNotify (Block *block, XEvent *cv)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window setAppMenuBar (Display *dpy, XContext ctxt, 
 *                                      Window w, Window menubar, int width, 
 *                                      int menubarHeight)
 *  Description:  
 * ===================================================================
 */
Window 
setAppMenuBar (Display *dpy, XContext ctxt, Window w, Window menubar, 
               int width, int menubarHeight) 
{
    App       *app;
    Window    old;

    XFindContext (dpy, w, ctxt, (XPointer *)&app);
    old = app->menubar;
    app->menubar = menubar;
    app->menubarHeight = menubarHeight;
    XResizeWindow (dpy, menubar, width, menubarHeight);

    return old;
} /*  end of function Window setAppMenuBar (Display *dpy, XContext ctxt, Window w, Window menubar, int width, int menubarHeight)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window setAppContextMenu (Display *dpy, XContext ctxt, 
 *                                          Window w, Window contextmenu)
 *  Description:  
 * ===================================================================
 */
Window 
setAppContextMenu (Display *dpy, XContext ctxt, Window w, 
                    Window contextmenu)
{
    App     *app;
    Window  old;

    XFindContext (dpy, w, ctxt, (XPointer *) &app);

    old = app->contextmenu;
    app->contextmenu = contextmenu;

    return old;
} /*  end of function Window setAppContextMenu (Display *dpy, XContext ctxt, Window w, Window contextmenu)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonPress (Block *block, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
static void
buttonPress (Block *block, XEvent *ev)
{
    if (ev->xbutton.button == Button3) {
        App  *app = &block->app;

        if (!app || !app->contextmenu) return;

        pieMenuMap (app->contextmenu, ev, app->ctxt);
        XUngrabPointer (ev->xbutton.display, ev->xbutton.time);
    }
} /* end of function buttonPress (Block *block, XEvent *ev)  */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonRelease (Block *block, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
    void
buttonRelease (Block *block, XEvent *ev)
{
    if (ev->xbutton.button == Button3) {
        App  *app = &block->app;

        if (!app  || !app->contextmenu) return;

        XUnmapWindow (ev->xany.display, app->contextmenu);
    }
} /*  end of function buttonRelease (Block *block, XEvent *ev)  */

static struct Funcs _AppFuncs = {
              appConfigureNotify,
              NULL,
              NULL,
              NULL,
              buttonPress,
              buttonRelease
};
struct Funcs *AppFuncs = &_AppFuncs;

/* -----------------------------> end of app.c <------------------------- */
