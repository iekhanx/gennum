/*
 * ==========================================================================
 *
 *       Filename:  button.h
 *
 *    Description:  Button.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:33:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _BUTTON_H_
#define _BUTTON_H_

typedef void (*Callback) (void *cbdata, XEvent *ev);

typedef struct Button Button;
struct Button {
        struct Funcs  *funcs;
        XChar2b       *text;
        int           text_width;
        int           font_ascent;
        XFontStruct   *font;
        int           width, height, center;
        unsigned long border, foreground;
        char          *background;
        Pixmap         bgpix;
        void           *cbdata;
        Callback       buttonRelease;
};

typedef struct MenuBarButton MenuBarButton;
struct MenuBarButton {
    struct Funcs         *funcs;
    XChar2b              *text;
    int                  text_width, font_ascent, width, height, center;
    XFontStruct          *font;
    unsigned long        border, foreground;
    char                 *background;
    Pixmap               bgpix;
    Window               menu;
    XContext             ctxt;
};

extern struct Funcs *MenuBarButtonFuncs;
extern struct Funcs *ButtonFuncs;

Window newButton (char *progname, Display *dpy, Window w, XrmDatabase db,
                  XContext ctxt, char *name, int x, int y, int width, 
                  int height, int center, Callback callback, void *cbdata);

Window newMenuBarButton (char *progname, Display *dpy, Window parent,
                          XrmDatabase db, XContext ctxt, char *name,
                          int x, int y, int width, int height, Window menu);
#endif
/* -----------------------------> end of button.h >------------------------ */
