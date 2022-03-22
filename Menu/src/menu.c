/*
 * ========================================================================
 *
 *       Filename:  menu.c
 *
 *    Description:  Menu.c 
 *
 *        Version:  1.0
 *        Created:  06/11/20 21:48:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * =========================================================================
 */
#include "funcs.h"
#include "menu.h"
#include <X11/extensions/shape.h>
#include "gradient.h"
#include "myMacro.h"


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  resizeBlock (Block *block, Window win, int width, 
 *                             int height, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
    void
resizeBlock (Block *block, Window win, int width, int height, XEvent *ev) 
{
    XEvent  tmp;

    XResizeWindow (ev->xany.display, win, width, height);
    
    if (!(block && block->funcs && block->funcs->configureNotify))
        return;

    tmp.xconfigure.type = ev->xany.type;
    tmp.xconfigure.display = ev->xany.display;
    tmp.xconfigure.window  = win;
    tmp.xconfigure.event   = win;
    tmp.xconfigure.width   = width;
    tmp.xconfigure.height  = height;
    tmp.xconfigure.border_width = 0;
    tmp.xconfigure.above = None;
    tmp.xconfigure.override_redirect = False;
    block->funcs->configureNotify (block, &tmp);
} /* -----  end of function resizeBlock   ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  menuConfigureNotify (Block *block, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
static void
menuConfigureNotify (Block *block, XEvent *ev) 
{
    Menu    *self = &block->menu;
    XConfigureEvent *xce = &ev->xconfigure;
    int     i, fullheight = 0;
    Window  w = xce->window;

    if (xce->width == self->width)  return;

    for (i=0; i<self->nsubws; i++) {
        Button *button;
        if (XFindContext (xce->display, self->subws[i], self->ctxt,
                     (XPointer*)&button))
            continue;
        fullheight += button->height;
        if (button->funcs != ButtonFuncs) {
            fprintf (stderr, "This is bad about thins\n");
        }else { resizeBlock ((Block*)button, self->subws[i], 
                 xce->width, button->height, ev); }
    }
    if (fullheight == 0) {
        fprintf (stderr, "Fullheight = 0\n"); return;
    }
    if (xce->height != fullheight) {
        XResizeWindow (xce->display, w, xce->width, fullheight);
    }
} /* -----  end of function menuConfigureNotify   ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newXMenu (Menu *menu, char *progname, 
 *                                 Display *dpy, XrmDatabase db, 
 *                                 XContext ctxt, char *name)
 *  Description:  
 * ===================================================================
 */
Window 
newXMenu (Menu *menu, char *progname, Display *dpy, XrmDatabase db, 
          XContext ctxt, char *name) 
{
    Window    win, parent = DefaultRootWindow (dpy);
    XSetWindowAttributes attr;

    UNUSED (progname);
    UNUSED (db);
    UNUSED (name);

    attr.save_under = True;
    attr.override_redirect = True;
    attr.background_pixel = BlackPixel (dpy, DefaultScreen(dpy));

    menu->ctxt = ctxt;

    win = XCreateWindow (dpy,
                         parent,
                         0, 0,
                         100, 100,
                         0,
                         CopyFromParent,
                         CopyFromParent,
                         CopyFromParent,
                         CWBackPixel | CWOverrideRedirect | CWSaveUnder,
                         &attr);
    XSelectInput (dpy, win, StructureNotifyMask);

    XSaveContext (dpy, win, ctxt, (XPointer)menu);

    return win;
} /* -----  end of function Window newXMenu   ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newXMenu (har *progname, Display *dpy, 
 *                                 XrmDatabase db, XContext ctxt, char *name)
 *  Description:  
 * ===================================================================
 */
Window 
newMenu (char *progname, Display *dpy, XrmDatabase db,
         XContext ctxt, char *name)
{
    Menu  *menu;

    menu = calloc (sizeof (*menu), 1);
    if (!menu) {
        fprintf (stderr, "Unable to allocate space %s\n", name); exit (32);
    }
    menu->funcs = MenuFuncs;

    return newXMenu (menu, progname, dpy, db, ctxt, name);
} /* -----  end of function Window newXMenu   ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  piemenuSetSubWins (Menu *piemenu, Window *subws, int nsubws)
 *  Description:  
 * ===================================================================
 */
    void
piemenuSetSubWins (Menu *piemenu, Window *subws, int nsubws) 
{
    UNUSED (subws);

    if (nsubws > 6) {
        fprintf (stderr, "Somebofy trying to create big Pie menu\n"); return;
    }
    piemenu->width = 0;
} /* -----  end of function piemenuSetSubWins   ----- */


/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window *menuSetSubWins (Display *dpy, XContext ctxt, 
 *                                       Window win, Window *subws, int nsubws)
 *  Description:  
 * ===================================================================
 */
Window 
*menuSetSubWins (Display *dpy, XContext ctxt, Window win, 
                   Window *subws,  int nsubws)
{
    Block   *bmenu = NULL;
    Menu    *menu;
    Window  *old;
    int     i, fullheight = 0, maxwidth = 100;

    XFindContext (dpy, win, ctxt, (XPointer*)&bmenu);
    menu = &bmenu->menu;
    old  = menu->subws;
    menu->subws = subws;
    menu->nsubws = nsubws;

    if (bmenu->menu.funcs == PieMenuFuncs) {
        piemenuSetSubWins (&bmenu->menu, subws, nsubws); return old;
    }

    for (i=0; i < nsubws; i++) {
        Button *button = NULL;
        if (XFindContext (dpy, menu->subws[i], ctxt, (XPointer*)&button))
            continue;

        XMoveWindow (dpy, menu->subws[i], 0, fullheight);
        fullheight += button->height;
        if (maxwidth < button->width)
            maxwidth = button->width;
    }
    for (i=0; i < nsubws; i++) {
        Button *button = NULL;
        if (XFindContext (dpy, menu->subws[i], ctxt, (XPointer*)&button))
            continue;
        button->width = maxwidth;
    }
    XResizeWindow (dpy, win, maxwidth, fullheight);

    return old;
} /* -----  end of function Window *menuSetSubWins  ----- */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  Window newPieMenu (char *progname, Display *dpy,
 *                                   XrmDatabase db, XContext ctxt, char *name)
 *  Description:  
 * ===================================================================
 */
Window 
newPieMenu (char *progname, Display *dpy, XrmDatabase db, 
            XContext ctxt, char *name)
{
    Menu  *menu;
    menu = calloc (sizeof (*menu), 1);
    if (!menu) {
        fprintf (stderr, "Unable to allocate space %s\n", name); exit (32);
    }
    menu->funcs = PieMenuFuncs;

    return newXMenu (menu, progname, dpy, db, ctxt, name);
} /* -----  end of function Window newPieMenu   ----- */

enum { MaxPIES = 6 };
static float xs[MaxPIES] = {0, .86, .86, 0, -.86, -.86};
static float ys[MaxPIES] = {-1, -.5, .5, 1, .5, -.5};

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  pieMenuMap (Window menuWin, XEvent *ev, XContext ctxt)
 *  Description:  
 * ===================================================================
 */
void
pieMenuMap (Window menuwin, XEvent *ev, XContext ctxt)
{
    int     i, menuwidth, menuheight, maxwidth = 0;
    Menu    *menu = NULL;
    Button  **buttons;
    Pixmap  pmap;
    GC      gc;

    printf ("retrieving %p %p %x %p\n", (void*) ev->xany.display,
                                        (void*)menuwin,
                                        ctxt,
                                        (void*)menu);
    XFindContext (ev->xany.display, menuwin, ctxt, (XPointer*)&menu);
    if (!menu)  return;
    if (menu->width) {
        menuwidth = 2.72 * menu->width;
        menuheight = 3 * menu->width;
        XMoveWindow (ev->xany.display, menuwin, 
                     ev->xbutton.x_root - menuwidth / 2,
                     ev->xbutton.y_root - menuheight / 2);
        XMapWindow (ev->xany.display, menuwin);
        return;
    }

    buttons = malloc (sizeof (*buttons)*menu->nsubws);
    for (i=0; i<menu->nsubws; i++) {
        Button *button = NULL;
        if (XFindContext (ev->xany.display, menu->subws[i], 
                          menu->ctxt, (XPointer*)&button))
            continue;
        buttons[i] = button;
        if (maxwidth < button->text_width + 2 * button->font_ascent)
            maxwidth = button->text_width + 2 * button->font_ascent;
    }
    /* width of complete pie is 2.72 time the width/height of piece */
    menuwidth = 2.72 * maxwidth;
    menuheight = 3 * maxwidth;
    XMoveResizeWindow (ev->xany.display, menuwin, 
                       ev->xbutton.x_root - menuwidth / 2,
                       ev->xbutton.y_root = menuheight / 2,
                       menuwidth + 1, menuheight);
    
    for (i=0; i<MaxPIES && i < menu->nsubws; i++) {
        XMoveResizeWindow (ev->xany.display, menu->subws[i],
                            (1.36 + xs[i]) * maxwidth - maxwidth / 2,
                            (1.5  + ys[i]) * maxwidth - maxwidth / 2,
                            maxwidth, maxwidth);
    }
    /* Shape it nicely n  display it */
    pmap = XCreatePixmap (ev->xany.display, menuwin, menuwidth, menuheight, 1);
    if (!pmap) fprintf (stderr, "Can't create pixmap\n");
    gc = XCreateGC (ev->xany.display, pmap, 0, NULL);
    XSetForeground (ev->xany.display, gc, 0);
    XFillRectangle (ev->xany.display, pmap, gc, 0, 0, menuwidth, menuheight);
    XSetForeground (ev->xany.display, gc, 1);

    for (i=0; i<MaxPIES && i < menu->nsubws; i++) {
        XFillArc (ev->xany.display, pmap, gc,
                           (1.35 + xs[i]) * maxwidth - maxwidth / 2,
                           (1.5  + ys[i]) * maxwidth - maxwidth / 2,
                           maxwidth, maxwidth, 0, 360*64);
    }
    XShapeCombineMask (ev->xany.display, menuwin, ShapeBounding, 
                       0, 0, pmap, ShapeSet);
    XFreePixmap (ev->xany.display, pmap);

    pmap = XCreatePixmap (ev->xany.display, menuwin, maxwidth, maxwidth, 1);
    XSetForeground (ev->xany.display, gc, 0);
    XFillRectangle (ev->xany.display, pmap, gc, 0, 0, maxwidth, maxwidth);
    XSetForeground (ev->xany.display, gc, 1);
    XFillArc (ev->xany.display, pmap, gc, 0, 0, maxwidth, maxwidth, 0, 360*64);

    for (i=0; i<MaxPIES && i < menu->nsubws; i++) {
        XShapeCombineMask (ev->xany.display, menu->subws[i],
                ShapeBounding, 0, 0, pmap, ShapeSet);
        buttons[i]->height = buttons[i]->width = maxwidth;
        buttons[i]->bgpix = getGradPixmap (ev->xany.display, 1, maxwidth,
                                           buttons[i]->background);
        XSetWindowBackgroundPixmap (ev->xany.display, menu->subws[i],
                                    buttons[i]->bgpix);
    }
    XFreePixmap (ev->xany.display, pmap);
    XFreeGC (ev->xany.display, gc);
    free (buttons);

    menu->width = maxwidth;

    XMapWindow (ev->xany.display, menuwin);
} /* end of function pieMenuMap   */

/* 
 * ===  FUNCTION  ====================================================
 *         Name:  pieMenuExpose (Block *block, XEvent *ev)
 *  Description:  
 * ===================================================================
 */
    void
piemenuExpose (Block *b, XEvent *ev) 
{
    Menu      *menu = &b->menu;
    XGCValues xgcv;
    int      i, maxwidth = menu->width;
    
    xgcv.line_width = 3;
    xgcv.foreground = WhitePixel (ev->xany.display, 
                                  DefaultScreen (ev->xany.display));
    xgcv.subwindow_mode = IncludeInferiors;
    XChangeGC (ev->xany.display, DefGC (ev->xany.display),
               GCSubwindowMode | GCLineWidth | GCForeground, &xgcv);

    for (i=0; i < MaxPIES && i < menu->nsubws; i++) {
        XDrawArc (ev->xany.display, ev->xany.window, DefGC (ev->xany.display),
                  (1.36 + xs[i]) * maxwidth - maxwidth /2,
                  (1.5  + ys[i]) * maxwidth - maxwidth /2,
                  maxwidth, maxwidth, 0, 360*64);
    }
} /*  end of function pieMenuExpose    */

static struct Funcs _MenuFuncs = {
                menuConfigureNotify,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL
};
struct Funcs  *MenuFuncs = &_MenuFuncs;

static struct Funcs _PieMenuFuncs = {
    NULL,
    NULL,
    NULL,
    piemenuExpose,
    NULL,
    NULL
};
struct Funcs *PieMenuFuncs = &_PieMenuFuncs;
/* ----------------------> end of menu.c <--------------------------- */

