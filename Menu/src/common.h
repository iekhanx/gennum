/*
 * ==========================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  Common.h header file 
 *
 *        Version:  1.0
 *        Created:  04/11/20 22:13:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Imran Khan (C), imrank340@gmail.com
 *   Organization:  Onami Systems Ltd
 *
 * ==========================================================================
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#include <X11/Xlib.h>     /* xlib  */
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/Xatom.h>
#include <X11/xpm.h>
#include <X11/Xos.h>

#include <stdio.h>       /* C runtime libs */
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>
#include <sys/stat.h>

#define DefGC(dpy) DefaultGC(dpy, DefaultScreen(dpy)) 
#define NUM_FONTS   30
#define MAX_IMAGES 100

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
#pragma GCC diagnostic ignored "-Wstringop-overflow="
#pragma GCC diagnostic ignored "-Wpointer-sign"

typedef struct {
    Font f;
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

/* Systems information and OS info */
void display_sysinfo (Display *dpy, Window win, int scn_num, GC gc,
        unsigned int win_width, unsigned int win_height);

/* Load given font name  */
Bool loadFont (char *fontname, FontCache fnt[], Display *dpy, GC gc, int cf);

/*  Load xpm images  */
int LoadImage (char *fname, Display *dpy, Window win, int scrn);

/* Find XPM files  */
char *FindXPMFile (char *fname);

XrmDatabase setupDB (Display *dpy, XrmOptionDescRec *xrmTable, 
                     int nCommandLineResources, const char *progname,
                     int *argc, char **argv);

char *getResource (Display *dpy, XrmDatabase db, char *name, 
                   char *cl, char *def);

unsigned long getColor (Display *dpy, XrmDatabase db, char *name,
                        char *cl, char *def);

XFontStruct *getFont (Display *dpy, XrmDatabase db, char *name,
                      char *cl, char *def);

int XChar2bLen (XChar2b *str);

int utf8toXChar2b (XChar2b *ourput_r, int outsize, 
                   const char *input, int inlen);

typedef union Block Block;

void resizeBlock (Block *block, Window win, int width, 
                  int height, XEvent *ev);

char *get_var (char *p);

#endif
/* ------------------------> end of common.h <------------------------*/
