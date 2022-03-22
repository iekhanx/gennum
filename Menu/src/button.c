/*
 * ========================================================================
 *
 *       Filename:  button.c
 *
 *    Description:  A complete new file created for button.c routine. 
 *
 *        Version:  1.0
 *        Created:  25/11/20 16:54:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "funcs.h"
#include "button.h"
#include "gradient.h"
#include "myMacro.h"


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newXButton
 *  Description:  return window with context set and saved.
 * ===================================================================
 */
static Window 
newXButton (Button *button, char *progname, Display *dpy, Window parent,
            XrmDatabase db, XContext ctxt, char *name, int x, int y,
            int width, int height)
{
    Window         win;
    char           resourcename [256]={""};
    char           classname [256]={""};
    char           *text;
    int            len;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling newXButton");
#endif

    sprintf (resourcename, "%s.%s", progname, name);
    sprintf (classname,    "%s,%s", progname, name);
    text = getResource (dpy, db, resourcename, classname, name);

    sprintf (resourcename, "%s.%s.font", progname, name);
    sprintf (classname,    "%s.font",    progname);
    button->font = getFont (dpy, db, resourcename, classname, "lucidasans-12");
    button->font_ascent = button->font->ascent;

    len = strlen (text);
    button->text = malloc (sizeof (*button->text)*(len+1));
    if (!button->text)
    {
        fprintf (stderr, "Can't display text: %ld\n",
                           (sizeof (*button->text)*(len+1)));
        len = 0; exit (33);
    } else {
        len = utf8toXChar2b (button->text, len, text, len);
        button->text_width = XTextWidth16 (button->font, button->text, len);
    }

    sprintf (resourcename, "%s.%s.foreground", progname, name);
    sprintf (classname,    "%s.foreground", progname);
    button->foreground = getColor (dpy, db, resourcename, classname, "blue");

    sprintf (resourcename, "%s.%s.border", progname, name);
    sprintf (classname,    "%s.border", progname);
    button->border = getColor (dpy, db, resourcename, classname, "lightblue");

    if (width < button->text_width + 2*button->font->ascent) {
        width = button->text_width + 2*button->font->ascent;
    }
    button->width = width;

    if (height < 2*button->font->ascent) {
        height = 2*button->font_ascent;
    }
    button->height = height;

    if (button->height <= 0) {
        fprintf (stderr, "Font Ascent*2 = %d\n",button->height);
    }
    
    sprintf (resourcename, "%s.%s.background", progname, name);
    sprintf (classname,    "%s.background", progname);
    button->background = getResource (dpy, db, resourcename, classname,
                                               "cornflowerblue");

    win = XCreateSimpleWindow (dpy,
                               parent,
                               x, y,
                               width, height,
                               0,
                               button->border,
                               0);
    if (!win)
    {
        fprintf (stderr, "Unable to create window\n"); exit (31);
    }
    button->bgpix = 0;

    XSelectInput (dpy, win,
                  ButtonPressMask      |
                  ButtonReleaseMask    |
                  StructureNotifyMask  |
                  ExposureMask         |
                  LeaveWindowMask      |
                  EnterWindowMask);

    XSaveContext (dpy, win, ctxt, (XPointer)button);
    XMapWindow (dpy, win);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif

    return win;
}		/* -----  end of function Window newXButton  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  newButton
 *  Description:  
 * ===================================================================
 */
    Window
newButton (char *progname, Display *dpy, Window parent, XrmDatabase db,
           XContext ctxt, char *name, int x, int y, int width, int height,
           int center, Callback callback, void *cbdata)

{   Button      *button;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling... ");
#endif

    button = calloc (sizeof (*button), 1);
    if (!button)  {
        fprintf (stderr, "Unable to allocate memory\n"); exit (32);
    }
    button->funcs = ButtonFuncs;
    button->center = center;
    button->buttonRelease = callback;
    button->cbdata = cbdata;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif

    return newXButton (button, progname, dpy, parent, db, ctxt, name, x, y,
                        width, height);
}		/* -----  end of function newButton  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonRedraw
 *  Description:  
 * ===================================================================
 */
    void
buttonRedraw (Button *button, XEvent *ev)
{
    int x, y, len;
    XGCValues xgcv;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif
    xgcv.line_width = 1;
    xgcv.line_style = LineSolid;
    xgcv.foreground = button->foreground;
    xgcv.font = button->font->fid;

    XChangeGC (ev->xany.display, 
               DefGC (ev->xany.display),
               GCForeground    |
               GCLineWidth     |
               GCLineStyle     |
               GCFont,
               &xgcv);

    if (button->text) {
        len = XChar2bLen (button->text);
        /* Left justify all meny and menubar button texts */
        x = button->center * ((button->width-button->text_width)/2);
        y = (button->height + button->font_ascent)/2;
        XDrawString16 (ev->xany.display,
                       ev->xany.window, 
                       DefGC(ev->xany.display),
                       x, y,
                       button->text,
                       len);
    } else {
        XDrawLine (ev->xany.display, 
                   ev->xany.window, 
                   DefGC (ev->xany.display),
                   0, 0,
                   button->width, 
                   button->height);

        XDrawLine (ev->xany.display, 
                   ev->xany.window,
                   DefGC(ev->xany.display),
                   button->width,
                   0, 0,
                   button->height);
    }

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif        
}		/* -----  end of function buttonRedraw  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonExpose
 *  Description:  
 * ===================================================================
 */
static void
buttonExpose (Block *blk, XEvent *ev)
{

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif

    if (ev->xexpose.count > 0)  return;

    if (!blk->button.bgpix) {
         blk->button.bgpix = getGradPixmap (ev->xany.display,
                                            1,
                                            blk->button.height,
                                            blk->button.background);
         XSetWindowBackgroundPixmap (ev->xany.display,
                                     ev->xany.window,
                                     blk->button.bgpix);
         XClearArea (ev->xany.display,
                     ev->xany.window,
                     0, 0,
                     blk->button.width,
                     blk->button.height,
                     True);
         return;
    }

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif

    buttonRedraw (&blk->button, ev);
}		/* -----  end of function buttonExpose  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonConfigureNotify
 *  Description:  
 * ===================================================================
 */
static void
buttonConfigureNotify (Block *b, XEvent *ev)
{
    Button   *btn = &b->button;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif

    if (!btn) return;

    if (btn->width != ev->xconfigure.width   ||
           btn->height != ev->xconfigure.height) {
        if (btn->height != ev->xconfigure.height) {
            if (btn->bgpix) {
                freePixmap (ev->xany.display,
                            btn->width,
                            btn->height,
                            btn->background);
            }
            btn->height = ev->xconfigure.height;
            btn->bgpix = getGradPixmap (ev->xany.display,
                                           1,
                                           btn->height,
                                           btn->background);
            XSetWindowBackgroundPixmap (ev->xany.display,
                                        ev->xany.window,
                                        btn->bgpix);
        }
        btn->width = ev->xconfigure.width;
        XClearWindow (ev->xany.display, ev->xany.window);
        /* Redraw button window */
        buttonRedraw (btn, ev);
    }

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif
}		/* -----  end of function buttonConfigureNotify  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonEnter
 *  Description:  
 * ===================================================================
 */
    void
buttonEnter (Block *b, XEvent *ev)
{
    Button     *btn = &b->button;

    XSetWindowAttributes   attr;
    GC                     gc = DefGC(ev->xany.display);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif        
    if (!btn)   return;

    attr.background_pixel = btn->border;
    attr.border_pixmap = btn->bgpix;

    XChangeWindowAttributes (ev->xany.display,
                             ev->xany.window,
                             CWBackPixel      |
                             CWBorderPixel,
                             &attr);
    XSetForeground (ev->xany.display, gc, btn->border);
    XFillRectangle (ev->xany.display,
                    ev->xany.window,
                    gc,
                    0, 0,
                    btn->width,
                    btn->height);
    buttonRedraw (btn, ev);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif
}		/* -----  end of function buttonEnter  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonLeave
 *  Description:  
 * ===================================================================
 */
    void
buttonLeave (Block *b, XEvent *ev)
{
    Button    *btn = &b->button;
#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif

    XSetWindowAttributes  attr;

    if (!btn)  return;
    
    attr.background_pixmap = btn->bgpix;
    attr.background_pixel  = None;
    attr.border_pixel  = btn->border;
    attr.border_pixmap = None;

    XChangeWindowAttributes (ev->xany.display,
                             ev->xany.window,
                             CWBackPixmap   |
                             CWBorderPixel,
                             &attr);
    XClearArea (ev->xany.display,
                ev->xany.window,
                0, 0,
                btn->width,
                btn->height, 
                True);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif
}		/* -----  end of function buttonLeave  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  newMenuBarButton
 *  Description:  
 * ===================================================================
 */
    Window
newMenuBarButton (char *progname, Display *dpy, Window parent,
                  XrmDatabase db, XContext ctxt, char *name, int x,
                  int y, int width, int height, Window menu)
{
    Block   *btn;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif
        
    btn = calloc (sizeof (*btn), 1);
    if (!btn) {
        fprintf (stderr, "Unable to allocate memory\n"); exit (32);
    }
    btn->funcs = MenuBarButtonFuncs;
    btn->menubarbutton.ctxt = ctxt;
    btn->menubarbutton.menu = menu;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif

    return newXButton (&btn->button,
                       progname,
                       dpy,
                       parent,
                       db,
                       ctxt,
                       name,
                       x, y,
                       width, height);
}		/* -----  end of function newMenuBarButton  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  buttonRelease
 *  Description:  
 * ===================================================================
 */
static  void
buttonRelease (Block *b, XEvent *ev)
{
    Button   *btn = &b->button;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif

    if (btn && btn->buttonRelease)
        btn->buttonRelease (btn->cbdata, ev);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif        
}		/* -----  end of function buttonRelease  ----- */
/* 
 * ===  FUNCTION  ====================================================
 *         Name:  menuBarButtonPress
 *  Description:  
 * ===================================================================
 */
static  void
menuBarButtonPress (Block *b, XEvent *ev)
{
    MenuBarButton  *mbb = &b->menubarbutton;
    int x, y;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif

    x = ev->xbutton.x_root - ev->xbutton.x;
    y = ev->xbutton.y_root - ev->xbutton.y + 20;
    XMoveWindow (ev->xbutton.display, mbb->menu, x, y);
    XMapWindow (ev->xbutton.display, mbb->menu);
    XUngrabPointer (ev->xbutton.display, ev->xbutton.time);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif        
}		/* -----  end of function menuBarButtonPress  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  menuBarButtonRelease
 *  Description:  
 * ===================================================================
 */
static  void
menuBarButtonRelease (Block *b, XEvent *ev)
{
    MenuBarButton  *mbb = &b->menubarbutton;

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Calling...");
#endif        
    XUnmapWindow (ev->xbutton.display, mbb->menu);

#ifdef _DEBUG_
        DEBUG_INFO_MSG("Exiting...");
#endif
}		/* -----  end of function menuBarButtonRelease  ----- */
static struct Funcs _ButtonFuncs = {
    buttonConfigureNotify,
    buttonLeave,
    buttonEnter,
    buttonExpose,
    NULL,
    buttonRelease
};
struct Funcs *ButtonFuncs = &_ButtonFuncs;

static struct Funcs _MenuBarButtonFuncs = {
    buttonConfigureNotify,
    buttonLeave,
    buttonEnter,
    buttonExpose,
    menuBarButtonPress,
    menuBarButtonRelease
};
struct Funcs *MenuBarButtonFuncs = &_MenuBarButtonFuncs;

/* ----------------------> End of button.c <-------------------------*/  
